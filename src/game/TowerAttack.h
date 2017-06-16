#ifndef __tower_attack_h__
#define __tower_attack_h__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "states/GameStateManager.h"

/** \mainpage TOWER ATTACK game
 *
 *	The goal of the game is to reach the end of the map with attackers. By clicking on towers the attackers start shooting (if are in range).
 *
 *	You can set up your own types of attackers and towers in the files:
 *<pre>
 *	<b>Formats of the files:</b>
 *  
 * 	For the types of <b>Tower</b>s (assets/towers.def):
 *		<color(r, g, b)>	<health>	<damage>	<range>		<shooting speed(seconds per shot)>		<ability> <ability> ... 
 *
 *		Possible abilities:	BASIC			- Basic shot with damage
 *							THREE_AT_TIME	- Three at a time shots with damage
 *							FREEZE			- Freeze attackers	
 *		
 * 	For the types of <b>Attacker</b>s (assets/attacker.def):
 *		<name>	<color(r, g, b)>	<health>	<damage>	<range>		<shooting speed(seconds per shot)> </pre>
 */
 
/**
 * Main TowerAttack game class. Initializes SDL and implements tha main loop of the game.
 */
class TowerAttack {
 
 public:
	/** Initialize the SDL and pushes MenuState to GameStateManager. */
	TowerAttack();
	
	/** Clean up the resources and close the SDL. */
	~TowerAttack();
	
	/**
	 * Start the game.
	 * Contains the main game loop.
	 */
	void start();
	static const int SCREEN_WIDTH = 1750; /**< Screen width. */	
	static const int SCREEN_HEIGHT = 315; /**< Screen height. */
	static const int QUIT_GAME = -1; /**< Quit game indicator. */	
	const int SCREEN_FPS = 60; /**< Frames per second. */
	const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS; /**< Screen tick per frame (ms). */
	
 private:
	SDL_Window * gWindow;
	SDL_Renderer * gRenderer;
	GameStateManager gameStateManager;
};

#endif /* __tower_attack_h__ */
