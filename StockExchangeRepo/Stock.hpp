#pragma once

#include <string>

class Stock {
private:
    std::string ticker;
    double price;

public:
    Stock(const std::string& ticker, double price);
    ~Stock();

    std::string getTicker() const;
    double getPrice() const;

    void setPrice(double newPrice);
    void printInfo() const;
};