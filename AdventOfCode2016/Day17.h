//
//  Day17.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/27/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Day17_h
#define Day17_h

#include "includes.h"

struct Path;

class Day17
{
public:
    Day17();
private:
    void evaluateDirections(Path* p, queue<Path*>& paths);
};

#endif /* Day17_h */
