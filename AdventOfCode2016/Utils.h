//
//  Utils.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/3/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Utils_h
#define Utils_h

#include <string>

using namespace std;

namespace Utils {
    //inline int wrap(int x, int min, int max) {return ((x - min) % max) + min;}
    int wrap(int x, int min, int max);
    void ltrim(string& s);
    void rtrim(string& s);
    void trim(string& s);
};

#endif /* Utils_h */
