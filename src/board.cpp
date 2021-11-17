#include "../include/board.h"
#define max(x,y) (((x) >= (y)) ? (x) : (y))
#define min(x,y) (((x) <= (y)) ? (x) : (y))


Board::Board(){
    blackLeft = redLeft = 12;
    blackKings = redKings = 0;
    boardTopLeftX = boardTopLeftY = 0;//usefull later, if we want to resize the win, maybe should move this to main later
    initializeVirtualBoard();
}

void Board::drawChecker(SDL_Renderer* renderer){
    SDL_Color white = BOARD_WHITE_COLOR;
    SDL_Color black = BOARD_BLACK_COLOR;

    for (int i=0; i < ROWS; ++i){
        for (int j=0; j < COLS; ++j){
            SDL_Color currentColor = (i+j) % 2 == 0 ? white : black;
            SDL_Rect outline;
            outline.w = SQUARE_SIZE;
            outline.h = SQUARE_SIZE;
            outline.x = boardTopLeftX + i*SQUARE_SIZE;
            outline.y = boardTopLeftY + j*SQUARE_SIZE;
            SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
            SDL_RenderFillRect(renderer, &outline);
        }
    }
}

void Board::initializeVirtualBoard(){
    for (int row; row < ROWS; row++){
        for (int col; col < COLS; col++){
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
    drawChecker(renderer);
    for (int row; row < ROWS; row++){
        for (int col; col < COLS; col++){
            Piece piece = virtualBoard[row][col];
            if (piece.color == "red" || piece.color == "black"){
                piece.drawPiece(renderer, boardTopLeftX, boardTopLeftY,SQUARE_SIZE);
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
    }
}

void Board::getValidMove(Piece* moves[ROWS][COLS][NB_PIECE], Piece piece){
    
    Piece skipped;
    int left = piece.col -1;
    int right = piece.col +1;
    int row = piece.row;
    
    skipped.clear();
    if (piece.color == "black"){
        eatLeft(moves, row-1, max((row-3),-1), -1, piece.color, left, skipped);
        eatRight(moves, row-1, max((row-3),-1), -1, piece.color, right, skipped);
    }else if(piece.color == "red"){
        eatLeft(moves, row+1, min((row+3),ROWS), 1, piece.color, left, skipped);
        eatRight(moves, row+1, min((row+3),ROWS), 1, piece.color, right, skipped);
    }
}

void Board::eatLeft(Piece* moves[ROWS][COLS][NB_PIECE],int start, int stop, int step, string color, int left, Piece skipped)
{
    Piece last;
    Piece current;
    int row;
    static int nbskipped = 0;

    for (int r=start; r<stop; r+=step){
        
        if (left<0){//next to the edge
            break;
        }

        current = virtualBoard[r][left];
        if (current.color == ""){//empty tile
            if (skipped.color != "" && last.color==""){
                break;
            }else if(skipped.color != ""){
                (*moves)[r][left][nbskipped] = skipped;//maybe to modify
            }else{
                (*moves)[r][left][nbskipped] = last;
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

void Board::eatLeft(Piece* moves[ROWS][COLS][NB_PIECE],int start, int stop, int step, string color, int right, Piece skipped)
{
    Piece last;
    Piece current;
    int row;
    static int nbskipped =0;
    for (int r=start; r<stop; r+=step){
        
        if (right>=COLS){//next to the edge
            break;
        }

        current = virtualBoard[r][right];
        if (current.color == ""){//empty tile
            if (skipped.color != "" && last.color==""){
                break;
            }else if(skipped.color != ""){
                (*moves)[r][right][nbskipped] = skipped;
            }else{
                (*moves)[r][right][nbskipped] = last;
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