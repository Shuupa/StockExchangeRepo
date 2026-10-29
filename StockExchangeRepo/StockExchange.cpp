#include "StockExchange.hpp"

#include <iostream>
#include <stdexcept>

StockExchange::StockExchange(
    const std::string& name,
    const Stock& stock
)
    : name(name), model(stock)
{
    if (name.empty()) {
        throw std::invalid_argument(
            "Exchange name cannot be empty"
        );
    }

    std::cout << "StockExchange created: "
        << this->name << '\n';
}

StockExchange::~StockExchange()
{
    std::cout << "StockExchange destroyed: "
        << name << '\n';
}

void StockExchange::showForecast(double changePercent) const
{
    std::cout << "Exchange: " << name << '\n';
    model.printForecast(changePercent);
}

void StockExchange::printInfo() const
{
    std::cout << "Stock exchange: " << name << '\n';
}