//
//  Day8.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/7/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day8.h"

static const int ROWS = 6;
static const int COLUMNS = 50;

Day8::Day8() {
    puts("Running Day 8 - a");

    bool lights[ROWS][COLUMNS] = {};

    FileUtil::parse(8, [&](const string& line){
        string instruction;
        char dummyChar;
        string dummyString;
        istringstream stream = istringstream(line);
        stream >> instruction;

        if (instruction == "rect") {
            int x, y;
            stream >> x >> dummyChar >> y;

            for (int i = 0; i < y; ++i)
                for (int j = 0; j < x; ++j)
                    lights[i][j] = true;
        }
        else if (instruction == "rotate") {
            string dimension;
            int idx;
            int offset;
            stream >> dimension >> dummyChar >> dummyChar >> idx >> dummyString >> offset;

            if (dimension == "row") {
                bool row[COLUMNS] = {};

                for (int i = 0; i < COLUMNS; ++i)
                    row[i] = lights[idx][i];

                for (int i = 0; i < COLUMNS; ++i)
                    lights[idx][i] = row[wrap(i - offset, 0, COLUMNS)];
            }
            else if (dimension == "column") {
                bool column[ROWS] = {};

                for (int i = 0; i < ROWS; ++i)
                    column[i] = lights[i][idx];

                for (int i = 0; i < ROWS; ++i)
                    lights[i][idx] = column[wrap(i - offset, 0, ROWS)];
            }
        }
    });

    int count = 0;
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLUMNS; ++j)
            if (lights[i][j]) ++count;

    cout << "Number of Lights: " << count << endl;

    puts("Running Day 8 - b");

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j)
            printf((lights[i][j]) ? "#" : " ");
        cout << endl;
    }
}
