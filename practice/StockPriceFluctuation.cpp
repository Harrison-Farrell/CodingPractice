// System includes
#include <algorithm>
#include <map>
#include <set>
#include <limits.h>

// Project includes
#include <spdlog/spdlog.h>

// three, five, zero rule.
//    destructor
//    copy constructor
//    move constructor
//    copy assignment operator
//    move assignment operator

class StockPrice
{
    public:
    // contrusctor
    StockPrice(){};

    ~StockPrice() = default;

    StockPrice(StockPrice& copy_constructor) = delete;
    StockPrice(StockPrice&& move_constructor) = delete;

    StockPrice& operator=(StockPrice&& move_assignment) = delete;
    StockPrice& operator=(StockPrice& copy_assignment) = delete;

    // Updates the price of the stock at the given timestamp
    // param[in] timestamp
    // param[in] price
    // param[out] void
    void update(int timestamp, int price)
    {
        spdlog::debug("Update timestamp:{}\tPrice:{}", timestamp, price);

        if(m_stockRecords.count(timestamp))
        {
            m_stockPrices.erase(m_stockRecords[timestamp]);
        }

        m_stockRecords[timestamp] = price;
        m_stockPrices.insert(price);

        spdlog::debug("Updated the Records. Maximum:Minium:Current:\t{}:{}:{}",
        maximum(), minimum(), current());
    }

    // Returns the latest price of the stock.
    // param[out] price
    int current()
    {
        // return largest timestamp price
        return m_stockRecords.rbegin()->second;
    }

    // Returns the maximum price of the stock.
    // param[out] price
    int maximum()
    {
        // dereference the largest of the price set
        return *m_stockPrices.rbegin();
    }

    // Returns the minimum price of the stock.
    // param[out] price
    int minimum()
    {
        // dereference the smallest of the price set
        return *m_stockPrices.begin();
    }

    private:
    // map<timestamp, price>
    std::map<int, int> m_stockRecords;
    // multiset<price>
    std::multiset<int> m_stockPrices;
};


int main(int argc, char** argv)
{
    // spdlog::set_level(spdlog::level::debug);

    StockPrice stockPrice = StockPrice();
    stockPrice.update(1, 10);                                   // Timestamps are [1] with corresponding prices [10].
    stockPrice.update(2, 5);                                    // Timestamps are [1,2] with corresponding prices [10,5].
    spdlog::info("Current Price: {}", stockPrice.current());    // return 5, the latest timestamp is 2 with the price being 5.
    spdlog::info("Maximum Price: {}", stockPrice.maximum());    // return 10, the maximum price is 10 at timestamp 1.                      
    stockPrice.update(1, 3);                                    // The previous timestamp 1 had the wrong price, so it is updated to 3.
    spdlog::info("Maximum Price: {}", stockPrice.maximum());    // return 5, the maximum price is 5 after the correction.
    stockPrice.update(4, 2);                                    // Timestamps are [1,2,4] with corresponding prices [3,5,2].
    spdlog::info("Minimum Price: {}", stockPrice.minimum());    // return 2, the minimum price is 2 at timestamp 4.

    return 0;
}