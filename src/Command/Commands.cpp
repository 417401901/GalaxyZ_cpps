//
// Created by wangx on 2020/4/8 0008.
//

#include "Commands.h"

Commands *Commands::cmd = nullptr;

void Commands::setCmd(Commands::FlyCmd f, Commands::ModCmd m) {
    setCmd(f);
    setCmd(m);
}

void Commands::setCmd(Commands::FlyCmd f) {
    std::unique_lock <std::mutex> lock(mtx);
    flyCmd = f;
    IsChange = true;
}

void Commands::setCmd(Commands::ModCmd m) {
    std::unique_lock <std::mutex> lock(mtx);
    modCmd = m;
}

Commands::FlyCmd Commands::getFlyCmd() {
    std::unique_lock <std::mutex> lock(mtx);
    IsChange = false;
    return flyCmd;
}

Commands::ModCmd Commands::getModCmd() {
    std::unique_lock <std::mutex> lock(mtx);
    return modCmd;
}

Commands::Commands() {

}
