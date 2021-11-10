#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "board.h"


class Game{
public:
    Piece selected;
    string turn; //BLACK or WHITE
    Board board;

    void update();
    string getWinner();
    void selectPiece(int col, int row);
    void move(int, int);
    void drawValidMoves(unordered_map<Piece, int *>);
    void changeTurn();
    void undoLastMove();//to specify
    void saveGame();//to specify
    void loadGame();//to specify
};

#endif /*game_h*/