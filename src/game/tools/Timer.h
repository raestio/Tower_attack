#ifndef __timer_h__
#define __timer_h__
#include <iostream>

/** Timer class used for countdown function and for capturing time. */
class Timer{

 public:
	/** Initialize variables. */
	Timer();
	
	/** Start timer. */
	void start();
	
	/**
	 * Start countdown.
	 * \param duration Duration of timer.
	 */
	void start(double duration);
	
	/** Stop timer. */
	void stop();
	
	/**
	 * Get timer's time.
	 * \return Timer's time in ms.
	 */
	int getTicks() const;
	
	/**
	 * Check the status of the timer
	 * \return <b>TRUE</b> if timer is running. Else <b>FALSE</b>.
	 */
	bool isStarted() const;
	
	/**
	 * Check if countdown finished.
	 * \return <b>TRUE</b> if timer's countdown finished. Else <b>FALSE</b>.
	 */
	bool finished();
	
	/** \return Delta time. */
	double getDeltaTime() const;
	
	/**
	 * Overloaded operator serializes timer.
	 * It writes member attributes to output stream.
	 */
	friend std::ostream & operator << (std::ostream & os, const Timer & t);
	
	/**
	 * Overloaded operator deserializes timer.
	 * It reads attributes from input stream.
	 */
	friend std::istream & operator >> (std::istream & is, Timer & t);
	
 private:
	double startTicks, current, previous, duration, delta;
	bool started;
};

#endif /* __timer_h__ */
