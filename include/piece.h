#ifndef piece_h
#define piece_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "const.h"

#ifdef _WIN32
    #include <SDL.h>
    #include <SDL_image.h>
#endif

#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#endif

#ifdef __linux
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif


using std::string;

class Piece{
public:
    int row, col; // position on the virtual board
    int x, y; // position on the screen
    string color;
    bool king;
    Piece();
    Piece(int Row, int Col, string Color);
    void clear();
    void setVirtualPosition();
    void setKing();
    bool getKing();
    void move(int Row, int Col);
    SDL_Texture* getTexture(SDL_Renderer* renderer);
    void drawPiece(SDL_Renderer* renderer, int boardTopLeftX, int boardTopLeftY,int sq);
};



#endif /*piece_h*/