class BrowserHistory {
private:
    vector<string> history;
    int currentIndex;

public:
    BrowserHistory(string homepage) {
        history.push_back(homepage);
        currentIndex = 0;
    }
    
    void visit(string url) {
        history.erase(history.begin() + currentIndex + 1, history.end());
        history.push_back(url);
        currentIndex = history.size() - 1;
    }
    
    string back(int steps) {
        currentIndex = max(0, currentIndex - steps);
        return history[currentIndex];
    }
    
    string forward(int steps) {
        currentIndex = min((int)history.size() - 1, currentIndex + steps);
        return history[currentIndex];
    }
};
