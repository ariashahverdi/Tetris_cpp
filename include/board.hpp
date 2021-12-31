#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <ncurses.h>
#include "block.hpp"
#include "action.hpp"

class Board {
    int _height;
    int _width;
    Block * _curr_block_ptr;
    Action *_curr_action;
    std::map<std::tuple<int,int>, const char *> board;
    Board(); // Constructor, make it impossible to call it
    bool check_move();
public:
    Board(int,int);
    ~Board();
    std::tuple<int,int> get_size();
    bool update();
    void draw();
};

#endif /* board_hpp */


/* 
Have board get a block, update the board by moving the blocks
and detect the collision in the board!
*/