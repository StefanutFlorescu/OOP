//
// Created by stef on 10/29/24.
//

#ifndef TEXT_FRAME_H
#define TEXT_FRAME_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Frame.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Button.h"

class OpenImageButton;

class Text_Frame {
    OpenImageButton *openImageButton;
    int width, height;
public:
    Text_Frame(int width, int height, sf::RenderWindow& window_main);
    Text_Frame(const Text_Frame &other) = delete;
    ~Text_Frame();
    friend std::ostream& operator<<(std::ostream& os, const Text_Frame& tf);
};



#endif //TEXT_FRAME_H
