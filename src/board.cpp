#include "board.hpp"

void init_screen(){
    initscr();
    raw();	
    halfdelay(1);	
	start_color();			
	noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    attron(A_BLINK);
}

Board::Board(int h, int w) {
    init_screen();
    _height = h;
    _width = w; 
    _counter = 0;
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

bool Board::check_move(int action) {
    
    int flag = true;
    if (action == up) {_curr_block_ptr->rotate();}

    auto coords = _curr_block_ptr->get_coords();
    int x = std::get<0>(coords);
    int y = std::get<1>(coords);

    switch (action) {
        case down:      x++;    break;
        case left:      --y;    break;
        case right:     y++;    break;
        default:                break;
    }

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            if ((x+i >= 0 && x+i < _height) && (y+j >= 0 && y+j < _width)){
                if (strncmp(board[{x+i,y+j}], "#",1) == 0 && _curr_block_ptr->get_cell(i,j) == 1) flag = false; 
            }
        }
    } 

    if (action == up) {_curr_block_ptr->rotate_revert();}
    return flag;
}

void Board::modify_board(int operation){
    auto coords = _curr_block_ptr->get_coords();
    int x = std::get<0>(coords);
    int y = std::get<1>(coords);
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            if ((x+i >= 0 && x+i < _height - 1) && (y+j >= 0 && y+j < _width)){
                if (strncmp(board[{x+i,y+j}], "O",1) == 0) {
                    board[{x+i,y+j}] = operation == clean ? " " : "#";
                }
            }
        }
    } 
}

std::vector<int> Board::find_and_clear_rows(){
    std::vector<int> res;
    bool flag;
    for(int i = 0; i < _height-1; i++){
        flag = true;
        for(int j = 1; j < _width-1; j++){
            if (strncmp(board[{i,j}], "#",1) != 0) {
                flag = false;
                break;
            }
        }
        if (flag) {res.push_back(i);}
    }  

    //sort in descending order
    sort(res.begin(), res.end(), std::greater<int>());  
    for (auto row : res){
        for(int j = 1; j < _width-1; j++){board[{row,j}] = "=";}
    }
    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return res;
}

void Board::clear_rows(std::vector<int> rows){
    int offset = 0;
    for (auto row : rows){
        for(int i = row+offset; i >= 0; --i){
            for(int j = 1; j < _width-1; ++j){
                board[{i,j}] = (i==0) ? " " : board[{i-1,j}];
            }
        }  
        ++offset;
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

bool Board::check_bounds(){
    auto coords = _curr_block_ptr->get_coords();
    int x = std::get<0>(coords);
    return (x > 0);
}

bool Board::update(){
    
    // Get an Action from User and if it is quit then return
    _curr_action->update();
    if (_curr_action->get_action() == quit) {return false;}
    
    // Check if there is no block in the board then generate one
    if (_curr_block_ptr == nullptr){_curr_block_ptr = new Block();}

    bool flag = false;
    // If Timeout move the block down
    if(++_counter%5==0){_counter=0; _curr_action->move_down(); flag = true;}

    int action = _curr_action->get_action();

    // Check if moving the block will cause the collision
    if (check_move(action)){

        // Clean the previous block 
        modify_board(clean);

        // Move the Block
        _curr_block_ptr->update(action);
        auto coords = _curr_block_ptr->get_coords();
        int x = std::get<0>(coords);
        int y = std::get<1>(coords);
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                board[{x+i,y+j}] = _curr_block_ptr->get_cell(i,j)? "O" : board[{x+i,y+j}];
            }
        } 
    }
    else if (flag){ // We have to move but we can't so we have to retire the block
        
        //Before fixing the block check if the x value is outof bound!
        // The game is finished! Show the score etc.
        if (!check_bounds()) {return false;}
        
        // Fix the block
        modify_board(fix);

        // Retire the Previous Block
        _curr_block_ptr = nullptr;



        auto rows = find_and_clear_rows();

        clear_rows(rows);
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
    mvprintw(10,40,"Hi");
    refresh(); 
};