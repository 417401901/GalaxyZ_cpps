//
// Created by wangx on 2020/3/3 0003.
//

#include "TaskScheduler.h"
#include "../Strategy/LoadPointFile.h"

TaskScheduler::TaskScheduler() : cmd(Commands::getCommand()), Task() {
    move = new MoveController();

    task_t = new std::thread(&TaskScheduler::run, this);

    task_t->detach();
}

void TaskScheduler::run() {
    for (;;) {
        while (!cmd->getIsChange()) {
            if (nowTask != nullptr) {
                if (nowTask->getStatus() == Task::OVER) {
                }
            }
            std::this_thread::yield();
        }
        cout << "离开等待" << endl;
        cout << cmd->getFlyCmd() << endl;
        switch (cmd->getFlyCmd()) {
            case Commands::TakeOff: {
                cout << "起飞" << endl;
                move->takeOff();
                cmd->setCmd(Commands::Wait);
            }
                break;
            case Commands::Land: {
                move->land();
                cmd->setCmd(Commands::Wait);
            }
                break;
            case Commands::Stop: {
                if (nowTask != nullptr)
                    delete nowTask;
                move->stopMove();
            }
                break;
            case Commands::Start: {
                if (nowTask == nullptr) {
                    switch (cmd->getModCmd()) {
                        case Commands::Point2Point: {
                            if (nowTask != nullptr)
                                delete nowTask;
                            nowTask = new Point2PointTask(move);
                        }
                            break;
                        case Commands::Formation: {

                        }
                            break;
                        case Commands::Hold: {

                        }
                            break;
                    }
                }
            }
                break;
        }
    }
}
