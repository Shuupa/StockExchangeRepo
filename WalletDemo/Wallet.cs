using System;

namespace StockExchangeCSharp;

public sealed class Wallet
{
    public double Balance { get; private set; }

    public Wallet(double balance = 0.0)
    {
        if (double.IsNaN(balance) || double.IsInfinity(balance) || balance < 0.0)
            throw new ArgumentException("Wallet balance cannot be negative", nameof(balance));

        Balance = balance;

        Console.WriteLine($"Wallet created: balance {Balance}");
    }

    public void Deposit(double amount)
    {
        if (double.IsNaN(amount) || double.IsInfinity(amount) || amount <= 0.0)
            throw new ArgumentException("Deposit amount must be positive", nameof(amount));

        Balance += amount;
    }

    public void Withdraw(double amount)
    {
        if (double.IsNaN(amount) || double.IsInfinity(amount) || amount <= 0.0)
            throw new ArgumentException("Withdraw amount must be positive", nameof(amount));

        if (amount > Balance)
            throw new ArgumentException("Not enough money in the wallet", nameof(amount));

        Balance -= amount;
    }

    public override string ToString() => $"Wallet balance: {Balance}";
}
