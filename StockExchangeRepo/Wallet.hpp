#pragma once

class Wallet {
private:
    double balance;

public:
    Wallet();
    explicit Wallet(double balance);
    ~Wallet();

    double getBalance() const;

    void deposit(double amount);
    void withdraw(double amount);
    void printInfo() const;
};