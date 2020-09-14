#define SFML_STATIC
#ifndef _IMAGE_H_
#define _IMAGE_H_

#pragma once

#include "cell.h"
#include "feature.h"
#include "SFML/Graphics.hpp"
#include<iostream>

using namespace std;

class Image
{
    public:
        void saveImage(string fileName,vector<unsigned char> &maze,const Feature &feature);
};

#endif