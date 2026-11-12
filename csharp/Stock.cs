using System;

namespace StockExchangeCSharp;

public sealed class Stock
{
    public string Ticker { get; }

    private double _price;
    public double Price
    {
        get => _price;
        private set
        {
            if (double.IsNaN(value) || double.IsInfinity(value) || value <= 0.0)
                throw new ArgumentException("Stock price must be positive", nameof(value));
            _price = value;
        }
    }

    public Stock(string ticker, double price)
    {
        if (string.IsNullOrWhiteSpace(ticker))
            throw new ArgumentException("Ticker cannot be empty", nameof(ticker));

        Ticker = ticker;
        Price = price; 

        Console.WriteLine($"Stock created: {Ticker}");
    }

    public void SetPrice(double newPrice) => Price = newPrice;

    public override string ToString() => $"Ticker: {Ticker}, price: {Price}";
}