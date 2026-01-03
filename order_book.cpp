#include "order_book.h"
#include <algorithm>

long OrderBook::add_limit_order(Side side, double price, long quantity, MatchResult* result_ptr) {
    MatchResult local_result;
    MatchResult& result = result_ptr ? *result_ptr : local_result;

    if (quantity <= 0) {
        return -1;
    }

    long order_id = next_id_++;

    if (side == Side::Buy) {
        match_buy(price, quantity, result);
        if (quantity > 0) {
            Order o{order_id, side, price, quantity};
            bids_[price].push_back(o);
        }
    } else {
        match_sell(price, quantity, result);
        if (quantity > 0) {
            Order o{order_id, side, price, quantity};
            asks_[price].push_back(o);
        }
    }

    return order_id;
}

void OrderBook::match_buy(double price, long& quantity, MatchResult& result) {
    // Мэчим покупку с лучшими асками
    while (quantity > 0 && !asks_.empty()) {
        auto best_ask_it = asks_.begin();
        double best_ask_price = best_ask_it->first;

        if (best_ask_price > price) {
            break;
        }

        auto& queue = best_ask_it->second;
        while (!queue.empty() && quantity > 0) {
            Order& top = queue.front();
            long traded = std::min(quantity, top.quantity);
            quantity -= traded;
            top.quantity -= traded;
            result.matched_volume += traded;

            if (top.quantity == 0) {
                queue.pop_front();
            }
        }

        if (queue.empty()) {
            asks_.erase(best_ask_it);
        }
    }
}

void OrderBook::match_sell(double price, long& quantity, MatchResult& result) {
    // Мэчим продажу с лучшими бидaми
    while (quantity > 0 && !bids_.empty()) {
        auto best_bid_it = bids_.begin();
        double best_bid_price = best_bid_it->first;

        if (best_bid_price < price) {
            break;
        }

        auto& queue = best_bid_it->second;
        while (!queue.empty() && quantity > 0) {
            Order& top = queue.front();
            long traded = std::min(quantity, top.quantity);
            quantity -= traded;
            top.quantity -= traded;
            result.matched_volume += traded;

            if (top.quantity == 0) {
                queue.pop_front();
            }
        }

        if (queue.empty()) {
            bids_.erase(best_bid_it);
        }
    }
}

void OrderBook::print_book(std::ostream& os) const {
    os << "ORDER BOOK\n";

    os << "  Asks:\n";
    for (const auto& [price, queue] : asks_) {
        long long total_qty = 0;
        for (const auto& o : queue) {
            total_qty += o.quantity;
        }
        os << "    " << price << " : " << total_qty << "\n";
    }

    os << "  Bids:\n";
    for (const auto& [price, queue] : bids_) {
        long long total_qty = 0;
        for (const auto& o : queue) {
            total_qty += o.quantity;
        }
        os << "    " << price << " : " << total_qty << "\n";
    }

    os << "\n";
}
