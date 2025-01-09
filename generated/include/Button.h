//
// Created by stef on 10/22/24.
//
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <filesystem>
#include <utility>
#include "Image.h"
#include "TextFrame.h"
#include "Filter.h"
#include "Exception.h"
#include "LoadManager.h"
#include "Command.h"

/**
 * @class Button
 * Here we have tall the buttons that we use in the app
 */

// Forward declarations for classes used as pointers
class Filter;
class TextFrame;

// Base class representing a generic button
class Button {
protected:
    sf::RectangleShape buttonShape; // Shape of the button
    sf::Text buttonText;            // Text displayed on the button
    sf::Font font;                  // Font used for the text
    LoadManager<sf::Font> fontManager;
    // Checks if the mouse cursor is over the button
    bool isMouseOver(const sf::RenderWindow& window) const;

public:
    // Constructor to initialize a button with position, size, and text
    Button(float x,float y, float width, float height, const std::string& text);

    // Copy constructor
    Button(const Button &b);

    // Copy assignment operator
    Button& operator=(const Button& other);

    // Virtual destructor
    virtual ~Button() = default;

    // Overloads the << operator for Button class
    friend std::ostream& operator<<(std::ostream& os, const Button& button);

    // Virtual Constructor(Clone)
    virtual std::shared_ptr<Button> clone() const;

    // Updates the button's text
    void change_text(const std::string& text);

    // Draws the button to the window
    void draw(sf::RenderWindow& window) const;

    // Updates the button based on user interaction
    virtual void update(sf::RenderWindow& window, const sf::Event& event);
};

// Derived class for an Open Image button
class OpenImageButton final : public Button {
    Image* image{};            // Pointer to the image
    std::string imagePath;     // Path to the image

public:
    // Constructor with default text
    OpenImageButton(float x, float y, float width, float height, const std::string& text = "Open Image");

    // Virtual Constructor(Clone)
    std::shared_ptr<Button> clone() const override;

    // Updates the button on interaction
    void update(sf::RenderWindow& window, const sf::Event& event) override;

    // Sets the image path
    void setImagePath(std::string inputString) { imagePath = std::move(inputString); }

    // Destructor
    ~OpenImageButton() override;
};

// Derived class for an Open Input button
class OpenInputButton final : public Button {
    TextFrame* textInputFrame; // Pointer to a text frame

public:
    // Constructor with default text
    OpenInputButton(float x, float y, float width, float height, const std::string& text = "Search Image");

    // Virtual Constructor(Clone)
    std::shared_ptr<Button> clone() const override;

    // Updates the button on interaction
    void update(sf::RenderWindow& window, const sf::Event& event) override;

    // Destructor
    ~OpenInputButton() override;
};

// Derived class for a Save Image button
class SaveImageButton final : public Button {
    TextFrame* textInputFrame; // Pointer to a text frame

public:
    // Constructor with default text
    SaveImageButton(float x, float y, float width, float height, const std::string& text = "Save");

    // Virtual Constructor(Clone)
    std::shared_ptr<Button> clone() const override;

    // Updates the button on interaction
    void update(sf::RenderWindow& window, const sf::Event& event) override;

    // Destructor
    ~SaveImageButton() override;
};

// Derived class for a Save Output button
class SaveOutputButton final : public Button {
    std::string outputPath; // Path to save the output

public:
    // Constructor with default text
    SaveOutputButton(float x, float y, float width, float height, const std::string& text = "Save Image");

    // Virtual Constructor(Clone)
    std::shared_ptr<Button> clone() const override;

    // Updates the button on interaction
    void update(sf::RenderWindow& window, const sf::Event& event) override;

    // Sets the output path
    void setOutputPath(const std::string& inputString);

    // Destructor
    ~SaveOutputButton() override;
};

// Base class for filter-related buttons
class FilterButton : public Button {
protected:
    Filter* filter{}; // Pointer to a filter

public:
    // Constructor with default text
    FilterButton(const float x, const float y, const float width, const float height, const std::string& text = "Filter")
        : Button(x, y, width, height, text) {}

    // Virtual Constructor(Clone)
    virtual std::shared_ptr<FilterButton> clone();

    // Virtual function to handle interaction
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

// Derived classes for specific filter buttons (Blur, Crop, Contrast, Saturation)
class BlurFilterButton final : public FilterButton {
    TextFrame* textInputFrame;

public:
    BlurFilterButton(float x, float y, float width, float height, const std::string& text = "Blur");
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

class CropFilterButton final : public FilterButton {
    TextFrame* textInputFrame;

public:
    CropFilterButton(float x, float y, float width, float height, const std::string& text = "Crop");
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

class ContrastFilterButton final : public FilterButton {
    TextFrame* textInputFrame;

public:
    ContrastFilterButton(float x, float y, float width, float height, const std::string& text = "Contrast");
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

class SaturationFilterButton final : public FilterButton {
    TextFrame* textInputFrame;

public:
    SaturationFilterButton(float x, float y, float width, float height, const std::string& text = "Saturation");
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void update(sf::RenderWindow& window, const sf::Event& event) override;
};

// Derived classes for selecting specific filter values
class SelectSaturationButton final : public FilterButton {
    int value = 1;

public:
    SelectSaturationButton(float x, float y, float width, float height, const std::string& text = "Select");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void changeValue(const int value) { this->value = value; }
};

class SelectContrastButton final : public FilterButton {
    int value = 1;

public:
    SelectContrastButton(float x, float y, float width, float height, const std::string& text = "Select");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void changeValue(const int value) { this->value = value; }
};

class SelectBlurButton final : public FilterButton {
    int value = 1;

public:
    SelectBlurButton(float x, float y, float width, float height, const std::string& text = "Select");
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void changeValue(const int value) { this->value = value; }
};

class SelectCropButton final : public FilterButton {
    int a = 1, b = 1, c = 1, d = 1;

public:
    SelectCropButton(float x, float y, float width, float height, const std::string& text = "Select");
    // Virtual Constructor(Clone)
    std::shared_ptr<FilterButton> clone() override;
    void update(sf::RenderWindow& window, const sf::Event& event) override;
    void changeValue(const int a, const int b, const int c, const int d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
};


// To do .....
// Factory class for creating buttons
class ButtonFactory {
public:
    enum ButtonType {
        Open,
        Save,
        Saturation,
        Contrast,
        Blur,
        Crop
    };

    // Factory method to create buttons based on type
    static std::unique_ptr<Button> createButton(const ButtonType type, float x, float y, float width, float height, const std::string& text = "") {
        switch (type) {
            //Text frame buttons
        case Open:
            return std::make_unique<OpenImageButton>(x, y, width, height, text);
        case Save:
            return std::make_unique<SaveOutputButton>(x, y, width, height, text);
        case Saturation:
            return std::make_unique<SelectSaturationButton>(x, y, width, height, text);
        case Contrast:
            return std::make_unique<SelectContrastButton>(x, y, width, height, text);
        case Blur:
            return std::make_unique<SelectBlurButton>(x, y, width, height, text);
        case Crop:
            return std::make_unique<SelectCropButton>(x, y, width, height, text);
        default:
            throw TextFrameException("Unknown filter type");
        }
    }
};

#endif // BUTTON_H
