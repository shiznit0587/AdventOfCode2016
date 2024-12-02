//
//  FileUtilTest.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/3/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "FileUtilTest.h"

FileUtilTest::FileUtilTest() {

    vector<string> lines3;

    FileUtil::parse(0, [&,this] (const string& line) {
        this->parseLine(line);  // calling class (non-static) method, requires 'this' in capture list
        lines2.push_back(line); // access to class member variable, requires '&' in capture list
        lines3.push_back(line); // acess to local variable, requires '&' in capture list
    });

    for (const string& line : lines1) {
        cout << line << endl;
    }

    for (const string& line : lines2) {
        cout << line << endl;
    }

    for (const string& line : lines3) {
        cout << line << endl;
    }
}

void FileUtilTest::parseLine(const string& line) {
    lines1.push_back(line);
}
