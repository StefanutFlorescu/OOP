#include "generated/include/Frame.h"

int Frame::WIDTH = 1280; // Application width
int Frame::HEIGHT = 720; // Application height
bool Frame::READY = false; // This controls if the image is in a ready state to be filtered or shown on the screen

// main function
int main() {
    Frame appFrame("Image Editor by Stef"); // Calling the frame function will start the application
    return 0;
}


