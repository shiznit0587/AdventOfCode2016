//
//  Day10.h
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/12/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#ifndef Day10_h
#define Day10_h

#include "includes.h"

struct Rule {
    int botId = -1;
    int lowBotId = -1;
    int highBotId = -1;
    int lowOutputId = -1;
    int highOutputId = -1;
};

struct Bot {
    int botId = -1;
    int chip1 = -1;
    int chip2 = -1;

    void receiveChip(int chip);
    void clearChips() {chip1 = -1; chip2 = -1;}
    bool hasTwoChips() const {return chip1 != -1 && chip2 != -1;}

    int lowChip() {return (chip1 < chip2) ? chip1 : chip2;}
    int highChip() {return (chip1 < chip2) ? chip2 : chip1;}
};

class Day10
{
public:
    Day10();
private:
    Bot& getBot(int botId);
    Rule& getRule(int botId);

    map<int, Rule> _rules;
    map<int, Bot> _bots;
    map<int, set<int>> _outputs;
};

#endif /* Day10_h */
