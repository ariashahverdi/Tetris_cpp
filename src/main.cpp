#include <iostream>
#include "board.hpp"
#include <ncurses.h>
#include <chrono>
#include <thread>

int main()
{
    srand (time(NULL));
    int HEIGHT = 20;
    int WIDTH = 20;
    Board my_board = Board(HEIGHT,WIDTH);    
    my_board.draw();
    bool status = true;
    while (status){
        status = my_board.update();
        my_board.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;
}
