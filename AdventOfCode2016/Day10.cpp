//
//  Day10.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/12/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day10.h"

Day10::Day10() {
    puts("Running Day 10 - a");

    string dummy;

    FileUtil::parse(10, [&](const string& line){
        istringstream stream = istringstream(line);

        if (line[0] == 'v') {
            int value, botId;
            stream >> dummy >> value >> dummy >> dummy >> dummy >> botId;
            getBot(botId).receiveChip(value);
        }
        else {
            int botId;
            string type;
            stream >> dummy >> botId;
            Rule& rule = getRule(botId);
            stream >> dummy >> dummy >> dummy >> type >> botId;

            if (type[0] == 'b')
                rule.lowBotId = botId;
            else
                rule.lowOutputId = botId;

            stream >> dummy >> dummy >> dummy >> type >> botId;

            if (type[0] == 'b')
                rule.highBotId = botId;
            else
                rule.highOutputId = botId;
        }
    });

    queue<Bot*> processQueue;

    for (auto& node : _bots)
        if (node.second.hasTwoChips())
            processQueue.push(&node.second);

    while (!processQueue.empty()){
        Bot& bot = *processQueue.front();
        processQueue.pop();

        if (bot.lowChip() == 17 && bot.highChip() == 61)
            cout << "Bot ID: " << bot.botId << endl;

        Rule& rule = getRule(bot.botId);

        if (rule.lowBotId != -1) {
            Bot& lowBot = getBot(rule.lowBotId);
            lowBot.receiveChip(bot.lowChip());
            if (lowBot.hasTwoChips())
                processQueue.push(&lowBot);
        }
        else if (rule.lowOutputId != -1)
            _outputs[rule.lowOutputId].insert(bot.lowChip());

        if (rule.highBotId != -1) {
            Bot& highBot = getBot(rule.highBotId);
            highBot.receiveChip(bot.highChip());
            if (highBot.hasTwoChips())
                processQueue.push(&highBot);
        }
        else if (rule.highOutputId != -1)
            _outputs[rule.highOutputId].insert(bot.highChip());

        bot.clearChips();
    }

    puts("Running Day 10 - b");
    cout << "Product of Outputs 0, 1, 2: " << (*_outputs[0].begin() * *_outputs[1].begin() * *_outputs[2].begin()) << endl;
}

Bot& Day10::getBot(int pBotId) {
    if (!_bots.count(pBotId)) {
        Bot bot = Bot();
        bot.botId = pBotId;
        _bots[pBotId] = bot;
    }
    return _bots[pBotId];
}

Rule& Day10::getRule(int pBotId) {
    if (!_rules.count(pBotId)) {
        Rule rule = Rule();
        rule.botId = pBotId;
        _rules[pBotId] = rule;
    }
    return _rules[pBotId];
}

void Bot::receiveChip(int chip) {
    if (chip1 == -1) chip1 = chip;
    else if (chip2 == -1) chip2 = chip;
}
