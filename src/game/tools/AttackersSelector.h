#ifndef __attackers_selector_h__
#define __attackers_selector_h__

#include <SDL2/SDL.h>
#include <memory>
#include <vector>

class Label;
class Attacker;

/** Class which displays set of attackers to screen and allows to choose some of them for the game. */
class AttackersSelector {

 public:
 	/** Initialize member attributes and create the counter label for selected attackers. */
 	AttackersSelector();
 	
 	/**
 	 * Set the set of attackers to choose from.
 	 * \param attackers Set of attackers to choose from represented by vector.
 	 */
 	void setAttackersToChoice(const std::vector< std::shared_ptr<Attacker> > & attackers);

	
	/**
	 * Handle click event.
	 * Method decides which attacker is selected, creates a copy of selected attacker and pushes it to <b>selectedAttackers</b> vector.
	 * \param e SDL_MOUSEBUTTONDOWN event.
	 */
	void handleEvent(SDL_Event & e);
	
	/** Updating the counter label and checking if the attackers are selected. */
	void update();
	
	/** Draw counter label and attackers. */
	void draw(SDL_Renderer * gRenderer) const;
	 	
 	/**
 	 * Check if the attackers are selected.
 	 * \return <b>TRUE</b> if attackers are selected. Else <b>FALSE</b>.
 	 */
	bool areAttackersSelected() const;
	
	/** \return Selected attackers. */
	std::vector< std::shared_ptr<Attacker> > getSelectedAttackers() const;
	const int SPACING = 4; /**< Spacing between displayed attackers. */
	const int ATTACKERS_TO_CHOICE = 5; /**< Number of attackers that must be selected. */
	
 private:	
 	bool attackersAreSelected;
 	int attackersToChoiceCount; /**< Number of currently selected attackers. */
 	std::vector< std::shared_ptr<Attacker> > attackersToChoice;
 	std::vector< std::shared_ptr<Attacker> > selectedAttackers;
 	std::shared_ptr<Label> attackersCounterLabel;
 	std::vector<std::shared_ptr<Label>> attackersNames;
};


#endif /* __attackers_selector_h__ */
