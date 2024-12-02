//
//  Day23.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/30/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day23.h"
#include "Assembunny.h"

Day23::Day23() {
    puts("Running Day 23 - a");

    Assembunny program;

    FileUtil::parse(23, [&](const string& line) { program.addInstruction(line); } );

    program.setRegister('a', 7);
    program.runProgram();

    cout << "a = " << program.getRegister('a') << ", b = " << program.getRegister('b') << ", c = " << program.getRegister('c') << ", d = " << program.getRegister('d') << endl;

    puts("Running Day 23 - b");

    program.resetProgram();
    program.setRegister('a', 12);
    program.runProgram();

    cout << "a = " << program.getRegister('a') << ", b = " << program.getRegister('b') << ", c = " << program.getRegister('c') << ", d = " << program.getRegister('d') << endl;
}
