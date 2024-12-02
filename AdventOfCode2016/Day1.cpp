//
//  Day1.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 11/30/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day1.h"

const string DIRECTION[] = {"NORTH", "EAST", "SOUTH", "WEST"};

void Day1::visit(const point& x) {
    if (mark.find(x) != mark.end() && b == nullptr) {
        b = new point(x.first, x.second);
        //printf("Visited Twice: [%d,%d]\n", x.first, x.second);
    }

    mark.insert(x);
}

Day1::Day1() {
    a = new point(0,0);
    int dir = 0; // 0-3 is NESW, respectively

    string input;
    FileUtil::parse(1, [&](const string& line){input = line;});

    std::stringstream stream(input);
    std::string command;

    while (getline(stream, command, ',')) { // split on comma
        trim(command); // trim leading space

        //cout << command << endl;

        switch (command[0]) {
            case 'L': dir = wrap(--dir, 0, 4); break;
            case 'R': dir = wrap(++dir, 0, 4); break;
        }

        // Now I need to parse the remaining number part of the string.
        int distance = atoi(command.substr(1).c_str());

        //cout << "direction = " << DIRECTION[dir] << ", distance = " << distance << endl;

        for (int i = 0; i < distance; ++i) {
            switch (dir) {
                case 0: a->second += 1; visit(*a); break;
                case 1: a->first  += 1; visit(*a); break;
                case 2: a->second -= 1; visit(*a); break;
                case 3: a->first  -= 1; visit(*a); break;
            }
        }

        //cout << "x = " << a->first << ", y = " << a->second << endl;
    }

    puts("Running Day 1 - a");
    printf("Distance = %d\n", (abs(a->first) + abs(a->second)));
    puts("Running Day 1 - b");
    printf("Distance = %d\n", (abs(b->first) + abs(b->second)));
}
