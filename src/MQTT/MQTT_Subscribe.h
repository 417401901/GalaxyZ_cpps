//
// Created by wangx on 2020/1/17.
//

#ifndef GALAXYZ_CPP_MQTT_SUBSCRIBE_H
#define GALAXYZ_CPP_MQTT_SUBSCRIBE_H

#include <iostream>
#include <string>
#include "mqtt/async_client.h"
#include "MQTT_Publish.h"

using namespace std;
extern const string LOCAL_ADDRESS;

class Message {

};

class Subscribe {
public:

    Subscribe(string topic, string address, string clientid);

    ~Subscribe() {};

    shared_ptr<const mqtt::message> getMessage();

private:
    mqtt::async_client *client;
    mqtt::topic *top;

};

#endif //GALAXYZ_CPP_MQTT_SUBSCRIBE_H
