//
// Created by wangx on 2020/3/23 0023.
//


#include "Task.h"

Task::Task() {
}


Task::~Task() {

}

template<typename T>
void Task::startThread(T &fun) {
    task_t = new std::thread(&fun, this);
    task_t->detach();
}
