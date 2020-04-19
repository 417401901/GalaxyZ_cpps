//
// Created by wangx on 2020/4/8 0008.
//

#ifndef GALAXYZ_CPP_COMMANDS_H
#define GALAXYZ_CPP_COMMANDS_H

#include <mutex>

class Commands {
public:
    typedef enum {
        Wait,
        TakeOff,
        Start,
        Stop,
        Land,
    } FlyCmd;
    typedef enum {
        Point2Point,
        Hold,
        Formation
    } ModCmd;

    FlyCmd getFlyCmd();

    ModCmd getModCmd();

    void setCmd(FlyCmd f, ModCmd m);

    void setCmd(FlyCmd f);

    void setCmd(ModCmd m);

    bool getIsChange() {
        return IsChange;
    }

    static Commands *getCommand() {
        if (cmd == nullptr) {
            cmd = new Commands();
        }
        return cmd;
    }

private:
    static Commands *cmd;

    Commands();

    std::mutex mtx;

    FlyCmd flyCmd;
    ModCmd modCmd;
    bool IsChange = false;
};


#endif //GALAXYZ_CPP_COMMANDS_H
