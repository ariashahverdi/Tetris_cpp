#include "block.hpp"

//
Block::Block() : shape_idx(rand()%3), x_cord(-3), y_cord(5) {};

Block::~Block() {};

std::tuple<int, int> Block::get_coords(){
    return std::tuple<int, int> {x_cord, y_cord};
}

int Block::get_cell(int i, int j){
    std::map<int, std::vector<std::vector<int>>> block_map = { 
        //{ U, {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}} },  
        { I, {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}} },
        { J, {{0,0,1,0},{0,0,1,0},{0,1,1,0},{0,0,0,0}} },
        { L, {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}} }
    };
    return block_map[shape_idx][i][j];
}

void Block::update(int next_action){
    //Check if the move is valid
    //Board(next_action, board)
    switch (next_action){
        case up:
            //rotate()
            break;
        case down:
            ++x_cord;
            break;
        case left:
            --y_cord;
            break;
        case right:
            ++y_cord;
            break;
        default:
            break;
    }
    return;
}

void Block::move(){
    //Check if the move is valid
    //Board(next_action, board)
    ++x_cord;
    return;
}

