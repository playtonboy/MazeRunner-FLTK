#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <FL/Fl.H>
#include "Game.h"
#include "GameWindow.h"

using namespace std;

int main() 
{
    srand(static_cast<unsigned>(time(0)));  // different random enemy moves every game

    // Load the game. If the maze is not valid, report it and stop.
    Game game;
    try 
    {
        game.load("maze.txt");
    } catch (string message) 
    {
        cerr << "Invalid maze: " << message << endl;
        return 1;
    }

    // Create the window: it adds the Grid and the status line.
    GameWindow* window = new GameWindow(game);
    window->show();

    // Hand control to FLTK. It waits for events and calls handle()
    return Fl::run();
}
