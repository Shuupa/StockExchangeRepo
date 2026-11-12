using System;

namespace StockExchangeCSharp;

public sealed class Bond : BaseAsset // sealed запрещает наследование
{
    public double CouponRate { get; }

    public Bond(string title, double price, double couponRate) : base(title, price)
    {
        CouponRate = couponRate;
        Console.WriteLine($"Bond(): {title}");
    }

    // Конструктор копирования
    public Bond(Bond other) : base(other)
    {
        CouponRate = other.CouponRate;
    }

    public override double GetDailyYield() => CouponRate / 365.0;

    // 8. Переопределение без вызова базового
    public override string Describe() => $"Облигация: {Title}, купон: {CouponRate:F2}%";
}