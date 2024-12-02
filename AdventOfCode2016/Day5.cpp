//
//  Day5.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/5/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day5.h"

Day5::Day5() {
    puts("Running Day 5 - a");

    string input = "ffykfhsq";

    char passwordA[9] = {};
    char passwordB[9] = {};
    int countA = 0, countB = 0, index = 0;

    while (countA < 8 || countB < 8) {
        string md5 = MD5(input + to_string(index)).hexdigest();

        if (md5.find("00000") == 0) {
            if (countA < 8) {
                passwordA[countA++] = md5[5];
                //cout << "Found password A character "  << countA << " at index " << index << " :: " << md5[5] << endl;
            }

            if (countB < 8 && isdigit(md5[5])) {
                char c[] = {md5[5], 0};
                int pos = atoi(c);
                if (pos < 8 && passwordB[pos] == 0) {
                    passwordB[pos] = md5[6];
                    //cout << "Found password B character "  << (pos + 1) << " at index " << index << " :: " << md5[6] << endl;
                    ++countB;
                }
            }
        }

        ++index;
    }

    cout << "Password: " << passwordA << endl;
    puts("Running Day 5 - b");
    cout << "Password: " << passwordB << endl;
}
