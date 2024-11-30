//
// Created by stef on 10/29/24.
//

#include "../include/TextFrame.h"

// Converts a string to an integer, returning true if successful, or false if an error occurs
bool convertStringToInt(const std::string& inputString, int& result) {
    try {
        // Attempt to convert the string to an integer
        size_t pos;
        result = std::stoi(inputString, &pos);

        // Check if the entire string was converted
        if (pos != inputString.length()) {
            throw std::invalid_argument("Non-numeric characters found");
        }

        return true; // Conversion successful
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    return false; // Conversion failed
}

// Extracts all numbers from a given string and returns them as a vector of integers
std::vector<int> extractNumbersFromString(const std::string& inputString) {
    std::istringstream stream(inputString);
    std::vector<int> numbers;
    int number;

    while (stream >> number) {
        numbers.push_back(number); // Extract and store each number
    }

    return numbers;
}

// Constructor: Initializes the Text_Frame with specified dimensions, button type, and main window
TextFrame::TextFrame(int width, int height, sf::RenderWindow& window_main, const std::string& buttonType)
    : width(width), height(height) {

    // Initialize the appropriate button based on the button type
    if (buttonType == "Open") {
        openButton = std::make_unique<OpenImageButton>(static_cast<float>(width) / 2 - 100, static_cast<float>(height) - 100, 200, 50);
    } else if (buttonType == "Save") {
        openButton = std::make_unique<SaveOutputButton>(static_cast<float>(width) / 2 - 100, static_cast<float>(height) - 100, 200, 50, "Save");
    } else if (buttonType == "Saturation") {
        openButton = std::make_unique<SelectSaturationButton>(static_cast<float>(width) / 2 - 100, static_cast<float>(height) - 100, 200, 50, "Apply");
    } else if (buttonType == "Contrast") {
        openButton = std::make_unique<SelectContrastButton>(static_cast<float>(width) / 2 - 100, static_cast<float>(height) - 100, 200, 50, "Apply");
    } else if (buttonType == "Blur") {
        openButton = std::make_unique<SelectBlurButton>(static_cast<float>(width) / 2 - 100, static_cast<float>(height) - 100, 200, 50, "Apply");
    } else if (buttonType == "Crop") {
        openButton = std::make_unique<SelectCropButton>(static_cast<float>(width) / 2 - 100, static_cast<float>(height) - 100, 200, 50, "Apply");
    }

    // Set up the SFML render window
    sf::RenderWindow window(sf::VideoMode(width, height), "Choose an image");
    window.setVisible(true);
    window.requestFocus();

    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("/System/Library/fonts/NewYork.ttf")) {
        exit(1);
    }

    // Set up text properties
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 50);

    // Create an input box for user input
    sf::RectangleShape inputBox(sf::Vector2f(900, 50));
    inputBox.setFillColor(sf::Color(30, 30, 30));
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(45, 45);

    std::string inputString;

    // Main render loop
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Ensure window focus
            window.requestFocus();

            // Handle button updates
            openButton->update(window, event);

            // Process text input
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    // Handle backspace
                    if (event.text.unicode == '\b' && !inputString.empty()) {
                        inputString.pop_back();
                    }
                    // Handle other characters
                    else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                        inputString += static_cast<char>(event.text.unicode);
                    }
                }
            }

            // Handle specific button types and their respective logic
            if (dynamic_cast<OpenImageButton*>(openButton.get()) != nullptr) {
                dynamic_cast<OpenImageButton*>(openButton.get())->setImagePath(inputString);
            } else if (dynamic_cast<SaveOutputButton*>(openButton.get()) != nullptr) {
                dynamic_cast<SaveOutputButton*>(openButton.get())->setOutputPath(inputString);
            } else try {
                if (dynamic_cast<SelectSaturationButton*>(openButton.get()) != nullptr) {
                    int number;
                    if (convertStringToInt(inputString, number)) {
                        dynamic_cast<SelectSaturationButton*>(openButton.get())->changeValue(number);
                    }
                } else if (dynamic_cast<SelectContrastButton*>(openButton.get()) != nullptr) {
                    int number;
                    if (convertStringToInt(inputString, number)) {
                        dynamic_cast<SelectContrastButton*>(openButton.get())->changeValue(number);
                    }
                } else if (dynamic_cast<SelectBlurButton*>(openButton.get()) != nullptr) {
                    int number;
                    if (convertStringToInt(inputString, number)) {
                        dynamic_cast<SelectBlurButton*>(openButton.get())->changeValue(number);
                    }
                } else if (dynamic_cast<SelectCropButton*>(openButton.get()) != nullptr) {
                    std::vector<int> numbers = extractNumbersFromString(inputString);
                    if (!numbers.empty() && numbers.size() == 4) {
                        dynamic_cast<SelectCropButton*>(openButton.get())->changeValue(numbers[0], numbers[1], numbers[2], numbers[3]);
                    } else {
                        throw TextFrameException("Invalid crop values: " + inputString);
                    }
                }
            } catch (const TextFrameException& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        // Update displayed text
        text.setString(inputString);

        // Render window elements
        window.clear(sf::Color(44, 44, 44));
        openButton->draw(window);
        if (Frame::getReady()) {
            window.close();
        }
        window.draw(inputBox);
        window.draw(text);
        window.display();
    }
}

// Overloaded output operator for Text_Frame
std::ostream& operator<<(std::ostream& os, const TextFrame& tf) {
    os << "TextFrame has been rendered with width: " << tf.width << " and height: " << tf.height;
    return os;
}
