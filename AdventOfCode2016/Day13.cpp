//
//  Day13.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/16/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

static const int INPUT = 1364;
static const int DEST_X = 31;
static const int DEST_Y = 39;

#include "Day13.h"

struct Node {
    Position pos = make_pair(0, 0);
    int distance = 0;
    Node(Position pPos) : pos(pPos) {}
    Node(Position pPos, int pDist) : pos(pPos), distance(pDist) {}
};

Day13::Day13() {
    puts("Running Day 13 - a");

    Node* start = new Node(make_pair(1, 1));
    const Node* end = nullptr;

    NodeMap inbox;
    NodeMap outbox;
    inbox.emplace(start->pos, start);

    while (end == nullptr && !inbox.empty()) {
        Node* n = findNext(inbox);
        inbox.erase(n->pos);
        outbox.emplace(n->pos, n);

        if (n->pos.first == DEST_X && n->pos.second == DEST_Y) {
            end = n;
            break;
        }

        set<Position> neighbors;
        getNeighbors(n->pos.first, n->pos.second, neighbors);

        for (const Position& neighbor : neighbors) {
            if (outbox.find(neighbor) == outbox.end()) {
                auto inboxEntry = inbox.find(neighbor);
                if (inboxEntry != inbox.end()) {
                    if (inboxEntry->second->distance > n->distance + 1)
                        inboxEntry->second->distance = n->distance + 1;
                }
                else
                    inbox.emplace(neighbor, new Node(neighbor, n->distance + 1));
            }
        }
    }

    cout << "Number of Steps = " << end->distance << endl;
    puts("Running Day 13 - b");

    inbox.clear();
    outbox.clear();

    inbox.emplace(start->pos, start);

    while (!inbox.empty()) {
        Node* n = findNext(inbox); // FIXME: I got the right answer, but this is incorrectly using A*
        inbox.erase(n->pos);
        outbox.emplace(n->pos, n);

        if (n->distance >= 50)
            continue;

        set<Position> neighbors;
        getNeighbors(n->pos.first, n->pos.second, neighbors);

        for (const Position& neighbor : neighbors) {
            if (outbox.find(neighbor) == outbox.end()) {
                auto inboxEntry = inbox.find(neighbor);
                if (inboxEntry != inbox.end()) {
                    if (inboxEntry->second->distance > n->distance + 1)
                        inboxEntry->second->distance = n->distance + 1;
                }
                else
                    inbox.emplace(neighbor, new Node(neighbor, n->distance + 1));
            }
        }
    }

    cout << "Number of Locations = " << outbox.size() << endl;
}

Node* Day13::findNext(const NodeMap inbox) {
    int bestScore = INT_MAX;
    Node* bestNode = nullptr;
    for (auto node : inbox) {
        int aStar = node.second->distance + (abs(DEST_X - node.second->pos.first) + abs(DEST_Y - node.second->pos.second));
        if (aStar < bestScore) {
            bestScore = aStar;
            bestNode = node.second;
        }
    }
    return bestNode;
}

void Day13::getNeighbors(int x, int y, set<Position>& outSet) {
    if (x - 1 >= 0 && isEmptySpace(x-1, y)) outSet.emplace(make_pair(x-1, y));
    if (y - 1 >= 0 && isEmptySpace(x, y-1)) outSet.emplace(make_pair(x, y-1));
    if (isEmptySpace(x, y+1)) outSet.emplace(make_pair(x, y+1));
    if (isEmptySpace(x+1, y)) outSet.emplace(make_pair(x+1, y));
}

bool Day13::isEmptySpace(int x, int y) {
    long num = x*x + 3*x + 2*x*y + y + y*y + INPUT;
    int count = 0;

    while (num != 0) {
        count += (num & 1);
        num >>= 1;
    }

    return (count & 1) == 0;
}
