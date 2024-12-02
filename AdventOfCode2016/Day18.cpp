//
//  Day18.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/27/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day18.h"

static const string INPUT = "^^.^..^.....^..^..^^...^^.^....^^^.^.^^....^.^^^...^^^^.^^^^.^..^^^^.^^.^.^.^.^.^^...^^..^^^..^.^^^^";
static const int NUM_COLS = 100;
static const int NUM_ROWS_A = 40;
static const int NUM_ROWS_B = 400000;

Day18::Day18() {
    char row[NUM_COLS] = {};
    for (int i = 0; i < NUM_COLS; ++i) row[i] = (INPUT[i] == '^');

    puts("Running Day 18 - a");
    cout << "Num Safe Tiles = " << countSafeTiles(row, NUM_ROWS_A) << endl;

    puts("Running Day 18 - b");
    cout << "Num Safe Tiles = " << countSafeTiles(row, NUM_ROWS_B) << endl;
}

int Day18::countSafeTiles(char row[], int numRows) {
    int numTraps = 0, curr = 0, prev = 1;
    char rows[2][NUM_COLS + 2] = {}; // Pad data set with safe on either side to avoid bounds checks later.

    for (int i = 0; i < NUM_COLS; ++i) {
        rows[0][i+1] = row[i];
        numTraps += rows[0][i+1];
    }

    for (int i = 1; i < numRows; ++i) {
        curr ^= 1;
        prev ^= 1;

        for (int j = 1; j <= NUM_COLS; ++j) {
            rows[curr][j] = (rows[prev][j-1] ^ rows[prev][j+1]);
            numTraps += rows[curr][j]; // Counting traps instead of safe tiles to avoid extra ^ 1 operations.
        }
    }

    return (NUM_COLS * numRows) - numTraps;
}
