#include "PathFinder.h"
#include "../map/Tile.h"
#include "../map/Map.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>

PathFinder::Node::Node() {
	gCost = hCost = 0;
}

PathFinder::Node::Node(const std::shared_ptr<Tile> tile) : tile(tile) {
	gCost = hCost = 0;
}

int PathFinder::Node::fCost() const { return gCost + hCost; }

void PathFinder::setNodeMap(const std::shared_ptr<Map> map) {
	for (int y = 0; y < Map::MAP_HEIGHT; ++y) {
		
		std::vector<Node> nodeVectorTmp;
		for (int x = 0; x < Map::MAP_WIDTH; ++x) {
			Node nodeTmp(map->getTileFrom(x * Tile::TILE_DIMENSION, y * Tile::TILE_DIMENSION));
			nodeVectorTmp.push_back(nodeTmp);
		}
		
		nodeMap.push_back(nodeVectorTmp);
	}
}

void PathFinder::findPath(const std::shared_ptr<Tile> startTile, const std::shared_ptr<Tile> finishTile) {
	std::map<int, Node*> openSet; //set of nodes to be evaluated
	std::map<int, Node*> closedSet; //already evaluated set of nodes
	
	Node * startNode = &nodeMap[startTile->getY()][startTile->getX()];
	Node * finishNode = &nodeMap[finishTile->getY()][finishTile->getX()];
	//insert start node to open set
	openSet.insert(std::pair<int,Node*> (nodeMap[startTile->getY()][startTile->getX()].tile->getID(), &nodeMap[startTile->getY()][startTile->getX()]));
	
	while (!openSet.empty()) {
		auto toEraseIt = openSet.begin();
		Node * currentNode = toEraseIt->second;
		auto nodeIt = toEraseIt;
		nodeIt++;
		
		//Find node from the open set with the lowest fCost
		for (; nodeIt != openSet.end(); ++nodeIt) {
			if (nodeIt->second->fCost() < currentNode->fCost() || (nodeIt->second->fCost() == currentNode->fCost() && nodeIt->second->hCost < currentNode->hCost)) {
				toEraseIt = nodeIt;
				currentNode = nodeIt->second;
			}
		}
		
		//remove current node from open set
		openSet.erase(toEraseIt);
		//add current node to closed set
		closedSet.insert(std::pair<int, Node*>(currentNode->tile->getID(), currentNode));
		
		//if current tile is the finish tile
		if (currentNode->tile->getID() == finishNode->tile->getID()) {
			retracePath(*startNode, *finishNode);
			return;
		}
		
		//get neighbours of the current node
		std::vector<PathFinder::Node*> neighbours = getNeighbours(*currentNode);
		for (Node * neighbour : neighbours) {
			//if neighbour is not walkable or is in closed set then skip the iteration
			if (!neighbour->tile->isWalkable() || closedSet.find(neighbour->tile->getID()) != closedSet.end()) { continue; }
			
			//claculate new distance to neighbour
			int newMovementCostToNeighbour = currentNode->gCost + getDistance(currentNode->tile, neighbour->tile);
			
			//check if the new path to neighbour is shorter or is not in open set
			if (newMovementCostToNeighbour < neighbour->gCost || openSet.find(neighbour->tile->getID()) == openSet.end()) {
			 	
			 	//set gCost an hCost and parent of neighbour to current
			 	neighbour->gCost = newMovementCostToNeighbour;
			 	neighbour->hCost = getDistance(neighbour->tile, finishNode->tile);
			 	neighbour->parent = currentNode;
			 	
			 	//insert the neighbour to open set if is not in open set
			 	if (openSet.find(neighbour->tile->getID()) == openSet.end()) { openSet.insert(std::pair<int,Node*>(neighbour->tile->getID(), neighbour)); }
			}
		}
			
	}
	
}

void PathFinder::retracePath(const Node & startNode, const Node & finishNode) {
	Node currentNode = finishNode;
	
	while (currentNode.tile->getID() != startNode.tile->getID()) {
		shortestPath.push_back(std::pair<double, double> (currentNode.tile->getX() * Tile::TILE_DIMENSION, currentNode.tile->getY() * Tile::TILE_DIMENSION));
		currentNode = *currentNode.parent;
	}
	std::reverse(shortestPath.begin(), shortestPath.end());
}

std::vector<PathFinder::Node*> PathFinder::getNeighbours(const Node & node){
	std::vector<Node*> neighbours;	
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			if ((x == 0 && y == 0) || (abs(x) == abs(y))) {	continue; }
			
			int checkX = node.tile->getX() + x;
			int checkY = node.tile->getY() + y;
			
			if (checkX >= 0 && checkX < Map::MAP_WIDTH && checkY >= 0 && checkY < Map::MAP_HEIGHT) {
				Node * tmp = &nodeMap[checkY][checkX];
				neighbours.push_back(tmp);
			}		
		}
	}	
	return neighbours;
}


int PathFinder::getDistance(const std::shared_ptr<Tile> tile1, const std::shared_ptr<Tile> tile2) const {
	return abs(tile1->getX() - tile2->getX()) + abs(tile1->getY() - tile2->getY());
}

std::vector< std::pair<double, double> > PathFinder::getShortestPath() const { return shortestPath; }

