#include "../include/piece.h"


Piece::Piece(){
    row = 0;
    col = 0;
    color.clear();
    king = NULL;
    x = 0;
    y = 0;
}


Piece::Piece(int Row, int Col, string Color){
    row = Row;
    col = Col;
    color = Color;
    king = false;
    x = 0;
    y = 0;
    setVirtualPosition();
}

void Piece::clear(){
    row = 0;
    col = 0;
    color.clear();
    king = NULL;
    x = 0;
    y = 0;
}

void Piece::setVirtualPosition(){
    x = SQUARE_SIZE * col + SQUARE_SIZE/2;
    y = SQUARE_SIZE * row + SQUARE_SIZE/2;
}

void Piece::setKing(){
    king = true;
}

bool Piece::getKing(){
    return king;
}

void Piece::move (int Row, int Col){
    row = Row;
    col = Col;
    setVirtualPosition();
}

SDL_Texture * Piece::getTexture(SDL_Renderer* renderer){
    //if black 
        //if king -> return blaclKing texture
        //else -> return black texture
    //else
        //if king -> return redking texture
        //else -> return reed texture
    SDL_Texture* texture;
    SDL_Surface* surface;
    if (color == "black"){
        if (king == true){
            surface = IMG_Load("../data/blackKing.png");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
        }else{
            surface = IMG_Load("../data/black.png");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
        }
    }else if (color == "red"){
        if (king == true){
            surface = IMG_Load("../data/redKing.png");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
        }else{
            surface = IMG_Load("../data/red.png");
            texture = SDL_CreateTextureFromSurface(renderer, surface);
        }
    }
    SDL_FreeSurface(surface);
    return texture;
}

void Piece::drawPiece(SDL_Renderer* renderer, int boardTopLeftX, int boardTopLeftY,int sq){
    int w, h;
    SDL_Rect fromRect, toRect;

    SDL_Texture* texture = getTexture(renderer);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    
    fromRect.w = w;
    fromRect.h = h;
    fromRect.x = fromRect.y = 0;

    toRect.h = sq;
    toRect.w = sq;
    toRect.x = boardTopLeftX + x - (w/2);
    toRect.y = boardTopLeftY + y - (h/2);

    SDL_RenderCopy(renderer, texture, &fromRect, &toRect);
}
