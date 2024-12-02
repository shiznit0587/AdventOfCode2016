//
//  Day21.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/29/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day21.h"

static const int PASSWORD_LENGTH = 8;

enum InstructionType {
    SWAP_POSITIONS,
    SWAP_LETTERS,
    REVERSE,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    ROTATE_BY_LETTER,
    MOVE
};

struct Instruction {

private:
    InstructionType type;
    int x = 0, y = 0;
    char a = 0, b = 0;

public:
    Instruction(string pLine, InstructionType pType, int pX) : line(pLine), type(pType), x(pX) {}
    Instruction(string pLine, InstructionType pType, int pX, int pY) : line(pLine), type(pType), x(pX), y(pY) {}
    Instruction(string pLine, InstructionType pType, char pA) : line(pLine), type(pType), a(pA) {}
    Instruction(string pLine, InstructionType pType, char pA, char pB) : line(pLine), type(pType), a(pA), b(pB) {}

    string line;

    void process(char* password) const {
        switch (type) {
            case SWAP_POSITIONS:    swap(password, x, y);               break;
            case SWAP_LETTERS:      swap(password, a, b);               break;
            case REVERSE:           reverse(password, x, y);            break;
            case ROTATE_LEFT:       rotateLeft(password, x);            break;
            case ROTATE_RIGHT:      rotateRight(password, x);           break;
            case ROTATE_BY_LETTER:  rotateByLetter(password, a);        break;
            case MOVE:              move(password, x, y);               break;
        }
    }

    void processReverse(char* password) const {
        switch (type) {
            case SWAP_POSITIONS:    swap(password, x, y);               break; // same in reverse
            case SWAP_LETTERS:      swap(password, a, b);               break; // same in reverse
            case REVERSE:           reverse(password, x, y);            break; // same in reverse
            case ROTATE_LEFT:       rotateRight(password, x);           break; // Just go right instead of left
            case ROTATE_RIGHT:      rotateLeft(password, x);            break; // Just go left instead of right
            case ROTATE_BY_LETTER:  rotateByLetterReverse(password, a); break; // Call a custom method for this one
            case MOVE:              move(password, y, x);               break; // Just swap x and y
        }
    }

    void swap(char* password, int x, int y) const {
        password[x] ^= password[y];
        password[y] ^= password[x];
        password[x] ^= password[y];
    }

    void swap(char* password, char x, char y) const {
        swap(password, indexOf(password, x), indexOf(password, y));
    }

    void reverse(char* password, int x, int y) const {
        for (int i = 0; i < (y - x + 1) / 2; ++i) swap(password, x + i, y - i);
    }

    void rotateLeft(char* password, int x) const {
        char temp[PASSWORD_LENGTH + 1] = {};
        for (int i = 0; i < PASSWORD_LENGTH; ++i) temp[i] = password[i];
        for (int i = 0; i < PASSWORD_LENGTH; ++i) password[wrap(i - x, 0, PASSWORD_LENGTH)] = temp[i];
    }

    void rotateRight(char* password, int x) const {
        char temp[PASSWORD_LENGTH + 1] = {};
        for (int i = 0; i < PASSWORD_LENGTH; ++i) temp[i] = password[i];
        for (int i = 0; i < PASSWORD_LENGTH; ++i) password[i] = temp[wrap(i - x, 0, PASSWORD_LENGTH)];
    }

    void rotateByLetter(char* password, char c) const {
        int rotations = 1 + indexOf(password, c);
        rotateRight(password, (rotations > 4) ? ++rotations : rotations);
    }

    void rotateByLetterReverse(char* password, char c) const {
        int idx = wrap(indexOf(password, c), 1, PASSWORD_LENGTH + 1);
        rotateLeft(password, idx - (idx + PASSWORD_LENGTH * (~idx & 1) - (~idx & 1)) / 2);
    }

    void move(char* password, int x, int y) const {
        char m = password[x];
        for (int i = x; i < PASSWORD_LENGTH; ++i) password[i] = password[i+1];
        for (int i = PASSWORD_LENGTH - 1; i > y; --i) password[i] = password[i-1];
        password[y] = m;
    }
    
    int indexOf(char* password, char c) const {
        int idx = 0;
        for (; idx < PASSWORD_LENGTH; ++idx) if (password[idx] == c) break;
        return idx;
    }
};

Day21::Day21() {
    puts("Running Day 21 - a");

    char password[PASSWORD_LENGTH + 1] = {};
    strcpy(password, "abcdefgh");

    //printf("%-36s : %s\n", "initial password", password);

    list<Instruction> steps;
    FileUtil::parse(21, [&](const string& line) {
        istringstream stream(line);

        string instruction, d;
        stream >> instruction;

        if (instruction == "swap") {
            stream >> instruction;
            if (instruction == "position") {
                int x, y;
                stream >> x >> d >> d >> y;
                steps.emplace_back(line, InstructionType::SWAP_POSITIONS, x, y);
            }
            else if (instruction == "letter") {
                char x, y;
                stream >> x >> d >> d >> y;
                steps.emplace_back(line, InstructionType::SWAP_LETTERS, x, y);
            }
        }
        else if (instruction == "rotate") {
            stream >> instruction;
            if (instruction == "based") {
                char x;
                stream >> d >> d >> d >> d >> x;
                steps.emplace_back(line, InstructionType::ROTATE_BY_LETTER, x);
            }
            else if (instruction == "left") {
                int x;
                stream >> x;
                steps.emplace_back(line, InstructionType::ROTATE_LEFT, x);
            }
            else if (instruction == "right") {
                int x;
                stream >> x;
                steps.emplace_back(line, InstructionType::ROTATE_RIGHT, x);
            }
        }
        else if (instruction == "reverse") {
            int x, y;
            stream >> d >> x >> d >> y;
            steps.emplace_back(line, InstructionType::REVERSE, x, y);
        }
        else if (instruction == "move") {
            int x, y;
            stream >> d >> x >> d >> d >> y;
            steps.emplace_back(line, InstructionType::MOVE, x, y);
        }
    });

    for (const Instruction& step : steps) {
        step.process(password);
        //printf("%-36s : %s\n", step.line.c_str(), password);
    }

    printf("%-36s : %s\n", "scrambled password", password);

    //puts("");
    puts("Running Day 21 - b");
    //puts("");

    strcpy(password, "fbgdceah");

    //printf("%-36s : %s\n", "initial password", password);

    for (auto step = steps.crbegin(); step != steps.crend(); ++step) {
        step->processReverse(password);
        //printf("%-36s : %s\n", step->line.c_str(), password);
    }

    printf("%-36s : %s\n\n", "unscrambled password", password);
}
