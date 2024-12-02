//
//  Day2.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/1/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day2.h"

Day2::Day2() {
    puts("Running Day 2 - a");

    vector<string> input;
    FileUtil::parse(2, [&](const string& line){input.push_back(line);});

    char code[] = "00000";

    char keypadA[3][3] = {{'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'}};

    int x = 1;
    int y = 1;
    int idx = 0;

    for (string& line : input) {
        for (char& dir : line) {
            switch (dir) {
                case 'U': if (y > 0) --y; break;
                case 'D': if (y < 2) ++y; break;
                case 'L': if (x > 0) --x; break;
                case 'R': if (x < 2) ++x; break;
            }
        }

        code[idx++] = keypadA[y][x];
    }

    printf("Code = %s\n", code);

    puts("Running Day 2 - b");

    char keypadB[5][5] = {{' ',' ','1',' ',' '},
                          {' ','2','3','4',' '},
                          {'5','6','7','8','9'},
                          {' ','A','B','C',' '},
                          {' ',' ','D',' ',' '}};

    x = 0;
    y = 2;
    idx = 0;

    for (string& line : input) {
        for (char& dir : line) {
            switch (dir) {
                case 'U': if (y > 0 && keypadB[y-1][x] != ' ') --y; break;
                case 'D': if (y < 4 && keypadB[y+1][x] != ' ') ++y; break;
                case 'L': if (x > 0 && keypadB[y][x-1] != ' ') --x; break;
                case 'R': if (x < 4 && keypadB[y][x+1] != ' ') ++x; break;
            }
        }

        code[idx++] = keypadB[y][x];
    }

    printf("Code = %s\n", code);

}
