#include "../include/board.h"

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
                }
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
                piece.drawPiece(renderer, boardTopLeftX, boardTopLeftY);
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