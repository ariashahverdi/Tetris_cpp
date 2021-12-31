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
public:
    Block();
    ~Block();
    std::tuple<int, int> get_coords();
    int get_cell(int, int);
    void update(int);
    void move();
};

#endif /* block_hpp */

