class LRUCache {
private:
    int capacity;
    unordered_map<int, pair<int, list<int>::iterator>> cache;
    list<int> order; 

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;
        order.splice(order.begin(), order, cache[key].second);
        return cache[key].first;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            cache[key].first = value;
            order.splice(order.begin(), order, cache[key].second);
            return;
        }
        if (cache.size() == capacity) {
            int lru = order.back();
            order.pop_back();
            cache.erase(lru);
        }
        order.push_front(key);
        cache[key] = {value, order.begin()};
    }
};
