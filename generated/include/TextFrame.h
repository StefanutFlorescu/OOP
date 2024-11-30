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
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <SFML/Window/VideoMode.hpp>
#include <vector>


#include "Button.h"

/**
 * @class TextFrame
 * Every input will go through this TextFrame
 */

class OpenImageButton;

class TextFrame
{
    std::unique_ptr<Button> openButton;
    int width, height;

public:
    TextFrame(int width, int height, sf::RenderWindow& window_main, const std::string& buttonType);
    TextFrame(const TextFrame& other) = delete;
    ~TextFrame() = default;
    friend std::ostream& operator<<(std::ostream& os, const TextFrame& tf);

    void handleTextInput(const sf::Event& event, std::string& inputString);
    void handleButtonUpdate(const std::string& inputString, std::unique_ptr<Button>& openButton);
};


#endif //TEXT_FRAME_H
