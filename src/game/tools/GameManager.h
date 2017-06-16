#ifndef __game_manager_h__
#define __game_manager_h__

#include "Timer.h"
#include <memory>
#include <vector>
#include <string>
class Map;
class Attacker;
class Tower;
class GameObject;

/**
 * Class saves and loads the game from file.
 * \throw std::string description of error which can be caused by loading or reading from the files.
 */
class GameManager {

 public:
 	/**
 	 * Creating instances is forbidden.
 	 */
 	GameManager() = delete;
 	
 	/**
 	 * Save game.
 	 * Method serializes each object.
 	 * \param map Map of the game.
 	 * \param towers <b>Tower</b>s
 	 * \param attackers <b>Attacker</b>s
 	 * \param freezeTimer Freeze timer to know the remaining time of the frozen attackers after the game loads.
 	 * \param attackersAttacking Flag if attackers are attacking.
 	 * \param attackersFrozen Flag if attackers are frozen.
 	 * \param score Score of the player.
 	 */
 	static void saveGame(const std::shared_ptr<Map> map, 
 						 const std::vector< std::shared_ptr<Tower> > & towers, const std::vector< std::shared_ptr<Attacker> > & attackers, 
 						 const Timer & freezeTimer, 
 						 bool attackersAttacking, bool attackersFrozen,
						 int score);
						 
	/**
 	 * Load game.
 	 * Method deserializes each object.
 	 * \param map Map in which the loaded <b>map</b> will be stored.
 	 * \param towers Vector of <b>Tower</b>s in which the loaded <b>towers</b> will be stored.
 	 * \param attackers Vector of <b>Attacker</b>s in which the loaded <b>attackers</b> will be stored.
 	 * \param freezeTimer Freeze timer in which the loaded <b>freezeTimer</b> will be stored.
 	 * \param attackersAttacking Flag in which the loaded <b>attackersAttacking</b> flag will be stored.
 	 * \param attackersFrozen Flag in which the loaded <b>attackersFrozen</b> flag will be stored.
 	 * \param score Score in which the loaded <b>score</b> will be stored.
 	 */
 	static void loadGame(std::shared_ptr<Map> * map,
 						 std::vector< std::shared_ptr<Tower> > & towers, std::vector< std::shared_ptr<Attacker> > & attackers,
						 Timer & freezeTimer,
						 bool & attackersAttacking, bool & attackersFrozen,
						 int & score);
	
	static constexpr char * SAVE_ATTACKERS_PATH = "assets/game_save/attackersVector.save"; /**< Path to attackers serialization file.*/
	static constexpr char * SAVE_TOWERS_PATH = "assets/game_save/towersVector.save"; /**<Path to towers serialization file.*/
	static constexpr char * SAVE_OBJECTS_PATH = "assets/game_save/objects.save"; /**<Path to remaining objects serialization file.*/
	
 private:
 	
 	/**
 	 * Serialize template object to file.
 	 * \param obj Object to be serialized.
 	 * \param filePath Path of the output file.
 	 * \param append If <b>TRUE</b> then the data appends to the file. Else the data will be overrided in the file.
 	 */
 	template<typename Object> 
 	static void serializeObject(const Object & obj, const char * filePath, bool append);
 	
 	/**
 	 * Serialize template container of pointers to objects to the file.
 	 * \param objects Container of objects pointers to be serialized.
 	 * \param filePath Path of the output file.
 	 */ 	 
 	template<typename Container> 
	static void serializeVector(const Container & objects, const char * filePath);
	
	/**
 	 * Deserialize template object from file.
 	 * \param obj Object to be deserialized.
 	 * \param filePath Path of the input file.
 	 * \param line Line of the file from which the <b>obj</b> will be deserialized.
 	 */ 
	template<typename Object> 
 	static bool deserializeObject(Object & obj, const char * filePath, int line);
 	
 	/**
 	 * Jump to the line in the file.
 	 * \param file File in which the jump is to be done.
 	 * \param line Number of the line.
 	 */	
	static std::ifstream & goToLine(std::ifstream & file, int line);
};

#endif /* __game_manager_h__ */
