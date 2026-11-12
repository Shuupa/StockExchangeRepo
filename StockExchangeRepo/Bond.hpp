#pragma once
#include "BaseAsset.hpp"

class Bond final : public BaseAsset { // final запрещает наследование
private:
    double m_couponRate;

public:
    Bond(const std::string& title, double price, double couponRate);

    double GetDailyYield() const override;
    std::string Describe() const override;

    // Клонирование
    std::unique_ptr<BaseAsset> Clone() const override;
};