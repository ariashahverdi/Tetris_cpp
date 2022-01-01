//
//  block.hpp
//  Tetris
//
//  Created by Aria Shahverdi on 12/19/21.
//

#ifndef block_hpp
#define block_hpp

#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include "action.hpp"

enum shapes { I, J, L, O, S, T, Z };

class Block {
    int shape_idx;
    int x_cord, y_cord;
    std::map<int, std::vector<std::vector<int>>> block_map = {  
        { I, {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}} },
        { J, {{0,0,1,0},{0,0,1,0},{0,1,1,0},{0,0,0,0}} },
        { L, {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}} },
        { O, {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}} },
        { S, {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}} },
        { T, {{0,0,0,0},{0,1,1,1},{0,0,1,0},{0,0,0,0}} },
        { Z, {{0,1,1,0},{0,0,1,1},{0,0,0,0},{0,0,0,0}} }
    };
    std::vector<std::vector<int>> temp_block;
public:
    Block();
    ~Block();
    std::tuple<int, int> get_coords();
    int get_cell(int, int);
    void update(int);
    //void move();
    void rotate();
    void rotate_revert();
};

#endif /* block_hpp */

