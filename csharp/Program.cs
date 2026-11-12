using System;

namespace StockExchangeCSharp;

public struct Money
{
    public int Rubles;
    public int Kopeck;
}

public static class Program
{
    public static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        Console.WriteLine("ЛАБОРАТОРНАЯ 4: НАСЛЕДОВАНИЕ (C#)\n");

        // 1. Конструкторы и наследование
        Console.WriteLine("1. Создание объектов");
        Stock apple = new Stock("AAPL", "Apple Inc.", 230.0);
        Bond bond = new Bond("US Treasury", 1000.0, 5.0);
        Console.WriteLine($"Всего акций: {Stock.GetStockCount()}\n");

        // 2. Полиморфизм
        Console.WriteLine("2. Полиморфизм (BaseAsset)");
        BaseAsset[] assets = { apple, bond };
        foreach (var asset in assets)
        {
            Console.WriteLine(asset.Describe());
        }
        Console.WriteLine();

        // 3. Глубокое копирование
        Console.WriteLine("3. Копирование");
        Stock copy = new Stock(apple);
        copy.SetPrice(350.0);
        Console.WriteLine($"Оригинал: {apple.Price} (не изменился)");
        Console.WriteLine($"Копия: {copy.Price}\n");

        // 10.2. Equals и GetHashCode
        Console.WriteLine("4. Сравнение по содержимому");
        Stock twin = new Stock("AAPL", "Apple Inc.", 230.0);
        Console.WriteLine($"apple == twin (по тикеру): {apple.Equals(twin)}");
        Console.WriteLine($"Хэш-коды совпадают: {apple.GetHashCode() == twin.GetHashCode()}\n");

        // 5. using var (IDisposable)
        Console.WriteLine("5. using var (IDisposable)");
        using (var log = new ForecastLog("Абонемент"))
        {
            log.Write("выдана книга");
        }
        Console.WriteLine("Ресурс освобожден\n");

        // 6. this и цепочка вызовов
        Console.WriteLine("6. this: цепочка вызовов");
        Stock chain = new Stock("SBER", "Sberbank", 300.0);
        chain.SetPrice(310.0).SetPrice(320.0);
        Console.WriteLine($"Цена после цепочки: {chain.Price}\n");

        // 7. Работа со строками
        Console.WriteLine("7. Строки");
        string title = "Apple Inc. (AAPL)";
        Console.WriteLine($"Длина: {title.Length}");
        Console.WriteLine($"Поиск 'Inc': {title.IndexOf("Inc")}");
        Console.WriteLine($"Подстрока: {title.Substring(0, 5)}\n");
    }
}