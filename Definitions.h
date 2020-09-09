// Definitions.h
// =============
//
// Type definitions to support path finding 
//

#pragma once

#include <vector>
#include <deque>
#include <memory>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

	
#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;

using namespace std;

// Represents a node in the search tree.
struct SNode
{
	int x;            // x coordinate
	int y;            // y coordinate
	int score;        // used in more complex algorithms
	int f;
	unsigned int g;
	int h;
	SNode* parent = 0; // note use of raw pointer here
};

// Lists of nodes (e.g Open, Closed and Paths) are implemented as double-ended queues
using NodeList = deque<unique_ptr<SNode>>;

// Terrain costs for map squares
enum ETerrainCost
{
	Clear = 1,
	Wood = 2,
	Water = 3,
	Wall = 0
};

// Maps of any size are implemented as 2D vectors
using TerrainMap = vector<vector<ETerrainCost>>;
//using mapDisplay = vector<vector<IModel*>>;



const int kTotalCoords = 100; // This needs to be changed from file input
const int kNumXCoords = 10;
const int kNumYCoords = 10;
extern int counter;
extern float frameTime;

const int coordTotal = 4; // x and y of both start and goal 
const int mapMaxSize = 10;
string loadFile(string filePrefix);
int readCoords(int coordTotal, int startEnd[], string &filePrefix);
char mapName();
void savePathToFile(NodeList &path, int counter);
TerrainMap readMapTwo(TerrainMap myMap, int &mapXSize, int &mapYSize, string &filePrefix);
TerrainMap transposeMap(TerrainMap myMap, int mapXSize, int mapYSize);
bool checkLists(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr <SNode>& findMe);
bool checkListsFValue(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr <SNode>& findMe);
void printSearch(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr<SNode> &current);
NodeList printPath(unique_ptr<SNode>& start, unique_ptr<SNode>& pathNode);
int sortCounter(int &counter);
void updateScene(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, vector<vector<IModel*>> myMapDisplay);
void colourPath(deque<unique_ptr<SNode>>& path, vector<vector<IModel*>> myMapDisplay);
