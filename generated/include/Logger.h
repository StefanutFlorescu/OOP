#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include "IObserver.h"

class Logger {
private:
    std::vector<IObserver*> observers;

    static Logger* instance;

    Logger() = default;

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* getInstance();

    void addObserver(IObserver* obs);
    void log(const std::string& message);
};

#endif // LOGGER_H
