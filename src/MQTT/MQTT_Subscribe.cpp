//
// Created by wangx on 2020/1/17.
//
#include "MQTT_Subscribe.h"

Subscribe::Subscribe(string topic, string adress, string clientid) {
    client = new mqtt::async_client(adress, clientid, nullptr);

    mqtt::connect_options opt;

    opt.set_automatic_reconnect(1, 10);

    client->connect(opt)->wait();
    client->start_consuming();
    client->subscribe(topic, 0)->wait();
}

shared_ptr<const mqtt::message> Subscribe::getMessage() {
    return client->consume_message();
}
