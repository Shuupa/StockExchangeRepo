#include "Wallet.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

Wallet::Wallet()
    : balance(0.0)
{
    std::cout << "Wallet created: balance " << balance << '\n';
}

Wallet::Wallet(double balance)
    : balance(balance)
{
    if (!std::isfinite(balance) || balance < 0.0) {
        throw std::invalid_argument("Wallet balance cannot be negative");
    }

    std::cout << "Wallet created: balance " << this->balance << '\n';
}

Wallet::~Wallet()
{
    std::cout << "Wallet destroyed: balance " << balance << '\n';
}

double Wallet::getBalance() const
{
    return balance;
}

void Wallet::deposit(double amount)
{
    if (!std::isfinite(amount) || amount <= 0.0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }

    balance += amount;
}

void Wallet::withdraw(double amount)
{
    if (!std::isfinite(amount) || amount <= 0.0) {
        throw std::invalid_argument("Withdraw amount must be positive");
    }

    if (amount > balance) {
        throw std::invalid_argument("Not enough money in the wallet");
    }

    balance -= amount;
}

void Wallet::printInfo() const
{
    std::cout << "Wallet balance: " << balance << '\n';
}