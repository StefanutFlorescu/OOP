//
// Created by Stefanut Florescu on 30.08.2025.
//

#include "../include/FileObserver.h"

FileObserver::FileObserver(const std::string& filename) {
    file.open(filename, std::ios::app);
}

FileObserver::~FileObserver() {
    if (file.is_open()) {
        file.close();
    }
}

void FileObserver::update(const std::string& message) {
    if (file.is_open()) {
        file << "[File] " << message << std::endl;
    }
}
