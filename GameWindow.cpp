#include <cstdio>
#include "GameWindow.h"

GameWindow::GameWindow(Game& game)
        : Fl_Window(100, 100, 640, 700, "MazeRunner"), game(game) 
{
    // Every widget created between here and end() is put inside this window.
    grid = new Grid(20, 20, game);
    message = new Fl_Box(20, 625, GRID_SIZE, 30);
    message->labelfont(FL_HELVETICA_BOLD);
    message->labelsize(16);
    stats = new Fl_Box(20, 655, GRID_SIZE, 30);

    // Created last, so it is drawn on top of the maze. Hidden until the end.
    summary = new Fl_Box(150, 170, 340, 300);
    summary->box(FL_BORDER_BOX);
    summary->color(fl_rgb_color(250, 250, 245));
    summary->labelfont(FL_COURIER_BOLD);
    summary->labelsize(18);
    summary->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER);
    summary->hide();

    updateStatus();
    end();
}

// Shows the last message and the numbers under the maze.
void GameWindow::updateStatus() 
{
    snprintf(messageText, sizeof(messageText), "%s", game.getMessage().c_str());
    snprintf(statsText, sizeof(statsText),
             "Score: %d  |  Lives: %d  |  Treasures: %d collected, %d left  |  Turns: %d",
             game.getScore(), game.getLives(), game.getTreasuresCollected(),
             game.getTreasuresRemaining(), game.getTurns());
    message->label(messageText);
    stats->label(statsText);
    message->redraw();
    stats->redraw();
}

// The end-of-run summary (T4).
void GameWindow::showSummary() 
{
    const char* result = "LOSE";
    if (game.hasWon()) {
        result = "WIN";
    }
    snprintf(summaryText, sizeof(summaryText),
             "GAME OVER\n\n"
             "Mode: Human\n"
             "Result: %s\n\n"
             "Score: %d\n"
             "Treasures collected: %d/%d\n"
             "Lives remaining: %d\n"
             "Turns: %d",
             result, game.getScore(), game.getTreasuresCollected(), TREASURE_COUNT,
             game.getLives(), game.getTurns());
    summary->label(summaryText);
    summary->show();
    summary->redraw();
}

// FLTK calls handle() for every event (key press, mouse click, ...).
int GameWindow::handle(int event) {
    if (event == FL_KEYDOWN) {
        int key = Fl::event_key();  // letters arrive as lowercase: 'w', 'a', ...
        if (key == 'w' || key == 'a' || key == 's' || key == 'd') 
        {
            game.movePlayer(key);   // one whole turn: player, enemies, collisions
            grid->update(game);     // display the result
            updateStatus();
            if (game.isOver()) 
            {    // check whether the game has ended
                showSummary();
            }
            return 1;  // we used this event
        }
    }
    return Fl_Window::handle(event);  // anything else: normal window behaviour
}
