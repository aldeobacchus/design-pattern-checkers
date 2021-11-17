#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "board.h"


class Game{
public:
    Piece selected;
    string turn; //BLACK or RED
    Board board;

    Game();
    void update();
    string getWinner();
    bool selectPiece(int col, int row);
    bool move(int, int);
    void drawValidMoves(unordered_map<Piece, int *>);
    void changeTurn();
    void undoLastMove();//to specify
    void saveGame();//to specify
    void loadGame();//to specify
};

#endif /*game_h*/