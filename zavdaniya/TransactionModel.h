#pragma once
#include <vector>
#include <string>
#include "TransactionData.h"
#include "TaxStrategy.h"
#include "Notifier.h"
#include "Observer.h"

class TransactionModel {
private:
    std::vector<TransactionData> m_transactions;
    std::vector<IObserver*> m_observers;
    ITaxCalculationStrategy* m_taxStrategy;

public:
    TransactionModel();
    ~TransactionModel();

    void setTaxStrategy(ITaxCalculationStrategy* strategy);
    void attachObserver(IObserver* observer);
    void detachObserver(IObserver* observer);
    void notifyObservers(const TransactionData& data);
    void processTransaction(int tx_id, double amount, INotifier* notifierPipeline);
    std::string getCurrentStrategyName() const;
};