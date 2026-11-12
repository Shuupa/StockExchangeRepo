#pragma once
#include <string>
#include <memory>
#include <iostream>

class BaseAsset {
private:
    std::string m_title;
    double m_price;

protected:
    std::string Header() const;

public:
    BaseAsset(const std::string& title, double price);
    BaseAsset(const BaseAsset& other);
    BaseAsset(BaseAsset&& other) noexcept;

    // Оператор присваивания (нужен для проверки this)
    BaseAsset& operator=(const BaseAsset& other);

    virtual ~BaseAsset(); // Виртуальный деструктор

    virtual double GetDailyYield() const = 0;

    // Клонирование
    virtual std::unique_ptr<BaseAsset> Clone() const = 0;

    virtual std::string Describe() const;

    std::string GetTitle() const { return m_title; }
    double GetPrice() const { return m_price; }

    // Для this
    BaseAsset& SetPrice(double newPrice);
};