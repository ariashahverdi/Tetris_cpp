//
//  action.hpp
//  Tetris
//
//  Created by Aria Shahverdi on 12/19/21.
//

#ifndef action_hpp
#define action_hpp

#include <iostream>
#include <stdio.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

enum act { up, left, right, down, none, quit };

class Action {
    int action;
public:
    Action();
    ~Action();
    void update();
    void move_down();
    int get_action();
    
};

#endif /* action_hpp */
