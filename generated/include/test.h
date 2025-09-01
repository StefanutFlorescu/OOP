//
// Created by stef on 10/27/24.
//

#ifndef TEST_H
#define TEST_H
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Button.h"
#include "Filter.h"
#include "Image.h"
#include "Frame.h"
#include "TextFrame.h"
#include "LoadManager.h"
#include "Logger.h"

#include <iostream>
int Frame::WIDTH = 860;
int Frame::HEIGHT = 640;
bool Frame::READY = false;
Logger* Frame::logger = nullptr;

#endif //TEST_H
