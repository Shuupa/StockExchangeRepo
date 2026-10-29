#include "Stock.hpp"
#include "ForecastModel.hpp"
#include "StockExchange.hpp"
#include "Wallet.hpp"
#include "Portfolio.hpp"
#include "Trader.hpp"

#include <iostream>
#include <stdexcept>

// ---------------------------------------------------------------
// PART 1. Shuupa's classes: Stock, ForecastModel, StockExchange
// ---------------------------------------------------------------
void runFriendPart()
{
    std::cout << "=== 1. Ordinary object, reference and pointer ===\n";

    Stock apple("AAPL", 230.0);

    Stock& stockReference = apple;
    Stock* stockPointer = &apple;

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
        std::cout << "Price validation error: "
            << error.what() << '\n';
    }

    try {
        independentModel.printForecast(-100.0);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Forecast validation error: "
            << error.what() << '\n';
    }

    std::cout << "\n=== 5. Dynamic object: new and delete ===\n";

    Stock* dynamicStock = new Stock("TSLA", 250.0);
    dynamicStock->printInfo();

    delete dynamicStock;
    dynamicStock = nullptr;

    std::cout << "\n=== 6. Dynamic array of objects ===\n";

    Stock* stockArray = new Stock[2]{
        { "MSFT", 420.0 },
        { "NVDA", 135.0 }
    };

    for (int i = 0; i < 2; ++i) {
        stockArray[i].printInfo();
    }

    delete[] stockArray;
    stockArray = nullptr;

    std::cout << "\n=== 7. Array of dynamic objects ===\n";

    Stock** stockPointers = new Stock * [2];

    stockPointers[0] = new Stock("AMZN", 190.0);
    stockPointers[1] = new Stock("GOOGL", 175.0);

    for (int i = 0; i < 2; ++i) {
        stockPointers[i]->printInfo();
    }

    for (int i = 0; i < 2; ++i) {
        delete stockPointers[i];
        stockPointers[i] = nullptr;
    }

    delete[] stockPointers;
    stockPointers = nullptr;

    std::cout << "\n=== End of part 1 (remaining objects are destroyed below) ===\n";
}

// ---------------------------------------------------------------
// PART 2. My classes: Wallet, Portfolio, Trader
// ---------------------------------------------------------------
void runMyPart()
{
    std::cout << "=== 1. Ordinary object, reference and pointer ===\n";

    Wallet wallet(500.0);

    Wallet& walletReference = wallet;
    Wallet* walletPointer = &wallet;

    walletReference.printInfo();
    walletPointer->deposit(100.0);
    walletPointer->printInfo();

    std::cout << "\n=== 2. Stock and forecast (Shuupa's classes) ===\n";

    Stock microsoft("MSFT", 400.0);
    ForecastModel model(microsoft);

    const double forecast = model.predictPrice(10.0);
    model.printForecast(10.0);

    std::cout << "\n=== 3. Composition: Portfolio owns Wallet ===\n";

    {
        Portfolio temporaryPortfolio("Temporary", 1000.0);
        temporaryPortfolio.buyStock(microsoft, 2);
        temporaryPortfolio.printInfo();

        std::cout << "Leaving portfolio scope...\n";
    }

    std::cout << "\n=== 4. Aggregation: Trader uses Portfolio ===\n";

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

    std::cout << "\n=== 5. Validation rules ===\n";

    try {
        mainPortfolio.buyStock(microsoft, 1000);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Buy validation error: "
            << error.what() << '\n';
    }

    try {
        mainPortfolio.sellStock(microsoft, 50);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Sell validation error: "
            << error.what() << '\n';
    }

    try {
        wallet.withdraw(10000.0);
    }
    catch (const std::invalid_argument& error) {
        std::cout << "Wallet validation error: "
            << error.what() << '\n';
    }

    std::cout << "\n=== 6. Dynamic object: new and delete ===\n";

    Wallet* dynamicWallet = new Wallet(250.0);
    dynamicWallet->printInfo();

    delete dynamicWallet;
    dynamicWallet = nullptr;

    std::cout << "\n=== 7. Dynamic array of objects ===\n";

    Wallet* walletArray = new Wallet[2];

    walletArray[0].deposit(10.0);
    walletArray[1].deposit(20.0);

    for (int i = 0; i < 2; ++i) {
        walletArray[i].printInfo();
    }

    delete[] walletArray;
    walletArray = nullptr;

    std::cout << "\n=== 8. Array of dynamic objects ===\n";

    Wallet** walletPointers = new Wallet * [2];

    walletPointers[0] = new Wallet(100.0);
    walletPointers[1] = new Wallet(200.0);

    for (int i = 0; i < 2; ++i) {
        walletPointers[i]->printInfo();
    }

    for (int i = 0; i < 2; ++i) {
        delete walletPointers[i];
        walletPointers[i] = nullptr;
    }

    delete[] walletPointers;
    walletPointers = nullptr;

    std::cout << "\n=== End of part 2 (remaining objects are destroyed below) ===\n";
}

int main()
{
    std::cout << "################ PART 1: Shuupa's classes ################\n"
        << "(Stock, ForecastModel, StockExchange)\n\n";

    runFriendPart();

    std::cout << "\n################ PART 2: my classes ################\n"
        << "(Wallet, Portfolio, Trader)\n\n";

    runMyPart();

    return 0;
}