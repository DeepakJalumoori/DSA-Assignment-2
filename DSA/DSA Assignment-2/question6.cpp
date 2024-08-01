class StockSpanner {
private:
    stack<pair<int, int>> priceStack;

public:
    StockSpanner() {}

    int next(int price) {
        int span = 1;
        
        while (!priceStack.empty() && priceStack.top().first <= price) {
            span += priceStack.top().second;
            priceStack.pop();
        }
        
        priceStack.push({price, span});
        
        return span;
    }
};