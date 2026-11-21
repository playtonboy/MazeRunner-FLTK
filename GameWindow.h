#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "Grid.h"
#include "Game.h"

// The screen. It shows the Grid, two status lines and, at the end of a
// run, a summary. It reads the keyboard by overriding handle().
class GameWindow : public Fl_Window 
{
private:
    Game& game;
    Grid* grid;
    Fl_Box* message;  // what just happened
    Fl_Box* stats;    // score, lives, treasures and turns
    Fl_Box* summary;  // shown on top of the maze when the game has ended
    // FLTK does not copy label text, so the text is kept here
    char messageText[100];
    char statsText[150];
    char summaryText[300];
    void updateStatus();
    void showSummary();
public:
    GameWindow(Game& game);
    int handle(int event);
};

#endif /* GAMEWINDOW_H_ */
