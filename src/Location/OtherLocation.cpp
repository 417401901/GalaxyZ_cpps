//
// Created by wangx on 2020/2/18 0018.
//
#include "OtherLocation.h"

OtherLocation::OtherLocation(Config *config) : DataNum(config->config_d["AllFlightNum"].GetInt() - 1),
                                               adress(config->config_d["Address"].GetString()),
                                               myid(config->config_d["MyID"].GetInt()) {
    TOPIC_FLIGHT = new string[DataNum];
    data = new LocationData[DataNum];

    for (int i = 0; i < DataNum; i++) {
        if (i != myid) {
            TOPIC_FLIGHT->append("Flight/Location/" + to_string(i) + "/");
        }
    }
    sub = new Subscribe("Flight/Location/#", adress, "rx_OtherLocation" + to_string(myid));
    thread_Location = new std::thread(&OtherLocation::run, this);
    thread_Location->detach();
}

Point::Point3d OtherLocation::getData(int num) {
    if (num < DataNum) {
        std::unique_lock <std::mutex> lock(mtx);
        return data[num].point;
    }
}

void OtherLocation::run() {


    for (;;) {
        process();
    }
}

void OtherLocation::process() {

    auto Message = sub->getMessage();
    std::unique_lock <mutex> lock(mtx);
    for (int i = 0; i < DataNum; i++) {
        if (Message->get_topic() == TOPIC_FLIGHT[i]) {
            if (sizeof(LocationData) == Message->get_payload().size()) {
                memcpy(data[i].msg, Message->get_payload().data(), size);
            }
            break;
        }
    }
}

