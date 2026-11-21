#ifndef BLOCK_H_
#define BLOCK_H_

#include <FL/Fl.H>
#include <FL/Fl_Box.H>

const int BLOCK_SIZE = 30;  // width and height of one square, in pixels

// One square of the maze on screen. A Block IS an Fl_Box (inheritance),
// so FLTK already knows how to draw it; we only choose its color and label.
class Block : public Fl_Box 
{
private:
    char symbol;
public:
    Block(int x, int y, char symbol);
    void setSymbol(char symbol);
};

#endif /* BLOCK_H_ */
