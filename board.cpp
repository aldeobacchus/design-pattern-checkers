#include "./include/board.h"
#define max(x,y) (((x) >= (y)) ? (x) : (y))
#define min(x,y) (((x) <= (y)) ? (x) : (y))
/*

//Didn't had the time to finish the implementation of Observer

class EventManager
{
private:
    vector<ObserverInterface*> observers;
public:
    virtual ~EventManager() {}

    void attach(ObserverInterface *observer){
        observers.push_back(observer);
    }

    void detach(const int index){
        observers.erase( observers.begin() +index);
    }

    void notify(){
        for (unsigned int i =0; i < observers.size(); i++){
            observers.at(i)->update(this);
        }
    }

};

class ObserverInterface
{
public:
    virtual ~ObserverInterface() {}
    virtual void update(EventManager* event);
};


class WinnerObserver : public ObserverInterface
{private:
    int watchRedLeft;
    int watchBlackLeft;
public:
    WinnerObserver(int a, int b): watchRedLeft(a), watchBlackLeft(b){}

    int getRed(){
        return watchRedLeft;
    }
    int getBlack(){
        return watchBlackLeft;
    }

    void update(EventManager* event){
        //what will append when someone win
    }
};
*/
Board::Board(){
    blackLeft = redLeft = 12;
    blackKings = redKings = 0;
    boardTopLeftX = boardTopLeftY = 0;//usefull later, if we want to resize the win, maybe should move this to main later
    initializeVirtualBoard();
}

Board* Board::instance=nullptr;


Board* Board::getInstance(){
    if(!instance){
        instance = new Board();
    }
    return instance;
}


void Board::drawChecker(SDL_Renderer* renderer){
    SDL_Color white = BOARD_WHITE_COLOR;
    SDL_Color black = BOARD_BLACK_COLOR;

    for (int i=0; i < ROWS; ++i){
        for (int j=0; j < COLS; ++j){
            SDL_Color currentColor = (i+j) % 2 == 0 ? white : black;
            SDL_Rect outline;
            outline.w = (SQUARE_SIZE);
            outline.h = (SQUARE_SIZE);
            outline.x = boardTopLeftX + i*(SQUARE_SIZE);
            outline.y = boardTopLeftY + j*(SQUARE_SIZE);
            SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
            SDL_RenderFillRect(renderer, &outline);
        }
    }
}

void Board::initializeVirtualBoard(){
    std::cout<<"initializing VBoard\n";
    for (int row=0; row < ROWS; row++){
        for (int col=0; col < COLS; col++){
            if (col % 2 == ((row+1) % 2)){
                if (row < 3){
                    virtualBoard[row][col] = Piece(row, col, "red");
                }else if(row > 4){
                    virtualBoard[row][col] = Piece(row, col, "black");
                }else{
                    virtualBoard[row][col].clear();
                }
            }else{
                virtualBoard[row][col].clear();
            }
        }
    }

}

void Board::drawGame(SDL_Renderer* renderer){
    int row;
    int col;
    drawChecker(renderer);
    for (row=0; row < ROWS; row++){
        for (col=0; col < COLS; col++){
            
            if (virtualBoard[row][col].color == "red" || virtualBoard[row][col].color == "black"){
                virtualBoard[row][col].drawPiece(renderer, boardTopLeftX, boardTopLeftY,(SQUARE_SIZE));

            }
        }
    }

}

void Board::move(Piece piece, int row, int col){
    Piece  temp;
    temp = virtualBoard[piece.row][piece.col];
    virtualBoard[piece.row][piece.col] = virtualBoard[row][col];
    virtualBoard[row][col] = temp;
    piece.move(row, col);

    if (row == ROWS-1 || row == 0){
        piece.setKing();
        if (piece.color == "red"){
            redKings ++;
        }
        if (piece.color == "black"){
            blackKings++;
        }
    }
}

void Board::remove(Piece piece){
    piece.clear();
    if (piece.color == "red"){
        redLeft --;
    }else if (piece.color == "black"){
        blackLeft --;
    }
}

Piece Board::getPiece(int row, int col){
    return virtualBoard[row][col];
}

string Board::getWinner(){
    if (redLeft <= 0){
        return "red";
    }else if(blackLeft <= 0){
        return "black";
    }else{
        return "";
    }
}

int Board::offset(int x, int y, int z){
    return (z*ROWS*COLS)+(y*ROWS)+x;
}

void Board::getValidMove(Piece* moves[ ROWS * COLS * NB_PIECE], Piece piece)
{    
    Piece skipped;
    int left = piece.col -1;
    int right = piece.col +1;
    int row = piece.row;
    std::cout<<"Get valid moves from ["<<piece.row<<":"<<piece.col<<"]{"<<piece.color<<"}\n";
    skipped.clear();
    if (piece.color == "black"){
        eatLeft(moves, row-1, max((row-3),-1), -1, piece.color, left, skipped);
        eatRight(moves, row-1, max((row-3),-1), -1, piece.color, right, skipped);
    }else if(piece.color == "red"){
        eatLeft(moves, row+1, min((row+3),ROWS), 1, piece.color, left, skipped);
        eatRight(moves, row+1, min((row+3),ROWS), 1, piece.color, right, skipped);
    }

}

void Board::eatLeft(Piece* moves[ ROWS * COLS * NB_PIECE], int start, int stop, int step, string color, int left, Piece skipped)
{
    Piece last;
    Piece current;
    int row;
    static int nbskipped = 0;
    int off;

    for (int r=start; r<stop; r+=step){
        
        if (left<0){//next to the edge
            break;
        }

        current = virtualBoard[r][left];
        off=offset(r,left,nbskipped);
        if (current.color == ""){//empty tile
            if (skipped.color != "" && last.color==""){
                break;
            }else if(skipped.color != ""){
                (*moves)[off] = skipped;//maybe to modify
            }else{
                (*moves)[off] = last;
            }

            if (last.color != ""){
                if (step == -1){
                    row = max((r-3),0);
                }else{
                    row = min((r+3),ROWS);
                }
                nbskipped++;
                eatLeft(moves, r+step, row, step, color, left-1, skipped=last);
                eatRight(moves, r+step, row, step, color, left+1, skipped=last);
            }
            break;
        }
        else if (current.color == color){//ally color
            break;
        }
        else{//opponent color
            last=current;
        }

        left -= 1;
    }
}

void Board::eatRight(Piece* moves[ ROWS * COLS * NB_PIECE],int start, int stop, int step, string color, int right, Piece skipped)
{
    Piece last;
    Piece current;
    int row;
    static int nbskipped =0;
    int off;
    for (int r=start; r<stop; r+=step){
        
        if (right>=COLS){//next to the edge
            break;
        }

        current = virtualBoard[r][right];
        off=offset(r,right,nbskipped);
        if (current.color == ""){//empty tile
            if (skipped.color != "" && last.color==""){
                break;
            }else if(skipped.color != ""){
                (*moves)[off] = skipped;
            }else{
                (*moves)[off] = last;
            }

            if (last.color != ""){
                if (step == -1){
                    row = max((r-3),0);
                }else{
                    row = min((r+3),ROWS);
                }

                eatLeft(moves, r+step, row, step, color, right-1, skipped=last);
                eatRight(moves, r+step, row, step, color, right+1, skipped=last);
            }
            break;
        }
        else if (current.color == color){//ally color
            break;
        }
        else{//opponent color
            last=current;
        }

        right += 1;
    }
}