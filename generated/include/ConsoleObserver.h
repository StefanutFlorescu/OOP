//
// Created by Stefanut Florescu on 30.08.2025.
//

#ifndef CONSOLEOBSERVER_H
#define CONSOLEOBSERVER_H

#include "IObserver.h"
#include <iostream>

class ConsoleObserver : public IObserver {
public:
    void update(const std::string& message) override;
};

#endif // CONSOLEOBSERVER_H
