// Created by stef on 10/22/24.

#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

/**
 * @class Image
 * Here we have the Image class
 */

// The Image class represents an image file and provides functionality for
// managing the image, such as saving to memory and displaying it in a window.
class Image {
private:
    // Path to the image file
    std::string imagePath;

    // Saves the image to memory after resizing and adjusting its dimensions
    void saveToMemory() const;

public:
    // Constructor: Initializes the Image object with an optional image path.
    explicit Image(std::string imagePath);

    // Destructor: Default destructor
    ~Image() = default;

    // Copy constructor: Copies an existing Image object
    Image(const Image& a);

    // Copy assignment operator: Assigns one Image object to another,
    // copying the image path and saving the new image to memory
    Image& operator=(const Image& a) {
        if (this != &a) {
            this->imagePath = a.imagePath;
            this->saveToMemory();
        }
        return *this;
    }

    // Overloaded << operator: Outputs the image details to a stream
    friend std::ostream& operator<<(std::ostream& os, const Image& image);

    // Displays the image in an SFML RenderWindow
    static void displayImage(sf::RenderWindow& window);
};

#endif // IMAGE_H
