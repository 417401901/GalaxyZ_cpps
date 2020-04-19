//
// Created by wangx on 2020/1/19.
//

#ifndef GALAXYZ_CPP_CONFIG_H
#define GALAXYZ_CPP_CONFIG_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <codecvt>

#include "rapidjson/document.h"
#include "Base/File2Json.h"


using namespace std;
using namespace rapidjson;

class Config {
public:
    static Config *getConfig() {

        if (conf == nullptr) {
            conf = new Config();
        }
        return conf;
    };
    Document config_d;
    static Config *conf;
protected:
    Config() {
        File2Json file2Json("../config.json");
        file2Json.getJson(config_d);
    }
};

#endif //GALAXYZ_CPP_CONFIG_H
