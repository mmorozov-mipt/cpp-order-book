#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <deque>
#include <iostream>

enum class Side {
    Buy,
    Sell
};

struct Order {
    long id;
    Side side;
    double price;
    long quantity;
};

struct MatchResult {
    long long matched_volume = 0;
};

class OrderBook {
public:
    OrderBook() : next_id_(1) {}

    // Добавить лимитную заявку. Возвращает её ID.
    long add_limit_order(Side side, double price, long quantity, MatchResult* result = nullptr);

    // Напечатать состояние стакана.
    void print_book(std::ostream& os = std::cout) const;

private:
    // BID: максимальная цена первая
    std::map<double, std::deque<Order>, std::greater<double>> bids_;
    // ASK: минимальная цена первая
    std::map<double, std::deque<Order>, std::less<double>> asks_;

    long next_id_;

    void match_buy(double price, long& quantity, MatchResult& result);
    void match_sell(double price, long& quantity, MatchResult& result);
};

#endif // ORDER_BOOK_H
