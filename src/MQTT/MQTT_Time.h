//
// Created by wangx on 2020/2/21 0021.
//

#ifndef GALAXYZ_CPP_MQTT_TIME_H
#define GALAXYZ_CPP_MQTT_TIME_H

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <thread>
#include <cstdlib>
#include "../Config.h"
#include "MQTT_Publish.h"
#include "MQTT_Subscribe.h"

class MQTT_Time {


public:
    explicit MQTT_Time(Config *c);

    ~MQTT_Time();

    void run();

private:

    int64_t getCurrentTime();

    Config *config;
    Publish *pub;
    Subscribe *sub;
};


#endif //GALAXYZ_CPP_MQTT_TIME_H
