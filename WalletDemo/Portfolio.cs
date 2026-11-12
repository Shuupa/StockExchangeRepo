using System;
using System.Collections.Generic;
using System.Text;

namespace StockExchangeCSharp;

public sealed class Portfolio
{
    public string Name { get; }

    private readonly Wallet _wallet; // композиция: часть создается внутри и наружу не отдается
    private readonly SortedDictionary<string, int> _shares = new(); // отсортирован, как std::map

    public Portfolio(string name, double startBalance)
    {
        if (string.IsNullOrWhiteSpace(name))
            throw new ArgumentException("Portfolio name cannot be empty", nameof(name));

        Name = name;
        _wallet = new Wallet(startBalance);

        Console.WriteLine($"Portfolio created: {Name}");
    }

    public int GetShares(string ticker) =>
        _shares.TryGetValue(ticker, out int count) ? count : 0;

    public void BuyStock(Stock stock, int quantity)
    {
        ArgumentNullException.ThrowIfNull(stock);

        if (quantity <= 0)
            throw new ArgumentException("Quantity must be positive", nameof(quantity));

        double cost = stock.Price * quantity;

        if (cost > _wallet.Balance)
            throw new ArgumentException("Not enough money to buy shares", nameof(quantity));

        _wallet.Withdraw(cost);
        _shares[stock.Ticker] = GetShares(stock.Ticker) + quantity;

        Console.WriteLine($"Bought {quantity} x {stock.Ticker} for {cost}");
    }

    public void SellStock(Stock stock, int quantity)
    {
        ArgumentNullException.ThrowIfNull(stock);

        if (quantity <= 0)
            throw new ArgumentException("Quantity must be positive", nameof(quantity));

        if (quantity > GetShares(stock.Ticker))
            throw new ArgumentException("Cannot sell more shares than owned", nameof(quantity));

        double income = stock.Price * quantity;

        _wallet.Deposit(income);
        _shares[stock.Ticker] -= quantity;

        Console.WriteLine($"Sold {quantity} x {stock.Ticker} for {income}");
    }

    public override string ToString()
    {
        var text = new StringBuilder();
        text.AppendLine($"Portfolio: {Name}");
        text.Append(_wallet);

        foreach (var item in _shares)
            text.Append($"\n  {item.Key}: {item.Value} shares");

        return text.ToString();
    }
}
