#pragma once
#include <iostream>
#include <string>
#include <ctime>

class INotifier {
public:
    virtual ~INotifier() = default;
    virtual std::string send(const std::string& message) const = 0;
};

class BasicNotifier : public INotifier {
public:
    std::string send(const std::string& message) const override {
        return message;
    }
};

class BaseNotifierDecorator : public INotifier {
protected:
    INotifier* m_wrapped;
public:
    explicit BaseNotifierDecorator(INotifier* notifier)
        : m_wrapped(notifier) {
    }

    std::string send(const std::string& message) const override {
        if (m_wrapped) {
            return m_wrapped->send(message);
        }
        return message;
    }
};

class LoggingDecorator : public BaseNotifierDecorator {
public:
    explicit LoggingDecorator(INotifier* notifier)
        : BaseNotifierDecorator(notifier) {
    }

    std::string send(const std::string& message) const override {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        char timeBuffer[80];
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &ltm);

        std::string formatted = "[" + std::string(timeBuffer) + "] " + message;
        return m_wrapped->send(formatted);
    }
};

class EncryptionDecorator : public BaseNotifierDecorator {
public:
    explicit EncryptionDecorator(INotifier* notifier)
        : BaseNotifierDecorator(notifier) {
    }

    std::string send(const std::string& message) const override {
        std::string encrypted_msg = "***[ENCRYPTED](" + message + ")***";
        return m_wrapped->send(encrypted_msg);
    }
};