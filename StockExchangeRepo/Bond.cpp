#include "Bond.hpp"
#include <iostream>

Bond::Bond(const std::string& title, double price, double couponRate)
    : BaseAsset(title, price), m_couponRate(couponRate)
{
    std::cout << "Bond(): " << title << "\n";
}

double Bond::GetDailyYield() const { return m_couponRate / 365.0; }

std::string Bond::Describe() const {
    return "Облигация: " + GetTitle() + ", купон: " + std::to_string(m_couponRate) + "%";
}

std::unique_ptr<BaseAsset> Bond::Clone() const {
    return std::make_unique<Bond>(*this);
}