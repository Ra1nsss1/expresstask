#pragma once
#include <string>
#include "TransactionModel.h"
#include "TransactionView.h"

class TransactionController {
private:
    TransactionModel& m_model;
    TransactionView& m_view;

public:
    TransactionController(TransactionModel& model, TransactionView& view);

    void setStrategy(ITaxCalculationStrategy* strategy);
    void createTransaction(int tx_id, double amount, INotifier* notifierPipeline);
    void attachObserver(IObserver* observer);
    void detachObserver(IObserver* observer);
};