using System;
using System.Runtime.CompilerServices;

namespace StockExchangeCSharp;

// Структура для демонстрации (пункт 4: для C# дополнительно показать struct)
public struct Money
{
    public int Rubles;
    public int Kopeck;
}

public static class Program
{
    // Атрибут NoInlining гарантирует, что JIT-компилятор не "зашьет" этот метод в Main,
    // и локальная переменная temp гарантированно умрет при выходе из метода.
    [MethodImpl(MethodImplOptions.NoInlining)]
    static WeakReference<Stock> RunGarbageCollectorDemo()
    {
        Stock temp = new Stock("DELISTED", 1.0);
        return new WeakReference<Stock>(temp);
    }
    [MethodImpl(MethodImplOptions.NoInlining)]
    static void CreateGarbageObject()
    {
        Stock temp = new Stock("DELISTED", 1.0);
    }
    public static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8; // для русских букв в консоли Windows

        Console.WriteLine("\n1. Ссылки и копии (класс)");
        Stock first = new Stock("AAPL", 230.0);
        Stock second = first; // копируется ссылка, а не объект
        second.SetPrice(250.0);
        Console.WriteLine($"first:  {first}");
        Console.WriteLine($"second: {second}");
        Console.WriteLine($"first == second: {ReferenceEquals(first, second)}"); // true

        Console.WriteLine("\n2. Ссылки и копии (struct)");
        var a = new Money { Rubles = 150, Kopeck = 50 };
        var b = a; // копируется ЗНАЧЕНИЕ
        b.Rubles = 300;
        Console.WriteLine($"a.Rubles = {a.Rubles} (исходная структура не изменилась)");
        Console.WriteLine($"b.Rubles = {b.Rubles}");

        Console.WriteLine("\n3. Агрегация");
        ForecastModel independentModel = new ForecastModel(first);
        independentModel.PrintForecast(5.0);

        Console.WriteLine("\n4. Композиция и освобождение ресурса");
        using (var log = new ForecastLog("Абонемент"))
        {
            log.Write("выдана книга «Война и мир»");
            StockExchange exchange = new StockExchange("NYSE", first);
            exchange.ShowForecast(-2.0);
        } // здесь гарантированно вызван Dispose()
        Console.WriteLine("После выхода из блока using ресурс освобожден.");

        Console.WriteLine("\n5. Проверка правил");
        try { first.SetPrice(-10.0); }
        catch (ArgumentException e) { Console.WriteLine($"Ошибка цены: {e.Message}"); }

        try { independentModel.PredictPrice(-100.0); }
        catch (ArgumentException e) { Console.WriteLine($"Ошибка прогноза: {e.Message}"); }

        Console.WriteLine("\n6. Сборщик мусора");

        long memoryBefore = GC.GetTotalMemory(true);
        Console.WriteLine($"Память до создания объекта: {memoryBefore} байт");

        // Создаем объект, который сразу становится мусором
        CreateGarbageObject();

        long memoryAfterCreate = GC.GetTotalMemory(false);
        Console.WriteLine($"Память после создания: {memoryAfterCreate} байт (объект еще жив)");

        // Принудительная сборка
        GC.Collect();
        GC.WaitForPendingFinalizers();
        GC.Collect();

        long memoryAfterCollect = GC.GetTotalMemory(true);
        Console.WriteLine($"Память после сборки: {memoryAfterCollect} байт (объект уничтожен)");
    }
}