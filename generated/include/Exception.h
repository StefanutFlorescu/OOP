//
// Created by Stefanut Florescu on 19.11.2024.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>
#include <iostream>

class ApplicationException : public std::exception {
protected:
    std::string message;
public:
    explicit ApplicationException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class ImageException : public ApplicationException
{
public:
    explicit ImageException(const std::string& msg) : ApplicationException(msg) {}
};

class FilterException : public ApplicationException
{
public:
    explicit FilterException(const std::string& msg) : ApplicationException(msg) {}
};

class FrameException : public ApplicationException
{
public:
    explicit FrameException(const std::string& msg) : ApplicationException(msg) {}
};

class TextFrameException : public ApplicationException
{
public:
    explicit TextFrameException(const std::string& msg) : ApplicationException(msg) {}
};


#endif //EXCEPTION_H
