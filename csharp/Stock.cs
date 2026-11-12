using System;

namespace StockExchangeCSharp;

public class Stock : BaseAsset
{
    public string Ticker { get; }

    // 11. Статическое поле
    private static int _count;

    public Stock(string ticker, string title, double price) : base(title, price)
    {
        if (string.IsNullOrWhiteSpace(ticker)) throw new ArgumentException("Ticker cannot be empty");
        Ticker = ticker;
        _count++;
        Console.WriteLine($"Stock(): {Ticker}");
    }

    // 5. Конструктор копирования
    public Stock(Stock other) : base(other)
    {
        Ticker = other.Ticker;
    }

    // 11. Статический метод
    public static int GetStockCount() => _count;

    // 2. Реализация абстрактного метода
    public override double GetDailyYield() => 2.0;

    // 8. Переопределение с вызовом базового метода
    public override string Describe() => base.Describe() + $" [Тикер: {Ticker}]";

    // 10.2. Сравнение по содержимому (Equals и GetHashCode)
    public override bool Equals(object? obj)
    {
        if (obj is not Stock other) return false;
        return Ticker == other.Ticker;
    }

    public override int GetHashCode() => Ticker.GetHashCode();
}