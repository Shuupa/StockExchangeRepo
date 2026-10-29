#pragma once

#include "Portfolio.hpp"
#include "Stock.hpp"

#include <string>

class Trader {
private:
    std::string name;
    Portfolio& portfolio;

public:
    Trader(const std::string& name, Portfolio& portfolio);
    ~Trader();

    void buyIfGrowth(const Stock& stock, double forecastPrice, int quantity);
    void sellIfDrop(const Stock& stock, double forecastPrice, int quantity);
    void printInfo() const;
};