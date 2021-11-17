#include "./include/window.h"


int main(int argc, char* argv[]){

    srand(time(NULL));
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart = SDL_GetTicks();
    int frameTime = 0;

    bool run = true;
    Window* gameWindow = new Window;

    gameWindow->init("Checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
    


    while(gameWindow->running() && run){

        if (gameWindow->getWinner() != ""){
            std::cout<<"Winner : "<< gameWindow->getWinner()<<"\n";
            run =false;
        }
        
        gameWindow->handleEvents();
        gameWindow->render();

        frameStart = SDL_GetTicks();
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }

    gameWindow->clean();
    delete gameWindow;

    return 0;
}