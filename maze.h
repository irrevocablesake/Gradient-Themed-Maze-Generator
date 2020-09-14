#pragma once
#ifndef _MAZE_H_
#define _MAZE_H_

#define SFML_STATIC
#include "cell.h"
#include<stack>
#include "image.h"
#include "feature.h"
#include<string>
#include<vector>
#include "SFML/Graphics.hpp"

using namespace std;

class Maze
{
    private:
        vector<unsigned char> maze;
        Feature f;

        int externalLimit;

        float total;
        sf::Time tempTime;

        sf::Color quadColor;
        sf::Color localBorderColor;
        
        int top,right,bottom,left;
        int toptemp,righttemp,bottomtemp,lefttemp;
        
        sf::VertexArray quad;
        sf::VertexArray border;
        
        vector<int> backtrack;
        uint64_t randomNumber;
        std::array<char, 4> direction;
        std::size_t currentIndex;

        Image image;
        
    public:
        void setFeatures(const Feature &feature);
        void createMaze(string windowName);
   
    private:  
       
        void checkNeighbour(int current);
        void dfsBacktrack();
        void initialize();
        void drawWindow(sf::RenderWindow &window, string windowName);
        void saveAsImage();
      
        void handleBorder(int borderCounter,sf::Color borderColor,int x,int y,int value);
        void createVertexArray(int explicitCheck=-1);
};

#endif