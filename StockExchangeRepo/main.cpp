#include "Stock.hpp"
#include "ForecastModel.hpp"
#include "StockExchange.hpp"
#include "Wallet.hpp"
#include "Portfolio.hpp"
#include "Trader.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

// ---------------------------------------------------------------
// PART 1. Shuupa's classes: Stock, ForecastModel, StockExchange
// ---------------------------------------------------------------
void runFriendPart()
{
    std::cout << "=== 1. Ordinary object, reference and pointer ===\n";

    Stock apple("AAPL", 230.0);

    Stock& stockReference = apple;
    Stock* stockPointer = &apple; // наблюдатель, не владеет

    stockReference.printInfo();
    stockPointer->printInfo();

    std::cout << "\n=== 2. Aggregation ===\n";

    ForecastModel independentModel(apple);
    independentModel.printForecast(5.0);

    std::cout << "\n=== 3. Composition and object lifetime ===\n";

    {
        StockExchange exchange("NYSE", apple);
        exchange.printInfo();
        exchange.showForecast(-2.0);

        std::cout << "Leaving exchange scope...\n";
    }

    std::cout << "Stock still exists after exchange destruction:\n";
    apple.printInfo();

    std::cout << "\n=== 4. Validation rules ===\n";

    try {
        apple.setPrice(-10.0);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Price validation error: " << error.what() << '\n';
    }

    try {
        independentModel.printForecast(-100.0);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Forecast validation error: " << error.what() << '\n';
    }

    std::cout << "\n=== 5. unique_ptr: dynamic object, ownership transfer ===\n";

    {
        auto dynamicStock = std::make_unique<Stock>("TSLA", 250.0);
        dynamicStock->printInfo();
        // здесь dynamicStock уничтожится автоматически
    }
    std::cout << "TSLA destroyed (unique_ptr out of scope)\n";

    auto novelty = std::make_unique<Stock>("NVDA", 135.0);
    StockExchange* dummyExchange = nullptr; // просто для примера
    // передача владения (демонстрация std::move)
    auto anotherOwner = std::move(novelty);
    if (!novelty) {
        std::cout << "Original pointer is empty after move\n";
    }
    anotherOwner->printInfo();
    // anotherOwner уничтожится в конце функции

    std::cout << "\n=== 6. Dynamic array of objects (vector) ===\n";

    std::vector<std::unique_ptr<Stock>> stockArray;
    stockArray.push_back(std::make_unique<Stock>("MSFT", 420.0));
    stockArray.push_back(std::make_unique<Stock>("NVDA", 135.0));

    for (const auto& s : stockArray) {
        s->printInfo();
    }
    // Автоматически очистится

    std::cout << "\n=== 7. unique_ptr: array of dynamic objects ===\n";

    std::unique_ptr<Stock> shelf[2];
    shelf[0] = std::make_unique<Stock>("AMZN", 190.0);
    shelf[1] = std::make_unique<Stock>("GOOGL", 175.0);

    for (int i = 0; i < 2; ++i) {
        shelf[i]->printInfo();
    }
    // автоматически уничтожатся

    std::cout << "\n=== 8. shared_ptr: multiple owners ===\n";

    auto first = std::make_shared<Stock>("SBER", 300.0);
    std::cout << "use_count: " << first.use_count() << '\n'; // 1
    {
        auto second = first; // копия
        std::cout << "use_count after copy: " << first.use_count() << '\n'; // 2
    }
    std::cout << "use_count after scope: " << first.use_count() << '\n'; // 1

    std::cout << "\n=== 9. weak_ptr: observer ===\n";

    std::weak_ptr<Stock> weakWatcher = first;
    std::cout << "weak expired? " << weakWatcher.expired() << '\n'; // 0 (false)
    if (auto locked = weakWatcher.lock()) {
        std::cout << "Still alive: ";
        locked->printInfo();
    }
    first.reset(); // уничтожаем последнего владельца
    std::cout << "After reset, weak expired? " << weakWatcher.expired() << '\n'; // 1 (true)
    if (auto locked = weakWatcher.lock()) {
        std::cout << "Still alive: ";
        locked->printInfo();
    }
    else {
        std::cout << "Object is destroyed\n";
    }

    std::cout << "\n=== End of part 1 ===\n";
}

