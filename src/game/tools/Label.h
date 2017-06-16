#ifndef __label_h__
#define __label_h__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
/**
 * Basic text label class.
 * \throw std::string If <b>FONT_FILE_PATH</b> does not exist or if the TTF file is corrupted.
 */
class Label {

 public:
 	/**
 	 * Create text label.
 	 * Font size adjusts to label's width due to LETTER_RATIO.
 	 * \param str String to be displayed.
 	 * \param x \param y Coordinates of top-left corner.
 	 * \param width Width of text label.
 	 */
	Label(const std::string & str, int x, int y, int width);
	
	/** Clean up resources. */
	~Label();
	
	/**
	 * Set label's text.
	 * \param str String to be displayed.
	 */
	void setText(const std::string & str);
	
	/**
	 * Set label's position.
	 * \param x \param y Coordinates of top-left corner.
	 */
	void setPosition(int x, int y);
	
	/**
	 * Set label's width.
	 * \param width Width of text label.
	 */
	void setWidth(int width);
	
	/** \return width of label */
	int getWidth() const;
	
	/** Draw label to screen. */
	void draw(SDL_Renderer * gRenderer) const;
	
	/** \return TRUE if coordinates (also parameters) x, y are inside of label's area. Else FALSE. */
	bool isTouched(int x, int y) const;
	
	const int LETTER_SIZE = 512; /**< Font size. */
	const double LETTER_RATIO = 2.0; /**< Label's height multiplier. */
	const char * FONT_FILE_PATH = "assets/font.ttf"; /**< Path to TTF file. */
 private:
 	/** Load TTF font. */
 	void loadFont();
 	int width;
 	std::string textString;
 	TTF_Font * font;
 	SDL_Rect textRect;
 	SDL_Color color;
};

#endif /* __label_h__ */
