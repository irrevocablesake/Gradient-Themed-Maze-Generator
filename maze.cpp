#include "maze.h"
#include<iostream>
#include<stack>
#include<time.h>
#include<cmath>

using namespace std;

//******************************************************************************************************************************
//Set the Feature of the Maze

void Maze::setFeatures(const Feature &feature)
{
    f=feature;
    f.rows=f.height/f.cellSize;
    f.cols=f.width/f.cellSize;
}

//******************************************************************************************************************************

//******************************************************************************************************************************
//Dfs Algorithm

void Maze::checkNeighbour(int current)
{
  currentIndex = 0;

  toptemp = current - f.cols;
  righttemp = current + 1;
  bottomtemp = current + f.cols;
  lefttemp = current - 1;

  if (toptemp >= 0 && !(maze[toptemp] & visitedMask)) {
    direction[currentIndex++] = 't';
  }
  if (righttemp <= (externalLimit) &&
      !(maze[righttemp] & visitedMask) &&
      abs((current / f.cols) - (righttemp / f.cols)) == 0) {
    direction[currentIndex++] = 'r';
  }
  if (bottomtemp <= (externalLimit) &&
      !(maze[bottomtemp] & visitedMask)) {
    direction[currentIndex++] = 'b';
  }
  if (lefttemp >= 0 &&
      !(maze[lefttemp] & visitedMask) &&
      abs((current / f.cols) - (lefttemp / f.cols)) == 0) {
    direction[currentIndex++] = 'l';
  }

 
     
    if(currentIndex>0)
    {
        randomNumber=(helper.xorshift128p(&helper.state))%currentIndex;
        backtrack.push_back(current);

        if(direction[randomNumber]=='t')
        {
            maze[toptemp] |= visitedMask;  
            backtrack.push_back(toptemp);
            maze[current] &=~topMask;
            maze[toptemp] &=~bottomMask;
        }
        else if(direction[randomNumber]=='r')
        {
           maze[righttemp] |= visitedMask;
            maze[current] &=~rightMask;
            maze[righttemp] &=~leftMask;
            backtrack.push_back(righttemp);
        }
        else if(direction[randomNumber]=='b')
        {
            maze[bottomtemp] |=visitedMask;
            maze[current] &=~ bottomMask;
            maze[bottomtemp]&=~topMask;
            backtrack.push_back(bottomtemp);
        }
        else if(direction[randomNumber]=='l')
        {
            maze[lefttemp]|=visitedMask;
            maze[current]&=~leftMask;
            backtrack.push_back(lefttemp);
            maze[lefttemp]&=~rightMask;
        }
    }
}

void Maze::dfsBacktrack()
{
    if(f.mode!=ANIMATE)
    {
        int current;
         
        while(!backtrack.empty())
        {
            current=backtrack.back();
            backtrack.pop_back();
           
            checkNeighbour(current);
        
        }
    }
    else if(f.mode==ANIMATE && !backtrack.empty())
    {
        int current=backtrack.back();
        backtrack.pop_back();

        checkNeighbour(current);
    }
}

//*****************************************************************************************************************************

//*****************************************************************************************************************************
//Graphics Generator

void Maze::handleBorder(int borderCounter,int x,int y,int value)
{
    int index;
    if(value<0)
    {
        index=(f.cols*x)+y;
    }
    else
    {
        index=value;
    }
    
    if(maze[index] & topMask)
    {
        border[borderCounter].color = f.borderColor;
        border[borderCounter+1].color = f.borderColor;
    }
    else
    {
        border[borderCounter].color =sf::Color::Transparent;
        border[borderCounter+1].color =sf::Color::Transparent;
    }    
    if(maze[index] & rightMask)
    {
        border[borderCounter+2].color = f.borderColor;
        border[borderCounter+3].color =f.borderColor;
    }
    else
    {
        border[borderCounter+2].color =sf::Color::Transparent;
        border[borderCounter+3].color = sf::Color::Transparent;
    }
    if(maze[index] & bottomMask)
    {
        border[borderCounter+4].color = f.borderColor;
        border[borderCounter+5].color = f.borderColor;
    }
    else
    {
        border[borderCounter+4].color =sf::Color::Transparent;
        border[borderCounter+5].color = sf::Color::Transparent;
    }
    if(maze[index] & leftMask)
    {
        border[borderCounter+6].color = f.borderColor;
        border[borderCounter+7].color = f.borderColor;
    }
    else
    {
        border[borderCounter+6].color = sf::Color::Transparent;
        border[borderCounter+7].color =sf::Color::Transparent;
    }
}

