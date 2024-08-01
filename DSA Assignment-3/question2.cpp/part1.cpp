#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class OpenAddressingHashMap {
private:
    vector<pair<int, int>> table;
    vector<bool> deleted;
    int capacity;
    int size;

    int hash(int key) {
        return key % capacity;
    }

public:
    OpenAddressingHashMap(int cap) : capacity(cap), size(0) {
        table.resize(capacity, {-1, -1});
        deleted.resize(capacity, false);
    }

    bool find(int key) {
        int index = hash(key);
        int start = index;
        while (table[index].first != -1) {
            if (table[index].first == key && !deleted[index]) {
                return true;
            }
            index = (index + 1) % capacity;
            if (index == start) break;
        }
        return false;
    }

    void insert(int key, int value) {
        if (find(key)) {
            // Key exists, update the value
            int index = hash(key);
            int start = index;
            while (table[index].first != key) {
                index = (index + 1) % capacity;
                if (index == start) return;
            }
            table[index].second = value;
        } else {
            int index = hash(key);
            int start = index;
            while (table[index].first != -1 && !deleted[index]) {
                index = (index + 1) % capacity;
                if (index == start) return;
            }
            table[index] = {key, value};
            deleted[index] = false;
            size++;
        }
    }

    void remove(int key) {
        int index = hash(key);
        int start = index;
        while (table[index].first != -1) {
            if (table[index].first == key && !deleted[index]) {
                deleted[index] = true;
                size--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == start) return;
        }
    }
};
