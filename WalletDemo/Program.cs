using System;
using System.Runtime.CompilerServices;

namespace StockExchangeCSharp;

// Демонстрационная программа: Wallet, Portfolio, Trader
public static class Program
{
    // NoInlining: JIT не встроит метод в Run, и локальная переменная гарантированно
    // перестанет быть достижимой после выхода из метода.
    [MethodImpl(MethodImplOptions.NoInlining)]
    private static WeakReference<Portfolio> CreateGarbagePortfolio()
    {
        var temp = new Portfolio("Abandoned", 100.0);
        return new WeakReference<Portfolio>(temp);
    }

    // Проверка вынесена в отдельный метод: иначе временная ссылка из TryGetTarget
    // остается в кадре большого метода Run и не дает сборщику уничтожить объект.
    [MethodImpl(MethodImplOptions.NoInlining)]
    private static bool IsAlive(WeakReference<Portfolio> reference) =>
        reference.TryGetTarget(out _);

    public static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8; // для русских букв в консоли Windows

        var microsoft = new Stock("MSFT", 400.0);

        Console.WriteLine("\n1. Ссылки и копии (класс Wallet)");
        var walletA = new Wallet(500.0);
        Wallet walletB = walletA; // копируется ссылка, а не объект
        walletB.Deposit(100.0);
        Console.WriteLine($"walletA: {walletA}");
        Console.WriteLine($"walletB: {walletB}");
        Console.WriteLine($"walletA == walletB: {ReferenceEquals(walletA, walletB)}"); // true

        Console.WriteLine("\n2. Ссылки и копии (struct Lot)");
        var lotA = new Lot { Ticker = "MSFT", Quantity = 10 };
        var lotB = lotA; // копируется ЗНАЧЕНИЕ
        lotB.Quantity = 99;
        Console.WriteLine($"lotA.Quantity = {lotA.Quantity} (исходная структура не изменилась)");
        Console.WriteLine($"lotB.Quantity = {lotB.Quantity}");

        Console.WriteLine("\n3. Композиция и агрегация");
        {
            var temporary = new Portfolio("Temporary", 1000.0); // Wallet создается внутри
            temporary.BuyStock(microsoft, 2);
            Console.WriteLine(temporary);
        }
        Console.WriteLine("Вышли из блока: в C++ здесь сработали бы деструкторы, в C# момент уничтожения неизвестен.");

        var main = new Portfolio("Main", 2000.0); // портфель создан снаружи
        var trader = new Trader("Alex", main);    // и передан трейдеру готовым
        Console.WriteLine(trader);
        trader.BuyIfGrowth(microsoft, 440.0, 3);
        trader.SellIfDrop(microsoft, 380.0, 1);
        trader.SellIfDrop(microsoft, 450.0, 1);
        trader = null; // трейдер больше не нужен, но портфель по-прежнему доступен
        Console.WriteLine("Портфель жив после того, как трейдер больше не используется:");
        Console.WriteLine(main);

        Console.WriteLine("\n4. Освобождение ресурса без деструктора (IDisposable + using)");
        var journal = new TradeJournal("Main");
        using (journal)
        {
            journal.Write("куплено 3 x MSFT");
            journal.Write("продано 1 x MSFT");
        } // здесь гарантированно вызван Dispose()
        Console.WriteLine("После выхода из блока using ресурс освобожден.");
        try { journal.Write("запись после закрытия"); }
        catch (ObjectDisposedException e) { Console.WriteLine($"Ошибка: {e.Message.Split('\n')[0]}"); }

        Console.WriteLine("\n5. Проверка правил");
        try { main.BuyStock(microsoft, 1000); }
        catch (ArgumentException e) { Console.WriteLine($"Ошибка покупки: {e.Message}"); }

        try { main.SellStock(microsoft, 50); }
        catch (ArgumentException e) { Console.WriteLine($"Ошибка продажи: {e.Message}"); }

        try { walletA.Withdraw(10000.0); }
        catch (ArgumentException e) { Console.WriteLine($"Ошибка кошелька: {e.Message}"); }

        Console.WriteLine("\n6. Сборщик мусора");
        WeakReference<Portfolio> weak = CreateGarbagePortfolio();
        Console.WriteLine($"Вышли из метода. Объект жив? {IsAlive(weak)} (сборки еще не было)");

        GC.Collect();
        GC.WaitForPendingFinalizers();
        GC.Collect();

        Console.WriteLine($"После GC.Collect(). Объект жив? {IsAlive(weak)}");
        Console.WriteLine("В C++ деструктор Portfolio вызывался бы сразу при выходе из блока.");
    }
}
