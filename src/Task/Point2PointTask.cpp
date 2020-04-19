//
// Created by wangx on 2020/3/15 0015.
//

#include "Point2PointTask.h"
#include "../Strategy/LoadPointFile.h"


Point2PointTask::~Point2PointTask() {
    delete pointGroup;
}


void Point2PointTask::run() {
    while (!pointGroup->isLast()) {
        Control->moveToPoint(pointGroup->getPoint());
        usleep(20000);
        while ((!Control->isArrived() && !Control->isOverTime()) || taskStatus == HANG) {
            std::this_thread::yield();
        }

    }
    taskStatus = OVER;

}

Point2PointTask::Point2PointTask(MoveController *ctrl) : Control(ctrl), Task() {
    LoadPointFile loadpf("../xinxing.json");
    pointGroup = loadpf.getPointGroup();
    task_t = new std::thread(&Point2PointTask::run, this);

    task_t->detach();
}

