//
//  Day9.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/11/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day9.h"

static const int OFFSET = '0';

struct marker {
    bool parsing = true;
    int count = 0;
    int mult = 0;
};

Day9::Day9() {
    puts("Running Day 9 - a");

    unsigned long int length = 0;
    FileUtil::parse(9, [&](const string& line){
        int count = 0;
        int mult = 0;
        bool eatingCount = false;
        bool eatingMult = false;

        for (const char& c : line) {
            if (eatingCount) {
                if (c == 'x') {
                    eatingCount = false;
                    eatingMult = true;
                }
                else {
                    if (count == 0)
                        count = c - OFFSET;
                    else
                        count = count * 10 + (c - OFFSET);
                }
            }
            else if (eatingMult) {
                if (c == ')')
                    eatingMult = false;
                else {
                    if (mult == 0)
                        mult = c - OFFSET;
                    else
                        mult = mult * 10 + (c - OFFSET);
                }
            }
            else if (count > 0) {
                --count;
                length += mult;
                if (count == 0)  mult = 0;
            }
            else if (c == '(')
                eatingCount = true;
            else
                ++length;
        }
    });

    cout << "Decompressed Length: " << length << endl;

    puts("Running Day 9 - b");

    length = 0;

    FileUtil::parse(9, [&](const string& line) {
        list<marker> markers;
        bool eatingCount = false;
        bool eatingMult = false;
        bool finishedEatingMarker = false;

        for (const char& c : line) {
            if (c == '(') {
                markers.push_back(marker());
                eatingCount = true;
            }
            else if (eatingCount) {
                if (c == 'x') {
                    eatingCount = false;
                    eatingMult = true;
                }
                else {
                    marker& m = markers.back();
                    if (m.count == 0)
                        m.count = c - OFFSET;
                    else
                        m.count = m.count * 10 + (c - OFFSET);
                }
            }
            else if (eatingMult) {
                if (c == ')') {
                    eatingMult = false;
                    finishedEatingMarker = true; // Delayed set, so marker's count isn't decremented on itself completing.
                }
                else {
                    marker& m = markers.back();
                    if (m.mult == 0)
                        m.mult = c - OFFSET;
                    else
                        m.mult = m.mult * 10 + (c - OFFSET);
                }
            }
            else {
                int mult = 1;
                for (const marker& m : markers)
                    mult *= m.mult;
                length += mult;
            }

            for (marker& m : markers)
                if (!m.parsing) m.count--;

            if (finishedEatingMarker) {
                markers.back().parsing = false;
                finishedEatingMarker = false;
            }

            markers.remove_if([](const marker& m){return !m.parsing && m.count == 0;});
        }
    });

    cout << "Decompressed Length: " << length << endl;
}
