//
// Created by wangx on 2020/4/9 0009.
//

#ifndef GALAXYZ_CPP_KEYBOARDCMD_H
#define GALAXYZ_CPP_KEYBOARDCMD_H


#include "../Task/Task.h"
#include "Commands.h"
#include <thread>

class KeyboardCmd {
public:
    KeyboardCmd();

    void run();

private:
    char key;
    Commands *cmd;
    std::thread *task_t;
};


#endif //GALAXYZ_CPP_KEYBOARDCMD_H
