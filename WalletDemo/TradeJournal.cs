using System;

namespace StockExchangeCSharp;

// Вспомогательный класс: журнал сделок. Освобождает ресурс через IDisposable,
// потому что деструктора с предсказуемым моментом вызова в C# нет.
public sealed class TradeJournal : IDisposable
{
    private readonly string _title;
    private bool _disposed;

    public TradeJournal(string title)
    {
        _title = title;
        Console.WriteLine($"[+] журнал сделок открыт: {_title}");
    }

    public void Write(string line)
    {
        ObjectDisposedException.ThrowIf(_disposed, this);
        Console.WriteLine($"    {line}");
    }

    public void Dispose()
    {
        if (_disposed)
            return;

        _disposed = true;
        Console.WriteLine($"[-] журнал сделок закрыт: {_title}");
    }
}
