#include "Timer.h"
#include <SDL2/SDL.h>
Timer::Timer() {
    delta = 0.02;
	startTicks = duration = current = previous = 0;
    started = false;
}

void Timer::start() {
    started = true;
    startTicks = SDL_GetTicks();
    
    //Compute delta time		
	current = SDL_GetTicks();
	delta = (double)(current - previous) / 1000;
	previous = current;
}

void Timer::start(double duration) {
    started = true;
	this->duration = duration;
    startTicks = SDL_GetTicks();
}

bool Timer::finished() {
	current = (SDL_GetTicks() - startTicks) / 1000.0;
	if ((SDL_GetTicks() - startTicks) / 1000.0 > duration) {
		stop();
		return true;
	} 
	
	return false;
}

void Timer::stop() {
    started = false;
	startTicks = 0;
}

int Timer::getTicks() const {
	return started ? SDL_GetTicks() - startTicks : 0;
}

bool Timer::isStarted() const { return started; }

double Timer::getDeltaTime() const { return delta; }

std::ostream & operator << (std::ostream & os, const Timer & t) {
	os << t.startTicks << " " << t.delta << " " << t.current << " " << t.previous << " " << t.duration << " " << t.started << " ";
	return os;
}

std::istream & operator >> (std::istream & is, Timer & t) {
	is >> t.startTicks >> t.delta >> t.current >> t.previous >> t.duration >> t.started;
	t.startTicks = t.current;
	return is;
}

