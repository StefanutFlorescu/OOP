#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory> // For std::unique_ptr
#include <array>  // For std::array
#include "TextFrame.h"
#include "Image.h"
#include "Button.h"
// Forward declarations of classes used within Frame
class Button;
class OpenInputButton;
class SaveImageButton;
class FilterButton;

/**
 * @class Frame
 * Represents the main application frame that handles UI elements, rendering, and events.
 */
class Frame {
private:
    // Static members: Shared application properties
    static int WIDTH;  // Application width
    static int HEIGHT; // Application height
    static bool READY; // Controls whether the image is ready to display or filter

    // UI components
    std::array<std::unique_ptr<FilterButton>, 4> filterButtons; // Array of filter buttons
    std::unique_ptr<OpenInputButton> searchImageButton;         // Button for opening input files
    std::unique_ptr<SaveImageButton> saveButton;                // Button for saving images

    // Private member functions
    void initializeButtons();                     // Initializes all buttons in the frame
    void handleEvents(sf::RenderWindow& window) const; // Handles user events
    void render(sf::RenderWindow& window) const;  // Renders all elements to the window

public:
    // Constructor and destructor
    explicit Frame(const std::string& title); // Constructs a Frame object with a given title
    ~Frame() = default;                       // Default destructor for automatic cleanup

    // Deleting copy and move semantics to ensure a single instance of Frame
    Frame(const Frame&) = delete;            // Delete copy constructor
    Frame(Frame&&) = delete;                 // Delete move constructor
    Frame& operator=(const Frame&) = delete; // Delete copy assignment operator

    // Friend function for output streaming
    friend std::ostream& operator<<(std::ostream& os, const Frame& frame);

    // Static utility functions
    [[nodiscard]] static int getWidth();       // Retrieves the application width
    [[nodiscard]] static int getHeight();      // Retrieves the application height
    static bool switchReady();   // Toggles the READY state
    [[nodiscard]] static bool getReady();      // Retrieves the READY state
};

#endif // FRAME_H