// ---------------------------------------------------------------
// PART 2. My classes: Wallet, Portfolio, Trader
// ---------------------------------------------------------------
void runMyPart()
{
    std::cout << "1. Ordinary object, reference and pointer\n";

    Wallet wallet(500.0);

    Wallet& walletReference = wallet;
    Wallet* walletPointer = &wallet;

    walletReference.printInfo();
    walletPointer->deposit(100.0);
    walletPointer->printInfo();

    std::cout << "\n2. Stock and forecast (Shuupa's classes)\n";

    Stock microsoft("MSFT", 400.0);
    ForecastModel model(microsoft);

    const double forecast = model.predictPrice(10.0);
    model.printForecast(10.0);

    std::cout << "\n3. Composition: Portfolio owns Wallet\n";

    {
        Portfolio temporaryPortfolio("Temporary", 1000.0);
        temporaryPortfolio.buyStock(microsoft, 2);
        temporaryPortfolio.printInfo();

        std::cout << "Leaving portfolio scope...\n";
    }

    std::cout << "\n4. Aggregation: Trader uses Portfolio\n";

    Portfolio mainPortfolio("Main", 2000.0);

    {
        Trader trader("Alex", mainPortfolio);
        trader.printInfo();

        trader.buyIfGrowth(microsoft, forecast, 3);
        trader.sellIfDrop(microsoft, 380.0, 1);
        trader.sellIfDrop(microsoft, 450.0, 1);

        std::cout << "Leaving trader scope...\n";
    }

    std::cout << "Portfolio still exists after trader destruction:\n";
    mainPortfolio.printInfo();

    std::cout << "\n5. Validation rules\n";

    try {
        mainPortfolio.buyStock(microsoft, 1000);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Buy validation error: " << error.what() << '\n';
    }

    try {
        mainPortfolio.sellStock(microsoft, 50);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Sell validation error: " << error.what() << '\n';
    }

    try {
        wallet.withdraw(10000.0);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Wallet validation error: " << error.what() << '\n';
    }

    std::cout << "\n6. unique_ptr: dynamic object\n";

    {
        auto dynamicWallet = std::make_unique<Wallet>(250.0);
        dynamicWallet->printInfo();
    }
    std::cout << "Wallet destroyed (unique_ptr out of scope)\n";

    std::cout << "\n7. unique_ptr: dynamic array\n";

    // Wallet имеет конструктор по умолчанию? Если нет, используем vector
    // Предположим, что есть.
    auto walletArray = std::make_unique<Wallet[]>(2);
    walletArray[0].deposit(10.0);
    walletArray[1].deposit(20.0);

    for (int i = 0; i < 2; ++i) {
        walletArray[i].printInfo();
    }
    // автоматически уничтожится

    std::cout << "\n8. unique_ptr: array of dynamic objects\n";

    std::unique_ptr<Wallet> walletShelf[2];
    walletShelf[0] = std::make_unique<Wallet>(100.0);
    walletShelf[1] = std::make_unique<Wallet>(200.0);

    for (int i = 0; i < 2; ++i) {
        walletShelf[i]->printInfo();
    }
    // автоматически уничтожатся

    std::cout << "\nEnd of part 2\n";
}

int main()
{
    std::cout << "PART 1: Shuupa's classes\n"
        << "(Stock, ForecastModel, StockExchange)\n\n";

    runFriendPart();

    std::cout << "\nPART 2: my classes\n"
        << "(Wallet, Portfolio, Trader)\n\n";

    runMyPart();

    return 0;
}