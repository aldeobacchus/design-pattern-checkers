#ifndef board_h
#define board_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "piece.h"


using std::vector;
using std::unordered_map;

class Board{
public:
    vector<vector<Piece>> virtualBoard;//virtual matrix containing the piece, this is the real board
    int blackLeft, redLeft;
    int blackKings, redKings;
    int boardTopLeftX;
    int boardTopLeftY;
    unordered_map<Piece, int *> movesList;//this is the list of all the possibles moves <piece, list pos[2] with the position of the move>


    Board();
    void drawChecker(SDL_Renderer* renderer);
    void initializeVirtualBoard();
    void drawGame();
    void move(Piece, int row, int col);
    void remove(Piece);
    Piece getPiece(int row, int col);
    string getWinner();
    unordered_map<Piece, int *> getValidMove(Piece piece);
    unordered_map<Piece, int *> eatLeft(int start, int stop, int step, string color);
    unordered_map<Piece, int *> eatLeft(int start, int stop, int step, string color, int * skipped);
    unordered_map<Piece, int *> eatRight(int start, int stop, int step, string color);
    unordered_map<Piece, int *> eatRight(int start, int stop, int step, string color, int * skipped);
};



#endif /*board_h*/