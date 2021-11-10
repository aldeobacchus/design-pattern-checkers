#ifndef piece_h
#define piece_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using std::string;

class Piece{
public:
    int row, col; // position on the virtual board
    int x, y; // position on the screen
    string color;
    bool king;
    Piece(int, int, string);
    void getPosition();
    void setKing();
    bool getKing();
    void move(int x, int y);
    void drawPiece();
};



#endif /*piece_h*/