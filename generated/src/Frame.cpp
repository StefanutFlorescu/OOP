#include "../include/Frame.h"
#include <memory> // For std::unique_ptr
#include <array>  // For std::array
#include <exception> // For exception handling

// Constructor: Initializes a Frame object with the specified title
Frame::Frame(const std::string& title) {
    // Observers
    Logger* logger = Logger::getInstance();

    static ConsoleObserver consoleObs;
    static FileObserver fileObs("log.txt");

    logger->addObserver(&consoleObs);
    logger->addObserver(&fileObs);

    logger->log("Frame created with title: " + title);

    try {
        // Initialize all buttons
        initializeButtons();

        // Set up window dimensions and create the render window
        const int width = WIDTH;
        const int height = HEIGHT;
        sf::RenderWindow window(sf::VideoMode(width, height), title);

        // Main event loop
        while (window.isOpen()) {
            handleEvents(window); // Process user input and events
            render(window);       // Render all elements to the screen
        }
    } catch (const ButtonException& e) {
        std::cerr << "Error initializing Frame: " << e.what() << std::endl;
    } catch (const FrameException& e) {
        std::cerr << "Error initializing Frame: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unknown error occurred while initializing Frame." << std::endl;
    }
}

// Private helper function: Initializes all buttons for the frame
void Frame::initializeButtons() {
    try {
        // Create the "Open Input" button
        searchImageButton = std::make_unique<OpenInputButton>(
            static_cast<float>(WIDTH) / 2 - 100,
            static_cast<float>(HEIGHT) - 100,
            200,
            50
        );

        // Create the "Save" button
        saveButton = std::make_unique<SaveImageButton>(
            static_cast<float>(WIDTH) / 2 + 150,
            static_cast<float>(HEIGHT) - 100,
            200,
            50,
            "Save"
        );

        // Initialize filter buttons using an array of std::unique_ptr
        filterButtons = {
            std::make_unique<BlurFilterButton>(
                static_cast<float>(WIDTH) / 2 - 350,
                static_cast<float>(HEIGHT) - 100,
                200,
                50,
                "Blur"
            ),
            std::make_unique<SaturationFilterButton>(
                static_cast<float>(WIDTH) / 2 - 350,
                static_cast<float>(HEIGHT) - 175,
                200,
                50,
                "Saturation"
            ),
            std::make_unique<ContrastFilterButton>(
                static_cast<float>(WIDTH) / 2 - 100,
                static_cast<float>(HEIGHT) - 175,
                200,
                50,
                "Contrast"
            ),
            std::make_unique<CropFilterButton>(
                static_cast<float>(WIDTH) / 2 + 150,
                static_cast<float>(HEIGHT) - 175,
                200,
                50,
                "Crop"
            )
        };
    } catch (const ButtonException& e) {
        std::cerr << "Error initializing buttons: " << e.what() << std::endl;
        throw; // Rethrow to propagate the error to the Frame constructor
    }
}

// Private helper function: Handles events for the window
void Frame::handleEvents(sf::RenderWindow& window) const {
    try {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close the window if the close event is triggered
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Update the state of each button
            searchImageButton->update(window, event);
            saveButton->update(window, event);
            for (const auto& button : filterButtons) {
                button->update(window, event);
            }
        }
    } catch (const FrameException& e) {
        std::cerr << "Error handling events: " << e.what() << std::endl;
    } catch (const ButtonException& e)
    {
        std::cerr << "Error handling the buttons: " << e.what() << std::endl;
    }

}

// Private helper function: Renders all elements to the window
void Frame::render(sf::RenderWindow& window) const {
    try {
        // Clear the window with a dark gray color
        window.clear(sf::Color(44, 44, 44));

        // Draw the "Open Input" and "Save" buttons
        searchImageButton->draw(window);
        saveButton->draw(window);

        // Draw all filter buttons
        for (const auto& button : filterButtons) {
            button->draw(window);
        }

        // Display the image if the frame is ready
        if (Frame::getReady()) {
            Image::displayImage(window);
        }

        // Display the rendered content on the screen
        window.display();
    } catch (const FrameException& e) {
        std::cerr << "Error rendering window: " << e.what() << std::endl;
    } catch (const ButtonException& e)
    {
        std::cerr << "Error rendering the buttons: " << e.what() << std::endl;
    }
}


// Overloaded output operator for the Frame class
std::ostream& operator<<(std::ostream& os, const Frame& frame) {
    os << "Frame-ul are " << Frame::getWidth() << " x " << Frame::getHeight() << " y";
    return os;
}

// Static member function: Get the width of the frame
int Frame::getWidth() {
    return WIDTH;
}

// Static member function: Get the height of the frame
int Frame::getHeight() {
    return HEIGHT;
}

// Static member function: Toggle the READY flag and return its new state
bool Frame::switchReady() {
    READY = !READY;
    return READY;
}

// Static member function: Get the current state of the READY flag
bool Frame::getReady() {
    return READY;
}
