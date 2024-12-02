//
//  FileUtil.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 11/30/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include <fstream>
#include "FileUtil.h"

namespace FileUtil {

    void parse(const int day, const function<void(const string&)> &cb) {

        string filename = "inputs/day" + to_string(day) + ".txt";

        ifstream file;
        file.open(filename.c_str());

        string line;
        while (getline(file, line)) {
            cb(line);
        }

        file.close();
    }
}
