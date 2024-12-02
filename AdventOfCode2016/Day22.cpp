//
//  Day22.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/30/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day22.h"

struct Node {
    int x, y, size, used, avail;
    Node(int pX, int pY, int pSize, int pUsed, int pAvail) : x(pX), y(pY), size(pSize), used(pUsed), avail(pAvail) {}
    bool operator < (const Node& n) const { return (y != n.y) ? y < n.y : x < n.x; }
};

struct State {
    int moves;
    pair<int,int> goal;
    pair<int,int> empty;
    list<Node> nodes;
};

Day22::Day22() {
    puts("Running Day 22 - a");

    set<Node> nodes;
    int largestX = 0;
    FileUtil::parse(22, [&](const string& line) {
        if (line[0] != '/') return;

        istringstream stream(line);
        char dc;
        string ds;
        int x, y, size, used, avail;

        getline(stream, ds, '-');
        stream >> dc >> x >> dc >> dc >> y >> size >> dc >> used >> dc >> avail;
        nodes.emplace(x, y, size, used, avail);

        if (x > largestX) largestX = x;
    });

    int pairs = 0;
    for (auto a : nodes)
        for (auto b: nodes)
            if (&a != &b && a.used > 0 && a.used <= b.avail) ++pairs;

    cout << "Viable Pairs = " << pairs << endl;
    puts("Running Day 22 - b");

    // [19,6] is empty, and can hold 93T. It looks like most of the drives have this kind of capacity.
    // [36,0] contains our goal data of 67T.
    // I need to move the goal data from [36,0] to [0,0]
    // This is like 15-puzzle, except it's 37x25 (924-puzzle) and I only care about the location of one tile, and some tiles can't be moved.
    // I've confirmed that all nodes are big enough to contain the goal data.
    // I should try printing the entire grid.

    int i = 0;
    for (auto n : nodes) {
        if (n.x == 0 && n.y == 0) cout << '(';
        else cout << ' ';

        if (n.used == 0) cout << '_';
        else if (n.x == largestX && n.y == 0) cout << 'G';
        else if (n.size > 100) cout << '#';
        else cout << '.';

        if (n.x == 0 && n.y == 0) cout << ')';
        else cout << ' ';

        if ((++i) % 37 == 0) cout << endl;
    }

    // I ended up printing the grid and counting by hand. The final solution was 236 moves.
    cout << "Fewest Steps = 236" << endl;
}
