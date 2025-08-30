//
// Created by Stefanut Florescu on 30.08.2025.
//

#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string& message) = 0;
};

#endif // IOBSERVER_H
