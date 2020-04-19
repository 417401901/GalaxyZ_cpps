//
// Created by wangx on 2020/2/20 0020.
//

#include <iostream>
#include "FlightData.h"
#include "CreatVehicle.h"
#include "../Base/Point.h"

FlightData *FlightData::flightData = nullptr;

FlightData::FlightData() : vehicle(CreatVehicle::getVehicle()) {

    ACK::ErrorCode ack = vehicle->subscribe->verify(responseTimeout);
    if (ACK::getError(ack) != ACK::SUCCESS) {
        ACK::getErrorCodeMessage(ack, __func__);
        delete (vehicle);
    }

    //Package
    int pkgIndex = 0;
    int freq = 50;
    TopicName topicList100Hz[] = {TOPIC_GPS_FUSED, TOPIC_POSITION_VO, TOPIC_VELOCITY};
    int numTopic = sizeof(topicList100Hz) / sizeof(topicList100Hz[0]);
    bool enableTimestamp = false;
    std::cout << "入" << std::endl;

    bool pkgStatus = vehicle->subscribe->initPackageFromTopicList(pkgIndex, numTopic,
                                                                  topicList100Hz, enableTimestamp, freq);

    if (!(pkgStatus)) {
        delete (vehicle);
    }
    std::cout << "出" << std::endl;
    ack = vehicle->subscribe->startPackage(pkgIndex, responseTimeout);
    if (ACK::getError(ack) != ACK::SUCCESS) {
        ACK::getErrorCodeMessage(ack, __func__);
        vehicle->subscribe->removePackage(pkgIndex, responseTimeout);
    }

    pkgIndex = 1;
    freq = 10;
    TopicName topicList10Hz[] = {TOPIC_STATUS_FLIGHT,
                                 TOPIC_STATUS_DISPLAYMODE};
    numTopic = sizeof(topicList10Hz) / sizeof(topicList10Hz[0]);
    enableTimestamp = false;

    pkgStatus = vehicle->subscribe->initPackageFromTopicList(
            pkgIndex, numTopic, topicList10Hz, enableTimestamp, freq);
    if (!(pkgStatus)) {
        delete (vehicle);
    }

    ack = vehicle->subscribe->startPackage(pkgIndex, responseTimeout);

    if (ACK::getError(ack) != ACK::SUCCESS) {
        ACK::getErrorCodeMessage(ack, __func__);
        // Cleanup before return
        vehicle->subscribe->removePackage(pkgIndex, responseTimeout);
    }

    //startGlobalPositionBroadcast();

}

FlightData::~FlightData() {
    int pkgIndex = 0;
    vehicle->subscribe->removePackage(pkgIndex, responseTimeout);
}

Telemetry::GlobalPosition FlightData::getGlobalPosition() const {
    return vehicle->broadcast->getGlobalPosition();
}

TypeMap<TOPIC_VELOCITY>::type FlightData::getVelocity() const {
    return vehicle->subscribe->getValue<TOPIC_VELOCITY>();
}

Point::Point3d FlightData::getPositionOV() const {
    Point::Point3d point;
    point.x = vehicle->subscribe->getValue<TOPIC_POSITION_VO>().x;
    point.y = vehicle->subscribe->getValue<TOPIC_POSITION_VO>().y;
    point.z = vehicle->subscribe->getValue<TOPIC_POSITION_VO>().z;
    return point;
}

TypeMap<TOPIC_GPS_FUSED>::type FlightData::getGpsFused() const {
    return vehicle->subscribe->getValue<TOPIC_GPS_FUSED>();
}

TypeMap<TOPIC_STATUS_FLIGHT>::type FlightData::getFlihtStatus() const {
    return vehicle->subscribe->getValue<TOPIC_STATUS_FLIGHT>();
}

TypeMap<TOPIC_STATUS_DISPLAYMODE>::type FlightData::getDisplayMode() const {
    return vehicle->subscribe->getValue<TOPIC_STATUS_DISPLAYMODE>();
}

bool FlightData::startGlobalPositionBroadcast() {
    uint8_t freq[16];

    /* Channels definition for A3/N3/M600
     * 0 - Timestamp
     * 1 - Attitude Quaternions
     * 2 - Acceleration
     * 3 - Velocity (Ground Frame)
     * 4 - Angular Velocity (Body Frame)
     * 5 - Position
     * 6 - GPS Detailed Information
     * 7 - RTK Detailed Information
     * 8 - Magnetometer
     * 9 - RC Channels Data
     * 10 - Gimbal Data
     * 11 - Flight Status
     * 12 - Battery Level
     * 13 - Control Information
     */
    freq[0] = DataBroadcast::FREQ_HOLD;
    freq[1] = DataBroadcast::FREQ_HOLD;
    freq[2] = DataBroadcast::FREQ_HOLD;
    freq[3] = DataBroadcast::FREQ_HOLD;
    freq[4] = DataBroadcast::FREQ_HOLD;
    freq[5] = DataBroadcast::FREQ_100HZ; // This is the only one we want to change
    freq[6] = DataBroadcast::FREQ_HOLD;
    freq[7] = DataBroadcast::FREQ_HOLD;
    freq[8] = DataBroadcast::FREQ_HOLD;
    freq[9] = DataBroadcast::FREQ_HOLD;
    freq[10] = DataBroadcast::FREQ_HOLD;
    freq[11] = DataBroadcast::FREQ_HOLD;
    freq[12] = DataBroadcast::FREQ_HOLD;
    freq[13] = DataBroadcast::FREQ_HOLD;

    ACK::ErrorCode ack = vehicle->broadcast->setBroadcastFreq(freq, 1);
    if (ACK::getError(ack)) {
        ACK::getErrorCodeMessage(ack, __func__);
        return false;
    } else {
        return true;
    }
}
