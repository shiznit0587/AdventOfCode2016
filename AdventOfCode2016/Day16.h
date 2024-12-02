//
//  Day16.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/20/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Day16_h
#define Day16_h

#include "includes.h"

class Day16
{
public:
    Day16();
private:
    string getChecksum(int diskSize) const;
    bool getChecksumBit(int diskSize, int checksumSize, int idx) const;
    bool isBitOn(int idx) const;
    bool isBitOn2(int idx, int dragonCurveSize);
};

#endif /* Day16_h */
