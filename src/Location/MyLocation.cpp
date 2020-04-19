//
// Created by wangx on 2020/2/19 0019.
//

#include "MyLocation.h"

MyLocation::MyLocation(Config *config) : myid(config->config_d["MyID"].GetInt()),
                                         adress(config->config_d["Address"].GetString()) {
    data = new LocationData;
    pub = new Publish("Flight/Location/" + to_string(myid) + "/", adress, "rx_OtherLocation" + to_string(myid));
    thread_Location = new std::thread(&MyLocation::run, this);
    thread_Location->detach();
}

void MyLocation::run() {
    for (;;) {
        process();
    }
    //  cout << "线程退出" << endl;
}

void MyLocation::pushData(Point::Point3d &p) {
    while (!IsGetFlish)
        std::this_thread::yield();

    std::unique_lock <std::mutex> lock(mtx);
    data->point = p;
    IsGetFlish = false;
    cv.notify_one();
}

MyLocation::~MyLocation() {

}

void MyLocation::process() {
    std::unique_lock <std::mutex> lock(mtx);
    cv.wait(lock, [this] { return !IsGetFlish; });

    pub->SendMessage(data->msg, size);

    IsGetFlish = true;
}
