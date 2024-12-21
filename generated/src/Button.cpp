//
// Created by stef on 10/22/24.
//

#include "../include/Button.h"
#include "../include/Frame.h"

// Initializing the buttons
Button::Button(const float x, const float y, const float width, const float height, const std::string& text)
{
    buttonShape.setPosition(x, y); // Setting the position on the screen
    buttonShape.setSize(sf::Vector2f(width, height)); // Setting the size for the button
    buttonShape.setFillColor(sf::Color(255, 215, 1)); // Setting the base color of the button

    // Insantiation of the LoadManager Template class with sd::Font
    LoadManager<sf::Font> fontManager;  // Changed to a more appropriate name
    const auto mainFont = fontManager.load("mainFont", "/System/Library/fonts/NewYork.ttf");
    font = *mainFont;
    buttonText.setFont(font); // Setting the font
    buttonText.setString(text); // Setting the text of the button
    buttonText.setCharacterSize(24); // Setting the font size
    buttonText.setFillColor(sf::Color::White); // Setting the text color
    const sf::FloatRect textRect = buttonText.getLocalBounds(); // Centralizing the text for the button
    buttonText.setOrigin(textRect.width / 2, textRect.height / 2); // setting the position for the text
    buttonText.setPosition( // setting the position for the text
        x + width / 2,
        y + height / 2 - 5
    );
}

// Copy constructor
Button::Button(const Button& b)
{
    this->buttonShape = b.buttonShape;
    this->buttonText = b.buttonText;
    this->font = b.font;
}

// Overloading the =operator
Button& Button::operator=(const Button& other)
{
    if (this != &other)
    {
        buttonShape = other.buttonShape;
        buttonText = other.buttonText;
        font = other.font;
    }
    return *this;
}

// Overloading the <<operator
std::ostream& operator<<(std::ostream& os, const Button& button)
{
    os << button.buttonText.getString().toAnsiString() << " was placed!";
    return os;
}

// Drawing the button on the screen
void Button::draw(sf::RenderWindow& window) const
{
    window.draw(buttonShape);
    window.draw(buttonText);
}

// Verifying if the mouse is over the button
bool Button::isMouseOver(const sf::RenderWindow& window) const
{
    const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return buttonShape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

// Updating the button
void Button::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color::Yellow);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            std::cout << "Button clicked!" << std::endl;
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color::Blue);
    }
}

// Changing the button text
void Button::change_text(const std::string& text)
{
    buttonText.setString(text);
}

// The button that gets an image on the screen
OpenImageButton::OpenImageButton(const float x, const float y, const float width, const float height,
                                 const std::string& text)
    : Button(x, y, width, height, text)
{
}

// Updating the button, that if the imagePath is correct the image should be rendered on the screen
void OpenImageButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0)); //also if the mouse over the button the color should change
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (!std::filesystem::exists(imagePath))
            {
                std::cerr << "Error: Image file does not exist at path: " << imagePath << std::endl;
            }
            else
            {
                image = new Image(imagePath);
                Frame::switchReady(); // This will make the app render the image
            }
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1)); // when the mouse is not on the button the color is back to normal
    }
}

OpenImageButton::~OpenImageButton()
{
    delete image; // Freeing the space for the image
}

// Constructor for OpenInputButton
OpenInputButton::OpenInputButton(const float x, const float y, const float width, const float height,
                                 const std::string& text)
    : Button(x, y, width, height, text), textInputFrame(nullptr)
{
}

