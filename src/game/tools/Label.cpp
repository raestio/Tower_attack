#include "Label.h"

Label::Label(const std::string & str, int x, int y, int width) {
	loadFont();
	color = { 0xFF, 0xFF, 0xFF, 0xFF };
	setText(str);
	setPosition(x, y);
	setWidth(width);
}

Label::~Label() {
	TTF_CloseFont(font);
	font = NULL;
}

void Label::loadFont() {
	font = TTF_OpenFont(FONT_FILE_PATH, LETTER_SIZE);
	if (!font) { throw std::string("Unable to load font file."); }
}

void Label::setText(const std::string & str) { textString = str; }

void Label::setWidth(int width) {
	this->width = width;
	textRect.w = width;
	textRect.h =  width / textString.length() * LETTER_RATIO;
}

int Label::getWidth() const { return width; }

void Label::setPosition(int x, int y) {
	textRect.x = x;
	textRect.y = y;
}

void Label::draw(SDL_Renderer * gRenderer) const {
	SDL_Surface * surfaceText = TTF_RenderText_Solid(font, textString.c_str(), color);
	SDL_Texture * text = SDL_CreateTextureFromSurface(gRenderer, surfaceText);
	SDL_FreeSurface(surfaceText);
	SDL_RenderCopy(gRenderer, text, NULL, &textRect);
	SDL_DestroyTexture(text);
}

bool Label::isTouched(int x, int y) const {
	return x >= textRect.x && x <= textRect.x + width && y >= textRect.y && y <= textRect.y + textRect.h;
}
