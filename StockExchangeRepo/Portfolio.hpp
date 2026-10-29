#pragma once

#include "Stock.hpp"
#include "Wallet.hpp"

#include <map>
#include <string>

class Portfolio {
private:
    std::string name;
    Wallet wallet;
    std::map<std::string, int> shares;

public:
    Portfolio(const std::string& name, double startBalance);
    ~Portfolio();

    int getShares(const std::string& ticker) const;

    void buyStock(const Stock& stock, int quantity);
    void sellStock(const Stock& stock, int quantity);
    void printInfo() const;
};