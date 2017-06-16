#ifndef __game_objects_loader_h__
#define __game_objects_loader_h__

#include <vector>
#include <memory>
#include <string>
class Ability;
class Tower;
class GameObject;
class Attacker;

/**
 * Class that loads <b>Attacker</b>s and <b>Tower</b>s from their definition files.
 * \throw std::string description of error which can be caused by loading or reading from the definiton files. 
 */
class GameObjectsLoader {

 public:
 	/** Load <b>Attacker</b>s and <b>Tower</b>s from their definition files. */
	void loadGameObjects();
	
	/** \return Loaded <b>Tower</b>s. */
	std::vector< std::shared_ptr<Tower> > getTowers() const;
	
	/** \return Loaded <b>Attacker</b>s. */
	std::vector< std::shared_ptr<Attacker> > getAttackers() const;
	const char * TOWERS_FILE_PATH = "assets/towers.def";
	const char * ATTACKERS_FILE_PATH = "assets/attackers.def";
	
 private:
 	/** Load <b>Tower</b>s. */
 	void loadTowers();
 	
 	/** Load <b>Attacker</b>s. */
 	void loadAttackers();
 	
 	/**
 	 * Create and return specific Tower's ability.
 	 * \param abilityStr Name of the ability.
 	 * \param shootingSpeed Shooting speed of Tower.
 	 * \param damage Damage of Tower.
 	 * \return Pointer to specific Ability.
 	 */
 	Ability * getAbility(const std::string & abilityStr, double shootingSpeed, int damage);
	std::vector< std::shared_ptr<Tower> > towers;
	std::vector< std::shared_ptr<Attacker> > attackers;
};

#endif /* __game_objects_loader_h__ */
