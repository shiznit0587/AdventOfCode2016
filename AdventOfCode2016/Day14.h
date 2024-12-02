//
//  Day14.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/19/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Day14_h
#define Day14_h

#include "includes.h"

class Day14
{
public:
    Day14();
    int get64thKeyIndex(const function<string(int)>& generator);
};

#endif /* Day14_h */
