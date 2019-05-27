#include <iostream>
#include "State.h"
#include <algorithm>
using namespace std;

template <typename myState>
bool BFS(const myState &goal,queue<myState> &agenda, set<myState> &closed,myState &solution)
{
    myState s;
    while (!(agenda.empty()))
    {
        s=agenda.front();
        agenda.pop();

        if (s==goal)
        {
            solution = s;
            return true;
        }

        if (closed.size()==0 || (closed.find(s)==closed.end()))// if closed set is empty or set does NOT contain s,

        {
            vector<myState> children;
            children=s.expand();
            closed.insert(s);
            for (unsigned int i=0;i<children.size();i++)
                agenda.push(children.at(i));
        }
    }

    return false;
}

template <typename myState>
bool DFS(const myState &goal,stack<myState> &agenda, set<myState> &closed,myState &solution)
{
    myState s;
    while (!(agenda.empty()))
    {
        s=agenda.top();
        agenda.pop();

        if (s==goal)
        {
            solution = s;
            return true;
        }

        if (closed.size()==0 || (closed.find(s)==closed.end()))

        {
            vector<myState> children;
            children=s.expand();
            closed.insert(s);
            for (unsigned int i=0;i<children.size();i++)
                agenda.push(children.at(i));
        }
    }

    return false;
}

template <typename myState>
bool BestFS(const myState &goal, vector<myState> &agenda, vector<myState> &closed, myState &solution)
{

    myState s;
    if (agenda.empty())
        return false;

    s = getBestRoute(agenda);


    if (s==goal)
    {
        solution = s;
        return true;
    }

      if (closed.size()==0 || (find(closed.begin(), closed.end(), s) == closed.end()))
                                                           // if closed set is empty or set does NOT contain s,

    {
        vector<myState> children;
        children=s.expand();

        closed.push_back(s);

        for (unsigned int i=0;i<children.size();i++)
            agenda.push_back(children.at(i));

    }
    return BestFS(goal,agenda,closed,solution);
}

State getBestRoute(vector<State> &agenda) //finding best State to follow and deleting that State from the agenda
{
    State bestState = agenda.at(0);
    int pos = 0;
    unsigned i;
    for (i=1;i<agenda.size()-1;i++)
    {
        if (agenda.at(i).getManhattan() < bestState.getManhattan())
            {
                bestState = agenda.at(i);
                pos = i;
            }
    }

    agenda.erase(agenda.begin() + pos);
    return bestState;
}

int main()
{
   int startingBoard[3][3] = {
   {6, 7, 1} ,   /*  initializers for row indexed by 0 */
   {0, 3, 2} ,   /*  initializers for row indexed by 1 */
   {8, 5, 4}   /*  initializers for row indexed by 2 */
};
    int goalBoard[3][3] = {
   {1, 2, 3} ,   /*  initializers for row indexed by 0 */
   {4, 5, 6} ,   /*  initializers for row indexed by 1 */
   {7, 8, 0}   /*  initializers for row indexed by 2 */
};
    State initial(1,0,startingBoard);//Creates the starting state
    State goal(2,2,goalBoard);//Sets a goal

    stack <State> agenda;
    queue <State> Qagenda;
    vector <State> bestFSAgenda;

    set <State> closed; //Closed set
    set <State> Qclosed;
    vector <State> bestFSClosed;

    agenda.push(initial);
    Qagenda.push(initial);
    bestFSAgenda.push_back(initial);

    cout<<"Starting State: \n"<<initial.toString()<<"\n"<<"\nGoal State: \n"<<goal.toString()<<endl;//Prints the starting to final state

    State solution;

    BestFS(goal,bestFSAgenda,bestFSClosed,solution);

    cout<<"BestFS Solution: "<<endl;
    cout<<solution.getPath()<<endl;;

    BFS(goal,Qagenda,Qclosed,solution);

    cout<<"BFS Solution: "<<endl;
    cout<<solution.getPath()<<endl;;

    DFS(goal,agenda,closed,solution);

    cout<<"DFS Solution: "<<endl;
    cout<<solution.getPath()<<endl;;


    return 0;
}
