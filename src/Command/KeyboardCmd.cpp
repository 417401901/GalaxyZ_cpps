//
// Created by wangx on 2020/4/9 0009.
//

#include "KeyboardCmd.h"
#include <iostream>

using namespace std;

void KeyboardCmd::run() {
    for (;;) {
        key = getchar();
        switch (key) {
            case 't': {
                cmd->setCmd(Commands::TakeOff);
            }
                break;
            case 'l': {
                cmd->setCmd(Commands::Land);
            }
                break;
            case 's': {
                cmd->setCmd(Commands::Stop);
            }
                break;
            case 'a': {
                cmd->setCmd(Commands::Start);
            }
                break;
        }
    }
}

KeyboardCmd::KeyboardCmd() {
    task_t = new std::thread(&KeyboardCmd::run, this);
    cmd = Commands::getCommand();

    task_t->detach();
}
