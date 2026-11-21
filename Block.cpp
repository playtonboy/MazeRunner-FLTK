#include "Block.h"

Block::Block(int x, int y, char symbol) : Fl_Box(x, y, BLOCK_SIZE, BLOCK_SIZE) 
{
    this->box(FL_FLAT_BOX);  // a plain filled square, no 3D border
	setSymbol(symbol); // set the color and label according to the symbol
}

// Color (and label) of the block, depending on its symbol.
// Used when the block is created and again after every move.
void Block::setSymbol(char symbol) 
{
    this->symbol = symbol;
    this->label("");
    this->labelcolor(FL_BLACK);
    this->labelfont(FL_HELVETICA_BOLD);

    if (symbol == '#') 
    {
        this->color(fl_rgb_color(60, 60, 60));
    } 
    else if (symbol == 'P') 
    {
        this->color(fl_rgb_color(40, 90, 170));
        this->labelcolor(FL_WHITE);
        this->label("P");
    } 
    else if (symbol == 'T')
    {
        this->color(fl_rgb_color(240, 200, 60));
        this->label("T");
    } 
    else if (symbol == 'E') 
    {
        this->color(fl_rgb_color(200, 50, 50));
        this->labelcolor(FL_WHITE);
        this->label("E");
    } 
    else if (symbol == 'X') 
    {
        this->color(fl_rgb_color(60, 160, 80));
        this->labelcolor(FL_WHITE);
        this->label("X");
    } 
    else 
    {
        this->color(FL_WHITE);
    }
    this->redraw();  // ask FLTK to draw the block again
}
