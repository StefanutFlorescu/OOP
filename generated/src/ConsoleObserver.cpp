//
// Created by Stefanut Florescu on 30.08.2025.
//
#include "../include/ConsoleObserver.h"
#include <iostream>

void ConsoleObserver::update(const std::string& message) {
    std::cout << "[Console] " << message << std::endl;
}