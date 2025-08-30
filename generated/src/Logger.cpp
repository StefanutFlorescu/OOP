//
// Created by Stefanut Florescu on 30.08.2025.
//
#include "../include/Logger.h"

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance() {
    if (!instance) {
        instance = new Logger();
    }
    return instance;
}

void Logger::addObserver(IObserver* obs) {
    observers.push_back(obs);
}

void Logger::log(const std::string& message) {
    for (auto* obs : observers) {
        obs->update(message);
    }
}

