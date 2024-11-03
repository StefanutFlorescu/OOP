//
// Created by stef on 10/27/24.
//
#include "../include/test.h"

TEST_CASE("Test functional") {
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
}

TEST_CASE("Button Test"){
    Button testButton(1,1,100,200,"Test");
    Button testButton2(testButton);
    Button testButton3 = testButton2;
    testButton2.change_text("Test2");

    // Redirect std::cout to a string stream to capture output
    std::ostringstream output;
    output << testButton;
    CHECK(output.str() == "Test a fost plasat!");
    output.str("");
    output.clear();
    output << testButton2;

    // Check if the output is as expected
    CHECK(output.str() == "Test2 a fost plasat!");
}

TEST_CASE("Filter Test"){
    Filter filter("/Users/stefanutflorescu/Downloads/OOP-main/resources/image.jpg");
    Filter filter2(filter);

    std::ostringstream output;
    output << filter;
    CHECK(output.str() == "/Users/stefanutflorescu/Downloads/OOP-main/resources/image.jpg");
    output.str("");
    output.clear();
    output << filter2;
    CHECK(output.str() == "/Users/stefanutflorescu/Downloads/OOP-main/resources/image.jpg");
}

TEST_CASE("Image Test"){
    Image image("/Users/stefanutflorescu/Downloads/OOP-main/resources/image.jpg");
    std::ostringstream output;
    output << image;
    CHECK(output.str() == "Image: /Users/stefanutflorescu/Downloads/OOP-main/resources/image.jpg\n");
}

TEST_CASE("Frame Test"){
    Frame* frame = new Frame("Test");
    std::ostringstream output;
    output << *frame;
    CHECK(output.str() == "Frame-ul are 860 x 640 y");
    delete frame;
}

TEST_CASE("Text_Frame teset"){
    sf::RenderWindow window(sf::VideoMode(320, 320), "test");
    Text_Frame text_frame(320,320, window);
    std::ostringstream output;
    output << text_frame;
    CHECK(output.str() == "Text_Frame has been rendered with width: 320 and height 320");
}


