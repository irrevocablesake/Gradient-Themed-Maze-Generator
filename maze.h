#pragma once
#ifndef _MAZE_H_
#define _MAZE_H_

#define SFML_STATIC
#include "cell.h"
#include<stack>
#include<string>
#include<vector>
#include "SFML/Graphics.hpp"

using namespace std;

class Maze
{
    private:
        vector<unsigned char> maze;
        
        int width;
        int height;
        int cellSize;
        int rows;
        int cols;
        int animate;
        int fps;
        int externalLimit;

        sf::Color start;
        sf::Color end;

        float total;
        sf::Time tempTime;

        sf::Color notVisitedColor;
        sf::Color currentColor;
        sf::Color borderColor;
        sf::Color backgroundColor;
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
        
    public:
        void setAnimation(int animate);
        void setFps(int fps);
        void setVisitedCellColor(sf::Color start,sf::Color end);
        void setNotVisitedCellColor(sf::Color color);
        void setCurrentCellColor(sf::Color color);
        void setBorderColor(sf::Color color);
        void setBackgroundColor(sf::Color color);
        void setWidth(int width);
        void setHeight(int height);
        void setCellSize(int size);
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