#ifndef __game_object_h__
#define __game_object_h__

#include <SDL2/SDL.h>
#include "../map/Tile.h"
#include <string>
#include <iostream>

/** Abstract class that represents game object. */
class GameObject {

 public:
 	/** Implicit constuctor initialize member attributes. */
 	GameObject();
 	
 	/**Constructor initializes member attributes with given parameters. */
 	GameObject(const SDL_Color color, int health, int damage, int range, int width);
 	
 	/** Virtual destructor. */
 	virtual ~GameObject();
 	
 	/** Update the game object. */
 	virtual void update(double deltaTime);
 	
 	/** Draw the game object. */
 	virtual void draw(SDL_Renderer * gRenderer) const = 0;
 	
 	/** Set the position of the game object. */
 	virtual void setPosition(double x, double y);
 	
 	/**
 	 * Allow fire for the game object.
 	 * \param target On which the game object will shot. 
 	 */
 	virtual void allowFire(const std::shared_ptr<GameObject> target);
 	
 	/** Forbid fire for the game object. */
 	virtual void forbidFire();
 	
 	/** \return <b>TRUE</b> if fire is allowed. Else <b>FALSE</b> */
 	virtual bool isFireAllowed() const;
 	
 	/** Virtual "copy constuctor". */
 	virtual GameObject * clone() const = 0;
 	
 	/** Serialize the game object. */
 	virtual void serialize(std::ostream & os) const;
 	
 	/** Deserializes the game object. */
 	virtual void deserialize(std::istream & is);
 	
 	/** Freeze the game object. */
 	virtual void freeze();
 	
 	/** \return <b>x</b> coordinate of the position. */
 	double getX() const;
 	
 	/** \return <b>y</b> coordinate of the position. */
 	double getY() const;
 	
 	/** \return <b>width</b> of the game object. */
 	int getWidth() const;
 	
 	/** \return <b>TRUE</b> if the game object is destroyed. Else <b>FALSE</b>. */
 	bool isDestroyed() const;
 	
 	/**
 	 * Decrease health of the game object.
 	 * \param hp Value that is subtracted from the <b>health</b>.
 	 */
 	void decreaseHealth(int hp);
 	
 	/**
 	 * Check if the game object has in range the position of another object.
 	 * \param x \param y Coordinates (top-left corner) of the another game object.
 	 * \param width Width of the another game object.
 	 * \return <b>TRUE</b> if has in range. Else <b>FALSE</b>
 	 */
 	bool isInRange(double x, double y, int width) const;
	
	/** Overloaded operator for serialization. */ 
 	friend std::ostream & operator << (std::ostream & os, const GameObject & o);
 	
 	/** Overloaded operator for deserialization. */
 	friend std::istream & operator >> (std::istream & is, GameObject & o);
 	
 protected:
 	/** Copy attributes from the parameter <b>x</b>.
 	 * \param x GameObject from which the parameters will be copied.
 	 */
 	void copyAttributes(const GameObject & x);
 	
 	/** Draw health of the game object to the screen. \param gRenderer */
 	void drawHealth(SDL_Renderer * gRenderer) const;
 	
 	/** Checking range between the game objects positions.
 	 * \return <b>TRUE</b> positions are in range. Else <b>FALSE</b>
 	 */
 	bool isInRangeBetween(double x1, double y1, double x2, double y2) const;
 	
 	/** Pythagorean theorem. 
 	 * \return Size of hypotenuse.
 	 */
 	double pythagorean(double a, double b) const;
 	SDL_Color color;
 	bool destroyed; /**< Flag if the game object is destroyed. */
 	int maxHealth, health, damage, range, width;
 	double posX, posY;
};

#endif /* __game_object_h__ */
