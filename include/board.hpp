#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <ncurses.h>
#include <thread>
#include "block.hpp"
#include "action.hpp"

enum operation { clean, fix };

class Board {
    int _height;
    int _width;
    int _counter;
    Block * _curr_block_ptr;
    Action *_curr_action;
    std::map<std::tuple<int,int>, const char *> board;
    Board(); // Constructor, make it impossible to call it
    bool check_move(int);
    void modify_board(int);
    std::vector<int> find_and_clear_rows();
    void clear_rows(std::vector<int>);
public:
    Board(int,int);
    ~Board();
    std::tuple<int,int> get_size();
    bool update();
    void draw();
};

#endif /* board_hpp */