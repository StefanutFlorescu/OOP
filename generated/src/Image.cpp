// Created by stef on 10/22/24.

#include <utility>
#include "../include/Image.h"
#include "../include/Frame.h"

// Constructor: Initializes the Image object with the given image path
Image::Image(std::string imagePath) : imagePath(std::move(imagePath)) {
    saveToMemory();
};

// Copy constructor: Copies the image path and saves the image to memory
Image::Image(const Image &a) {
    this->imagePath = a.imagePath;
    this->saveToMemory();
}

// Save the image to memory by resizing it and saving scaled versions to disk
void Image::saveToMemory() const {
    // Load the image from the given file path
    const cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return;
    }

    // Get image dimensions and calculate the aspect ratio
    const int imageWidth = image.cols;
    const int imageHeight = image.rows;
    const float aspectOrig = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);
    const float aspectScreen = static_cast<float>(Frame::getWidth()) / static_cast<float>(Frame::getHeight());

    int scaledWidth, scaledHeight;

    // Scale the image while maintaining its aspect ratio
    if (aspectOrig > aspectScreen) {
        scaledWidth = Frame::getWidth();
        scaledHeight = static_cast<int>(static_cast<float>(scaledWidth) / aspectOrig);
    } else {
        scaledHeight = Frame::getHeight();
        scaledWidth = static_cast<int>(static_cast<float>(scaledHeight) * aspectOrig);
    }

    // Reduce the scaled dimensions to 60% of the original calculation
    scaledWidth *= 0.6;
    scaledHeight *= 0.6;

    // Resize the image
    cv::Mat resized;
    cv::resize(image, resized, cv::Size(scaledWidth, scaledHeight), cv::INTER_LINEAR);

    // Save the resized image to a temporary file
    std::string outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg";
    if (cv::imwrite(outputPath, resized)) {
        std::cout << "Image saved successfully to " << outputPath << std::endl;
    } else {
        std::cerr << "Failed to save the image!" << std::endl;
    }

    // Save the original image to another file
    std::string outputPath2 = "/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg";
    if (cv::imwrite(outputPath2, image)) {
        std::cout << "Image saved successfully to " << outputPath2 << std::endl;
    } else {
        std::cerr << "Failed to save the image!" << std::endl;
    }
}

// Display the resized image in the SFML window
void Image::displayImage(sf::RenderWindow& window) {
    LoadManager<sf::Texture> textureManager;
    const auto texture = textureManager.load("main", "/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg");
    // Create a sprite from the texture and center it horizontally
    sf::Sprite sprite(*texture);
    sprite.setPosition(static_cast<float>(Frame::getWidth()) / 2 - sprite.getGlobalBounds().width / 2, 25);

    // Draw the sprite in the window
    window.draw(sprite);
}

// Overload the << operator to print the image's path
std::ostream& operator<<(std::ostream& os, const Image& image) {
    os << "Image: " << image.imagePath << std::endl;
    return os;
}
