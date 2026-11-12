using System;

namespace StockExchangeCSharp;

public sealed class StockExchange
{
    public string Name { get; }

    private readonly ForecastModel _model; // композиция: часть создается внутри

    public StockExchange(string name, Stock stock)
    {
        if (string.IsNullOrWhiteSpace(name))
            throw new ArgumentException("Exchange name cannot be empty", nameof(name));

        Name = name;
        _model = new ForecastModel(stock ?? throw new ArgumentNullException(nameof(stock)));

        Console.WriteLine($"StockExchange created: {Name}");
    }

    public void ShowForecast(double changePercent)
    {
        Console.WriteLine($"Exchange: {Name}");
        _model.PrintForecast(changePercent);
    }

    public void PrintInfo()
    {
        Console.WriteLine($"Stock exchange: {Name}");
    }
}
