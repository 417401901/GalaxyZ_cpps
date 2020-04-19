//
// Created by wangx on 2019/12/31.
//

#ifndef GALAXYZ_MYLOCATION_H
#define GALAXYZ_MYLOCATION_H

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include "Location.h"
#include "../MQTT/MQTT_Publish.h"
#include "../Config.h"
//负责将本机数据发送到其他终端

class MyLocation : Location {

public:

    MyLocation(Config *config);

    ~MyLocation();

    void pushData(Point::Point3d &p);

    void run();

    void process();

private:
    bool IsGetFlish = true;
    std::mutex mtx;
    std::condition_variable cv;
    Publish *pub;
    int myid;
    string adress;
};

#endif //GALAXYZ_MYLOCATION_H
