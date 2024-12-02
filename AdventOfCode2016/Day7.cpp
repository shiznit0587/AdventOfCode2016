//
//  Day7.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/6/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day7.h"

Day7::Day7() {
    int countA = 0, countB = 0;

    FileUtil::parse(7, [&](const string& line) {

        bool foundABBA = false, valid = true, insideHypernetSequence = false;
        set<string> foundABAs, foundBABs;

        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == '[')
                insideHypernetSequence = true;
            else if (line[i] == ']')
                insideHypernetSequence = false;
            else if (i >= 2 && isalpha(line[i]) && isalpha(line[i-1]) && isalpha(line[i-2])) {
                if (line[i] == line[i-2] && line[i] != line[i-1]) {
                    if (insideHypernetSequence)
                        foundBABs.insert(line.substr(i-1, 2)); // Just grab 'AB'
                    else
                        foundABAs.insert(line.substr(i-2, 2)); // Just grab 'AB'
                }

                if (i >= 3 && isalpha(line[i-3]) && line[i] == line[i-3] && line[i-1] == line[i-2] && line[i] != line[i-1]) {
                    if (insideHypernetSequence)
                        valid = false; // invalid!
                    else
                        foundABBA = true; // abba found.
                }
            }
        }

        if (foundABBA && valid) ++countA;

        for (const string& aba : foundABAs) {
            if (foundBABs.find(aba) != foundBABs.end()) {
                ++countB;
                break;
            }
        }
    });

    puts("Running Day 7 - a");
    cout << "IPs supporting TLS: " << countA << endl;
    puts("Running Day 7 - b");
    cout << "IPs supporting SSL: " << countB << endl;
}