void Maze::createVertexArray(int explicitCheck)
{
    int padding=10;
    int counter=0;
    int borderCounter=0;

    float initial=1;
    float p=initial;
  
    float firstCalcx;
    float firstCalcy;
    float secondCalcx;
    float secondCalcy;
    float thirdCalcx;
    float thirdCalcy;

    if(explicitCheck==1)
    {
        for(int i=0;i<f.rows;i++)
        {
            for(int j=0;j<f.cols;j++)
            {
                firstCalcx=(j*f.cellSize)+padding;
                firstCalcy=(i*f.cellSize)+f.cellSize+padding;
                secondCalcx=j*f.cellSize+padding;
                secondCalcy=i*f.cellSize+padding;
                thirdCalcx=(j*f.cellSize)+f.cellSize+padding;
              
                quad[counter].position.x=firstCalcx;
                quad[counter].position.y=firstCalcy;

                quad[counter+1].position.x=secondCalcx;
                quad[counter+1].position.y=secondCalcy;

                quad[counter+2].position.x=thirdCalcx;
                quad[counter+2].position.y=secondCalcy;

                quad[counter+3].position.x=thirdCalcx;
                quad[counter+3].position.y=firstCalcy;

                border[borderCounter].position.x=secondCalcx;
                border[borderCounter].position.y=secondCalcy;

                border[borderCounter+1].position.x=thirdCalcx;
                border[borderCounter+1].position.y=secondCalcy;

                border[borderCounter+2].position.x=thirdCalcx;
                border[borderCounter+2].position.y=secondCalcy;

                border[borderCounter+3].position.x=thirdCalcx;
                border[borderCounter+3].position.y=firstCalcy;

                border[borderCounter+4].position.x=thirdCalcx;
                border[borderCounter+4].position.y=firstCalcy;

                border[borderCounter+5].position.x=secondCalcx;
                border[borderCounter+5].position.y=firstCalcy;

                border[borderCounter+6].position.x=firstCalcx;
                border[borderCounter+6].position.y=firstCalcy;

                border[borderCounter+7].position.x=secondCalcx;
                border[borderCounter+7].position.y=secondCalcy;

                int visited=maze[(f.cols*i)+j] & visitedMask;
                if(!visited)
                {   
                    quad[counter].color = f.notVisitedColor;
                    quad[counter+1].color = f.notVisitedColor;
                    quad[counter+2].color =f.notVisitedColor;
                    quad[counter+3].color =f.notVisitedColor;
                }
                else
                {
                   
                    quadColor.r=(f.start.r*p)+(f.end.r*(1-p));
                    quadColor.g=(f.start.g*p)+(f.end.g*(1-p));
                    quadColor.b=(f.start.b*p)+(f.end.b*(1-p));

                    quad[counter].color = quadColor;
                    quad[counter+1].color = quadColor;
                    quad[counter+2].color = quadColor;
                    quad[counter+3].color =quadColor;
                }
  
                handleBorder(borderCounter,i,j,-1);
            
                counter=counter+4;
                borderCounter=borderCounter+8;
            }
            p=p-((initial/f.rows));
        }
    }
    else
    {
        if(!backtrack.empty())
        {
            float first=initial-(int(backtrack.back()/f.cols)) * (initial/f.rows);
            float second=1 - first;
 
            quadColor.r=(f.start.r*first)+(f.end.r*second);
            quadColor.g=(f.start.g*first)+(f.end.g*second);
            quadColor.b=(f.start.b*first)+(f.end.b*second);

            quad[(backtrack.back()*4)].color = quadColor;
            quad[(backtrack.back()*4)+1].color = quadColor;
            quad[(backtrack.back()*4)+2].color = quadColor;
            quad[(backtrack.back()*4)+3].color =quadColor;

            if(backtrack.size()>=2)
            {
                handleBorder((backtrack.back()*8),-1,-1,backtrack.back());            
                handleBorder((backtrack[(backtrack.size()-2)]*8),-1,-1,backtrack[(backtrack.size()-2)]);            
            }
        }
    }
}

void Maze::drawWindow(sf::RenderWindow &window,string windowName)
{
      int padding=10;
      window.create(sf::VideoMode((f.cols*f.cellSize)+(2*padding),(f.rows*f.cellSize)+(2*padding)),windowName);
      
      if(f.mode==ANIMATE)
      {
        window.setFramerateLimit(f.fps);
      }
      
      while(window.isOpen())
      {
          sf::Event event;
          while(window.pollEvent(event))
          {
              if(event.type==sf::Event::Closed)
              {
                  window.close();
              }
          }

          window.clear(f.backgroundColor);

            if(f.mode==ANIMATE)
            {
                dfsBacktrack();
                createVertexArray(-1);
                if(!backtrack.empty())
                {
                    quad[(backtrack.back()*4)].color = f.currentColor;
                    quad[(backtrack.back()*4)+1].color = f.currentColor;
                    quad[(backtrack.back()*4)+2].color = f.currentColor;
                    quad[(backtrack.back()*4)+3].color =f.currentColor;
                }
            }        

            window.draw(quad);
            window.draw(border);

            window.display();

        if(f.mode==ANIMATE && !backtrack.empty())
        {
            quad[(backtrack.back()*4)].color = quadColor;
            quad[(backtrack.back()*4)+1].color = quadColor;
            quad[(backtrack.back()*4)+2].color = quadColor;
            quad[(backtrack.back()*4)+3].color =quadColor;
        }
      }
}

//****************************************************************************************************************************

//****************************************************************************************************************************
//Initialization and Handler

void Maze::initialize()
{
    try 
    {
        unsigned char initial=0b0000'1111;
        maze.resize(f.rows*f.cols,initial); 
    }
    catch (const std::bad_alloc&)
    {
        cout<<"error in initializing the array";
    }
    if(f.mode!=IMAGE)
    {
    quad.setPrimitiveType(sf::Quads);
    border.setPrimitiveType(sf::Lines);

    quad.resize(4*f.rows*f.cols);
    border.resize(8*f.rows*f.cols);
    }
}

void Maze::createMaze(string windowName)
{
    initialize();

    maze[0] |= visitedMask;
    backtrack.push_back(0);

    externalLimit=(f.rows*f.cols)-1;

    if(f.mode==IMAGE)
    {   
        dfsBacktrack(); 
        // image.saveImage("love_testing.png",maze,f);
    }
    else if(f.mode==DISPLAY)
    {
        sf::RenderWindow window;
        dfsBacktrack();
        createVertexArray(1);
        drawWindow(window,windowName);
        image.saveImage("love_testing.png",maze,f);
    }
    else if(f.mode==ANIMATE)
    {
        sf::RenderWindow window;
        createVertexArray(1);
        drawWindow(window,windowName);
        image.saveImage("love_testing.png",maze,f);
    }

    maze.clear();
    vector<unsigned char>().swap(maze);
}

//*****************************************************************************************************************************