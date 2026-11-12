using System;

namespace StockExchangeCSharp;

public sealed class ForecastModel
{
    private readonly Stock _stock; // агрегация: ссылка на объект, созданный снаружи

    public ForecastModel(Stock stock)
    {
        _stock = stock ?? throw new ArgumentNullException(nameof(stock));
        Console.WriteLine($"ForecastModel created for {_stock.Ticker}");
    }

    public double PredictPrice(double changePercent)
    {
        double multiplier = 1.0 + changePercent / 100.0;
        if (multiplier <= 0.0)
            throw new ArgumentException("Forecasted price must be positive", nameof(changePercent));

        return _stock.Price * multiplier;
    }

    public void PrintForecast(double changePercent)
    {
        Console.WriteLine($"Forecast for {_stock.Ticker} after {changePercent}% change: {PredictPrice(changePercent)}");
    }
}