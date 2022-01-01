
#include "micromouseserver.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <char>moves;
void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
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
*/
    if ((isWallRight() == true) and (isWallLeft() == true) and (isWallForward() == false)) {
        moves.push_back('F');
        moveForward();

    }
    if ((isWallRight() == false) and (isWallLeft() == true) and (isWallForward() == true)) {
        turnRight();
        moves.push_back('R');
    }
    if ((isWallRight() == true) and (isWallLeft() == false) and (isWallForward() == true)) {
        turnLeft();
        moves.push_back('L');
    }
    if ((isWallRight() == true) and (isWallLeft() == true) and (isWallForward() == true)) {
        turnRight();
        turnRight();
        for (const char i : moves) {
            qDebug(&i);
            printUI(&i);

          }
       printUI("Reverse:");
        reverse(moves.begin(), moves.end());
        for (const char i : moves) {
            qDebug(&i);
            printUI(&i);
            if(i == 'F') {
                moveForward(); }
            if(i == 'R') {
                turnLeft(); }
            if(i== 'L') {
                turnRight();
            }


          }
        turnRight();
        turnRight();

    }
    else {
        moveForward();
        moves.push_back('F');
    }

}





