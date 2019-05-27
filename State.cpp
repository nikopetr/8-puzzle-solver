#include "State.h"
#include <iostream>

State::State()
{

}

State::State(int row, int col, int puzzle[][WIDTH])
{
    this->freeX = row;
    this->freeY = col;

    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            this->puzzle[i][j]=puzzle[i][j];
}

void State::setFree(int x, int y)
{
    freeX = x;
    freeY = y;
}

int State::getFreeY()
{
    return freeY;
}

int State::getFreeX()
{
    return freeX;
}

State State::operator= (State o)
{
    freeX = o.freeX;
    freeY = o.freeY;

    path = o.path;

    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            puzzle[i][j]=o.puzzle[i][j];

    return *this;
}

// note: We're passing s by const reference here to avoid making a copy of s.
bool State::operator==(const State& s) const //A function becomes const when const keyword is used in function’s declaration.
                                            //The idea of const functions is not allow them to modify the object on which they are called.
{
    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
                {
                    if (puzzle[i][j] != s.puzzle[i][j])
                        return false;
                }

    return true;
}

string State::toString () const
{
    stringstream ot;

    for (int i = 0; i < WIDTH; i++)
    {
        ot << "\n";
        for (int j = 0; j < HEIGHT; j++)
            if (puzzle[i][j] != 0)
                ot<<puzzle[i][j]<< "  ";
            else
                ot<<" "<< "  ";

    }

    return ot.str();
}

string State::getPath()
{
    unsigned i;
    string s;
    if (path.size()>0)
    {
        for (i=0;i<path.size()-1;i++)
            s+=path.at(i)+", ";
        s+=path.at(i)+ "\n";
    }
    return s;
}

int State::getManhattan() const
{
    int distance = 0;
    for (int i = 0; i < WIDTH; i++)
        for (int j = 0; j < HEIGHT; j++)
        {
            if (puzzle[i][j] != 0)
                distance += abs(i - calculateRightRow(puzzle[i][j])) + abs(j - calculateRightCol(puzzle[i][j]));
            else
                distance += abs(i - (WIDTH - 1)) + abs(j - (HEIGHT - 1));
        }
    return distance;
}

int State::calculateRightRow(int value) const
{
    double div = (double(value) / double(WIDTH));

    if (div <= 1)
        return 0;
    else if (div <= 2)
        return 1;
    else return 2;
}

int State::calculateRightCol(int value) const
{
    return (value - 1) % HEIGHT;
}

bool operator< (const State& a, const State& o)
{
    return (a.toString() < o.toString());
    //return (a.getManhattan() > o.getManhattan());
}

void State::swapTileValues(int row, int col, State &n)
{
    n.puzzle[n.getFreeX()][n.getFreeY()] = n.puzzle[row][col];
    n.puzzle[row][col] = 0;
}

bool State::moveFreeUp(State &n)
{
    if (getFreeX()>0)
    {
        n=*this;
        swapTileValues(n.getFreeX()-1, n.getFreeY(), n);
        n.setFree(n.getFreeX()-1, n.getFreeY());
        n.path.push_back("U"); // U for up
        return true;
    }
    return false;
}

bool State::moveFreeDown(State &n)
{
    if (getFreeX()<2)
    {
        n=*this;
        swapTileValues(n.getFreeX()+1, n.getFreeY(), n);
        n.setFree(n.getFreeX()+1, n.getFreeY());
        n.path.push_back("D"); //D for down
        return true;
    }
    return false;
}
bool State::moveFreeLeft(State &n)
{
    if (getFreeY()>0)
    {
        n=*this;
        swapTileValues(n.getFreeX(), n.getFreeY()-1, n);
        n.setFree(n.getFreeX(), n.getFreeY()-1);
        n.path.push_back("L");  // L for Left
        return true;
    }
    return false;
}
bool State::moveFreeRight(State &n)
{
    if (getFreeY()<2)
    {
        n=*this;
        swapTileValues(n.getFreeX(), n.getFreeY()+1, n);
        n.setFree(n.getFreeX(), n.getFreeY()+1);
        n.path.push_back("R"); //R for right
        return true;
    }
    return false;
}

vector <State> State::expand()
{
    vector <State> children;
    State child;

    if (moveFreeUp(child))
        children.push_back(child);
    if (moveFreeLeft(child))
        children.push_back(child);
    if (moveFreeDown(child))
        children.push_back(child);
    if (moveFreeRight(child))
        children.push_back(child);

    return children;
}
