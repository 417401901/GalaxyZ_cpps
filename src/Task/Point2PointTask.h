//
// Created by wangx on 2020/3/15 0015.
//

#ifndef GALAXYZ_CPP_POINT2POINTTASK_H
#define GALAXYZ_CPP_POINT2POINTTASK_H


#include "Task.h"
#include "../Controller/MoveController.h"

class Point2PointTask : public Task {
public:
    Point2PointTask(MoveController *ctrl);

    ~Point2PointTask();

    void run() override;

private:
    MoveController *Control;
    PointGroup *pointGroup;
};


#endif //GALAXYZ_CPP_POINT2POINTTASK_H
