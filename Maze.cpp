#include <fstream>
#include "Maze.h"

using namespace std;  

// Maze constructor: fills the grid with empty cells and sets the player and enemies to (0, 0). 
// It is safe to have it like this because the Maze is always loaded from a file before it is used
Maze::Maze() {
    playerStart.row = 0;
    playerStart.col = 0;
    for (int i = 0; i < ENEMY_COUNT; i++) 
    {
        enemyStarts[i] = playerStart;
    }
    for (int r = 0; r < MAZE_SIZE; r++) 
    {
        for (int c = 0; c < MAZE_SIZE; c++) 
        {
            grid[r][c] = '.';
        }
    }
}

// Reads the maze from a text file. Throws a string if the file is not usable.
/* load() reads the file line by line, checks the size and contents, and throws an error message that main catches, so a broken maze never reaches the game */
void Maze::load(const string& filename) 
{
    ifstream file(filename);
    if (!file) 
    {
        throw string("Cannot open the maze file");
    }

    int row = 0;
    string line;
    while (getline(file, line)) 
    {
        if (row == MAZE_SIZE) 
        {
            throw string("The maze has too many rows");
        }
        int length = line.size();
		if (length > 0 && line[length - 1] == '\r') // Windows line endings
        {  
            length = length - 1;
        }
        if (length != MAZE_SIZE) 
        {
            throw string("A row of the maze does not have 20 columns");
        }
        for (int col = 0; col < MAZE_SIZE; col++) 
        {
            grid[row][col] = line[col];
        }
        row++;
    }
    if (row != MAZE_SIZE) 
    {
        throw string("The maze does not have 20 rows");
    }
    validate();

    // From now on the Player and Enemy objects keep track of where they are,
    // so 'P' and 'E' are removed from the map. The map only has things
    // that do not move: walls, treasures and the exit.
    grid[playerStart.row][playerStart.col] = '.';
    for (int i = 0; i < ENEMY_COUNT; i++) {
        grid[enemyStarts[i].row][enemyStarts[i].col] = '.';
    }
}

// Counts the objects and remembers where the player and the enemies start.
void Maze::validate() {
    int players = 0;
    int treasures = 0;
    int enemies = 0;
    int exits = 0;

    for (int r = 0; r < MAZE_SIZE; r++) 
    {
        for (int c = 0; c < MAZE_SIZE; c++) 
        {
            char symbol = grid[r][c];
            if (symbol == 'P') 
            {
                players++;
                playerStart.row = r;
                playerStart.col = c;
            } 
            else if (symbol == 'T') 
            {
                treasures++;
            } 
            else if (symbol == 'E') 
            {
                if (enemies < ENEMY_COUNT) 
                {  // only room for 3 in the array
                    enemyStarts[enemies].row = r;
                    enemyStarts[enemies].col = c;
                }
                enemies++;
            } 
            else if (symbol == 'X') 
            {
                exits++;
            } 
            else if (symbol != '#' && symbol != '.' && symbol != ' ') 
            {
                throw string("Unknown symbol in the maze file");
            }
        }
    }

    if (players != 1 || treasures != 5 || enemies != 3 || exits != 1) 
    {
        throw string("The maze must contain exactly 1 player, 5 treasures, 3 enemies and 1 exit");
    }
}

Position Maze::getPlayerStart() const 
{
    return playerStart;
}

Position Maze::getEnemyStart(int index) const 
{
    return enemyStarts[index];
}

char Maze::getSymbol(int row, int col) const 
{
    return grid[row][col];
}

bool Maze::isInside(Position position) const 
{
    return position.row >= 0 && position.row < MAZE_SIZE
        && position.col >= 0 && position.col < MAZE_SIZE;
}

bool Maze::isWall(Position position) const 
{
    return grid[position.row][position.col] == '#';
}

// Makes a cell empty, for example after a treasure was collected.
void Maze::clearCell(Position position) 
{
    grid[position.row][position.col] = '.';
}
