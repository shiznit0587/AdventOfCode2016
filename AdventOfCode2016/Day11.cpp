//
//  Day11.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/12/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day11.h"

//static const char NUM_ITEMS = 4;
//static const char NUM_ITEMS = 10;
static const char NUM_ITEMS = 14;
static const char NUM_FLOORS = 4;
static const char TOP_FLOOR = NUM_FLOORS - 1;
//static const string ITEM_NAMES[NUM_ITEMS] = {"HG", "HM", "LG", "LM"};
//static const string ITEM_NAMES[NUM_ITEMS] = {"PG", "PM", "TG", "TM", "pG", "pM", "RG", "RM", "CG", "CM"};
static const string ITEM_NAMES[NUM_ITEMS] = {"PG", "PM", "TG", "TM", "pG", "pM", "RG", "RM", "CG", "CM", "EG", "EM", "DG", "DM"};

struct State
{
private:
    static const char BITS_PER_FIELD = 2;
    static const char FIELD_MASK = 3;
    int s = 0;
    // __EEDDCCBBAA99887766554433221100, with each pair of bits being an item's floor (0-3)

    list<int> prev; // For each state, I'm keeping a copy of all previous states up to this one.

    void addStatesForItemAtFloor(char floor, const set<char>& items, set<State>& outSet) const {
        for (const char item : items) {
            // Add a state for moving this item to the new floor.
            State newState = makeNext();
            newState.setFloor(floor);
            newState.moveItemToFloor(item, floor);
            outSet.insert(newState);

            for (const char item2 : items)
                if (item != item2) {
                    // Add a state for moving these two items to the new floor.
                    State newState2 = makeNext();
                    newState2.setFloor(floor);
                    newState2.moveItemToFloor(item, floor);
                    newState2.moveItemToFloor(item2, floor);
                    outSet.insert(newState2);
                }
        }
    }

    State makeNext() const {
        State next = State(*this);
        next.prev.push_back(s);
        return next;
    }

public:
    State() {};

    State(State const &pS) {
        s = pS.s;
        for (int state : pS.prev)
            prev.push_back(state);
    }

    State(int pS) {
        s = pS;
    }

    inline void moveItemToFloor(char item, char floor) {
        // Clear item's current floor, then set it to the new one.
        s = (s & ~(FIELD_MASK << (item * BITS_PER_FIELD))) | ((floor & FIELD_MASK) << (item * BITS_PER_FIELD));
    }

    inline bool isItemOnFloor(char item, char floor) const {
        return (s & (FIELD_MASK << (item * BITS_PER_FIELD))) == ((floor & FIELD_MASK) << (item * BITS_PER_FIELD));
    }

    inline char getItemFloor(char item) const {
        return (s & (FIELD_MASK << (item * BITS_PER_FIELD))) >> (item * BITS_PER_FIELD);
    }

    inline char getFloor() const { return (s >> 28) & FIELD_MASK; }
    inline void setFloor(char floor) { moveItemToFloor(14, floor); }

    inline const list<int>& getPrev() const { return prev; }

    void getNextStates(set<State>& outSet) const {
        set<char> items;
        char floor = getFloor();

        for (char i = 0; i < NUM_ITEMS; ++i)
            if (isItemOnFloor(i, floor))
                items.insert(i);

        if (floor != 0)
            addStatesForItemAtFloor(floor - 1, items, outSet);

        if (floor != TOP_FLOOR)
            addStatesForItemAtFloor(floor + 1, items, outSet);
    }

    bool isValid() const {
        for (char i = 0; i < NUM_FLOORS; ++i) {
            bool hasGenerator = false;
            // Even items are generators. Odd items are microchips.
            for (char j = 0; j < NUM_ITEMS; j += 2)
                if (isItemOnFloor(j, i))
                    hasGenerator = true;

            if (hasGenerator)
                // Check that for each microchip, the corresponding generator is present.
                for (char j = 1; j < NUM_ITEMS; j += 2)
                    if (isItemOnFloor(j, i) && !isItemOnFloor(j - 1, i))
                       return false;
        }

        return true;
    }

    bool isComplete() const {
        // A complete state is one in which all items and the elevator are on floor 3.
        //return (s & 0x300000FF) == 0x300000FF;
        //return (s & 0x300FFFFF) == 0x300FFFFF;
        return (s & 0x3FFFFFFF) == 0x3FFFFFFF;
    }

