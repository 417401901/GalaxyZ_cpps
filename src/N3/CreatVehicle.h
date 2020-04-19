//
// Created by wangx on 2020/3/24 0024.
//

#ifndef GALAXYZ_CPP_CREATVEHICLE_H
#define GALAXYZ_CPP_CREATVEHICLE_H

#include "../Config.h"
#include <dji_vehicle.hpp>
#include "EnvironmentN3.h"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

class CreatVehicle {
public:
    static Vehicle *getVehicle() {
        if (vehicle == nullptr) {

            bool threadSupport = true;
            vehicle = new Vehicle(Config::getConfig()->config_d["Device"].GetString(),
                                  Config::getConfig()->config_d["Baudrate"].GetUint(),
                                  threadSupport,
                                  false);
            EnvironmentN3 environmentN3(vehicle);
        }

        return vehicle;
    }

private:
    static Vehicle *vehicle;
};

#endif //GALAXYZ_CPP_CREATVEHICLE_H
