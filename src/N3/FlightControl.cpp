//
// Created by wangx on 2020/2/26 0026.
//

#include "FlightControl.h"
#include "CreatVehicle.h"

FlightControl::FlightControl() : vehicle(CreatVehicle::getVehicle()), flightdata(FlightData::getFlightData()) {
    ACK::ErrorCode Status = vehicle->obtainCtrlAuthority(responseTimeout);
    if (ACK::getError(Status) != ACK::SUCCESS) {
        ACK::getErrorCodeMessage(Status, __func__);
    }
}

FlightControl::~FlightControl() = default;

bool FlightControl::takeOff() {
    ACK::ErrorCode takeoffStatus = vehicle->control->takeoff(responseTimeout);
    if (ACK::getError(takeoffStatus) != ACK::SUCCESS) {
        ACK::getErrorCodeMessage(takeoffStatus, __func__);
        return false;
    }
    // First check: Motors started
    int motorsNotStarted = 0;
    int timeoutCycles = 20;

    while (flightdata->getFlihtStatus() !=
           VehicleStatus::FlightStatus::ON_GROUND &&
           flightdata->getDisplayMode() !=
           VehicleStatus::DisplayMode::MODE_ENGINE_START &&
           motorsNotStarted < timeoutCycles) {
        motorsNotStarted++;
        usleep(100000);
    }

    if (motorsNotStarted == timeoutCycles) {
        std::cout << "Takeoff failed. Motors are not spinning." << std::endl;
        // Cleanup
        return false;
    } else {
        std::cout << "Motors spinning...\n";
    }

    int stillOnGround = 0;
    timeoutCycles = 110;

    while (flightdata->getFlihtStatus() !=
           VehicleStatus::FlightStatus::IN_AIR &&
           (flightdata->getDisplayMode() !=
            VehicleStatus::DisplayMode::MODE_ASSISTED_TAKEOFF ||
            flightdata->getDisplayMode() !=
            VehicleStatus::DisplayMode::MODE_AUTO_TAKEOFF) &&
           stillOnGround < timeoutCycles) {
        stillOnGround++;
        usleep(100000);
    }

    if (stillOnGround == timeoutCycles) {
        std::cout << "Takeoff failed. Aircraft is still on the ground, but the "
                     "motors are spinning."
                  << std::endl;
        // Cleanup

        return false;
    } else {
        std::cout << "Ascending...\n";
    }

    while (flightdata->getDisplayMode() ==
           VehicleStatus::DisplayMode::MODE_ASSISTED_TAKEOFF ||
           flightdata->getDisplayMode() ==
           VehicleStatus::DisplayMode::MODE_AUTO_TAKEOFF) {
        sleep(1);
    }


    if (flightdata->getDisplayMode() !=
        VehicleStatus::DisplayMode::MODE_P_GPS ||
        flightdata->getDisplayMode() !=
        VehicleStatus::DisplayMode::MODE_ATTITUDE) {
        std::cout << "Successful takeoff!\n";
    } else {
        std::cout
                << "Takeoff finished, but the aircraft is in an unexpected mode. "
                   "Please connect DJI GO.\n";
        return false;
    }
    return true;
}

bool FlightControl::land() {
    // Start landing
    ACK::ErrorCode landingStatus = vehicle->control->land(responseTimeout);
    if (ACK::getError(landingStatus) != ACK::SUCCESS) {
        ACK::getErrorCodeMessage(landingStatus, __func__);
        return false;
    }

    // First check: Landing started
    int landingNotStarted = 0;
    int timeoutCycles = 20;


    while (flightdata->getDisplayMode() !=
           VehicleStatus::DisplayMode::MODE_AUTO_LANDING &&
           landingNotStarted < timeoutCycles) {
        landingNotStarted++;
        usleep(100000);
    }

    if (landingNotStarted == timeoutCycles) {
        return false;
    } else {
        std::cout << "Landing...\n";
    }

    // Second check: Finished landing

    while (flightdata->getDisplayMode() ==
           VehicleStatus::DisplayMode::MODE_AUTO_LANDING &&
           flightdata->getFlihtStatus() ==
           VehicleStatus::FlightStatus::IN_AIR) {
        sleep(1);
    }

    if (flightdata->getDisplayMode() !=
        VehicleStatus::DisplayMode::MODE_P_GPS ||
        flightdata->getDisplayMode() !=
        VehicleStatus::DisplayMode::MODE_ATTITUDE) {
        std::cout << "Successful landing!\n";
    } else {
        return false;
    }

    return true;
}

bool FlightControl::moveByPositionOffset(float x, float y, float z) {
    vehicle->control->positionAndYawCtrl(x, y, z, 0);
    return true;
}
