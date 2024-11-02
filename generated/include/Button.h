//
// Created by stef on 10/22/24.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Image.h"
#include "Text_Frame.h"
#include <iostream>

class Text_Frame;

class Button {
protected:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font font;
    bool isMouseOver(const sf::RenderWindow& window) const;

public:
    Button(float x, float y, float width, float height, const std::string& text);
    Button(const Button &b);
    Button& operator=(const Button& other);
    virtual ~Button() = default;
    friend std::ostream& operator<<(std::ostream& os, const Button& button);

    void change_text(const std::string& text);
    void draw(sf::RenderWindow& window) const;
    virtual void update(sf::RenderWindow& window, const sf::Event& event);

};

class OpenImageButton : public Button  {
    Image* image{};
public:
    OpenImageButton(float x, float y, float width, float height,const std::string& text = "Open Image");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    ~OpenImageButton() override;
};


class OpenInputButton: public Button  {
    Text_Frame* text_input_frame;
public:
    OpenInputButton(float x, float y, float width, float height,const std::string& text = "Search Image");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    ~OpenInputButton() override;
};


#endif //BUTTON_H
