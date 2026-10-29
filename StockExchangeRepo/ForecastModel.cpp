#include "ForecastModel.hpp"

#include <iostream>
#include <stdexcept>

ForecastModel::ForecastModel(const Stock& stock)
    : stock(stock)
{
    std::cout << "ForecastModel created for "
        << stock.getTicker() << '\n';
}

ForecastModel::~ForecastModel()
{
    std::cout << "ForecastModel destroyed for "
        << stock.getTicker() << '\n';
}

double ForecastModel::predictPrice(double changePercent) const
{
    const double multiplier = 1.0 + changePercent / 100.0;

    if (multiplier <= 0.0) {
        throw std::invalid_argument(
            "Forecasted price must be positive"
        );
    }

    return stock.getPrice() * multiplier;
}

void ForecastModel::printForecast(double changePercent) const
{
    std::cout << "Forecast for " << stock.getTicker()
        << " after " << changePercent << "% change: "
        << predictPrice(changePercent) << '\n';
}