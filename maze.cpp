#include "maze.h"
#include<iostream>
#include<stack>
#include<time.h>
#include<cmath>

using namespace std;

// helper function

struct xorshift128p_state
{
  uint64_t a, b;
}state;

uint64_t xorshift128p(struct xorshift128p_state *state)
{
	uint64_t t = state->a;
	uint64_t const s = state->b;
	state->a = s;
	t ^= t << 23;		// a
	t ^= t >> 17;		// b
	t ^= s ^ (s >> 26);	// c
	state->b = t;
	return (t + s);
}

//helper function

// features section

void Maze::setWidth(int width)
{
    this->width=width;
}

void Maze::setHeight(int height)
{
    this->height=height;
}

void Maze::setCellSize(int size)
{
    cellSize=size;
    rows=height/cellSize;
    cols=width/cellSize;
}

void Maze::setNotVisitedCellColor(sf::Color color)
{
    notVisitedColor=color;
}

void Maze::setCurrentCellColor(sf::Color color)
{
    currentColor=color;
}

void Maze::setVisitedCellColor(sf::Color start, sf::Color end)
{
    this->start=start;
    this->end=end;
}

void Maze::setBorderColor(sf::Color color)
{
    borderColor=color;
}

void Maze::setBackgroundColor(sf::Color color)
{
    backgroundColor=color;
}

void Maze::setAnimation(int animate)
{
    this->animate=animate;
}

void Maze::setFps(int fps)
{
    this->fps=fps;
}

// features section

// maths model generator

void Maze::checkNeighbour(int current)
{
    // randomNumber=rand()%d;
    std::size_t currentIndex = 0;
  direction = {};

  toptemp = current - cols;
  righttemp = current + 1;
  bottomtemp = current + cols;
  lefttemp = current - 1;

  if (toptemp >= 0 && toptemp <= (externalLimit) &&
      !(maze[toptemp] & visitedMask)) {
    direction[currentIndex++] = 't';
  }
  if (righttemp >= 0 && righttemp <= (externalLimit) &&
      !(maze[righttemp] & visitedMask) &&
      abs((current / cols) - (righttemp / cols)) == 0) {
    direction[currentIndex++] = 'r';
  }
  if (bottomtemp >= 0 && bottomtemp <= (externalLimit) &&
      !(maze[bottomtemp] & visitedMask)) {
    direction[currentIndex++] = 'b';
  }
  if (lefttemp >= 0 && lefttemp <= (externalLimit) &&
      !(maze[lefttemp] & visitedMask) &&
      abs((current / cols) - (lefttemp / cols)) == 0) {
    direction[currentIndex++] = 'l';
  }

 
     
    if(currentIndex>0)
    {
        randomNumber=(xorshift128p(&state))%currentIndex;
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
    if(animate!=1)
    {
        int current;
         
        while(!backtrack.empty())
        {
            current=backtrack.back();
            backtrack.pop_back();
           
            checkNeighbour(current);
        
        }
    }
    else if(animate==1 && !backtrack.empty())
    {
        int current=backtrack.back();
        backtrack.pop_back();

        checkNeighbour(current);
    }
}

// maths model generator

// graphics generator

void Maze::handleBorder(int borderCounter,sf::Color borderColor,int x,int y,int value)
{
    int index;
    if(animate!=1)
    {
        index=(cols*x)+y;
    }
    else
    {
        index=value;
    }
    
    if(maze[index] & topMask)
    {
        border[borderCounter].color = this->borderColor;
        border[borderCounter+1].color = this->borderColor;
    }
    else
    {
        border[borderCounter].color =borderColor;
        border[borderCounter+1].color =borderColor;
    }    
    if(maze[index] & rightMask)
    {
        border[borderCounter+2].color = this->borderColor;
        border[borderCounter+3].color = this->borderColor;
    }
    else
    {
        border[borderCounter+2].color =borderColor;
        border[borderCounter+3].color = borderColor;
    }
    if(maze[index] & bottomMask)
    {
        border[borderCounter+4].color = this->borderColor;
        border[borderCounter+5].color = this->borderColor;
    }
    else
    {
        border[borderCounter+4].color =borderColor;
        border[borderCounter+5].color = borderColor;
    }
    if(maze[index] & leftMask)
    {
        border[borderCounter+6].color = this->borderColor;
        border[borderCounter+7].color = this->borderColor;
    }
    else
    {
        border[borderCounter+6].color = borderColor;
        border[borderCounter+7].color =borderColor;
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

  

    if(explicitCheck!=1)
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                firstCalcx=(j*cellSize)+padding;
                firstCalcy=(i*cellSize)+cellSize+padding;
                secondCalcx=j*cellSize+padding;
                secondCalcy=i*cellSize+padding;
                thirdCalcx=(j*cellSize)+cellSize+padding;
              
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

                int visited=maze[(cols*i)+j] & visitedMask;
                if(!visited)
                {   
                    quad[counter].color = notVisitedColor;
                    quad[counter+1].color = notVisitedColor;
                    quad[counter+2].color = notVisitedColor;
                    quad[counter+3].color =notVisitedColor;
                }
                else
                {
                   
                    quadColor.r=(start.r*p)+(end.r*(1-p));
                    quadColor.g=(start.g*p)+(end.g*(1-p));
                    quadColor.b=(start.b*p)+(end.b*(1-p));

                    quad[counter].color = quadColor;
                    quad[counter+1].color = quadColor;
                    quad[counter+2].color = quadColor;
                    quad[counter+3].color =quadColor;

                    localBorderColor=quadColor;
                }

                if(!animate)
                {
                    handleBorder(borderCounter,localBorderColor,i,j,-1);
                }
                else
                {
                    handleBorder(borderCounter,borderColor,i,j,-1);
                    if((cols*i+j)==backtrack.back())   
                    {
                        quad[counter].color = currentColor;
                        quad[counter+1].color =currentColor;
                        quad[counter+2].color = currentColor;
                        quad[counter+3].color =currentColor;
                    }      
                }

                counter=counter+4;
                borderCounter=borderCounter+8;
            }
            p=p-((initial/rows));
        }
    }
    else
    {

        if(!backtrack.empty())
        {
            float first=initial-(int(backtrack.back()/cols)) * (initial/rows);
            float second=1 - first;
 
            quadColor.r=(start.r*first)+(end.r*second);
            quadColor.g=(start.g*first)+(end.g*second);
            quadColor.b=(start.b*first)+(end.b*second);

            quad[(backtrack.back()*4)].color = quadColor;
            quad[(backtrack.back()*4)+1].color = quadColor;
            quad[(backtrack.back()*4)+2].color = quadColor;
            quad[(backtrack.back()*4)+3].color =quadColor;

            if(backtrack.size()>2)
            {
                handleBorder((backtrack.back()*8),quadColor,-1,-1,backtrack.back());

                first=initial-int((backtrack[backtrack.size()-2])/cols) * (initial/rows);
                second=1 -first;

                sf::Color newQuadColor;

                newQuadColor.r=(start.r*first)+(end.r*second);
                newQuadColor.g=(start.g*first)+(end.g*second);
                newQuadColor.b=(start.b*first)+(end.b*second);
            
                handleBorder((backtrack[(backtrack.size()-2)]*8),newQuadColor,-1,-1,backtrack[(backtrack.size()-2)]);
              
            }
        }
    }
}

