
#include "micromouseserver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;


//Useful Variables:------------------------------------------------------------------------------------------------------------------------------

int back_status = 0; //Whether robot is backtracing or not
int position[3] = {0,0,0}; // third value serves as a clock --> 0 means forward, 1 means right, 2 means back, 3 means left and so forth(use mod 4)
vector <char>moves; //moves vector used for an old implementation
// Visited vector holding coords that have been visited
vector<vector<int>> visited
{
    {0,0}
};
// Pnode vector holds coords with parent nodes and position
vector<vector<int>> pnode
{
    {0,0,0}
};
vector<int> temp_loc;
int pre_turn = 0; // whether previous move was a turn(for pnode marking)

// Useful Functions:------------------------------------------------------------------------------------------------------------------------------

void forward_update() {
    cout << "update";
    if  ( (position[2] % 4) == 0) { // forward
        position[1] = position[1] + 1;

    } else if  ( (position[2] % 4) == 1) { // right
        position[0] = position[0] + 1;

    } else if  ( (position[2] % 4) == 2) { // back
        position[1] = position[1] - 1;
    } else if  ( (position[2] % 4) == 3) { // left
        position[0] = position[0] - 1;

    }
}
void printPos() {
    cout << "[ " << position[0] << ", "<< position[1] << ", " << position[2] << " ]" << endl;
}
void print_vector(vector <vector<int> > vctr) {
    for (unsigned int i = 0; i < vctr.size(); i++)
        {
            for (unsigned int j = 0; j < vctr[i].size(); j++)
            {
                cout << vctr[i][j] << ",";
            }
            cout << endl;
        }}
bool isForwardVisited() { 
    if  ( abs(position[2] % 4) == 0) { // forward
        temp_loc.push_back(position[0]);
        temp_loc.push_back(position[1]+1);

    } else if  ( abs(position[2] % 4) == 1) { // right
        temp_loc.push_back(position[0]+1);
        temp_loc.push_back(position[1]);

    } else if  ( abs(position[2] % 4) == 2) { // back
        temp_loc.push_back(position[0]);
        temp_loc.push_back(position[1]-1);

    } else if  ( abs(position[2] % 4) == 3) { // left
        temp_loc.push_back(position[0]-1);
        temp_loc.push_back(position[1]);

    }
    cout << "[ "<< temp_loc[0] << ", "<< temp_loc[1] << "]";
    if ((count(visited.begin(), visited.end(), temp_loc))) {
        return true;
    }
    else {
        return false;
    }
    temp_loc.erase(temp_loc.begin(),temp_loc.end());
}
bool isRightVisited() {
    if  ( abs(position[2] % 4) == 0) { // forward
        temp_loc.push_back(position[0]+1);
        temp_loc.push_back(position[1]);

    } else if  ( abs(position[2] % 4) == 1) { // right
        temp_loc.push_back(position[0]);
        temp_loc.push_back(position[1]-1);

    } else if  ( abs(position[2] % 4) == 2) { // back
        temp_loc.push_back(position[0]-1);
        temp_loc.push_back(position[1]);

    } else if  ( abs(position[2] % 4) == 3) { // left
        temp_loc.push_back(position[0]);
        temp_loc.push_back(position[1]+1);

    }
    if ((count(visited.begin(), visited.end(), temp_loc))) {
        return true;
    }
    else {
        return false;
    }
    temp_loc.erase (temp_loc.begin(),temp_loc.end());
}
bool isLeftVisited() {
    if  ( abs(position[2] % 4) == 0) { // forward
        temp_loc.push_back(position[0]-1);
        temp_loc.push_back(position[1]);

    } else if  ( abs(position[2] % 4) == 1) { // right
        temp_loc.push_back(position[0]);
        temp_loc.push_back(position[1]+1);

    } else if  ( abs(position[2] % 4) == 2) { // back
        temp_loc.push_back(position[0]+1);
        temp_loc.push_back(position[1]);

    } else if  ( abs(position[2] % 4) == 3) { // left
        temp_loc.push_back(position[0]);
        temp_loc.push_back(position[1]-1);

    }
    if ((count(visited.begin(), visited.end(), temp_loc))) {
        return true;
    }
    else {
        return false;
    }
    temp_loc.erase (temp_loc.begin(),temp_loc.end());
}

// Functions defined in micromouseserver.cpp by me are:
/*
 * bool isDestination()
 * void turnBackwards()
*/

