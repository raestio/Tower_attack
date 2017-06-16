#include "TowerAttack.h"

#include <iostream>
#include <string>

#include "states/MenuState.h"
#include "tools/Timer.h"


TowerAttack::TowerAttack() {
	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO); 
	
	//Set texture filtering to linear
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	//Create window
	gWindow = SDL_CreateWindow( "Tower Attack",	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	//Create renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	
	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
	//Initialize SDL_ttf
	TTF_Init();
	
	//Display the game menu
	gameStateManager.push(std::shared_ptr<State> (new MenuState(&gameStateManager)));	
}

TowerAttack::~TowerAttack() {
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL
	SDL_Quit();
}

void TowerAttack::start() {
	int now = 0;
	int previous = 0;	
	double deltaTime;
	Timer capTimer;
	
	//While game is running
	while (true) {
		capTimer.start();
		
		//Rendering
		try {
			gameStateManager.inputHandle();
			gameStateManager.update(capTimer.getDeltaTime());
			gameStateManager.render(gRenderer);
		}
		//User has quited the game
		catch (int quit) { break; }
		//Error occured
		catch (const std::string & str) { 
			std::cout << "Error:\n" << str << std::endl;
			break;
		}
		
		int frameTicks = capTimer.getTicks();
		if( frameTicks < SCREEN_TICK_PER_FRAME ) {
			//Wait remaining time
			SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
		}		
	}
}
