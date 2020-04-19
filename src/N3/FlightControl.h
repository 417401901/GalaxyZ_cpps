//
// Created by wangx on 2020/2/26 0026.
//

#ifndef GALAXYZ_CPP_FLIGHTCONTROL_H
#define GALAXYZ_CPP_FLIGHTCONTROL_H

#include "EnvironmentN3.h"
#include "FlightData.h"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

class FlightControl {
public:
    FlightControl();

    ~FlightControl();

    bool takeOff();

    bool moveByPositionOffset(float x, float y, float z);

    bool land();

private:
    Vehicle *vehicle;
    FlightData *flightdata;
    int responseTimeout = 1;
};


#endif //GALAXYZ_CPP_FLIGHTCONTROL_H
