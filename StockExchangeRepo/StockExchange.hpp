#pragma once

#include "ForecastModel.hpp"

#include <string>

class StockExchange {
private:
    std::string name;
    ForecastModel model;

public:
    StockExchange(const std::string& name, const Stock& stock);
    ~StockExchange();

    void showForecast(double changePercent) const;
    void printInfo() const;
};