void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own functions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);


    for(int i = 0; i < 3; i++) {
      char x = to_string(position[i]);
      printUI(x);
    }
  */

    //Pre-Movement Logging: ------------------------------------------------------------------------------------
    printPos();
    vector<int> location { position[0], position[1]};
    if (!(count(visited.begin(), visited.end(), location))) {
        visited.push_back(location);
    }


    //BackTracing:
    if (back_status == 1) {
        cout<< ">Back";
        int n = pnode.size();
        vector<int> last_pnode = pnode[n-1];
        vector<int> last_pnode_loc = {last_pnode[0], last_pnode[1]};
        if (location == last_pnode_loc) {
            cout<<" ,last Pnode found";
            int x = abs(((last_pnode[2] % 4) - (position[2] % 4 )) % 4);
            cout << x;
            for (int i = 0; i < x; i++) {
              turnRight();
              position[2] = position[2] + 1;
            }
            if (!isForwardVisited()) {
                moveForward();
                forward_update();
                pre_turn = 0;
                back_status = 0;
                cout<< " ,new_Forward";
                return;
            } else if(!isRightVisited()) {
                turnRight();
                position[2] = position[2] + 1;
                pre_turn = 1;
                back_status = 0;
                cout << " ,new_Right";
                return;
            } else if(!isLeftVisited()) {
                turnLeft();
                position[2] = position[2] - 1;
                pre_turn = 1;
                back_status = 0;
                cout<< " ,new_Left";
                return;
            }
        }

    }

    // Single cases:  ------------------------------------------------------------------------------------
    if ((isWallRight() == true) and (isWallLeft() == true) and (isWallForward() == false)) {
        moves.push_back('F');
        moveForward();
        pre_turn = 0;
        cout<<", SingleForward";
        forward_update();
        return;



    }
    else if ((isWallRight() == false) and (isWallLeft() == true) and (isWallForward() == true)) {
        cout<<" ,Single Right";
        turnRight();
        pre_turn = 1;
        position[2] = position[2] + 1;
        moves.push_back('R');
        return;
    }
    else if ((isWallRight() == true) and (isWallLeft() == false) and (isWallForward() == true)) {
        turnLeft();
        cout<<" ,Single Left";
        pre_turn = 1;
        position[2] = position[2] - 1;
        moves.push_back('L');
        return;
    }





    //Destination checks ------------------------------------------------------------------------------------------------------------------------------
    else if (((!isWallForward() && !isWallLeft() && isWallRight()) || (!isWallForward() && !isWallRight() && isWallLeft())) && back_status == 0) {
        cout << ", Dest_check ";
        if (isDestination()) {
            cout<<", Dest ";
            foundFinish();
            return;
        }
        else {
            //Parent node cases:
            if ((!isWallForward() && !isWallLeft() && isWallRight())
                     || (!isWallForward() && !isWallRight() && isWallLeft())
                     || (isWallForward() && !isWallRight() && !isWallLeft())
                     || (!isWallForward() && isWallRight() && !isWallLeft()))
            {
                if (pre_turn == 0 && back_status == 0) {
                    vector<int> temp = {position[0], position[1], position[2]};
                    pnode.push_back(temp);
                    cout << " ,pnode added ";
                }

            }
            if (!isWallForward()) {
                moveForward();
                pre_turn = 0;
                forward_update();
                cout <<" ,Forward/Dest";
            }
            else {
                turnRight();
                pre_turn = 1;
                position[2] = position[2] + 1;
                cout<< " ,Right/Dest";
            }
            return;
        }
    }

    //Dead end checks ------------------------------------------------------------------------------------------------------------------------------
    else if ((isWallRight() == true) and (isWallLeft() == true) and (isWallForward() == true)) {
        cout<<">Visited" << endl;
        print_vector(visited);
        cout<<">Pnodes"<<endl;
        print_vector(pnode);
        back_status = 1;
        turnBackward();
        position[2] = position[2] + 2;
        forward_update();
    }





    // Other situations: ------------------------------------------------------------------------------------------------------------------------------
    else {
        //Parent node cases:
        if ((!isWallForward() && !isWallLeft() && isWallRight())
                 || (!isWallForward() && !isWallRight() && isWallLeft())
                 || (isWallForward() && !isWallRight() && !isWallLeft())
                 || (!isWallForward() && isWallRight() && !isWallLeft()))
        {
            if (pre_turn == 0 && back_status == 0) {
                vector<int> temp = {position[0], position[1], position[2]};
                pnode.push_back(temp);
                cout << " pnode added ";
            }

        }
        if (!isWallForward()) {
            moveForward();
            pre_turn = 0;
            forward_update();
        }
        else {
            turnRight();
            pre_turn = 1;
            position[2] = position[2] + 1;
        }
        return;
    }

}



/*
 * Other code:
 *        //printUI("Reverse:");
       reverse(moves.begin(), moves.end());
       for (const char i : moves) {

            if(i == 'F') {
                moveForward();
                cout<<"Not supposed";
                forward_update();
            }
            if(i == 'R') {
                turnLeft();
                position[2] = position[2] - 1;
            }
            if(i== 'L') {
                turnRight();
                position[2] = position[2] + 1;
            }
          }

        cout<<"Not sup";
        turnBackward();
        position[2] = position[2] + 2;
        forward_update();
        return;
 *
 *
 *
 *
 *
 *
 *
 *
*/
