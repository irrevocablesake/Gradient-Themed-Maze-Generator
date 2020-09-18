#define SFML_STATIC
#ifndef _FEATURE_H_
#define _FEATURE_H_

#pragma once

#include "SFML/Graphics.hpp"

using namespace std;

struct Feature
{
    int width;
    int height;
    int rows;
    int cols;
    int cellSize;
    int fps;
    int mode;

    sf::Color borderColor;
    sf::Color backgroundColor;
    sf::Color start;
    sf::Color end;
    sf::Color visitedColor;
    sf::Color notVisitedColor;
    sf::Color currentColor;
};

#endif