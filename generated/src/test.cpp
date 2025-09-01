//
// Created by stef on 10/27/24.
//
#include "../include/test.h"

TEST_CASE("Test functional") {
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
}
TEST_CASE("Load Manager") {
    // Test loading a texture
    try {
        LoadManager<sf::Texture> textureManager;
        auto backgroundTexture = textureManager.load("main", "/Users/stefanutflorescu/Documents/OOP/OOP/resources/temp.jpg");

        if (!backgroundTexture) {
            throw std::runtime_error("backgroundTexture is null after loading.");
        }
        std::cout << "Texture loaded successfully." << std::endl;
    } catch (const std::exception& e) {
        FAIL(e.what());
    }

    // Test loading a font
    try {
        LoadManager<sf::Font> fontManager;  // Changed to a more appropriate name
        auto mainFont = fontManager.load("mainFont", "/System/Library/fonts/NewYork.ttf");

        if (!mainFont) {
            throw std::runtime_error("mainFont is null after loading.");
        }

        std::cout << "Font loaded successfully." << std::endl;

        // Optional: Check if the font is valid by using it in a simple SFML object
        sf::Text testText;
        testText.setFont(*mainFont);
        testText.setString("Test");
        if (testText.getFont() != mainFont.get()) {
            throw std::runtime_error("Failed to set the font properly.");
        }

    } catch (const std::exception& e) {
        FAIL(e.what());
    }
}