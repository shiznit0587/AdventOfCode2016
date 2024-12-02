//
//  Day12.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/15/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day12.h"
#include "Assembunny.h"

Day12::Day12() {
    puts("Running Day 12 - a");

    Assembunny program;

    FileUtil::parse(12, [&](const string& line) { program.addInstruction(line); } );

    program.runProgram();

    cout << "a = " << program.getRegister('a') << ", b = " << program.getRegister('b') << ", c = " << program.getRegister('c') << ", d = " << program.getRegister('d') << endl;

    puts("Running Day 12 - b");

    program.resetProgram();
    program.setRegister('c', 1);
    program.runProgram();

    cout << "a = " << program.getRegister('a') << ", b = " << program.getRegister('b') << ", c = " << program.getRegister('c') << ", d = " << program.getRegister('d') << endl;
}
