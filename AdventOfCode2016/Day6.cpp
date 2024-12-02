//
//  Day6.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/5/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day6.h"

static const int OFFSET = 'a';

Day6::Day6() {
    puts("Running Day 6 - a");

    char counts[8][26] = {};

    FileUtil::parse(6, [&](const string& line){
        int idx = 0;
        for (const char& c : line) {
            counts[idx++][c - OFFSET]++;
        }
    });

    char messageA[9] = {};
    char messageB[9] = {};

    for (int i = 0; i < 8; ++i) {
        int maxCount = 0;
        int minCount = INT_MAX;
        char messageCharA = 0;
        char messageCharB = 0;
        for (int j = 0; j < 26; ++j) {
            if (counts[i][j] > maxCount) {
                maxCount = counts[i][j];
                messageCharA = j + OFFSET;
            }
            if (counts[i][j] < minCount) {
                minCount = counts[i][j];
                messageCharB = j + OFFSET;
            }
        }
        messageA[i] = messageCharA;
        messageB[i] = messageCharB;
    }

    cout << "Message: " << messageA << endl;
    puts("Running Day 6 - b");
    cout << "Message: " << messageB << endl;
}
