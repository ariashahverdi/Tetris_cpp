#include "block.hpp"

//
Block::Block() : shape_idx(rand()%7), x_cord(-3), y_cord(5) {};

Block::~Block() {};

std::tuple<int, int> Block::get_coords(){
    return std::tuple<int, int> {x_cord, y_cord};
}

int Block::get_cell(int i, int j){
    return block_map[shape_idx][i][j];
}

void Block::update(int next_action){
    //Check if the move is valid
    //Board(next_action, board)
    switch (next_action){
        case up:
            rotate();
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

/*
void Block::move(){
    ++x_cord;
    return;
}
*/

// by 90 degrees in
// anti-clockwise direction
void rotateMatrix(std::vector<std::vector<int>> & mat, int N)
{
    // Consider all squares one by one
    for (int x = 0; x < N / 2; x++) {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < N - x - 1; y++) {
            // Store current cell in
            // temp variable
            int temp = mat[x][y];
 
            // Move values from right to top
            mat[x][y] = mat[y][N - 1 - x];
 
            // Move values from bottom to right
            mat[y][N - 1 - x]
                = mat[N - 1 - x][N - 1 - y];
 
            // Move values from left to bottom
            mat[N - 1 - x][N - 1 - y]
                = mat[N - 1 - y][x];
 
            // Assign temp to left
            mat[N - 1 - y][x] = temp;
        }
    }
}

void Block::rotate(){
    temp_block = block_map[shape_idx];
    rotateMatrix(block_map[shape_idx], 4);
}

void Block::rotate_revert(){
    block_map[shape_idx] = temp_block;
}