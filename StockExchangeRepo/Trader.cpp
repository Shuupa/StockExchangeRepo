#include "Trader.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

Trader::Trader(const std::string& name, Portfolio& portfolio)
    : name(name), portfolio(portfolio)
{
    if (name.empty()) {
        throw std::invalid_argument("Trader name cannot be empty");
    }

    std::cout << "Trader created: " << this->name << '\n';
}

Trader::~Trader()
{
    std::cout << "Trader destroyed: " << name << '\n';
}

void Trader::buyIfGrowth(const Stock& stock, double forecastPrice, int quantity)
{
    if (!std::isfinite(forecastPrice) || forecastPrice <= 0.0) {
        throw std::invalid_argument("Forecast price must be positive");
    }

    if (forecastPrice > stock.getPrice()) {
        std::cout << name << ": growth expected for "
            << stock.getTicker() << ", buying\n";
        portfolio.buyStock(stock, quantity);
    }
    else {
        std::cout << name << ": no growth expected for "
            << stock.getTicker() << ", not buying\n";
    }
}

void Trader::sellIfDrop(const Stock& stock, double forecastPrice, int quantity)
{
    if (!std::isfinite(forecastPrice) || forecastPrice <= 0.0) {
        throw std::invalid_argument("Forecast price must be positive");
    }

    if (forecastPrice < stock.getPrice()) {
        std::cout << name << ": drop expected for "
            << stock.getTicker() << ", selling\n";
        portfolio.sellStock(stock, quantity);
    }
    else {
        std::cout << name << ": no drop expected for "
            << stock.getTicker() << ", not selling\n";
    }
}

void Trader::printInfo() const
{
    std::cout << "Trader: " << name << '\n';
}