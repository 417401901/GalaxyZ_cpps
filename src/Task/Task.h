//
// Created by wangx on 2020/3/23 0023.
//

#ifndef GALAXYZ_CPP_TASK_H
#define GALAXYZ_CPP_TASK_H

#include <thread>
#include <mutex>

class Task {
public:
    Task();

    typedef enum {
        ACTIVE,
        HANG,
        OVER
    } TaskStatus;

    virtual void hang() {
        if (taskStatus == ACTIVE) {
            taskStatus = HANG;
        }
    }

    virtual void active() {
        if (taskStatus == HANG) {
            taskStatus = ACTIVE;
        }
    }

    TaskStatus getStatus() {
        return taskStatus;
    }

    ~Task();

    virtual void run() = 0;

protected:
    bool NeedRun = true;
    int WaitTimes;
    std::mutex mutex_;
    std::thread *task_t;
    TaskStatus taskStatus;


    template<typename T>
    void startThread(T &fun);
};


#endif //GALAXYZ_CPP_TASK_H
