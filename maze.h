#pragma once
#ifndef _MAZE_H_
#define _MAZE_H_

#define SFML_STATIC
#include "masking.h"
#include<stack>
#include "helper.h"
#include "image.h"
#include "feature.h"
#include<string>
#include<vector>
#include "SFML/Graphics.hpp"

using namespace std;

enum Mode
{
    ANIMATE=1,
    IMAGE=-1,
    DISPLAY=0,
};

class Maze
{
    private:
        vector<unsigned char> maze;
        Feature f;
        Helper helper;

        int externalLimit;

        float total;
        sf::Time tempTime;

        sf::Color quadColor;
        
        int top,right,bottom,left;
        int toptemp,righttemp,bottomtemp,lefttemp;
        
        sf::VertexArray quad;
        sf::VertexArray border;
        
        vector<int> backtrack;
        uint64_t randomNumber;
        
        char direction[4];

        std::size_t currentIndex;

        Image image;
        
    public:
        void setFeatures(const Feature &feature);
        void createMaze(string windowName);
   
    private:  
       
        void checkNeighbour(int current);
        void dfs();
        void initialize();
        void drawWindow(sf::RenderWindow &window, string windowName);
        void saveAsImage();
        void handleBorder(int borderCounter,int x,int y,int value);
        void createVertexArray(int explicitCheck=-1);
};

#endif