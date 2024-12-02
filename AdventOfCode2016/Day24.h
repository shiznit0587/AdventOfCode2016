//
//  Day24.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/31/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Day24_h
#define Day24_h

#include "includes.h"

static const char OFFSET = '0';

typedef pair<int,int> Point;

struct Location {
    Point point;
    int interestPointId = -1;
    bool isWall;

    bool isPointOfInterest() const { return interestPointId != -1; }
    bool isTraversable() const { return !isWall; }
    char printChar() const { return isWall ? '#' : isPointOfInterest() ? interestPointId + OFFSET : ' '; }

    Location(int x, int y, char c) {
        point = make_pair(x,y);
        isWall = (c == '#');
        if (isdigit(c))
            interestPointId = c - OFFSET;
    }
};

class Day24
{
public:
    Day24();
private:
    void findShortestDistance(Location* a, Location* b) const;
    Location* findNext(const map<Point, Location*> &inbox) const;
    void getNeighbors(Point p, set<Location*> &outSet) const;

    map<Point, Location*> blueprint;
    vector<Location*> pointsOfInterest;
};

#endif /* Day24_h */
