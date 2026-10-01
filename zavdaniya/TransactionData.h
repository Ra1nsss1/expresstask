#pragma once
#include <string>
struct TransactionData {
    int id;
    double amount;
    double tax;
    double net;
    std::string notification_text;
};