#include <iostream>
#include <map>
#include "rapidcsv.h"

rapidcsv::Document getCSV(const std::string& fileName) {
    rapidcsv::Document doc(fileName);
    return doc;
}

int main()
{
    auto customers = getCSV("customers.csv");
    auto orders = getCSV("orders.csv");
    auto products = getCSV("products.csv");

    // Every customer
    // Customer: <name>, <address>
    for (int i = 0; i < customers.GetRowCount(); i++) {
        auto row = customers.GetRow<std::string>(i);
        std::cout   << "Customer: "
                    << row[1]
                    << ", "
                    << row[2]
                    << std::endl;
    }

    // Every product
    // Product: <name>, <price>
    std::map<std::string,float> productPrices;
    for (int i = 0; i < products.GetRowCount(); i++) {
        auto row = products.GetRow<std::string>(i);

        productPrices[row[1]] = std::stof(row[2]);
        std::cout   << "Product: "
                    << row[1]
                    << ", "
                    << row[2]
                    << std::endl;
    }

    // Total amount ordered per product
    // <product name> amount: <amount>
    std::map<std::string, std::string> productIds;
    std::map<std::string,int> productAmount;
    for (int i = 0; i < products.GetRowCount(); i++) {
        auto productRow = products.GetRow<std::string>(i);
        int amount = 0;

        for (int j = 0; j < orders.GetRowCount(); j++) {
            auto orderRow = orders.GetRow<int>(j);
            if (std::to_string(orderRow[2]) == productRow[0]) {
                amount += orderRow[3];
            }
        }

        productIds[productRow[0]] = productRow[1];
        productAmount[productRow[1]] = amount;
        std::cout << productRow[1] << " amount: " << amount << std::endl;
    }

    // Total money spent per product
    // <product name> gross income: <amount>
    std::map<std::string, int>::iterator it;
    for (it = productAmount.begin(); it != productAmount.end(); it++) {
        std::cout << it->first << " gross income: " << productPrices[it->first] * float(productAmount[it->first]) << std::endl;
    }

    // Total money spent per customer
    // <name> money spent: <amount>
    for (int i = 0; i < customers.GetRowCount(); i++) {
        auto customerRow = customers.GetRow<std::string>(i);
        auto customerId = customerRow[0];
        float moneySpent = 0;

        for (int j = 0; j < orders.GetRowCount(); j++) {
            auto orderRow = orders.GetRow<int>(j);
            if (std::to_string(orderRow[1]) == customerId) {
                auto productId = std::to_string(orderRow[2]);
                auto amount = orderRow[3];
                auto productName = productIds[productId];
                moneySpent += productPrices[productName] * float(amount);
            }
        }

        std::cout   << customerRow[1]
                    << " money spent: "
                    << moneySpent
                    << std::endl;
    }
}