// g++ -g -o3 -c main.cpp -o main.o -I"I:/SFML/include"
// g++ -g -o3 -c cell.cpp -o cell.o -I"I:/SFML/include"
// g++ -g -o3 -c maze.cpp -o maze.o -I"I:/SFML/include"

// g++ -g -o3 main.o maze.o cell.o -o main -L"I:/SFML/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lsfml-network-s -lwinmm -lopengl32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -lgdi32 -lkernel32 -luser32 -lwinspool -lshell32 -lole32 -luuid -lcomdlg32 -lfreetype -ladvapi32

#include "Maze.h"

using namespace std;

int main()
{
    sf::Color grey(200,200,200);
    sf::Color start(0,139,139);
    sf::Color end(0,25,51);
    
    Maze maze;
    maze.setAnimation(1);
    maze.setFps(0);
    maze.setWidth(1000);
    maze.setHeight(600);
    maze.setCellSize(24);
    maze.setBackgroundColor(grey);
    maze.setBorderColor(sf::Color::White);
    maze.setCurrentCellColor(sf::Color::Red);
    maze.setNotVisitedCellColor(grey);
    maze.setVisitedCellColor(start,end);
   
    maze.createMaze("DFS Backtracking Maze");
  
    return 0;
}