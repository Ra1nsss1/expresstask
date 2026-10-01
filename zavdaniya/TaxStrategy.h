#pragma once
#include <string>

class ITaxCalculationStrategy {
public:
    virtual ~ITaxCalculationStrategy() = default;
    virtual double calculate(double amount) const = 0;
    virtual std::string getName() const = 0;
};

class StandardTaxStrategy : public ITaxCalculationStrategy {
public:
    double calculate(double amount) const override {
        return amount * 0.195;
    }
    std::string getName() const override {
        return "StandardTaxStrategy (19.5%)";
    }
};

class ITSectorTaxStrategy : public ITaxCalculationStrategy {
public:
    double calculate(double amount) const override {
        return amount * 0.05;
    }
    std::string getName() const override {
        return "ITSectorTaxStrategy (5%)";
    }
};