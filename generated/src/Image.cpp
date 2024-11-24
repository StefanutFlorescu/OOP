//
// Created by stef on 10/22/24.
//

#include <utility>

#include "../include/Image.h"

#include "../include/Frame.h"

Image::Image(std::string ImagePath) : image_path(std::move(ImagePath)) {
    save_to_memory();
};

Image::Image(const Image &a) {
    this->image_path = a.image_path;
    this->save_to_memory();
}

void Image::save_to_memory() const
{
    const cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
    if(image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
    }

    const int image_width = image.cols;
    const int image_height = image.rows;
    const float aspect_orig = static_cast<float>(image_width) / static_cast<float>(image_height);
    const float aspect_screen = static_cast<float>(Frame::getWidth()) / static_cast<float>(Frame::getHeight());

    int scaled_width, scaled_height;

    if (aspect_orig > aspect_screen) {
        scaled_width = Frame::getWidth();
        scaled_height = static_cast<int>(static_cast<float>(scaled_width) / aspect_orig);
    } else {
        scaled_height = Frame::getHeight();
        scaled_width = static_cast<int>(static_cast<float>(scaled_height) * aspect_orig);
    }
    scaled_width *= 0.6;
    scaled_height *= 0.6;

    cv::Mat resized;
    resize(image, resized, cv::Size(scaled_width, scaled_height), cv::INTER_LINEAR);

    std::string outputPath = "/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg";
    if (cv::imwrite(outputPath, resized)) {
        std::cout << "Image saved successfully to " << outputPath << std::endl;
    } else {
        std::cerr << "Failed to save the image!" << std::endl;
    }

    std::string outputPath2 = "/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg";
    if (cv::imwrite(outputPath2, image)) {
        std::cout << "Image saved successfully to " << outputPath2 << std::endl;
    } else {
        std::cerr << "Failed to save the image!" << std::endl;
    }

}


void Image::display_image(sf::RenderWindow& window) {
    sf::Texture texture;
    if (!texture.loadFromFile("/Users/stefanutflorescu/Downloads/OOP-main/resources/temp.jpg")) {
        std::cerr << "Error loading image!" << std::endl;
        return;
    }
    sf::Sprite sprite(texture);
    sprite.setPosition(static_cast<float>(Frame::getWidth())/2 - sprite.getGlobalBounds().width/2, 25);
    window.draw(sprite);
}

std::ostream& operator<<(std::ostream& os, const Image& image) {
    os << "Image: " << image.image_path << std::endl;
    return os;
}






