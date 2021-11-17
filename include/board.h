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
using std::tuple;

class Board{
public:
    //vector<vector<Piece>> virtualBoard;//virtual matrix containing the piece, this is the real board
    Piece virtualBoard[ROWS][COLS];
    int blackLeft, redLeft;
    int blackKings, redKings;
    int boardTopLeftX;
    int boardTopLeftY;
    //Piece movesList[ROWS][COLS];//matrix of all the possibles moves


    Board();
    void drawChecker(SDL_Renderer* renderer);
    void initializeVirtualBoard();
    void drawGame(SDL_Renderer* renderer);
    void move(Piece piece, int row, int col);
    void remove(Piece piece);
    Piece getPiece(int row, int col);
    string getWinner();
    void getValidMove(Piece moves[ROWS][COLS], Piece piece);
    //void eatLeft(vector<Piece> moves[ROWS][COLS], int start, int stop, int step, string color, int left);
    //void eatLeft(unordered_map<int *, bool> moves,int start, int stop, int step, string color, int left, Piece skipped);
    void eatLeft(Piece moves[ROWS][COLS],int start, int stop, int step, string color, int left, Piece skipped);
    void eatRight(Piece moves[ROWS][COLS],int start, int stop, int step, string color, int right, Piece skipped);
    //void eatRight(unordered_map<int *, bool> moves, int start, int stop, int step, string color, int right, Piece skipped);
    //unordered_map<Piece, int *> eatRight(int start, int stop, int step, string color, int dir, int * skipped);
};



#endif /*board_h*/