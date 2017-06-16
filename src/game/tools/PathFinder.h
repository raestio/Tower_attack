#ifndef __path_finder_h__
#define __path_finder_h__

#include <memory>
#include <vector>
#include <list>
#include <map>

class Map;
class Tile;

/** Class for searching the shortest path using A* algorithm. */
class PathFinder {

 public:
 	/**
 	 * Create map of <b>Node</b>s from the original <b>map</b> in order to execute path finding algorithm.
 	 * We want to have map's <b>Tile</b>s in Node structure because of the Node's member attributes which are required for path searching.
 	 * 
 	 * \param map Original map of <b>Tile</b>s from which the map of <b>Node</b>s will be created.
 	 */
	void setNodeMap(const std::shared_ptr<Map> map);
	
	/**
	 * Find the shortest path between two tiles.
	 * \param startTile Starting tile of path.
	 * \param finishTile Ending tile of path.
	 */
	void findPath(const std::shared_ptr<Tile> startTile, const std::shared_ptr<Tile> finishTile);
	
	/**
	 * \return Returns the shortest path computed in <b>findPath</b> method.
	 */
	std::vector< std::pair<double, double> > getShortestPath() const;
	
	/** Struct that contains necessary elements for path searching. */
 	struct Node {
 		/** Initialize member attributes. */
		Node();
		
		/** Initialize member attributes and set the tile attribute. */
		Node(const std::shared_ptr<Tile> tile);
		
		/** \return Sum of <b>gCost</b> and <b>hCost</b>. */
		int fCost() const;
		int gCost; /**< Distance from the starting node.*/
		int hCost; /**< Distance from the end node. (heuristic)*/
		Node * parent; /**< Pointer to parent node used for retracing path. */
		std::shared_ptr<Tile> tile; /**< Tile of the original map.*/
	};
	
 private:
 	/**
 	 * Retrace path which was found in <b>findPath</b> method.
 	 * Path will be stored in <b>shortestPath</b>.
 	 */
 	void retracePath(const Node & startNode, const Node & finishNode);
 	
 	/**
 	 * Find the neighbours of the given node in <b>nodeMap</b>.
 	 * \param node Node from which the neighbours will be searched.
 	 */
 	std::vector<PathFinder::Node*> getNeighbours(const Node & node); 
 	
 	/** \return Distance between two tiles. */
 	int getDistance(const std::shared_ptr<Tile> tile1, const std::shared_ptr<Tile> tile2) const;
 	
 	std::vector< std::vector<Node> > nodeMap; /**< Represented map of nodes by vector of vectors. (2D vector)*/
 	std::vector< std::pair<double, double> > shortestPath; /**< Path represented by vector of two coordinates <b>x</b> and <b>y</b>.*/
};

#endif /* __path_finder_h__ */
