//
// Created by wangx on 2020/1/17.
//

#ifndef GALAXYZ_CPP_OTHERLOCATION_H
#define GALAXYZ_CPP_OTHERLOCATION_H

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <string>
#include "../Config.h"

using namespace std;

#include "Location.h"
#include "../MQTT/MQTT_Subscribe.h"


class OtherLocation : Location {
public:
    OtherLocation(Config *config);

    ~OtherLocation() {};

    inline int getDateNum() { return DataNum; };

    Point::Point3d getData(int num);


private:
    std::mutex mtx;
    string *TOPIC_FLIGHT;
    string adress;
    int myid;
    int DataNum;
    Subscribe *sub;

    void process();

    void run();
};

#endif //GALAXYZ_CPP_OTHERLOCATION_H
