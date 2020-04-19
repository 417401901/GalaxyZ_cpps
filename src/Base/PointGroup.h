//
// Created by wangx on 2020/3/4 0004.
//

#ifndef GALAXYZ_CPP_POINTGROUP_H
#define GALAXYZ_CPP_POINTGROUP_H

#include <vector>
#include <iostream>
#include "Point.h"

using namespace std;

class PointGroup {

public:
    typedef struct {
        int index;
        Point::Point3d point;
    } TaskPoint;

    PointGroup();

    ~PointGroup();

    void clear();

    Point::Point3d getPoint();

    void pushPoint(TaskPoint PutPoint);

    bool sortPoint();

    bool isLast() {
        return taskpoint.end() == iterator;
    };
private:
    vector <TaskPoint> taskpoint;
    vector<TaskPoint>::const_iterator iterator;
    int g_index = 0;


};


#endif //GALAXYZ_CPP_POINTGROUP_H
