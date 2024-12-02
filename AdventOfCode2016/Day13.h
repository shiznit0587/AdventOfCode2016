//
//  Day13.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/16/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Day13_h
#define Day13_h

#include "includes.h"

struct Node;

typedef pair<int, int> Position;
typedef map<Position, Node*> NodeMap;

class Day13
{
public:
    Day13();
private:
    Node* findNext(const NodeMap inbox);
    void getNeighbors(int x, int y, set<Position>& outNeighbors);
    bool isEmptySpace(int x, int y);
};

#endif /* Day13_h */
