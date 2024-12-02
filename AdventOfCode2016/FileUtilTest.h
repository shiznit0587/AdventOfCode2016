//
//  FileUtilTest.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/3/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef FileUtilTest_h
#define FileUtilTest_h

#include "includes.h"

class FileUtilTest
{
public:
    FileUtilTest();

private:
    void parseLine(const string& line);

    vector<string> lines1;
    vector<string> lines2;
};

#endif /* FileUtilTest_h */
