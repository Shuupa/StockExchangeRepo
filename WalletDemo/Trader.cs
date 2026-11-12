using System;

namespace StockExchangeCSharp;

public sealed class Trader
{
    public string Name { get; }

    private readonly Portfolio _portfolio; // агрегация: портфель создан снаружи и живет без трейдера

    public Trader(string name, Portfolio portfolio)
    {
        if (string.IsNullOrWhiteSpace(name))
            throw new ArgumentException("Trader name cannot be empty", nameof(name));

        Name = name;
        _portfolio = portfolio ?? throw new ArgumentNullException(nameof(portfolio));

        Console.WriteLine($"Trader created: {Name}");
    }

    public void BuyIfGrowth(Stock stock, double forecastPrice, int quantity)
    {
        ArgumentNullException.ThrowIfNull(stock);
        CheckForecast(forecastPrice);

        if (forecastPrice > stock.Price)
        {
            Console.WriteLine($"{Name}: growth expected for {stock.Ticker}, buying");
            _portfolio.BuyStock(stock, quantity);
        }
        else
        {
            Console.WriteLine($"{Name}: no growth expected for {stock.Ticker}, not buying");
        }
    }

    public void SellIfDrop(Stock stock, double forecastPrice, int quantity)
    {
        ArgumentNullException.ThrowIfNull(stock);
        CheckForecast(forecastPrice);

        if (forecastPrice < stock.Price)
        {
            Console.WriteLine($"{Name}: drop expected for {stock.Ticker}, selling");
            _portfolio.SellStock(stock, quantity);
        }
        else
        {
            Console.WriteLine($"{Name}: no drop expected for {stock.Ticker}, not selling");
        }
    }

    private static void CheckForecast(double forecastPrice)
    {
        if (double.IsNaN(forecastPrice) || double.IsInfinity(forecastPrice) || forecastPrice <= 0.0)
            throw new ArgumentException("Forecast price must be positive", nameof(forecastPrice));
    }

    public override string ToString() => $"Trader: {Name}";
}
