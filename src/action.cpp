//
//  action.cpp
//  Tetris
//
//  Created by Aria Shahverdi on 12/19/21.
//

#include "action.hpp"

Action::Action() : action(none) {};

//endwin();
Action::~Action() {};

void Action::update(){
    int ch;
    for (;;) {
        if ((ch = getch()) == ERR) {
            //user hasn't responded
            action = none;
            break; 
        }
        else {
            // user has pressed a key ch
            switch (ch) {
                case KEY_DOWN: /* user pressed backspace */
                    action = down;
                    break;
                case KEY_LEFT: /* user pressed backspace */
                    action = left;
                    break;
                case KEY_RIGHT: /* user pressed backspace */
                    action = right;
                    break;
                case KEY_UP: /* user pressed backspace */
                    action = up;
                    break;
                case 'q':
                    action = quit;
                    break;
                default:
                    action = none;
                    break;
            }
            break;
        }
    }
}

void Action::move_down(){action = down;}

int Action::get_action(){return action;}

