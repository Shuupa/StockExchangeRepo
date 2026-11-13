#pragma once

#include "Portfolio.hpp"
#include "Stock.hpp"

#include <memory>
#include <string>

class Trader {
private:
    std::string name;
    std::shared_ptr<Portfolio> portfolio;

public:
    Trader(const std::string& name, std::shared_ptr<Portfolio> portfolio);
    ~Trader();

    void buyIfGrowth(const Stock& stock, double forecastPrice, int quantity);
    void sellIfDrop(const Stock& stock, double forecastPrice, int quantity);
    void printInfo() const;
};