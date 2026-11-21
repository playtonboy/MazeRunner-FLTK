#include <cstdio>
#include "GameWindow.h"

GameWindow::GameWindow(Game& game)
        : Fl_Window(100, 100, 640, 700, "MazeRunner"), game(game), aiMode(false) 
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
             "Mode: %s\n"
             "Result: %s\n\n"
             "Score: %d\n"
             "Treasures collected: %d/%d\n"
             "Lives remaining: %d\n"
             "Turns: %d",
             aiMode ? "AI (BFS)" : "Human", result, game.getScore(), game.getTreasuresCollected(), TREASURE_COUNT,
             game.getLives(), game.getTurns());
    summary->label(summaryText);
    summary->show();
    summary->redraw();
}

// One whole turn (player, enemies, collisions) and then show the result.
// Used for the keyboard and for the AI, so it is written only once.
void GameWindow::playTurn(char direction) 
{
    game.movePlayer(direction);
    grid->update(game);
    updateStatus();
    if (game.isOver()) 
    {
        showSummary();
    }
}

// FLTK calls this function after AI_DELAY seconds. We cannot write our own
// while loop (FLTK would freeze), so every call plays ONE turn and then asks
// FLTK to call it again, until the game is over.
// It is static because FLTK needs a plain function; 'data' is the window.
void GameWindow::aiTimer(void* data) 
{
    GameWindow* window = static_cast<GameWindow*>(data);
    char move = window->ai.chooseMove(window->game);  // BFS: next step
    window->playTurn(move);
    if (!window->game.isOver()) 
    {
        Fl::repeat_timeout(AI_DELAY, aiTimer, data);
    }
}

// FLTK calls handle() for every event (key press, mouse click, ...).
int GameWindow::handle(int event) 
{
    if (event == FL_KEYDOWN && !aiMode) 
    {
        int key = Fl::event_key();  // letters arrive as lowercase: 'w', 'a', ...
        if (key == 'w' || key == 'a' || key == 's' || key == 'd') 
        {
            playTurn(key);
            return 1;  // we used this event
        }
        // I = AI Mode: from now on the AI plays and the keyboard is ignored
        if (key == 'i' && !game.isOver()) 
        {
            aiMode = true;
            Fl::add_timeout(AI_DELAY, aiTimer, this);
            return 1;
        }
    }
    return Fl_Window::handle(event);  // anything else: normal window behaviour
}
