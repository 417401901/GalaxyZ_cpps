//
// Created by wangx on 2020/3/3 0003.
//

#ifndef GALAXYZ_CPP_TASKSCHEDULER_H
#define GALAXYZ_CPP_TASKSCHEDULER_H


#include "Task.h"
#include "Point2PointTask.h"
#include "../Command/Commands.h"

class TaskScheduler : Task {
public:
    TaskScheduler();

    void run() override;

private:
    Task *nowTask;
    Task *hangTask;
    Commands *cmd;
    MoveController *move;
};


#endif //GALAXYZ_CPP_TASKSCHEDULER_H
