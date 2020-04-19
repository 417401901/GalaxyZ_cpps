//
// Created by wangx on 2020/2/21 0021.
//

#include <sys/time.h>
#include "MQTT_Time.h"

int64_t MQTT_Time::getCurrentTime() {
    //直接调用这个函数就行了，返回值最好是int64_t，long long应该也可以
    struct timeval tv{};
    gettimeofday(&tv, NULL);    //该函数在sys/time.h头文件中
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

MQTT_Time::MQTT_Time(Config *c) : config(c) {
    pub = new Publish("Time/" + to_string(config->config_d["MyID"].GetInt()) + "/",
                      string(config->config_d["Address"].GetString()),
                      "Timep" + to_string(config->config_d["MyID"].GetInt()));
    cout << "pub建立成功" << endl;
    sub = new Subscribe("Time/" + to_string(config->config_d["MyID"].GetInt()) + "/",
                        string(config->config_d["Address"].GetString()),
                        "Times" + to_string(config->config_d["MyID"].GetInt()));
    cout << "sub建立成功" << endl;

}

void MQTT_Time::run() {
    int64_t time = this->getCurrentTime();
    const char *c = to_string(time).c_str();

    pub->SendMessage(c, sizeof(c));
    cout << "time1:" << to_string(this->getCurrentTime() - time) << endl;
    auto msg = sub->getMessage();

    cout << "time2:" << to_string(this->getCurrentTime() - time) << endl;
}

MQTT_Time::~MQTT_Time() = default;

