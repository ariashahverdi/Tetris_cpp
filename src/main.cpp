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
    int timer = 0;
    bool status = true;
    while (status){
        status = my_board.update();
        my_board.draw();
        //my_action.update();
        //my_blk.update(my_action);
        //if(++timer%5==0){timer=0;my_blk.move();}
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

