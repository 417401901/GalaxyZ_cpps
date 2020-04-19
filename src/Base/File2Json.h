//
// Created by wangx on 2020/4/6 0006.
//

#ifndef GALAXYZ_CPP_FILE2JSON_H
#define GALAXYZ_CPP_FILE2JSON_H

#include <string>
#include <fstream>
#include "rapidjson/document.h"

using namespace rapidjson;

using namespace std;

class File2Json {
public:
    File2Json(string filename) {
        ifstream file;

        file.open(filename, ios_base::in);
        file.seekg(0, file.end);
        std::size_t file_size = file.tellg();
        data = new char[file_size + 1]();
        //char config[40] = "";
        file.seekg(0, file.beg);

        file.read(data, file_size + 1);

    }

    void getJson(Document &d) {
        d.Parse(data);
    }

    ~File2Json() {
        delete data;
    }

private:
    char *data;
};


#endif //GALAXYZ_CPP_FILE2JSON_H
