//
// Created by wangx on 2020/3/3 0003.
//

#ifndef GALAXYZ_CPP_STATUS_H
#define GALAXYZ_CPP_STATUS_H


class Status {
public:
    typedef enum {
        WAIT,
        RECIVE,
        RECIVE_E,
        RUNING,
        RUNING_E,
    } STATUS_TASK;

    Status() {};

    ~Status();

    STATUS_TASK getStatus() const {
        return NowStatus;
    };

    void changeStatus(STATUS_TASK s) {
        NowStatus = s;
    }

private:
    STATUS_TASK NowStatus;
};


#endif //GALAXYZ_CPP_STATUS_H
