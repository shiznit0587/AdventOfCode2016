//
//  Day14.cpp
//  AdventOfCode2016
//
//  Created by Philip Stachowski on 12/19/16.
//  Copyright © 2016 Philip Stachowski. All rights reserved.
//

#include "Day14.h"

static const string SALT = "ihaygndm";

struct Key {
    int index;
    string hash;
    char character;
    Key() {}
    Key(const Key& k) : index(k.index), hash(k.hash), character(k.character) {}
    Key(int pIdx, string pHash, char pChar) : index(pIdx), hash(pHash), character(pChar) {}
    bool operator == (const Key& k) const { return index == k.index && hash == k.hash && character == k.character; }
    bool operator < (const Key& k) const { return index < k.index; }
};

Day14::Day14() {
    puts("Running Day 14 - a");

    int indexA = get64thKeyIndex([](int index) { return MD5(SALT + to_string(index)).hexdigest();});

    cout << "64th Key Index = " << indexA << endl;
    puts("Running Day 14 - b");

    int indexB = get64thKeyIndex([](int index) {
        string hash = MD5(SALT + to_string(index)).hexdigest();
        for (int i = 0; i < 2016; ++i) hash = MD5(hash).hexdigest();
        return hash;
    });

    cout << "64th Key Index = " << indexB << endl;
}

int Day14::get64thKeyIndex(const function<string (int)>& generator) {
    int index = 0;
    vector<Key> candidates;
    vector<Key> keys;
    int endIndex = INT_MAX;

    while (index <= endIndex) {
        string hash = generator(index);

        for (int i = 0; i < hash.size() - 2; ++i)
            if (hash[i] == hash[i+1] && hash[i+1] == hash[i+2]) {
                candidates.push_back({index, hash, hash[i]});
                break;
            }

        vector<Key> removals;
        set<int> removalIdxs;
        for (const Key& candidate : candidates)
            for (int i = 0; i < hash.size() - 4; ++i)
                if (candidate.index != index &&
                    removalIdxs.find(candidate.index) == removalIdxs.end() &&
                    hash[i] == candidate.character &&
                    hash[i+1] == candidate.character &&
                    hash[i+2] == candidate.character &&
                    hash[i+3] == candidate.character &&
                    hash[i+4] == candidate.character) {

                    keys.emplace_back(candidate);
                    removals.emplace_back(candidate);
                    removalIdxs.insert(candidate.index);

                    if (keys.size() == 64) endIndex = index + 1000;
                }

        auto newEnd = remove_if(candidates.begin(), candidates.end(), [&](const Key& c){return (find(removals.begin(), removals.end(), c) != removals.end());});
        candidates.erase(newEnd, candidates.end());

        newEnd = remove_if(candidates.begin(), candidates.end(), [&](const Key& c){return (c.index + 1000 < index);});
        candidates.erase(newEnd, candidates.end());

        ++index;
    }

    sort(keys.begin(), keys.end());

    return keys[63].index;
}
