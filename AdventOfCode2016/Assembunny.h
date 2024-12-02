//
//  Assembunny.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/30/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Assembunny_h
#define Assembunny_h

#include "includes.h"

typedef array<string, 3> Instruction;

class Assembunny {
public:
    void addInstruction(const string& instr);
    void runProgram();
    void advanceProgram();
    bool isProgramComplete() const;
    void resetProgram();
    void setRegister(char r, int val);
    int getRegister(char r) const;
private:
    const Instruction& getInstruction(int idx) const;
    Instruction& getModifiableInstruction(int idx);

    int cursor = 0;
    vector<Instruction> program;
    map<int, Instruction> modifiedInstructions;
    array<int, 4> registers = {0, 0, 0, 0};
};

#endif /* Assembunny_h */
