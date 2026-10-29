#include "Portfolio.hpp"

#include <iostream>
#include <stdexcept>

Portfolio::Portfolio(const std::string& name, double startBalance)
    : name(name), wallet(startBalance)
{
    if (name.empty()) {
        throw std::invalid_argument("Portfolio name cannot be empty");
    }

    std::cout << "Portfolio created: " << this->name << '\n';
}

Portfolio::~Portfolio()
{
    std::cout << "Portfolio destroyed: " << name << '\n';
}

int Portfolio::getShares(const std::string& ticker) const
{
    auto item = shares.find(ticker);

    if (item == shares.end()) {
        return 0;
    }

    return item->second;
}

void Portfolio::buyStock(const Stock& stock, int quantity)
{
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be positive");
    }

    const double cost = stock.getPrice() * quantity;

    if (cost > wallet.getBalance()) {
        throw std::invalid_argument("Not enough money to buy shares");
    }

    wallet.withdraw(cost);
    shares[stock.getTicker()] += quantity;

    std::cout << "Bought " << quantity << " x " << stock.getTicker()
        << " for " << cost << '\n';
}

void Portfolio::sellStock(const Stock& stock, int quantity)
{
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be positive");
    }

    if (quantity > getShares(stock.getTicker())) {
        throw std::invalid_argument("Cannot sell more shares than owned");
    }

    const double income = stock.getPrice() * quantity;

    wallet.deposit(income);
    shares[stock.getTicker()] -= quantity;

    std::cout << "Sold " << quantity << " x " << stock.getTicker()
        << " for " << income << '\n';
}

void Portfolio::printInfo() const
{
    std::cout << "Portfolio: " << name << '\n';
    wallet.printInfo();

    for (const auto& item : shares) {
        std::cout << "  " << item.first << ": "
            << item.second << " shares\n";
    }
}