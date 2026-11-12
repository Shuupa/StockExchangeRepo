#include "Stock.hpp"
#include <iostream>
#include <stdexcept>

int Stock::m_count = 0; // Инициализация статического поля

Stock::Stock(const std::string& ticker, const std::string& title, double price)
    : BaseAsset(title, price), m_ticker(ticker)
{
    if (ticker.empty()) throw std::invalid_argument("Ticker cannot be empty");
    m_count++;
    std::cout << "Stock(): " << m_ticker << "\n";
}

Stock::Stock(const std::string& ticker, double price)
    : Stock(ticker, ticker, price) {
}

int Stock::GetStockCount() { return m_count; }

double Stock::GetDailyYield() const { return 2.0; }

std::string Stock::Describe() const {
    return BaseAsset::Describe() + " [Тикер: " + m_ticker + "]";
}

std::unique_ptr<BaseAsset> Stock::Clone() const {
    return std::make_unique<Stock>(*this);
}