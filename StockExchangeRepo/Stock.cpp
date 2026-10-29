#include "Stock.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

Stock::Stock(const std::string& ticker, double price)
    : ticker(ticker), price(price)
{
    if (ticker.empty()) {
        throw std::invalid_argument("Ticker cannot be empty");
    }

    if (!std::isfinite(price) || price <= 0.0) {
        throw std::invalid_argument("Stock price must be positive");
    }

    std::cout << "Stock created: " << this->ticker << '\n';
}

Stock::~Stock()
{
    std::cout << "Stock destroyed: " << ticker << '\n';
}

std::string Stock::getTicker() const
{
    return ticker;
}

double Stock::getPrice() const
{
    return price;
}

void Stock::setPrice(double newPrice)
{
    if (!std::isfinite(newPrice) || newPrice <= 0.0) {
        throw std::invalid_argument("Stock price must be positive");
    }

    price = newPrice;
}

void Stock::printInfo() const
{
    std::cout << "Ticker: " << ticker
        << ", price: " << price << '\n';
}