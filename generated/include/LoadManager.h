//
// Created by Stefanut Florescu on 12.12.2024.
//

#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include "Command.h"

template <typename Resource>
class LoadManager {
private:
    std::map<std::string, std::shared_ptr<Resource>> resources; // Stores loaded resources

public:
    // Load a resource from a file
    std::shared_ptr<Resource> load(const std::string& name, const std::string& filepath) {
        // Check if the resource is already loaded
        if (!resources.contains(name)) {
            auto resource = std::make_shared<Resource>();
            if (!resource->loadFromFile(filepath)) {
                throw std::runtime_error("Failed to load resource from: " + filepath);
            }
            resources[name] = resource; // Cache the loaded resource
        }
        return resources[name];
    }

    // Get a loaded resource by name
    std::shared_ptr<Resource> get(const std::string& name) const {
        auto it = resources.find(name);
        if (it == resources.end()) {
            throw std::runtime_error("Resource not found: " + name);
        }
        return it->second;
    }

    // Clear all resources
    void clear() {
        resources.clear();
    }

    //From Command Design Pattern
    void executeCommand(Command& command) {
        command.execute();
    }
};

template <typename Resource>
class LoadResourceCommand final : public Command {
private:
    LoadManager<Resource>& manager;
    std::string name;
    std::string filepath;

public:
    LoadResourceCommand(LoadManager<Resource>& manager, const std::string& name, const std::string& filepath)
        : manager(manager), name(name), filepath(filepath) {}

    void execute() override {
        manager.load(name, filepath);
        std::cout << "Loaded resource: " << name << " from " << filepath << std::endl;
    }
};

template <typename Resource>
class ClearResourcesCommand : public Command {
private:
    LoadManager<Resource>& manager;

public:
    explicit ClearResourcesCommand(LoadManager<Resource>& manager) : manager(manager) {}

    void execute() override {
        manager.clear();
        std::cout << "Cleared all resources." << std::endl;
    }
};







#endif //LOADMANAGER_H
