// g++ -g -o3 -c main.cpp -o main.o -I"I:/SFML/include"
// g++ -g -o3 -c maze.cpp -o maze.o -I"I:/SFML/include"
// g++ -g -o3 -c image.cpp -o image.o -I"I:/SFML/include"
// g++ -g -o3 -c helper.cpp -o helper.o -I"I:/SFML/include"
// g++ -g -o3 main.o maze.o image.o helper.o -o main -L"I:/SFML/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-system-s -lsfml-network-s -lwinmm -lopengl32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lws2_32 -lgdi32 -lkernel32 -luser32 -lwinspool -lshell32 -lole32 -luuid -lcomdlg32 -lfreetype -ladvapi32

#include "feature.h"
#include "Maze.h"

using namespace std;

int main()
{
    sf::Color grey(200,200,200);
    sf::Color start(0,139,139);
    sf::Color end(0,25,51);
    
    Feature feature;

    feature.animate=1;
    feature.fps=0;
    feature.width=500;
    feature.height=500;
    feature.cellSize=22;
    feature.backgroundColor=grey;
    feature.borderColor=sf::Color::White;
    feature.currentColor=sf::Color::Red;
    feature.notVisitedColor=grey;
    feature.start=start;
    feature.end=end;

  
    Maze maze;
    maze.setFeatures(feature);
   
    maze.createMaze("DFS Backtracking Maze");
  
    return 0;
}