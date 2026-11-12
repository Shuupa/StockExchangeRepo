#include "BaseAsset.hpp"
#include <iostream>
#include <stdexcept>

BaseAsset::BaseAsset(const std::string& title, double price)
    : m_title(title), m_price(price)
{
    if (title.empty()) throw std::invalid_argument("Title cannot be empty");
    if (price <= 0.0) throw std::invalid_argument("Price must be positive");
    std::cout << "BaseAsset(): " << m_title << "\n";
}

BaseAsset::BaseAsset(const BaseAsset& other)
    : m_title(other.m_title), m_price(other.m_price)
{
    std::cout << "BaseAsset(const BaseAsset&): " << m_title << "\n";
}

BaseAsset::BaseAsset(BaseAsset&& other) noexcept
    : m_title(std::move(other.m_title)), m_price(other.m_price)
{
    std::cout << "BaseAsset(BaseAsset&&): " << m_title << "\n";
}

BaseAsset& BaseAsset::operator=(const BaseAsset& other) {
    if (this == &other) {
        return *this; // Защита от самоприсваивания (this)
    }
    m_title = other.m_title;
    m_price = other.m_price;
    return *this; // Возврат *this
}

BaseAsset::~BaseAsset() {
    std::cout << "~BaseAsset(): " << m_title << "\n";
}

std::string BaseAsset::Header() const {
    return m_title + " (цена: " + std::to_string(m_price) + ")";
}

std::string BaseAsset::Describe() const {
    return Header() + ", доходность: " + std::to_string(GetDailyYield()) + "%";
}

BaseAsset& BaseAsset::SetPrice(double newPrice) {
    if (newPrice <= 0.0) throw std::invalid_argument("Price must be positive");
    m_price = newPrice;
    return *this;
}