//
//  Day24.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/31/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day24.h"

Day24::Day24() {
    puts("Running Day 24 - a");

    int maxX = 0, maxY = 0;

    FileUtil::parse(24, [&](const string& line) {
        maxX = (int)line.length(); // should be the same for every line.
        for (int x = 0; x < maxX; ++x)
            blueprint[make_pair(x, maxY)] = new Location(x, maxY, line[x]);
        ++maxY;
    });

    // Print the map.

    for (int y = 0; y < maxY; ++y) {
        for (int x = 0; x < maxX; ++x)
            cout << blueprint[make_pair(x, y)]->printChar();
        cout << endl;
    }

    // Okay, so I've parsed the map. Next I have to identify all of the locations I need to visit.

    for (auto entry : blueprint)
        if (entry.second->isPointOfInterest())
            pointsOfInterest.push_back(entry.second);

    // Sort the POIs just to make my life debugging easier.

    sort(pointsOfInterest.begin(), pointsOfInterest.end(), [](Location* a, Location* b) {
        return a->interestPointId < b->interestPointId;});

    // Print the POIs.

    for (auto poi : pointsOfInterest)
        cout << "Point of Interest " << poi->interestPointId << " is at (" << poi->point.first << "," << poi->point.second << ")" << endl;

    // Now that I know where all the locations I need to visit are, I need to find the shortest path between each one.
    // This is what Day13 was all about.

    for (auto poi1 : pointsOfInterest)
        for (auto poi2 : pointsOfInterest)
            if (poi1 != poi2)
                // Find the shortest distance between these two locations and store it.
                findShortestDistance(poi1, poi2);
}

void Day24::findShortestDistance(Location* a, Location* b) const {

    Location* start = a;
    Location* end = nullptr;

    map<Point, Location*> inbox;
    map<Point, Location*> outbox;
    inbox.emplace(start->point, start);

    while (end == nullptr && !inbox.empty()) {
        Location* l = findNext(inbox);
        inbox.erase(l->point);
        outbox.emplace(l->point, l);

        if (l->point == b->point) {
            end = l;
            break;
        }

        // Get the neighbors.
    }
}

Location* Day24::findNext(const map<Point, Location*> &inbox) const {
    return nullptr;
}

void Day24::getNeighbors(Point p, set<Location*> &outSet) const {
    if (p.first - 1 >= 0 && blueprint[make_pair(p.first - 1, p.second)]->isTraversable())
        outSet.emplace(<#_Args &&__args...#>)
}
