//
//  Day19.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/28/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day19.h"

static const int NUM_ELVES = 3017957;

struct Elf {
    Elf* previous = nullptr;
    Elf* next = nullptr;
    int number = 0;
    int presents = 0;
    Elf(int n, int p) : number(n), presents(p) {}
};

Day19::Day19() {
    puts("Running Day 19 - a");

    int* gifts = new int[NUM_ELVES];
    for (int i = 0; i < NUM_ELVES; ++i) gifts[i] = 1;
    int idx = 0;

    while (true) {
        int takeIdx = (idx + 1) % NUM_ELVES;
        while (gifts[takeIdx] == 0)
            takeIdx = (takeIdx + 1) % NUM_ELVES;

        gifts[idx] += gifts[takeIdx];
        gifts[takeIdx] = 0;

        if (gifts[idx] == NUM_ELVES)
            break;

        idx = takeIdx;
        while (gifts[idx] == 0)
            idx = (idx + 1) % NUM_ELVES;
    }

    cout << "Elf with all presents = " << (idx + 1) << endl;

    puts("Running Day 19 - b");

    // TODO: Try using the built-in list structure with an iterator.

    Elf* head = new Elf(0, 1);
    Elf* tail = head;
    Elf* takeFromElf = nullptr;

    for (int i = 1; i < NUM_ELVES; ++i) {
        Elf* elf = new Elf(i, 1);
        elf->previous = tail;
        tail->next = elf;
        tail = elf;

        if (i == NUM_ELVES >> 1)
            takeFromElf = elf;
    }

    tail->next = head;
    head->previous = tail;

    int elvesRemaining = NUM_ELVES;

    while (elvesRemaining > 1) {
        takeFromElf->previous->next = takeFromElf->next;
        takeFromElf->next->previous = takeFromElf->previous;
        --elvesRemaining;

        takeFromElf = takeFromElf->next;
        if ((elvesRemaining & 1) == 0)
            takeFromElf = takeFromElf->next;
    }

    cout << "Elf with all presents = " << takeFromElf->number + 1 << endl;
}
