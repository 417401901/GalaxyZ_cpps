//
// Created by wangx on 2020/3/15 0015.
//

#include "LoadPointFile.h"
#include "../Base/File2Json.h"

LoadPointFile::LoadPointFile(string filename) {
    File2Json flie2Json(filename);
    flie2Json.getJson(d);
    gPoint = new PointGroup();
}

PointGroup *LoadPointFile::getPointGroup() {
    for (auto &p:d.GetArray()) {
        PointGroup::TaskPoint Tpoint;

        Tpoint.index = p["index"].GetInt();
        Tpoint.point.x = (float) (p["x"].GetDouble());
        Tpoint.point.y = (float) (p["y"].GetDouble());
        Tpoint.point.z = (float) (p["z"].GetDouble());
        gPoint->pushPoint(Tpoint);
    }
    return gPoint;
}

LoadPointFile::~LoadPointFile()
= default;

