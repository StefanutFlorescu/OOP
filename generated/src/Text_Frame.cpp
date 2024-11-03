//
// Created by stef on 10/29/24.
//

#include "../include/Text_Frame.h"


Text_Frame::Text_Frame(int width, int height, sf::RenderWindow& window_main)
: width(width), height(height) {

    openImageButton = new OpenImageButton(static_cast<float>(width) / 2 - 100, static_cast<float>(height) - 100, 200, 50);
    sf::RenderWindow window(sf::VideoMode(width, height), "Choose an image");
    window.setVisible(true);
    window.requestFocus();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            window.requestFocus();

            openImageButton->update(window, event);
        }

        window.clear(sf::Color(44, 44, 44));
        openImageButton->draw(window);

        // Check if the image should be displayed in window_main
        if (Frame::getReady()) {
            window.close(); // Close the selection window
        }

        window.display();
    }

    // After the window closes, you might want to do something with window_main if needed
}

Text_Frame::~Text_Frame() {
    delete openImageButton;
}

std::ostream& operator<<(std::ostream& os, const Text_Frame& t) {
    os<<"Text_Frame has been rendered with width: "<<t.width<<" and height "<< t.height;
    return os;
}