    void print() const {
        for (char i = TOP_FLOOR; i >= 0; --i) {
            cout << "F" << (i+1) << " ";
            if (getFloor() == i) cout << "E  ";
            else cout << ".  ";
            for (char j = 0; j < NUM_ITEMS; ++j)
                if (isItemOnFloor(j, i)) cout << ITEM_NAMES[j] << " ";
                else cout << ".  ";
            cout << endl;
        }
        cout << endl;
    }

    bool operator <  (const State &rhs) const { return prev.size() != rhs.prev.size() ? prev.size() < rhs.prev.size() : s <  rhs.s; }
    bool operator == (const State &rhs) const { return prev.size() == rhs.prev.size() && s == rhs.s; }

    // This is only used for determining if this state's been visited yet.
    // Two states are similar if the elevator is on the same floor and they have the same number of part pairs, lone generators, and lone microchips on each floor.
    // 38 of the 64 bits used. 9 for each floor and 2 for the elevator. For each floor, 3 for the count of part pairs, 3 for the count of single generators, and 3 for the count of single microchips.
    operator long() const {
        char items[NUM_FLOORS][3] = {};
        for (char i = 0; i < NUM_ITEMS; i += 2) {
            char generatorFloor = getItemFloor(i);
            char microchipFloor = getItemFloor(i + 1);
            if (generatorFloor == microchipFloor)
                items[generatorFloor][0]++;
            else {
                items[generatorFloor][1]++;
                items[microchipFloor][2]++;
            }
        }

        long floors[NUM_FLOORS] = {};
        for (char i = 0; i < NUM_FLOORS; ++i)
            floors[i] = (items[i][0] << 6) | (items[i][1] << 3) | (items[i][2]); // PAI-GEN-MIC

        // ________ ________ ________ __EE3333 33333222 22222211 11111110 00000000
        return ((long)getFloor() << 36) | (floors[3] << 27) | (floors[2] << 18) | (floors[1] << 9) | (floors[0]);
    }
};

Day11::Day11() {
    puts("Running Day 11 - a");

    State start;
    State* end = nullptr;

    /*
     F4 .  .  .  .  .
     F3 .  .  .  LG .
     F2 .  HG .  .  .
     F1 E  .  HM .  LM
    */
    //start.moveItemToFloor(0, 1);
    //start.moveItemToFloor(1, 0);
    //start.moveItemToFloor(2, 2);
    //start.moveItemToFloor(3, 0);

    /*
     F4 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
     F3 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
     F2 .  .  PM .  .  .  pM .  .  .  .  .  .  .  .
     F1 E  PG .  TG TM pG .  RG RM CG CM EG EM DG DM
    */
    start.moveItemToFloor(0, 0);
    start.moveItemToFloor(1, 1);
    start.moveItemToFloor(2, 0);
    start.moveItemToFloor(3, 0);
    start.moveItemToFloor(4, 0);
    start.moveItemToFloor(5, 1);
    start.moveItemToFloor(6, 0);
    start.moveItemToFloor(7, 0);
    start.moveItemToFloor(8, 0);
    start.moveItemToFloor(9, 0);
    start.moveItemToFloor(10, 0);
    start.moveItemToFloor(11, 0);
    start.moveItemToFloor(12, 0);
    start.moveItemToFloor(13, 0);

    set<long> visited;
    queue<State> inbox;

    visited.insert(start);
    inbox.push(start);

    while (end == nullptr && !inbox.empty()) {
        State s = inbox.front(); // copy before popping, so that the prev list nodes don't get scoped out. (WHY DOES THIS HAPPEN???)
        inbox.pop();

        if (s.isComplete()) {
            end = new State(s); // We 'new' here for the same reason we copy above.
            break;
        }

        set<State> nextStates;
        s.getNextStates(nextStates);

        set<State> unvisited;
        for (const State& state : nextStates)
            if (visited.find(state) == visited.end()) {
                unvisited.insert(state);
                visited.insert(state);
            }

        for (const State& state : unvisited)
            if (state.isValid())
                inbox.push(state);
    }

    if (end != nullptr) {
        cout << endl << "Solution Found!" << endl << endl;

        for (const State& state : end->getPrev())
            state.print();
        end->print();

        cout << "# Steps = " << end->getPrev().size() << endl;
    }
    else
        cout << "No Solution Found" << endl;
}
