//
// Created by Stefanut Florescu on 12.12.2024.
//

#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>

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
};



#endif //LOADMANAGER_H
