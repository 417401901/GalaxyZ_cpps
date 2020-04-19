//
// Created by wangx on 2020/2/18 0018.
//

#ifndef GALAXYZ_CPP_ENVIRONMENTN3_H
#define GALAXYZ_CPP_ENVIRONMENTN3_H

#include "../Config.h"
#include <dji_vehicle.hpp>

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

class EnvironmentN3 {
public:
    EnvironmentN3(Vehicle *vehicle);

    ~EnvironmentN3();


private:
    bool openSerial();

    bool Active();

    Config *conf;

    Vehicle *vehicle;

    int responseTimeout = 1;
};


#endif //GALAXYZ_CPP_ENVIRONMENTN3_H
