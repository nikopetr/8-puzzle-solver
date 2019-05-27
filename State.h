#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <cstdlib> //For abs()
#define WIDTH 3
#define HEIGHT 3

using namespace std;

class State
{
    int freeX, freeY;//free cell position
    int puzzle[WIDTH][HEIGHT];// The numbers of each cell
    vector <string> path; // path taken

    public:
          /*Constructors*/
    State();
    State(int x, int y, int puzzle[][WIDTH]);

    void setFree(int i, int j);//Sets free the specified tile
    int getFreeY();//Returns the current Y position of the free tile
    int getFreeX();//Returns the current x position of the free tile
    State operator= (State o);//to copy the State object
    bool operator==(const State& o) const ;// to check if the two objects are equal
    string toString () const;// to return as a String the current State
    string getPath();//Returns path that the free tile has moved so far
    friend bool operator< (const State& a,const State& o);//return true if State a is smaller
    vector <State> expand();//Expanding the States and returns it's children
    int getManhattan() const;//Heuristic function

    private:

    int calculateRightRow(int value) const;//Calculates the right column for the given value
    int calculateRightCol(int value) const;//Calculates the right row for the given value
    void swapTileValues(int row, int col, State &n);//Changes the value of the previous free tile
    bool moveFreeUp(State &n);//Goes up if the tile above the current is free
    bool moveFreeDown(State &n);//Goes up if the tile below the current is free
    bool moveFreeLeft(State &n);//Goes left if the tile left to the current is free
    bool moveFreeRight(State &n);//Goes right if the tile right to the current is free
};

#endif // STATE_H
