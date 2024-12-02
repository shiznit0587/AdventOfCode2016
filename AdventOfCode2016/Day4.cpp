//
//  Day4.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/4/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day4.h"

static const int OFFSET = 'a';
static const int LETTERS = 26;
static const int CHECKSUM_LENGTH = 5;

Day4::Day4() {
    puts("Running Day 4 - a");

    int sectorIdSum = 0;
    int finalSectorId = 0;

    FileUtil::parse(4, [&,this](const string& line){
        int counts[LETTERS] = {};
        int sectorId = 0;

        for (const char& c : line) {
            if (isalpha(c))
                counts[c - OFFSET]++;
            else if (isdigit(c)) {
                sectorId = atoi(&c); // will eat all sequential digit characters.
                break; // next is checksum.
            }
        }

        string calcChecksum = calculateChecksum(counts);
        string lineChecksum = line.substr(line.find_first_of('[') + 1, CHECKSUM_LENGTH);

        if (calcChecksum == lineChecksum) {
            sectorIdSum += sectorId;
            string name = line.substr(0, line.find_last_of('-'));

            // Perform the shift cypher based on the sector id
            for (int i = 0; i < name.size(); ++i)
                if (isalpha(name[i]))
                    name[i] = ((name[i] - OFFSET + sectorId) % LETTERS) + OFFSET;

            if (name == "northpole-object-storage")
                finalSectorId = sectorId;
        }
    });

    printf("Sector ID Sum = %d\n", sectorIdSum);
    puts("Running Day 4 - b");
    printf("Sector ID = %d\n", finalSectorId);
}

string Day4::calculateChecksum(int counts[]) {
    char checksum[CHECKSUM_LENGTH + 1] = {}; // null-terminated c string
    int idx = 0;

    while (idx < CHECKSUM_LENGTH) {
        int maxCount = 0;

        for (int i = 0; i < LETTERS; ++i)
            if (counts[i] > maxCount)
                maxCount = counts[i];

        for (int i = 0; i < LETTERS; ++i) {
            if (counts[i] == maxCount) {
                counts[i] = 0;
                checksum[idx++] = i + OFFSET;
            }

            if (idx == CHECKSUM_LENGTH)
                break;
        }
    }

    return checksum;
}
