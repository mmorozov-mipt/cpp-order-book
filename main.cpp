#include "order_book.h"

int main() {
    OrderBook book;

    std::cout << "Initial state:\n";
    book.print_book();
    std::cout << "---------------------\n";

    MatchResult r1;
    std::cout << "Add BUY 50 @ 100.0\n";
    book.add_limit_order(Side::Buy, 100.0, 50, &r1);

    std::cout << "Add BUY 40 @ 99.5\n";
    book.add_limit_order(Side::Buy, 99.5, 40, &r1);

    std::cout << "Add SELL 30 @ 101.0\n";
    book.add_limit_order(Side::Sell, 101.0, 30, &r1);

    std::cout << "Add SELL 20 @ 102.0\n";
    book.add_limit_order(Side::Sell, 102.0, 20, &r1);

    std::cout << "Book after initial orders:\n";
    book.print_book();
    std::cout << "---------------------\n";

    MatchResult r2;
    std::cout << "Add BUY 60 @ 101.0 (aggressive)\n";
    book.add_limit_order(Side::Buy, 101.0, 60, &r2);
    std::cout << "Matched volume: " << r2.matched_volume << "\n";

    std::cout << "Final book:\n";
    book.print_book();

    return 0;
}
