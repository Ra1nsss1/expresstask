#pragma once
#include <iostream>
#include <string>

class TransactionView {
public:
    void showMessage(const std::string& msg) const {
        std::cout << "\n>>> [VIEW]: " << msg << "\n";
    }

    void showSeparator() const {
        std::cout << std::string(75, '=') << "\n";
    }
};