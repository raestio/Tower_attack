#include "TowersDeployment.h"
#include <cstdlib>
#include <ctime>
#include "../map/Map.h"
#include "../game_objects/Tower.h"

void TowersDeployment::deployTowers(const std::vector< std::shared_ptr< Tower >> & loadedTowers, std::vector< std::shared_ptr< Tower >> & deployedTowers, std::shared_ptr<Map> map) {								
		srand(time(NULL));
		for (int row = 1; row < Map::MAP_HEIGHT - 1; ++row) {
			for (int col = 2; col < Map::MAP_WIDTH - 2; ++col) {
				
				if (map->isWalkableAt(row, col) && map->isWalkableAt(row, col - 1) && map->isWalkableAt(row, col + 1) && map->isWalkableAt(row - 1, col) && map->isWalkableAt(row + 1, col) && rand() % 6 == 1) {				
					std::shared_ptr<Tower> tmpTower = std::shared_ptr<Tower> (loadedTowers[rand() % loadedTowers.size()]->clone());
					tmpTower->setPosition(col, row);
					map->deployTower(row, col, tmpTower);
					deployedTowers.push_back(tmpTower);
				}				
			}	
		}	
		
}
