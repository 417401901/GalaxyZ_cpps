//
// Created by wangx on 2020/2/20 0020.
//

#ifndef GALAXYZ_CPP_FLIGHTDATA_H
#define GALAXYZ_CPP_FLIGHTDATA_H

#include <dji_vehicle.hpp>
#include "../Base/Point.h"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

class FlightData {
public:

    static FlightData *getFlightData() {
        if (flightData == nullptr) {
            flightData = new FlightData();
        }
        return flightData;
    }

    TypeMap<TOPIC_VELOCITY>::type getVelocity() const;

    Point::Point3d getPositionOV() const;

    TypeMap<TOPIC_GPS_FUSED>::type getGpsFused() const;

    unsigned char getFlihtStatus() const;

    unsigned char getDisplayMode() const;

    GlobalPosition getGlobalPosition() const;

private:

    static FlightData *flightData;

    FlightData();

    ~FlightData();

    Vehicle *vehicle;

    int responseTimeout = 1;

    bool startGlobalPositionBroadcast();


};


#endif //GALAXYZ_CPP_FLIGHTDATA_H
