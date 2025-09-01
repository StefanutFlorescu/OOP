//
// Created by Stefanut Florescu on 30.08.2025.
//

#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include "IObserver.h"
#include <fstream>
#include <string>

class FileObserver : public IObserver {
private:
    std::ofstream file;
public:
    explicit FileObserver(const std::string& filename);
    ~FileObserver() override;

    void update(const std::string& message) override;
};

#endif // FILEOBSERVER_H

