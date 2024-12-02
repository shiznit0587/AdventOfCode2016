//
//  Day20.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/29/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day20.h"

struct RangeBound {
    int blacklist;
    uint ip = 0;
    RangeBound(int pBlacklist) : blacklist(pBlacklist) {}
    bool operator < (const RangeBound& k) const { return ip < k.ip; }
};

Day20::Day20() {
    set<RangeBound> bounds;
    FileUtil::parse(20, [&](const string& line) {
        RangeBound begin(1), end(-1);
        char dummy;
        istringstream stream = istringstream(line);
        stream >> begin.ip >> dummy >> end.ip;
        bounds.insert(begin);
        bounds.insert(end);
    });

    uint candidateIP = 0, firstIP = 0;
    int allowedIPs = 0, blacklists = 0;
    for (const RangeBound& b : bounds) {
        if (firstIP == 0 && blacklists == 0 && b.ip > candidateIP) firstIP = candidateIP;
        blacklists += b.blacklist;
        if (blacklists == 0) candidateIP = b.ip + 1;
        if (blacklists == 1 && b.blacklist == 1) allowedIPs += b.ip - candidateIP;
    }

    puts("Running Day 20 - a");
    cout << "First IP = " << firstIP << endl;
    puts("Running Day 20 - b");
    cout << "Allowed IPs = " << allowedIPs << endl;
}
