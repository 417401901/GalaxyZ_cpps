//
// Created by wangx on 2020/3/15 0015.
//

#ifndef GALAXYZ_CPP_LOADPOINTFILE_H
#define GALAXYZ_CPP_LOADPOINTFILE_H


#include <rapidjson/pointer.h>
#include <rapidjson/document.h>
#include "../Base/PointGroup.h"

using namespace rapidjson;

class LoadPointFile {
public:
    LoadPointFile(string fliename);

    ~LoadPointFile();

    PointGroup *getPointGroup();

private:
    PointGroup *gPoint;
    Document d;
};


#endif //GALAXYZ_CPP_LOADPOINTFILE_H
