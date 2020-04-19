//
// Created by wangx on 2020/3/3 0003.
//


#include "MoveController.h"
#include "../N3/CreatVehicle.h"

MoveController::MoveController()
        : control(new FlightControl()), config(Config::getConfig()), flightdata(FlightData::getFlightData()) {
    pidX = new PID(config->config_d["PID"].GetObject()["X"].GetObject()["KP"].GetFloat(),
                   config->config_d["PID"].GetObject()["X"].GetObject()["KI"].GetFloat(),
                   config->config_d["PID"].GetObject()["X"].GetObject()["KD"].GetFloat(),
                   config->config_d["PID"].GetObject()["X"].GetObject()["ILIMIT"].GetFloat(),
                   config->config_d["PID"].GetObject()["X"].GetObject()["OUTLIMIT"].GetFloat());

    pidY = new PID(config->config_d["PID"].GetObject()["Y"].GetObject()["KP"].GetFloat(),
                   config->config_d["PID"].GetObject()["Y"].GetObject()["KI"].GetFloat(),
                   config->config_d["PID"].GetObject()["Y"].GetObject()["KD"].GetFloat(),
                   config->config_d["PID"].GetObject()["Y"].GetObject()["ILIMIT"].GetFloat(),
                   config->config_d["PID"].GetObject()["Y"].GetObject()["OUTLIMIT"].GetFloat());

    pidZ = new PID(config->config_d["PID"].GetObject()["Z"].GetObject()["KP"].GetFloat(),
                   config->config_d["PID"].GetObject()["Z"].GetObject()["KI"].GetFloat(),
                   config->config_d["PID"].GetObject()["Z"].GetObject()["KD"].GetFloat(),
                   config->config_d["PID"].GetObject()["Z"].GetObject()["ILIMIT"].GetFloat(),
                   config->config_d["PID"].GetObject()["Z"].GetObject()["OUTLIMIT"].GetFloat());

    thread_move = new std::thread(&MoveController::run, this);
    thread_move->detach();
}

bool MoveController::takeOff() {
    control->takeOff();
    return true;
}

bool MoveController::land() {
    control->land();
    return true;
}

bool MoveController::moveToPoint(Point::Point3d point) {
    setPoint = point;
    canMove = true;
    process_count = 0;
    return true;
}

void MoveController::run() {
    while (true) {
        if (canMove) {
            RealPoint = flightdata->getFlightData()->getPositionOV();

            if (abs(setPoint.x - RealPoint.x) <
                config->config_d["MoveSet"].GetObject()["posThreshold"].GetFloat() &&
                abs(setPoint.y - RealPoint.y) <
                config->config_d["MoveSet"].GetObject()["posThreshold"].GetFloat() &&
                abs(setPoint.z - RealPoint.z) <
                config->config_d["MoveSet"].GetObject()["posThreshold"].GetFloat()) {
                isarrived = true;
                process_count = 0;
            }
            process_count++;
            cout << isarrived << endl;
            pidX->setValue(setPoint.x, RealPoint.x);
            pidY->setValue(setPoint.y, RealPoint.y);
            pidZ->setValue(setPoint.z, RealPoint.z);

            control->moveByPositionOffset(pidX->getResult(), pidY->getResult(), pidZ->getResult());

            if (process_count > config->config_d["MoveSet"].GetObject()["timeThreshold"].GetInt64()) {
                isovertime = true;
                process_count = 0;
            } else {
                isovertime = false;
            }

        } else {
            control->moveByPositionOffset(0, 0, 0);
        }
        usleep(10000);
    }
}

bool MoveController::stopMove() {
    canMove = false;
    return true;
}

bool MoveController::isArrived() {
    return isarrived;
}

bool MoveController::isOverTime() {
    return isovertime;
}


