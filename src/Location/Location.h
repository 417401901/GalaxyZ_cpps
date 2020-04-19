//
// Created by wangx on 2020/2/20 0020.
//

#ifndef GALAXYZ_CPP_LOCATION_H
#define GALAXYZ_CPP_LOCATION_H

#include <thread>
#include "../Base/Point.h"

class Location {
public:
    typedef union {
        Point::Point3d point;
        char msg[12];
    } LocationData;

    virtual void pushData(Point::Point3d &p) = 0;

    virtual Point::Point3d getData() = 0;

    inline int Size() { return size; }

protected:
    std::thread *thread_Location{};
    LocationData *data{};
    const int size = sizeof(LocationData);
};


#endif //GALAXYZ_CPP_LOCATION_H
