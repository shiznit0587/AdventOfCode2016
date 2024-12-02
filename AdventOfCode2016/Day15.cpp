//
//  Day15.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/20/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day15.h"

Day15::Day15() {
    puts("Running Day 15 - a");

    vector<int> positions = {17, 7, 19, 5, 3, 13};
    vector<int> states = {1, 0, 2, 0, 0, 5};

    int timeA = simulate(positions, states);

    cout << "Min Time = " << timeA << endl;

    puts("Running Day 15 - b");

    positions = {17, 7, 19, 5, 3, 13, 11};
    states = {1, 0, 2, 0, 0, 5, 0};

    int timeB = simulate(positions, states);

    cout << "Min Time = " << timeB << endl;
}

int Day15::simulate(vector<int> positions, vector<int> states) {

    auto numStates = states.size();
    auto states_begin = states.begin();
    auto states_end = states.end();
    auto compare = [](int s){return s == 0;};

    // Convert the states for all discs to what position they will be in when a capsule dropped at time=0 passes them.
    for (auto i = 0; i < numStates; ++i)
        states[i] = wrap(states[i] + (i+1), 0, positions[i]);

    // Find time where the largest disc is first in the 0th position.
    auto maxDiscPositionIter = max_element(positions.begin(), positions.end());
    int maxDiscSize = *maxDiscPositionIter;
    int maxDiscStart = states[distance(positions.begin(), maxDiscPositionIter)];
    int time = maxDiscSize - maxDiscStart;

    // Advance all discs by this amount of time.
    for (auto i = 0; i < numStates; ++i)
        states[i] = wrap(states[i] + time, 0, positions[i]);

    int minTime;

    while (true) {
        // Check if the capsule will fall through at the current time.
        if (all_of(states_begin, states_end, compare)) {
            minTime = time;
            break;
        }

        // Progress to the next time for which the largest disc will be in the 0th position.
        for (auto i = 0; i < numStates; ++i)
            states[i] = wrap(states[i] + maxDiscSize, 0, positions[i]);

        time += maxDiscSize;
    }

    return time;
}
