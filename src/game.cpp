#include "../include/game.h"

Game::Game(SDL_Renderer* Renderer){
    renderer = Renderer;
    selected = NULL;
    board = new Board();
    turn = "black";
     
    initValidMoves(validMoves);
}

void Game::init(){
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 255);
    SDL_RenderClear(renderer);
    board->drawGame(renderer);
    SDL_RenderPresent(renderer);
}

void Game::update(){
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 255);
    SDL_RenderClear(renderer);
    board->drawGame(renderer);
    std::cout<<"drawGame Done\n";
    drawValidMoves(validMoves);
    std::cout<<"drawValidMoves Done\n";
    SDL_RenderPresent(renderer);
}

string Game::getWinner(){
    return board->getWinner();
}

int Game::offset(int x, int y, int z){
    return (z*ROWS*COLS) + (y*ROWS) +x;
}
bool Game::selectPiece(int row, int col){
    Piece piece;
    bool result;
    std::cout<<"Selecting a piece at ["<<row<<":"<<col<<"]\n";
    if (selected != NULL){ //if we already have selected something
        result = move(row, col);//trying to move to this new location
        if (!result){//for exemple if there is already something in this new location
            selected=NULL;
            selectPiece(row, col);
        }
    }
    piece = board->getPiece(row, col);
    //std::cout<<"Turn : "<<turn<<"selectedColor"<<piece.color<<"\n";
    if (piece.color == turn){
        selected = &piece;
        std::cout<<"Piece selected\n";
        board->getValidMove(validMoves,piece);
        return true;
    }
    return false;
}

bool Game::isValid(int row, int col){
    int off;
    off=offset(row, col, 0);
    Piece piece = (*validMoves)[off];
    if (piece.color == "red" || piece.color == "black"){
        return true;
    }else{
        return false;
    }
}

bool Game::move(int row, int col){
    Piece piece = board->getPiece(row, col);
    Piece* skipped;
    Piece* toRemove = nullptr;

    if ((*selected).color != "" && piece.color == "" && isValid(row, col)){
        board->move(*selected, row, col);
        int off=offset(row, col, 0);
        skipped=validMoves[off];
        for (int i=0; i<NB_PIECE;i++){
            if (skipped[i].color == "red" || skipped[i].color == "black"){
                *toRemove = board->getPiece(skipped->row,skipped->col);
                board->remove(*toRemove);
            }
        }
        changeTurn();
    }else{
        return false;
    }
    return true;
}

void Game::initValidMoves(Piece* moves[ ROWS * COLS * NB_PIECE]){
    int off;

    for (int r=0;r<ROWS;r++){
        for (int c=0;c<COLS;c++){
            for(int n=0;n>NB_PIECE;n++){
                off=offset(r,c,n);
                validMoves[off]=nullptr;
                std::cout<<"validmove init\n";
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

void Game::drawValidMoves(Piece* validMoves[ ROWS * COLS * NB_PIECE]){
    std::cout<<"drawing Valid Moves\n\n";
    int off;
    for (int r=0;r<ROWS;r++){
        std::cout<<"    R:"<<r<<"\n";
        for (int c=0;c<COLS;c++){
            std::cout<<"  C:"<<c<<"\n";
            for(int n=0;n<NB_PIECE;n++){
                std::cout<<"N:"<<n<<"\n";
                off = offset(r,c,n);
                if (validMoves[off]){//segfault
                    std::cout<<"Drawing valid moves  COLOR : ";
                    std::cout<<validMoves[off]->color<<"\n";
                    std::cout<<"r:"<<r<<" c :"<<c<<" n:"<<n<<"\n";
                    validMoves[off]->drawPiece(renderer,board->boardTopLeftX, board->boardTopLeftY,(SQUARE_SIZE)/4);
                    
                }
            }
        }
    }
}
