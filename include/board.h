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

//class EventManager;
//class ObserverInterface;
//class WinnerObserver{}

class Board{
private:
    //Singleton
    Board();
    static Board *instance;
public:
    Piece virtualBoard[ROWS][COLS];
    int blackKings, redKings;
    int boardTopLeftX;
    int boardTopLeftY;
    int blackLeft, redLeft;



    //Board();
    static Board* getInstance();
    Board( Board const& ) = delete;
    Board& operator = ( Board const& ) = delete;
    void drawChecker(SDL_Renderer* renderer);
    void initializeVirtualBoard();
    void drawGame(SDL_Renderer* renderer);
    void move(Piece piece, int row, int col);
    void remove(Piece piece);
    Piece getPiece(int row, int col);
    string getWinner();
    int offset(int x, int y, int z);
    void getValidMove(Piece* moves[ ROWS * COLS * NB_PIECE], Piece piece);
    void eatLeft(Piece* moves[ ROWS * COLS * NB_PIECE],int start, int stop, int step, string color, int left, Piece skipped);
    void eatRight(Piece* moves[ ROWS * COLS * NB_PIECE],int start, int stop, int step, string color, int right, Piece skipped);
    };



#endif /*board_h*/