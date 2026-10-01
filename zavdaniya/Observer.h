#pragma once
#include <iostream>
#include "TransactionData.h"

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const TransactionData& data) = 0;
};

class ConsoleLoggerObserver : public IObserver {
public:
    void update(const TransactionData& data) override {
        std::cout << "[Observer: ConsoleLogger] Нова транзакція: ID " << data.id
            << " на суму " << data.amount << " UAH (Податок: " << data.tax << " UAH)\n";
    }
};

class EmailNotifierObserver : public IObserver {
public:
    void update(const TransactionData& data) override {
        std::cout << "[Observer: EmailNotifier] Надсилання e-mail... " << data.notification_text << "\n";
    }
};

class UIAnalyticsObserver : public IObserver {
public:
    void update(const TransactionData& data) override {
        std::cout << "[Observer: UIAnalytics] Оновлено статистику для ID " << data.id << "\n";
    }
};
