//
// Created by wangx on 2020/1/3.
//

#ifndef GALAXYZ_CPP_MQTT_PUBLISH_H
#define GALAXYZ_CPP_MQTT_PUBLISH_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>    // For sleep
#include <atomic>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"

using namespace std;


class Publish {
public:
    Publish(const string topic, const string adress, const string clientid);

    ~Publish();

    void SendMessage(const void *msg, int len);

private:
    mqtt::async_client *client;
    mqtt::topic *top;


};

#endif //GALAXYZ_CPP_MQTT_PUBLISH_H
