Part2 Final Algorithm:
By: Sandeep Bajamahal


Note: Two functions: isDestination and turnBackwards are defined in micromouseserver.cpp as part of the microMouseServer class. 


Prioritize going Forward(), then right, then left

Decision making Process:
Initialize an array of all coords visited
Write three bools to check if forward is visited, left is visited, and right is visited
Use bools to not move to visited coords
Use a global integer to know if the mouse is backtracking or not(to allow for visiting coords when necessary)
1. If only way is forward, move forward
2. If only way is right, move right
3. If only way is left, move left
4. If there are two ways, save position in an array called pnodes and move in priority
5. Repeat steps 1/2/3 and 4 until a dead end is reached, or a destination is found
6. Turn around and repeat steps 1/2/3( or backtrace) until the most recent entry into pnode has been reached
7. Move in priority and repeat step 5
8. If entire pnode has been visited, turn in final direction left and move in priority until next pnode is reached



Globals:
Visited -> vector of vectors in format {x, y}
Add position to visited if:
	1) It is not in it
	2) Not in the dest function
Back_status -> 0 for no backtracking, 1 for backtracking, 2 for backtracking to previous parent node
Pnode -> vector of vectors as [x, y, rotation]

Tasks(moving from main branch to part2 approach):
1. Create visited
2. Add visited to code
3. Create nodes
4. Add pnode protocol

isForwardVIsited
isRightVisited
isLeftVisited


Pnode protocol:
1. Pnode initiated
2. Priority move taken
3. Next Pnode initiated.
4. Pnode routes explored
5. If all paths are taken, turn backward, print searching for prev node

Wall cases
Global statuses:
Pre-turn : 0, 1
Backtracing : 0, 1, 2

Backtrace(if b.t. = 1) 
1. Check if location = last pnode
    1. If so, reorient & print
    2. Move to unvisited spot in priority
    3. If all spots visited
        1. Set b.t = 2
        2. Turn backwards
        3. Del last entry of pnodes
Backtrace(if b.t. = 2)
1. Check if location = 2nd to last Pnode
    1. If so, check ops
    2. Move to unvisited spot
    3. If all spots
        1. Set b.t. = 2,
        2. Turn backwards
        3. Del last entry of pnodes



1 option:
FRL - save to visited, begin backtracing

2 option:
FR - perform destination check, save to Pnode(if pre-turn = 0), save to visited
FL - perform destination check, save to Pnode(if pre-turn = 0), save to visited
RL - save to Pnode, save to visited

1 option:
F - update position, move F if not visited else backtrace & turn back
R - update position, turn R if not visited else backtrace & turn back
L - update position, turn L if not visited else backtrace & turn back




In-Depth Algorithm:

1. Begin in single-case priority(Forward, Right, Left)
    1. Maintain a list of pnodes position with two option cells, append at two option cells
    2. Perform destination checks with specific two option cells(FL, FR)
    3. On every move/turn non destination check for already visited cells
    4. Maintain a position system
    5. Maintain a list of visited cells and location










