//
// Created by Stefanut Florescu on 01.01.2025.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
// Command design pattern used for the LoadManager to add a layer of abstractization in case of an update
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

#endif //COMMAND_H
