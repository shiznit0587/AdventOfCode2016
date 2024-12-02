//
//  Assembunny.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/30/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Assembunny.h"

static const int A = 'a';

void Assembunny::addInstruction(const string& instr) {
    istringstream ss(instr);
    Instruction i;
    ss >> i[0] >> i[1] >> i[2];
    program.push_back(i);
}

void Assembunny::runProgram() {
    while (!isProgramComplete())
        advanceProgram();
}

void Assembunny::advanceProgram() {
    const Instruction& i = getInstruction(cursor);

    if (i[0] == "cpy") {
        if (isalpha(i[2][0])) {
            if (isalpha(i[1][0]))
                setRegister(i[2][0], getRegister(i[1][0]));
            else
                setRegister(i[2][0], atoi(i[1].c_str()));
        }
    }
    else if (i[0] == "inc") {
        setRegister(i[1][0], getRegister(i[1][0]) + 1);
    }
    else if (i[0] == "dec") {
        setRegister(i[1][0], getRegister(i[1][0]) - 1);
    }
    else if (i[0] == "jnz") {
        int val;
        if (isalpha(i[1][0]))
            val = getRegister(i[1][0]);
        else
            val = atoi(i[1].c_str());

        if (val != 0) {
            if (isalpha(i[2][0]))
                val = getRegister(i[2][0]);
            else
                val = atoi(i[2].c_str());

            cursor += val - 1; // Increment by 1 less because we're about to increment below.
        }
    }
    else if (i[0] == "tgl") {
        int instrIdx;
        if (isalpha(i[1][0]))
            instrIdx = cursor + getRegister(i[1][0]);
        else
            instrIdx = cursor + atoi(i[1].c_str());

        if (0 <= instrIdx && instrIdx < program.size()) {
            Instruction& instr = getModifiableInstruction(instrIdx);
            if (instr[0] == "inc")
                instr[0] = "dec";
            else if (instr[0] == "dec" || instr[0] == "tgl")
                instr[0] = "inc";
            else if (instr[0] == "jnz")
                instr[0] = "cpy";
            else if (instr[0] == "cpy")
                instr[0] = "jnz";
        }
    }

    ++cursor;
}

bool Assembunny::isProgramComplete() const {
    return (cursor < 0 || program.size() <= cursor);
}

void Assembunny::resetProgram() {
    cursor = 0;
    fill(registers.begin(), registers.end(), 0);
    modifiedInstructions.clear();
}

void Assembunny::setRegister(char r, int val) {
    registers[r - A] = val;
}

int Assembunny::getRegister(char r) const {
    return registers[r - A];
}

const Instruction& Assembunny::getInstruction(int idx) const {
    auto iter = modifiedInstructions.find(idx);
    if (iter != modifiedInstructions.end())
        return iter->second;
    return program[idx];
}

Instruction& Assembunny::getModifiableInstruction(int idx) {
    auto iter = modifiedInstructions.find(idx);
    if (iter != modifiedInstructions.end())
        return iter->second;
    Instruction i;
    i[0] = program[idx][0];
    i[1] = program[idx][1];
    i[2] = program[idx][2];
    modifiedInstructions[idx] = i;
    return modifiedInstructions.find(idx)->second;
}
