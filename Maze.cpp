
// Mikhail Nesterenko
// tests maze function implementation
// 10/21/2022

#include "Maze.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main() {

    srand(time(nullptr)); // random seed
    //srand(1); // fixed seed

    //
    // first part: checking Room functions
    //

    Room myRoom; // create a room
    myRoom.x = 2;
    myRoom.y = 'b';

    // print Room
    cout << "myRoom, fixed location: ";
    printRoom(myRoom);
    cout << endl;

    Room newMoveRoom = nextMove(myRoom); // asks user for new adjacent room
    cout << "user selected adjacent room: ";
    printRoom(newMoveRoom);
    cout << endl;

    if(matchRoom(myRoom, newMoveRoom)) {
        cout << "myRoom is the same as newMoveRoom" << endl;
    }
    //
    // second part: checking wall functions
    //

    // select a fixed wall
    RoomPair myWall = {{2,'b'}, {2,'c'}};

    // print wall
    cout << "myWall, fixed location: ";
    printPair(myWall);
    cout << endl;

    // select and print a random wall
    myWall = pickWall();
    cout << "myWall, random location: ";
    printPair(myWall);
    cout << endl;
    
    RoomPair myMove;
    myMove.one = myRoom; // myMove.one.x & myRoom.one.y
    myMove.two = newMoveRoom;
    cout << "myMove, location: ";
    printPair(myMove);
    cout << endl;
    
    if (matchPair(myWall, myMove)) {
        cout << "there is a wall between these two rooms" << endl;
    }
    else {
        cout << "there is no wall between these two rooms" << endl;
    }
    
    //
    // third part: check maze functions
    //
    
    RoomPair myMaze[numWalls]; // array of walls in the maze

    clearWalls(myMaze); //assigning -1 and '*' to all rooms of the walls

    // printing walls of the maze
    cout << "uninitialized maze walls: ";
    printMaze(myMaze);
    cout << endl;

    if (checkMaze(myMaze, myMove) != -1)
        cout << "there is a wall between these two rooms" << endl;
    else
        cout << "there is no wall between these two rooms" << endl;

    build(myMaze); // placing walls at random locations in the maze
    cout << "built maze: ";
    printMaze(myMaze);
    cout << endl;
    
}

const RoomPair pickWall() {
    Room rand_room;
    rand_room.x = rand() % mazeSize + 1;
    rand_room.y = rand() % (mazeSize - 1) + 'a';

    Room adj_room = rand_room;

    bool selected = false;
    while (!selected) {
        int rand_direction = rand() % 4; // 0 = up, 1 = down, 2 = left, 3 = right
        if (rand_direction == 0 && rand_room.y != 'a') { // checking top
            adj_room.y = rand_room.y + 1;
            adj_room.x = rand_room.x;
            selected = true;
        }
        else if (rand_direction == 1 && rand_room.y != 'a' + mazeSize - 1) { // checking bottom
            adj_room.y = rand_room.y + 1;
            adj_room.x = rand_room.x;
            selected = true;            
        }

        else if (rand_direction == 2 && rand_room.x != 1) { // checking left
            adj_room.y = rand_room.y;
            adj_room.x = rand_room.x - 1;
            selected = true;
        }

        else if (rand_direction == 3 && rand_room.x != mazeSize) { // checking right
            adj_room.y = rand_room.y;
            adj_room.x = rand_room.x + 1;
            selected = true;
        }
    }
    RoomPair result = {{rand_room.x, rand_room.y},{adj_room.x, adj_room.y}};
    return result;
}

void clearWalls(RoomPair cleared_walls[]) {
    for (int i = 0; i < numWalls; ++i) {
        cleared_walls[i].one.x = -1;
        cleared_walls[i].two.x = -1;
        cleared_walls[i].one.y = '*';
        cleared_walls[i].two.y = '*';
    }
}

bool matchRoom(const Room& room_1, const Room& room_2) {
    if (room_1.x == room_2.x && room_1.y == room_2.y) {
        return true;
    }
    else
        return false;
}

bool matchPair(const RoomPair& new_rooms_1, const RoomPair& new_rooms_2) {
    if (matchRoom(new_rooms_1.one, new_rooms_2.one) == true && matchRoom(new_rooms_1.two, new_rooms_2.two) == true) {
        return true;
    }
    else {
        return false;
    }
}

int checkMaze(const RoomPair user_maze[], const RoomPair user_move) {
    for (int i = 0; i < numWalls; ++i) {
        if (matchPair(user_maze[i], user_move) == true) {
            return i;
        }
    }
    return -1;
}

void build(RoomPair pair_list[]) {
    int walls_built = 0;
    while (walls_built < numWalls) {
        RoomPair rooms = pickWall(); // random room generated with pickWall()
        if (checkMaze(pair_list, rooms) == -1) {
            pair_list[walls_built] = rooms;
            ++walls_built;
        }
    }
}

void printRoom(const Room &location) { // prints the location of the room
    cout << location.x << location.y;
}

void printPair(const RoomPair &pair) { // prints the locations of the adjacent rooms
    //cout << endl;
    printRoom(pair.one);
    cout << "|";
    printRoom(pair.two);
}

void printMaze(const RoomPair maze[]) { // prints the locations of all the internal walls of the maze
    for (int i = 0; i < numWalls; i++) {
        printPair(maze[i]);
        if (i != numWalls) {
            cout << ", ";
        }
    }
}

const Room nextMove(const Room &currentRoom) {
    cout << "Select a room with (l = left) (r = right) (u = up) (d = down)" << endl;
    char user_selection;
    cin >> user_selection;
    Room new_room;
    new_room.x = currentRoom.x; // needed a new variable to pass the new values of the funtion parameters .x and .y to
    new_room.y = currentRoom.y;
    switch (user_selection) {
        case 'l':
            new_room.x = currentRoom.x - 1;
            break;
        case 'r':
            new_room.x = currentRoom.x + 1;
            break;
        case 'u':
            new_room.y = currentRoom.y + 1;
            break;
        case 'd':
            new_room.y = currentRoom.y - 1;
            break;
        default:
            break;
    }
    return new_room;
}
