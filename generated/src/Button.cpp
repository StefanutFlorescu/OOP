//
// Created by stef on 10/22/24.
//

#include "../include/Button.h"
#include "../include/Frame.h"


Button::Button(const float x, const float y, const float width, const float height, const std::string& text)
{
    buttonShape.setPosition(x, y);
    buttonShape.setSize(sf::Vector2f(width, height));
    buttonShape.setFillColor(sf::Color(255, 215, 1));

    if(!font.loadFromFile("/System/Library/fonts/NewYork.ttf")) {
        std::cerr<<"Error in loading font!"<<std::endl;
        exit(1);
    }
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.width / 2, textRect.height / 2);
    buttonText.setPosition(
        x + width/2,
        y + height/2 - 5
    );
}

Button::Button(const Button &b) {
    this->buttonShape = b.buttonShape;
    this->buttonText = b.buttonText;
    this->font = b.font;
}

Button& Button::operator=(const Button& other) {
    if (this != &other) {
        buttonShape = other.buttonShape;
        buttonText = other.buttonText;
        font = other.font;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Button &button) {
    // Am avut nevoie de conversia de la final pentru tipurile de string
    os << button.buttonText.getString().toAnsiString()<< " a fost plasat!";
    return os;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(buttonShape);
    window.draw(buttonText);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return buttonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}


void Button::update(sf::RenderWindow& window, const sf::Event& event) {
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color::Yellow);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::cout << "Button clicked!" << std::endl;
        }
    } else {
        buttonShape.setFillColor(sf::Color::Blue);
    }
}

void Button::change_text(const std::string &text) {
    buttonText.setString(text);
}




OpenImageButton::OpenImageButton(const float x, const float y, const float width, const float height, const std::string &text)
    : Button(x, y, width, height, text){}


void OpenImageButton::update(sf::RenderWindow& window, const sf::Event& event) {
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            image = new Image("/Users/stefanutflorescu/Downloads/PhotoEditorPhoto-2/resources/image.jpg");
            Frame::switchReady();
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}
OpenImageButton::~OpenImageButton() {
        delete image;//Daca dezalocam un nullptr nu se intampla nimic
}



OpenInputButton::OpenInputButton(const float x, const float y, const float width, const float height, const std::string &text)
    : Button(x, y, width, height, text), text_input_frame(nullptr) {
}

void OpenInputButton::update(sf::RenderWindow& window, const sf::Event& event) {
    if(Frame::getReady())
        this->change_text("Remove Image");
    else
        this->change_text("Search Image");
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            if(!Frame::getReady()) {
                text_input_frame = new Text_Frame(500,300,window);
            } else {
                Frame::switchReady();
            }
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

OpenInputButton::~OpenInputButton() {
    delete text_input_frame;//Daca dezalocam un nullptr nu se intampla nimic
}

