#pragma once
#include "BaseAsset.hpp"
#include <string>
#include <iostream>

class Stock : public BaseAsset {
private:
    std::string m_ticker;
    static int m_count;

public:
    // Основной конструктор
    Stock(const std::string& ticker, const std::string& title, double price);

    // Конструктор для совместимости со старым кодом
    Stock(const std::string& ticker, double price);

    static int GetStockCount();

    double GetDailyYield() const override;
    std::string Describe() const override;

    // Клонирование
    std::unique_ptr<BaseAsset> Clone() const override;

    // --- Обертки для старых классов ---
    std::string getTicker() const { return m_ticker; }
    double getPrice() const { return GetPrice(); }
    void printInfo() const { std::cout << Describe() << "\n"; }
    void setPrice(double newPrice) { SetPrice(newPrice); }
};