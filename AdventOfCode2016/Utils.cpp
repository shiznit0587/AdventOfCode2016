//
//  Utils.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/3/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

//#include <algorithm>
//#include <functional>
#include "Utils.h"

int Utils::wrap(int x, int min, int max) {
    while (x < min) x += (max - min);
    while (x >= max) x -= (max - min);
    return x;
    //return ((x - min) % max) + min;
}

// trim from start
void Utils::ltrim(string& s) {
    //s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    s.erase(0, s.find_first_not_of(' '));
}

// trim from end
void Utils::rtrim(string& s) {
    //s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    s.erase(s.find_last_not_of(' ') + 1);
}

// trim from both ends
void Utils::trim(string& s) {
    ltrim(s);
    rtrim(s);
}
