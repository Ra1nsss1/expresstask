#include "TransactionModel.h"

using namespace std;

TransactionModel::TransactionModel() {
    m_taxStrategy = new StandardTaxStrategy();
}

TransactionModel::~TransactionModel() {
    delete m_taxStrategy;
}

void TransactionModel::setTaxStrategy(ITaxCalculationStrategy* strategy) {
    if (m_taxStrategy) {
        delete m_taxStrategy;
    }
    m_taxStrategy = strategy;
}

void TransactionModel::attachObserver(IObserver* observer) {
    m_observers.push_back(observer);
}

void TransactionModel::detachObserver(IObserver* observer) {
    for (size_t i = 0; i < m_observers.size(); ++i) {
        if (m_observers[i] == observer) {
            m_observers.erase(m_observers.begin() + i);
            break;
        }
    }
}

void TransactionModel::notifyObservers(const TransactionData& data) {
    for (IObserver* observer : m_observers) {
        if (observer) {
            observer->update(data);
        }
    }
}

void TransactionModel::processTransaction(int tx_id, double amount, INotifier* notifierPipeline) {
    double tax = m_taxStrategy ? m_taxStrategy->calculate(amount) : 0.0;
    double net = amount - tax;

    string raw_msg = "Транзакція #" + to_string(tx_id) +
        ": Сума=" + to_string(static_cast<int>(amount)) +
        " UAH, Податок=" + to_string(static_cast<int>(tax)) +
        " UAH, До виплати=" + to_string(static_cast<int>(net)) + " UAH";

    string formatted_message = notifierPipeline ? notifierPipeline->send(raw_msg) : raw_msg;

    TransactionData tx_data{ tx_id, amount, tax, net, formatted_message };
    m_transactions.push_back(tx_data);

    notifyObservers(tx_data);
}

string TransactionModel::getCurrentStrategyName() const {
    return m_taxStrategy ? m_taxStrategy->getName() : "Без стратегії";
}