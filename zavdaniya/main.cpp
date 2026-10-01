#include <iostream>
#include <windows.h>
#include "TransactionModel.h"
#include "TransactionView.h"
#include "TransactionController.h"
#include "Notifier.h"
#include "Observer.h"
#include "TaxStrategy.h"

using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // 1. Створюємо MVC
    TransactionModel model;
    TransactionView view;
    TransactionController controller(model, view);

    // 2. Спостерігачі (Observer)
    ConsoleLoggerObserver consoleObs;
    EmailNotifierObserver emailObs;
    model.attachObserver(&consoleObs);
    model.attachObserver(&emailObs);

    // 3. Декоратори (Decorator)
    BasicNotifier base;
    LoggingDecorator logger(&base);
    EncryptionDecorator fullPipeline(&logger);

    int id = 1;
    int choice = 0;

    // Цикл меню
    while (choice != 3) {
        cout << "\n=========================================\n";
        cout << "Поточна стратегія: " << model.getCurrentStrategyName() << "\n";
        cout << "1. Обрати стратегію податку\n";
        cout << "2. Ввести суму транзакції\n";
        cout << "3. Вийти\n";
        cout << "Оберіть дію: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int stratChoice;
            cout << "\n--- Вибір стратегії ---\n";
            cout << "1. Стандартна (19.5%)\n";
            cout << "2. IT-сектор (5%)\n";
            cout << "Ваш вибір: ";
            cin >> stratChoice;

            if (stratChoice == 1) {
                controller.setStrategy(new StandardTaxStrategy());
            }
            else if (stratChoice == 2) {
                controller.setStrategy(new ITSectorTaxStrategy());
            }
            else {
                cout << "Невідомий вибір стратегії!\n";
            }
            break;
        }
        case 2: {
            double amount;
            cout << "\nВведіть суму транзакції: ";
            cin >> amount;

            // Виклик контролера для обробки
            controller.createTransaction(id++, amount, &fullPipeline);
            break;
        }
        case 3:
            cout << "\nВихід з програми...\n";
            break;

        default:
            cout << "Невірний вибір, спробуйте ще раз.\n";
            break;
        }
    }

    return 0;
}