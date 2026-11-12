using System;

namespace StockExchangeCSharp;

public sealed class ForecastLog : IDisposable
{
    private readonly string _title;

    public ForecastLog(string title)
    {
        _title = title;
        Console.WriteLine($"[+] журнал открыт: {_title}");
    }

    public void Write(string line)
    {
        Console.WriteLine($"    {line}");
    }

    public void Dispose()
    {
        Console.WriteLine($"[-] журнал закрыт: {_title}");
    }
}