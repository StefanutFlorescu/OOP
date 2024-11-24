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
#include <filesystem>
#include <utility>
#include "Filter.h"

class Filter;
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
    virtual void update(sf::RenderWindow& window, const sf::Event& event) ;

};

class OpenImageButton : public Button  {
    Image* image{};
    std::string imagePath;
public:
    OpenImageButton(float x, float y, float width, float height,const std::string& text = "Open Image");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void setImagePath(std::string inputString){ imagePath = std::move(inputString); };
    ~OpenImageButton() override;
};


class OpenInputButton: public Button  {
    Text_Frame* text_input_frame;
public:
    OpenInputButton(float x, float y, float width, float height,const std::string& text = "Search Image");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    ~OpenInputButton() override;
};

class SaveImageButton : public Button  {
    Text_Frame* text_input_frame;
public:
    SaveImageButton(float x, float y, float width, float height,const std::string& text = "Save");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    ~SaveImageButton() override;
};


class SaveOutputButton final : public Button
{
    std::string output_path;
public:
    SaveOutputButton(float x, float y, float width, float height,const std::string& text = "Save Image");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void setOutputPath(const std::string& inputString);
    ~SaveOutputButton() override;
};


class FilterButton : public Button
{
protected:
    Filter* filter{};
public:
    FilterButton(float x, float y, float width, float height,const std::string& text = "Filter") : Button(x, y, width, height, text) {};
    virtual void update(sf::RenderWindow& window, const sf::Event& event) = 0;
};

class BlurFilterButton final : public FilterButton
{
    Text_Frame* text_input_frame;
public:
    BlurFilterButton(float x, float y, float width, float height,const std::string& text = "Blur");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

class CropFilterButton final : public FilterButton
{
    Text_Frame* text_input_frame;
public:
    CropFilterButton(float x, float y, float width, float height,const std::string& text = "Crop");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

class ContrastFilterButton final : public FilterButton
{
    Text_Frame* text_input_frame;
public:
    ContrastFilterButton(float x, float y, float width, float height,const std::string& text = "Contrast");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

class SaturationFilterButton final : public FilterButton
{
    Text_Frame* text_input_frame;
public:
    SaturationFilterButton(float x, float y, float width, float height,const std::string& text = "Saturation");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};


class SelectSaturationButton : public FilterButton
{
    int value = 1;
    public:
    SelectSaturationButton(float x, float y, float width, float height,const std::string& text = "Select");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void changeValue(int value){this->value = value;};
};


class SelectContrastButton : public FilterButton
{
    int value = 1;
public:
    SelectContrastButton(float x, float y, float width, float height,const std::string& text = "Select");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void changeValue(int value){this->value = value;};
};



class SelectBlurButton : public FilterButton
{
    int value = 1;
public:
    SelectBlurButton(float x, float y, float width, float height,const std::string& text = "Select");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void changeValue(int value){this->value = value;};
};



class SelectCropButton : public FilterButton
{
    int a = 1;
    int b = 1;
    int c = 1;
    int d = 1;
public:
    SelectCropButton(float x, float y, float width, float height,const std::string& text = "Select");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void changeValue(int a, int b, int c, int d){this->a = a;this->b = b;this->c = c;this->d = d;};
};





class ButtonFactory {
public:
    enum ButtonType {
        IMAGE,
        INPUT,
    };

    static std::unique_ptr<Button> createFilter(ButtonType type, float x, float y, float width, float height,const std::string& text = "") {
        switch (type) {
        case IMAGE:
            return std::make_unique<OpenImageButton>(x, y, width, height,text);
        case INPUT:
            return std::make_unique<OpenInputButton>(x, y, width, height,text);
        default:
            throw std::invalid_argument("Unknown filter type");
        }
    }
};




#endif //BUTTON_H
