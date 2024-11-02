#include "../include/Frame.h"

Frame::Frame(const std::string& title){
    searchImageButton= new OpenInputButton(static_cast<float>(WIDTH)/2 - 100, static_cast<float>(HEIGHT)-100, 200, 50);
    const int width = WIDTH;
    const int height = HEIGHT;
    sf::RenderWindow window(sf::VideoMode(width, height), title);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            searchImageButton->update(window, event);
        }

        window.clear(sf::Color(44, 44, 44));
        searchImageButton->draw(window);

        if (Frame::getReady()) {
            Image::display_image(window);
        }

        window.display();
    }

}
std::ostream& operator<<(std::ostream& os, const Frame& frame) {
    os << "Frame-ul are" << Frame::getWidth() << "x" << Frame::getHeight() << std::endl;
    return os;
}
int Frame::getWidth() {
    return WIDTH;
}
int Frame::getHeight() {
    return HEIGHT;
}

bool Frame::switchReady() {
    READY = !READY;
    return READY;
}

bool Frame::getReady() {
    return READY;
}

