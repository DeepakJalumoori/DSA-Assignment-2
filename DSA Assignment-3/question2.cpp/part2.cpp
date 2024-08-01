#include <iostream>
#include <vector>
#include <list>

using namespace std;

class SeparateChainingHashMap {
private:
    vector<list<pair<int, int>>> table;
    int capacity;

    int hash(int key) {
        return key % capacity;
    }

public:
    SeparateChainingHashMap(int cap) : capacity(cap) {
        table.resize(capacity);
    }

    bool find(int key) {
        int index = hash(key);
        for (const auto& entry : table[index]) {
            if (entry.first == key) {
                return true;
            }
        }
        return false;
    }

    void insert(int key, int value) {
        int index = hash(key);
        for (auto& entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
    }

    void remove(int key) {
        int index = hash(key);
        table[index].remove_if([key](const pair<int, int>& entry) {
            return entry.first == key;
        });
    }
};
