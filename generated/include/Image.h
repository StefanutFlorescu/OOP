//
// Created by stef on 10/22/24.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>


class Image {
private:
    std::string image_path;
    void save_to_memory() const;
public:
    explicit Image(std::string  = "Image Editor");
    ~Image() = default;
    Image(const Image& a);
    Image& operator=(const Image &a) {
        if (this != &a) {
            this->image_path = a.image_path;
            this->save_to_memory();
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const Image& image);
    static void display_image(sf::RenderWindow& window);

};

#endif //IMAGE_H