// Update function for OpenInputButton
void OpenInputButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    // Change button text based on Frame readiness
    if (Frame::getReady())
        this->change_text("Remove Image");
    else
        this->change_text("Search Image");

    // Check if mouse is over the button
    if (isMouseOver(window))
    {
        // Change button color to indicate hover state
        buttonShape.setFillColor(sf::Color(200, 0, 0));

        // Check for mouse button press event
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            // Create a new Text_Frame if Frame is not ready
            if (!Frame::getReady())
            {
                textInputFrame = new TextFrame(1000, 300, window, "Open");
            }
            else
            {
                // Toggle Frame readiness
                Frame::switchReady();
            }
        }
    }
    else
    {
        // Default button color when not hovered
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Destructor for OpenInputButton
OpenInputButton::~OpenInputButton()
{
    // Safely delete the text_input_frame pointer
    delete textInputFrame; // Deallocating a nullptr is safe and has no effect
}

// Constructor for SaveOutputButton
SaveOutputButton::SaveOutputButton(const float x, const float y, const float width, const float height,
                                   const std::string& text)
    : Button(x, y, width, height, text)
{
}

// Setter for output path in SaveOutputButton
void SaveOutputButton::setOutputPath(const std::string& inputString)
{
    outputPath = inputString;
}

// Update function for SaveOutputButton
void SaveOutputButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    // Check if mouse is over the button
    if (isMouseOver(window))
    {
        // Change button color to indicate hover state
        buttonShape.setFillColor(sf::Color(200, 0, 0));

        // Check for mouse button press event
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            // Verify if the image file exists at the specified path
            if (!std::filesystem::exists("/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg"))
            {
                std::cerr << "Error: Image file does not exist at path: "
                          << "/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg" << std::endl;
            }
            else
            {
                // Read the image file
                const cv::Mat image = cv::imread("/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg",
                                                 cv::IMREAD_COLOR);

                // Attempt to save the image
                if (cv::imwrite(outputPath, image))
                {
                    std::cout << "Image saved successfully to " << outputPath << std::endl;
                    Frame::switchReady();
                }
                else
                {
                    std::cerr << "Failed to save the image!" << std::endl;
                }
            }
        }
    }
    else
    {
        // Default button color when not hovered
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Destructor for SaveOutputButton
SaveOutputButton::~SaveOutputButton() = default;

// Constructor for SaveImageButton
SaveImageButton::SaveImageButton(const float x, const float y, const float width, const float height,
                                 const std::string& text)
    : Button(x, y, width, height, text), textInputFrame(nullptr)
{
}

// Update function for SaveImageButton
void SaveImageButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    // Check if mouse is over the button
    if (isMouseOver(window))
    {
        // Change button color to indicate hover state
        buttonShape.setFillColor(sf::Color(200, 0, 0));

        // Check for mouse button press event
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            Frame::switchReady(); // Toggle Frame readiness
            textInputFrame = new TextFrame(1000, 300, window, "Save");
        }
    }
    else
    {
        // Default button color when not hovered
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Destructor for SaveImageButton
SaveImageButton::~SaveImageButton()
{
    // Safely delete the text_input_frame pointer
    delete textInputFrame; // Deallocating a nullptr is safe and has no effect
}

// Constructor for BlurFilterButton
BlurFilterButton::BlurFilterButton(const float x, const float y, const float width, const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new BlurFilter(); // Initialize with BlurFilter
}

// Update function for BlurFilterButton
void BlurFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        // Highlight button when hovered
        buttonShape.setFillColor(sf::Color(200, 0, 0));

        // Check for mouse click event
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            Frame::switchReady(); // Toggle readiness of the frame
            textInputFrame = new TextFrame(1000, 300, window, "Blur");
        }
    }
    else
    {
        // Default button color
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Constructor for CropFilterButton
CropFilterButton::CropFilterButton(const float x, const float y, const float width, const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new CropFilter(); // Initialize with CropFilter
}

// Update function for CropFilterButton
void CropFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            Frame::switchReady();
            textInputFrame = new TextFrame(1000, 300, window, "Crop");
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Constructor for ContrastFilterButton
ContrastFilterButton::ContrastFilterButton(const float x, const float y, const float width, const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new ContrastFilter(); // Initialize with ContrastFilter
}

// Update function for ContrastFilterButton
void ContrastFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            Frame::switchReady();
            textInputFrame = new TextFrame(1000, 300, window, "Contrast");
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Constructor for SaturationFilterButton
SaturationFilterButton::SaturationFilterButton(const float x, const float y, const float width, const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new SaturationFilter(); // Initialize with SaturationFilter
}

// Update function for SaturationFilterButton
void SaturationFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            Frame::switchReady();
            textInputFrame = new TextFrame(1000, 300, window, "Saturation");
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Constructor for SelectSaturationButton
SelectSaturationButton::SelectSaturationButton(const float x,const float y,const float width,const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new SaturationFilter(); // Initialize with SaturationFilter
}

// Update function for SelectSaturationButton
void SelectSaturationButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            dynamic_cast<SaturationFilter*>(filter)->setSaturation(value); // Set saturation value
            filter->applyFilter(); // Apply the filter
            Frame::switchReady();
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Constructor for SelectContrastButton
SelectContrastButton::SelectContrastButton(const float x,const float y,const float width,const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new ContrastFilter(); // Initialize with ContrastFilter
}

// Update function for SelectContrastButton
void SelectContrastButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            dynamic_cast<ContrastFilter*>(filter)->setContrast(value); // Set contrast value
            filter->applyFilter(); // Apply the filter
            Frame::switchReady();
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Constructor for SelectBlurButton
SelectBlurButton::SelectBlurButton(const float x,const float y,const float width,const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new BlurFilter(); // Initialize with BlurFilter
}

// Update function for SelectBlurButton
void SelectBlurButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            dynamic_cast<BlurFilter*>(filter)->setBlur(value); // Set blur value
            filter->applyFilter(); // Apply the filter
            Frame::switchReady();
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

// Constructor for SelectCropButton
SelectCropButton::SelectCropButton(const float x,const float y,const float width,const float height, const std::string& text)
    : FilterButton(x, y, width, height, text)
{
    filter = new CropFilter(); // Initialize with CropFilter
}

// Update function for SelectCropButton
void SelectCropButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window))
    {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            dynamic_cast<CropFilter*>(filter)->setCrop(a, b, c, d); // Set crop dimensions
            filter->applyFilter(); // Apply the filter
            Frame::switchReady();
        }
    }
    else
    {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}



/////----------------------Virtual Constructors-----------------------//////


std::shared_ptr<Button> Button::clone() const
{
    return std::make_shared<Button>(*this);
}

std::shared_ptr<Button> OpenImageButton::clone() const
{
    return std::make_shared<OpenImageButton>(*this);
}

std::shared_ptr<Button> OpenInputButton::clone() const
{
    return std::make_shared<OpenInputButton>(*this);
}

std::shared_ptr<Button> SaveImageButton::clone() const
{
    return std::make_shared<SaveImageButton>(*this);
}

std::shared_ptr<Button> SaveOutputButton::clone() const
{
    return std::make_shared<SaveOutputButton>(*this);
}




std::shared_ptr<FilterButton> BlurFilterButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}

std::shared_ptr<FilterButton> CropFilterButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}

std::shared_ptr<FilterButton> ContrastFilterButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}

std::shared_ptr<FilterButton> SaturationFilterButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}



std::shared_ptr<FilterButton> SelectSaturationButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}

std::shared_ptr<FilterButton> SelectBlurButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}

std::shared_ptr<FilterButton> SelectContrastButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}
std::shared_ptr<FilterButton> SelectCropButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}

std::shared_ptr<FilterButton> FilterButton::clone()
{
    return std::make_shared<FilterButton>(*this);
}

void FilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    std::cout<<"Updated!"<<std::endl;
}







