#pragma once

#include "Stock.hpp"

class ForecastModel {
private:
    const Stock& stock;

public:
    explicit ForecastModel(const Stock& stock);
    ~ForecastModel();

    double predictPrice(double changePercent) const;
    void printForecast(double changePercent) const;
};
