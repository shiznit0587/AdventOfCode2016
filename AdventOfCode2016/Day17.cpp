//
//  Day17.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/27/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day17.h"

static const string INPUT = "vwbaicqe";

struct Path {
    int x;
    int y;
    string path;
    Path() : x(0), y(0), path("") {}
    Path(int pX, int pY, string pPath) : x(pX), y(pY), path(pPath) {}
};

Day17::Day17() {
    puts("Running Day 17 - a");

    Path* start = new Path();
    Path* end = nullptr;

    queue<Path*> paths;
    paths.push(start);

    while (end == nullptr && paths.size() > 0) {
        Path* p = paths.front();
        paths.pop();

        if (p->x == 3 && p->y == 3) {
            end = p;
            break;
        }

        evaluateDirections(p, paths);
    }

    cout << "Shortest Path = " << end->path << endl;
    puts("Running Day 17 - b");

    delete end;
    end = nullptr;
    start = new Path();

    while (paths.size() > 0) paths.pop();

    paths.push(start);
    long longestPath = 0;

    while (paths.size() > 0) {
        Path* p = paths.front();
        paths.pop();

        if (p->x == 3 && p->y == 3) {
            if (p->path.size() > longestPath) longestPath = p->path.size();
        }
        else
            evaluateDirections(p, paths);
    }

    cout << "Longest Path Length = " << longestPath << endl;
}

void Day17::evaluateDirections(Path *p, queue<Path *> &paths) {
    string hash = MD5(INPUT + p->path).hexdigest();
    if (p->y > 0 && isalpha(hash[0]) && hash[0] != 'a') paths.push(new Path(p->x, p->y - 1, p->path + 'U'));
    if (p->y < 3 && isalpha(hash[1]) && hash[1] != 'a') paths.push(new Path(p->x, p->y + 1, p->path + 'D'));
    if (p->x > 0 && isalpha(hash[2]) && hash[2] != 'a') paths.push(new Path(p->x - 1, p->y, p->path + 'L'));
    if (p->x < 3 && isalpha(hash[3]) && hash[3] != 'a') paths.push(new Path(p->x + 1, p->y, p->path + 'R'));
}
