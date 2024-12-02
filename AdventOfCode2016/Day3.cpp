//
//  Day3.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/3/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day3.h"

Day3::Day3() {
    puts("Running Day 3 - a");

    int count = 0;
    int t1[3], t2[3], t3[3];

    FileUtil::parse(3, [&](const string& line){
        istringstream stream = istringstream(line);
        stream >> t1[0] >> t1[1] >> t1[2];

        if (checkTriangle(t1)) ++count;
    });

    cout << "Possible Triangles = " << count << endl;

    puts("Running Day 3 - b");

    count = 0;
    int idx = 0;

    FileUtil::parse(3, [&](const string& line){
        istringstream stream = istringstream(line);
        stream >> t1[idx] >> t2[idx] >> t3[idx];

        idx = wrap(++idx, 0, 3);

        if (idx == 0) {
            if (checkTriangle(t1)) ++count;
            if (checkTriangle(t2)) ++count;
            if (checkTriangle(t3)) ++count;
        }
    });

    cout << "Possible Triangles = " << count << endl;
}

inline bool Day3::checkTriangle(int t[]) {
    return (t[0] + t[1] > t[2]) && (t[0] + t[2] > t[1]) && (t[1] + t[2] > t[0]);
}
