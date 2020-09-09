// AStar.h
// ======^^^^^^==
//
// Declaration of Search class for AStar algorithm
//

#pragma once

#include "Definitions.h"  // Type definitions
#include "Search.h"       // Base (=interface) class definition

#include <TL-Engine.h>
using namespace tle;

// AStar search class definition

/* TODO - Replace this class with classes to implement real search algorithms*/

// Inherit from interface and provide implementation for 0* algorithm
class CAStar : public ISearch
{
	// I have not implemented any constructors or destructors.
	// Whether you need some is up to how you choose to do your implementation.

	// Constructs the path from start to goal for the given terrain
	bool FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, int mapYSize, int mapXSize, I3DEngine* myEngine, vector<vector<IModel*>> myMapDisplay);
};