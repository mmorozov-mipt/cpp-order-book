# C++ Order Book Simulator

This project implements a simplified limit order book simulator in C++ similar to real exchange engines used in algorithmic and high-frequency trading systems.

The simulator supports:
- adding limit orders
- matching buy and sell orders
- partial execution
- cancellation of orders
- maintaining best bid/ask prices
- execution statistics

The main goal of the project is to demonstrate skills in:
- modern C++
- data structures and algorithms
- low-latency system design basics
- working with real-time trading models

## Project structure

order_book.h — implementation of order book class  
main.cpp — example of engine usage and basic testing  

## Features

- price–time priority
- separate bid/ask books
- support of multiple orders at same price level
- efficient matching algorithm
- minimal dynamic memory usage approach

## How to build

Requires any modern C++ compiler (gcc / clang / MSVC).

Compile:

g++ -std=c++17 main.cpp order_book.cpp -o order_book

Run:

./order_book

## Example use cases

- educational demonstration of exchange mechanics
- foundation for HFT / trading interview tasks
- prototype for backtesting trading strategies
- supporting project for C++ portfolio

## Disclaimer

This project is intended for educational and research purposes only
and does not constitute trading advice or a real trading system.
