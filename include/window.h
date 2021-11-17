#pragma once
#include "SDL.h"

#undef main

#include "game.h"
#include <vector>

class Window
{
public:
	void update(float deltaTime);
	void handleEvents();
	void clean();
	void render();
	bool running();

	Window();
	~Window();
	void calculateInitialWindowDimensions();
		
	void init(const char* title, int xpos, int ypos, bool fullscreen);
	void handleKeyDown(SDL_KeyboardEvent& key);
	void handleKeyUp(SDL_KeyboardEvent& key);
	void resizeWindow(int windowWidth, int windowHeight);
    string getWinner();
	static SDL_Renderer* renderer;
	static int screenHeight;
	static int screenWidth;
private:
	bool isRunning;
	SDL_Window* window;
	bool frozen;
	Game* game;

};