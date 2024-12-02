//
//  Day16.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/20/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day16.h"

static const int DISK_SIZE_A = 272;
static const int DISK_SIZE_B = 35651584;
static const int INPUT_SIZE = 17;
static const bool INPUT[INPUT_SIZE] = {1,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,1};

Day16::Day16() {
    puts("Running Day 16 - a");
    cout << "Checksum = " << getChecksum(DISK_SIZE_A) << endl;

    puts("Running Day 16 - b");
    cout << "Checksum = " << getChecksum(DISK_SIZE_B) << endl;
}

string Day16::getChecksum(int diskSize) const {

    int checksumSize = diskSize;
    while ((checksumSize & 1) == 0)
        checksumSize >>= 1;

    vector<bool> checksum;
    for (int i = 0; i < checksumSize; ++i)
        checksum.push_back(getChecksumBit(diskSize, checksumSize, i));

    ostringstream stream;
    for (const bool& b : checksum)
        stream << (b ? '1' : '0');

    return stream.str();
}

bool Day16::getChecksumBit(int diskSize, int checksumSize, int idx) const {
    if (diskSize == checksumSize)
        return isBitOn(idx);
    return !(getChecksumBit(diskSize, checksumSize * 2, idx * 2) ^ getChecksumBit(diskSize, checksumSize * 2, idx  * 2 + 1));
}

bool Day16::isBitOn(int idx) const {
    if (idx < INPUT_SIZE)
        return INPUT[idx];

    int size = INPUT_SIZE;
    while (size < idx)
        size = (size << 1) | 1;

    if (idx == size)
        return false;

    return !isBitOn(size - idx - 1);
}
