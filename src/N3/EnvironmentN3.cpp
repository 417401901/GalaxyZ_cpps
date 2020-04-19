//
// Created by wangx on 2020/2/18 0018.
//

#include "EnvironmentN3.h"


EnvironmentN3::EnvironmentN3(Vehicle *vehicle) : conf(Config::getConfig()), vehicle(vehicle) {
    bool threadSupport = true;

    openSerial();
    Active();
}

EnvironmentN3::~EnvironmentN3()
= default;


bool EnvironmentN3::openSerial() {
    //串口相关打开信息
    if (!vehicle->protocolLayer->getDriver()->getDeviceStatus()) {
        cout << "open device fail!" << endl;

        return false;
    }
    cout << "初始化完成" << endl;
    return true;
}

bool EnvironmentN3::Active() {
    DJI::OSDK::Vehicle::ActivateData activateData;
    //验证无人机信息
    activateData.version = vehicle->getFwVersion();
    activateData.ID = conf->config_d["AppID"].GetInt();
    char app_key[65];
    activateData.encKey = app_key;
    strcpy(activateData.encKey, conf->config_d["AppKey"].GetString());


    ACK::ErrorCode ack = vehicle->activate(&activateData, 1);
    if (ACK::getError(ack)) {
        cout << ack.data << endl;

        ACK::getErrorCodeMessage(ack, __func__);
        delete (vehicle);
    }
    //从N3订阅所需的信息
}

