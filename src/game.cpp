#include "../include/game.h"

Game::Game(SDL_Renderer* Renderer){
    renderer = Renderer;
    selected = NULL;
    board = new Board();
    turn = "black";
    initValidMoves(validMoves);
}

void Game::update(){
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 255);
    SDL_RenderClear(renderer);
    board->drawGame(renderer);
    drawValidMoves(validMoves);
    SDL_RenderPresent(renderer);
}

string Game::getWinner(){
    return board->getWinner();
}

bool Game::selectPiece(int row, int col){
    Piece piece;
    bool result;
    if (selected != NULL){ //if we already have selected something
        result = move(row, col);//trying to move to this new location
        if (!result){//for exemple if there is already something in this new location
            selected=NULL;
            selectPiece(row, col);
        }
    }
    piece = board->getPiece(row, col);
    if (piece.color == turn){
        selected = &piece;
        board->getValidMove(validMoves,piece);
        return true;
    }
    return false;
}

bool Game::isValid(int row, int col){
    Piece piece = (*validMoves)[row][col][0];
    if (piece.color == "red" || piece.color == "black"){
        return true;
    }else{
        return false;
    }
}

bool Game::move(int row, int col){
    Piece piece = board->getPiece(row, col);
    Piece* skipped;
    Piece* toRemove;

    if ((*selected).color != "" && piece.color == "" && isValid(row, col)){
        board->move(*selected, row, col);
        skipped=(*validMoves)[row][col];
        for (int i=0; i<NB_PIECE;i++){
            if (skipped[i].color == "red" || skipped[i].color == "black"){
                *toRemove = board->getPiece(skipped->row,skipped->col);
                board->remove(*toRemove);
            }
        }
        changeTurn();
    }
}

void Game::initValidMoves(Piece* move[ROWS][COLS][NB_PIECE]){
    for (int r=0;r<ROWS;r++){
        for (int c=0;c<COLS;c++){
            for(int n=0;n>NB_PIECE;n++){
                validMoves[r][c][n]=nullptr;
            }
        }
    }
}

void Game::changeTurn(){
    initValidMoves(validMoves);
    if(turn == "red"){
        turn = "black";
    }else{
        turn = "red";
    }
}

void Game::drawValidMoves(Piece* validMoves[ROWS][COLS][NB_PIECE]){
    for (int r=0;r<ROWS;r++){
        for (int c=0;c<COLS;c++){
            for(int n=0;n>NB_PIECE;n++){
                if (validMoves[r][c][n]!=nullptr){
                    validMoves[r][c][n]->drawPiece(renderer,board->boardTopLeftX, board->boardTopLeftY,SQUARE_SIZE/4);
                }
            }
        }
    }
}
