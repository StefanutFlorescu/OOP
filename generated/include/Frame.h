#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Text_Frame.h"
#include "Image.h"
#include "Button.h"

class Button;
class OpenInputButton;

class Frame {
    static int WIDTH;
    static int HEIGHT;
    static bool READY;
    OpenInputButton *searchImageButton;
public:
    Frame(const std::string& title);
    ~Frame() = default;
    Frame(Frame const&) = delete;
    Frame(Frame&&) = delete;
    Frame& operator=(Frame const&) = delete;
    friend std::ostream& operator<<(std::ostream& os, const Frame& frame);

    static int getWidth();
    static int getHeight();
    static bool switchReady();
    static bool getReady();

};

#endif // FRAME_H
