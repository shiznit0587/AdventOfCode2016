//
//  main.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 11/30/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef MAIN_H
#define MAIN_H

#include <chrono>
#include <iostream>
#include "stdlib.h"
#include "FileUtilTest.h"
#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include "Day6.h"
#include "Day7.h"
#include "Day8.h"
#include "Day9.h"
#include "Day10.h"
#include "Day11.h"
#include "Day12.h"
#include "Day13.h"
#include "Day14.h"
#include "Day15.h"
#include "Day16.h"
#include "Day17.h"
#include "Day18.h"
#include "Day19.h"
#include "Day20.h"
#include "Day21.h"
#include "Day22.h"
#include "Day23.h"
#include "Day24.h"

using namespace std;

int main(int argc, const char * argv[]) {

    puts(":: Advent of Code ::");
    puts("");

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    Day24();

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    puts("");
    cout << "Elapsed Time: " << elapsed_seconds.count() << "s" << endl << endl;

    //system("pause");
}

#endif // MAIN_H
