#include "TransactionController.h"

using namespace std;

TransactionController::TransactionController(TransactionModel& model, TransactionView& view)
    : m_model(model), m_view(view) {
}

void TransactionController::setStrategy(ITaxCalculationStrategy* strategy) {
    m_model.setTaxStrategy(strategy);
    m_view.showMessage("Змінено стратегію оподаткування на: " + m_model.getCurrentStrategyName());
}

void TransactionController::createTransaction(int tx_id, double amount, INotifier* notifierPipeline) {
    m_view.showMessage("Запуск обробки транзакції #" + to_string(tx_id) + " на суму " + to_string(static_cast<int>(amount)) + " UAH...");
    m_model.processTransaction(tx_id, amount, notifierPipeline);
}

void TransactionController::attachObserver(IObserver* observer) {
    m_model.attachObserver(observer);
}

void TransactionController::detachObserver(IObserver* observer) {
    m_model.detachObserver(observer);
}