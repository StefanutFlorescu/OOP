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
            if (!std::filesystem::exists(imagePath)) {
                std::cout<<"File Path :"<<imagePath<<std::endl;
                std::cerr << "Error: Image file does not exist at path: " << imagePath << std::endl;
            }
            else
            {
                image = new Image(imagePath);
                Frame::switchReady();
            }
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
                text_input_frame = new Text_Frame(1000,300,window,"Open");
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


SaveOutputButton::SaveOutputButton(const float x, const float y, const float width, const float height, const std::string &text)
    : Button(x, y, width, height, text){}

void SaveOutputButton::setOutputPath(const std::string& inputString)
{
    output_path = inputString;
}

void SaveOutputButton::update(sf::RenderWindow& window, const sf::Event& event) {
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (!std::filesystem::exists("/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg")) {
                std::cerr << "Error: Image file does not exist at path: " <<"/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg" << std::endl;
            }
            else
            {
                cv::Mat image = cv::imread("/Users/stefanutflorescu/Downloads/OOP-main/resources/original.jpg", cv::IMREAD_COLOR);
                if (cv::imwrite(output_path, image)) {
                    std::cout << "Image saved successfully to " << output_path << std::endl;
                    Frame::switchReady();
                } else {
                    std::cerr << "Failed to save the image!" << std::endl;
                }
            }
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

SaveOutputButton::~SaveOutputButton() = default;


SaveImageButton::SaveImageButton(const float x, const float y, const float width, const float height, const std::string &text)
    : Button(x, y, width, height, text), text_input_frame(nullptr) {
}

void SaveImageButton::update(sf::RenderWindow& window, const sf::Event& event) {
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
                std::cout<<"S-a ajuns aici"<<std::endl;
                Frame::switchReady();
                text_input_frame = new Text_Frame(1000,300,window,"Save");
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
}

SaveImageButton::~SaveImageButton() {
    delete text_input_frame;//Daca dezalocam un nullptr nu se intampla nimic
}





BlurFilterButton::BlurFilterButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new BlurFilter();
}
void BlurFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            //filter->applyFilter();
            Frame::switchReady();
            text_input_frame = new Text_Frame(1000,300,window,"Blur");
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};


CropFilterButton::CropFilterButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new CropFilter();
}
void CropFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            //filter->applyFilter();
            Frame::switchReady();
            text_input_frame = new Text_Frame(1000,300,window,"Crop");
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};


ContrastFilterButton::ContrastFilterButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new ContrastFilter();
}
void ContrastFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            //filter->applyFilter();
            Frame::switchReady();
            text_input_frame = new Text_Frame(1000,300,window,"Contrast");
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};


SaturationFilterButton::SaturationFilterButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new SaturationFilter();
}
void SaturationFilterButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            //filter->applyFilter();
            Frame::switchReady();
            text_input_frame = new Text_Frame(1000,300,window,"Saturation");
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};




SelectSaturationButton::SelectSaturationButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new SaturationFilter();
}
void SelectSaturationButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            dynamic_cast<SaturationFilter*>(filter)->setSaturation(value);
            filter->applyFilter();
            Frame::switchReady();
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};






SelectContrastButton::SelectContrastButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new ContrastFilter();
}
void SelectContrastButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            dynamic_cast<ContrastFilter*>(filter)->setContrast(value);
            filter->applyFilter();
            Frame::switchReady();
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};



SelectBlurButton::SelectBlurButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new BlurFilter();
}
void SelectBlurButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            std::cout<<"Crapa1"<<std::endl;
            dynamic_cast<BlurFilter*>(filter)->setBlur(value);
            std::cout<<"Crapa2"<<std::endl;
            filter->applyFilter();
            Frame::switchReady();
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};




SelectCropButton::SelectCropButton(float x, float y, float width, float height, const std::string& text) : FilterButton(x, y, width, height, text)
{
    filter = new CropFilter();
}
void SelectCropButton::update(sf::RenderWindow& window, const sf::Event& event)
{
    if (isMouseOver(window)) {
        buttonShape.setFillColor(sf::Color(200, 0, 0));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left ) {
            std::cout<<"Crapa1"<<std::endl;
            dynamic_cast<CropFilter*>(filter)->setCrop(a,b,c,d);
            std::cout<<"Crapa2"<<std::endl;
            filter->applyFilter();
            Frame::switchReady();
        }
    } else {
        buttonShape.setFillColor(sf::Color(105, 1, 1));
    }
};

