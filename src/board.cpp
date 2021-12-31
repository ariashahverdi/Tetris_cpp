#include "board.hpp"

void init_screen(){
    initscr();
    raw();	
    halfdelay(1);	
	start_color();			
	noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    //attron(A_BLINK);

}

Board::Board(int h, int w) {
    init_screen();
    _height = h;
    _width = w; 
    _curr_block_ptr = nullptr;
    _curr_action = new Action();
    for(int i = 0; i < _height; i++){
        board[{i,0}] = "#";
        for(int j = 1; j < _width - 1; j++){
            if(i == _height-1) board[{i,j}] = "#";
            else board[{i,j}] = " ";
        }
        board[{i,_width-1}] = "#";      
    }
};

Board::~Board() {endwin();};
/*
bool Board::add_block() const {
    if (_curr_block == nullptr){
        _curr_block = Block();
        return true;
    }
    return false;
};
*/

bool Board::check_move() {
    auto coords = _curr_block_ptr->get_coords();
    int x = std::get<0>(coords);
    int y = std::get<1>(coords);

    switch (_curr_action->get_action()) {
        case down:      x++;    break;
        case left:      --y;    break;
        case right:     y++;    break;
        case up:        --x;    break;
        default:                break;
    }

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            if ((x+i >= 0 && x+i < _height - 1) && (y+j >= 0 && y+j < _width)){
                if (strncmp(board[{x+i,y+j}], "#",1) == 0 && _curr_block_ptr->get_cell(i,j) == 1)return false; 
            }
        }
    }     
    return true;
}

bool Board::update(){
    // Get an Action from User and if it is quit then return
    _curr_action->update();
    if (_curr_action->get_action() == quit) {return false;}
    // Check if there is no block in the board then generate one
    if (_curr_block_ptr == nullptr){_curr_block_ptr = new Block();}
    // Check if moving the block will cause the collision
    if (check_move()){
        _curr_block_ptr->update(_curr_action->get_action());
        auto coords = _curr_block_ptr->get_coords();
        int x = std::get<0>(coords);
        int y = std::get<1>(coords);
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                board[{x+i,y+j}] = _curr_block_ptr->get_cell(i,j)? "O" : board[{x+i,y+j}];
            }
        } 
    }

   return true;
};


std::tuple<int,int> Board::get_size(){
    std::tuple<int, int> size = {_height, _width};
    return size;
}


void Board::draw(){
    mvprintw(0,0,"");
    for(int i = 0; i < _height; i++){
        for(int j = 0; j < _width; j++) printw(board[{i,j}]);
        printw("\n"); 
    }
    refresh(); 
};



/*
int HEIGHT = 20;
int WIDTH = 20;  
void board(int x, int y){
    mvprintw(0,0,"");
    for(int i = 0; i < HEIGHT; i++)
    {
        printw("#");
        for(int j = 1; j < WIDTH - 1; j++)
        {
            if(i == 0 || i == HEIGHT-1) {printw("#");}
            else if (i == x && j == y){printw("O");}
            else printw(" ");
        }
        printw("#\n"); 
        refresh();      
    }
}
*/
