//
// Created by wangx on 2020/3/4 0004.
//

#include "PointGroup.h"

PointGroup::PointGroup() {

}

PointGroup::~PointGroup() {

}

void PointGroup::clear() {
    taskpoint.clear();
    iterator = taskpoint.cbegin();
    g_index = 0;
}

void PointGroup::pushPoint(TaskPoint PutPoint) {
    taskpoint.push_back(PutPoint);
    iterator = taskpoint.cbegin();
}

Point::Point3d PointGroup::getPoint() {
    Point::Point3d p;
    if (iterator != taskpoint.end()) {
        p = iterator->point;
    } else {
        p = (iterator - 1)->point;
    }
    iterator++;
    return p;
}

bool PointGroup::sortPoint() {
    for (auto it_i = taskpoint.begin(); it_i != taskpoint.end() - 1; ++it_i) {
        for (auto it_j = taskpoint.begin(); it_j != taskpoint.begin() + (taskpoint.end() - it_i - 1); ++it_j) {
            if (it_j->index > (it_j + 1)->index) {
                std::swap(*it_j, *(it_j + 1));
            }
        }
    }
    return true;
}
