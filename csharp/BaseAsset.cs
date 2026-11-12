using System;

namespace StockExchangeCSharp;

public abstract class BaseAsset
{
    public string Title { get; }
    public double Price { get; protected set; }

    // 5. Конструктор с параметрами
    protected BaseAsset(string title, double price)
    {
        if (string.IsNullOrWhiteSpace(title)) throw new ArgumentException("Title cannot be empty");
        if (price <= 0.0) throw new ArgumentException("Price must be positive");
        Title = title;
        Price = price;
        Console.WriteLine($"BaseAsset(): {Title}");
    }

    // 5. Конструктор копирования (глубокая копия)
    protected BaseAsset(BaseAsset other)
    {
        Title = other.Title;
        Price = other.Price;
        Console.WriteLine($"BaseAsset(const BaseAsset&): {Title}");
    }

    // 2. Абстрактный метод
    public abstract double GetDailyYield();

    // 8. Виртуальный метод
    public virtual string Describe() => $"{Title} (цена: {Price:F2}), доходность: {GetDailyYield():F2}%";

    // Защищенный метод (protected)
    protected string Header() => Title;

    // 10. this: сеттер
    public BaseAsset SetPrice(double newPrice)
    {
        if (newPrice <= 0.0) throw new ArgumentException("Price must be positive");
        Price = newPrice;
        return this;
    }
}