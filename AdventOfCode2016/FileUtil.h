//
//  FileUtil.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/3/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef FileUtil_h
#define FileUtil_h

#include <functional>
#include <string>

using namespace std;

namespace FileUtil {

    void parse(const int day, const function<void(const string&)> &cb);
}

#endif /* FileUtil_h */
