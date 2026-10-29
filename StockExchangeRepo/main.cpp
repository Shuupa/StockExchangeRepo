#include "Stock.hpp"
#include "ForecastModel.hpp"
#include "StockExchange.hpp"

#include <iostream>
#include <stdexcept>

int main()
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
        {"MSFT", 420.0},
        {"NVDA", 135.0}
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

    std::cout << "\n=== End of program ===\n";

    return 0;
}