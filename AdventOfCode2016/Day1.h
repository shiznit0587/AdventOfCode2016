//
//  Day1.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/3/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Day1_h
#define Day1_h

#include "includes.h"

typedef pair<int, int> point;

class Day1
{
public:
    Day1();
private:
    void visit(const point& x);

    set<point> mark;
    point* a;
    point* b;
};

#endif /* Day1_h */
