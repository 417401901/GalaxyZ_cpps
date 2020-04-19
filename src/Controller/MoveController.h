//
// Created by wangx on 2020/3/3 0003.
//

#ifndef GALAXYZ_CPP_MOVECONTROLLER_H
#define GALAXYZ_CPP_MOVECONTROLLER_H

#include <thread>
#include "../N3/FlightControl.h"
#include "PID.h"
#include "../Base/PointGroup.h"
#include <mutex>

class MoveController {
public:


    MoveController();

    ~MoveController();

    bool moveToPoint(Point::Point3d point);

    bool stopMove();

    bool takeOff();

    bool land();

    bool isArrived();

    bool isOverTime();

    void run();

private:
    Point::Point3d setPoint;
    Point::Point3d RealPoint;
    FlightControl *control;
    FlightData *flightdata;
    Config *config;
    PID *pidX;
    PID *pidY;
    PID *pidZ;
    bool canMove = false;
    bool isarrived = false;
    bool isovertime = false;
    int process_count = 0;
    std::thread *thread_move;
    std::mutex mtx;
};


#endif //GALAXYZ_CPP_MOVECONTROLLER_H
