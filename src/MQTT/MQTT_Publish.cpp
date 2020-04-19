//
// Created by wangx on 2020/1/8.
//
#include "MQTT_Publish.h"

Publish::Publish(const string topic, const string adress, const string clientid) {
    mqtt::connect_options connopts;

    this->client = new mqtt::async_client(adress, clientid, nullptr);

    connopts.set_automatic_reconnect(1, 5);

    this->client->connect(connopts)->wait();

    this->top = new mqtt::topic(*this->client, topic, 0);
}

void Publish::SendMessage(const void *msg, int len) {
    this->top->publish(msg, len);
}

Publish::~Publish() {
    delete client;
    delete top;
}
