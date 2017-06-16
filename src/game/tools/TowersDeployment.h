#ifndef __towers_deployment_h__
#define __towers_deployment_h__

#include <memory>
#include <vector>

class Map;
class Tower;

/** Class that deploys towers on the map. */
class TowersDeployment {

 public:
 	/** Creating instances is forbidden. */
 	TowersDeployment() = delete;
 	
 	/**
 	 * Deploy towers on the map.
 	 * A method randomly makes copies from set of towers and deploys them on the map. These deployed towers will be stored in parameter <b> deployedTowers </b>.
 	 * \param loadedTowers Set of towers to choice.
 	 * \param deployedTowers Vector in which the deployed towers will be stored.
 	 * \param map Map where towers will be deployed.
 	 */
	static void deployTowers(const std::vector< std::shared_ptr<Tower> > & loadedTowers, std::vector< std::shared_ptr<Tower> > & deployedTowers, std::shared_ptr<Map> map);
};

#endif /* __towers_deployment_h__ */