void Maze::drawWindow(sf::RenderWindow &window,string windowName)
{
      int padding=10;
      window.create(sf::VideoMode((cols*cellSize)+(2*padding),(rows*cellSize)+(2*padding)),windowName);
      
      if(animate)
      {
        window.setFramerateLimit(fps);
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

          window.clear(backgroundColor);

            if(animate)
            {
                dfsBacktrack();
                createVertexArray(1);
                if(!backtrack.empty())
                {
                    quad[(backtrack.back()*4)].color = currentColor;
                    quad[(backtrack.back()*4)+1].color = currentColor;
                    quad[(backtrack.back()*4)+2].color = currentColor;
                    quad[(backtrack.back()*4)+3].color =currentColor;
                }
            }        

            window.draw(quad);
            window.draw(border);

            window.display();

        if(animate && !backtrack.empty())
        {
            quad[(backtrack.back()*4)].color = quadColor;
            quad[(backtrack.back()*4)+1].color = quadColor;
            quad[(backtrack.back()*4)+2].color = quadColor;
            quad[(backtrack.back()*4)+3].color =quadColor;
        }
      }
}

// graphics generator

// image saving

void Maze::saveAsImage()
{
    
    float initial=1;
    float p=initial;
    sf::Color quadColor;

    int width=(cols * cellSize) + 20;
    int height=(rows * cellSize) + 20;

    sf::Uint8 *pixels=new sf::Uint8[width * height * 4];

    for(int x = 0; x < width; x++)
    {
            for(int y = 0; y < 10; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

     for(int x = 0; x < 10; x++)
    {
            for(int y = 0; y < height; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

 for(int x = 0; x < width; x++)
    {
            for(int y = height-10; y < height; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

 for(int x = width-10; x < width; x++)
    {
            for(int y =0; y < height; y++)
            {
                pixels[((x + y * width) * 4) + 0] = 255; // R?
                pixels[((x + y * width) * 4) + 1] = 255; // G?
                pixels[((x + y * width) * 4) + 2] = 255; // B?
                pixels[((x + y * width) * 4) + 3] = 255; // A?
            }
        }

    for(int x=0;x<rows;x++)
    {
        for(int y=0;y<cols;y++)
        {

            quadColor.r=(start.r*p)+(end.r*(1-p));
            quadColor.g=(start.g*p)+(end.g*(1-p));
            quadColor.b=(start.b*p)+(end.b*(1-p));
            for(int i=y * cellSize + 10;i<y * cellSize + 10 +cellSize;i++)
            {
                for(int j=x * cellSize + 10;j< x* cellSize + 10 + cellSize;j++)
                {
                    pixels[((i + j * (width )) * 4 )+ 0]=quadColor.r;
                    pixels[((i + j * (width )) * 4 )+ 1]=quadColor.g;
                    pixels[((i + j * (width )) * 4 )+ 2]=quadColor.b;
                    pixels[((i + j * (width )) * 4 )+ 3]=255;
                }      
            }

             if(maze[cols * x + y] & topMask)
            {
                for(int i=(y * cellSize + 10);i<=(y * cellSize +cellSize + 10);i++)
                {
                    pixels[((i + (x * cellSize +10) * (width)) * 4 )+ 0]=borderColor.r;
                    pixels[((i + (x * cellSize + 10) * (width )) * 4 )+ 1]=borderColor.g;
                    pixels[((i + (x * cellSize +10 ) * (width )) * 4 )+ 2]=borderColor.b;
                    pixels[((i + (x * cellSize+10) * (width )) * 4 )+ 3]=255;
                }
            }

             if(maze[cols * x + y] & rightMask)
            {
                for(int i=(x * cellSize + 10);i<=(x * cellSize +cellSize + 10);i++)
                {
                    pixels[(((y * cellSize + cellSize +10) + i* (width)) * 4 )+ 0]=borderColor.r;
                    pixels[(((y * cellSize + cellSize +10) + i* (width)) * 4 )+ 1]=borderColor.g;
                    pixels[(((y * cellSize  + cellSize+10) + i* (width )) * 4 )+ 2]=borderColor.b;
                    pixels[(((y * cellSize + cellSize +10) + i* (width )) * 4 )+ 3]=255;
                }
            }
            if(maze[cols * x + y] & leftMask)
            {
                for(int i=(x * cellSize + 10);i<=(x * cellSize +cellSize + 10);i++)
                {
                    pixels[(((y * cellSize  +10) + i* (width )) * 4 )+ 0]=borderColor.r;
                    pixels[(((y * cellSize  +10) + i* (width )) * 4 )+ 1]=borderColor.g;
                    pixels[(((y * cellSize  +10) + i* (width )) * 4 )+ 2]=borderColor.b;
                    pixels[(((y * cellSize  +10) + i* (width )) * 4 )+ 3]=255;
                }
            }
            if(maze[cols * x + y] & bottomMask)
            {
                for(int i=(y * cellSize + 10);i<=(y * cellSize +cellSize + 10);i++)
                {
                    pixels[((i + (x * cellSize +cellSize+10) * (width)) * 4 )+ 0]=borderColor.r;
                    pixels[((i + (x * cellSize +cellSize+ 10) * (width)) * 4 )+ 1]=borderColor.g;
                    pixels[((i + (x * cellSize+cellSize +10 ) * (width )) * 4 )+ 2]=borderColor.b;
                    pixels[((i + (x * cellSize+cellSize+10) * (width )) * 4 )+ 3]=255;
                }
            }
        }
             p=p-(initial/rows);
    }

    sf::Image image;
    image.create(cols*cellSize + 20,rows * cellSize + 20,pixels);
    image.saveToFile("finally.png");

    delete[] pixels;
}

// image saving

void Maze::initialize()
{
    srand(time(NULL));
    state.a=rand();
    state.b=rand();
    try 
    {
        maze.resize(rows*cols); 
    }
    catch (const std::bad_alloc&)
    {
        cout<<"error in initializing the array";
    }
    if(animate!=-1)
    {
    quad.setPrimitiveType(sf::Quads);
    border.setPrimitiveType(sf::Lines);

    quad.resize(4*rows*cols);
    border.resize(8*rows*cols);
    }
}

void Maze::createMaze(string windowName)
{
    unsigned char initial=0b0000'1111;

    initialize();

    for(int i=0;i<rows*cols;i++)
    {
        maze[i]=initial;
    }

    maze[0] |= visitedMask;
    backtrack.push_back(0);

    externalLimit=(rows*cols)-1;

    if(animate==-1)
    {   
        dfsBacktrack();
        saveAsImage();
    }
    else if(animate==0)
    {
        sf::RenderWindow window;
        dfsBacktrack();
        createVertexArray(-1);
        drawWindow(window,windowName);
        saveAsImage();
    }
    else if(animate==1)
    {
        sf::RenderWindow window;
        createVertexArray(-1);
        drawWindow(window,windowName);
        saveAsImage();
    }

    maze.clear();
    vector<unsigned char>().swap(maze);
}