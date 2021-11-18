#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "board.h"


class Game{
public:
    Piece* selected;
    string turn; //BLACK or RED
    //Board* board;
    SDL_Renderer* renderer;
    Piece* validMoves[ ROWS * COLS * NB_PIECE]; 

    Game(SDL_Renderer* Renderer);
    void init();
    void update();
    void initValidMoves(Piece* validMoves[ ROWS * COLS * NB_PIECE]);
    string getWinner();
    int offset(int x, int y, int z);
    bool selectPiece(int row, int col);
    bool move(int row, int col);
    void drawValidMoves(Piece* validMoves[ ROWS * COLS * NB_PIECE]);
    bool isValid(int row, int col);
    void changeTurn();
    void undoLastMove();//to specify
    void saveGame();//to specify
    void loadGame();//to specify
};

#endif /*game_h*/