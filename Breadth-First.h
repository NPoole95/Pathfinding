//Breadth-First.h
// ======^^^^^^==
//
// Declaration of Search class for Breadth-First algorithm
//

#pragma once

#include "Definitions.h"  // Type definitions
#include "Search.h"       // Base (=interface) class definition

// Breadth-First search class definition
//bool checkOpenList(deque<unique_ptr<SNode>>& myList, unique_ptr <SNode>& findMe);
//void printSearch(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr <SNode>& current);

class CBreadthFirst : public ISearch
{
	// I have not implemented any constructors or destructors.
	// Whether you need some is up to how you choose to do your implementation.

	// Constructs the path from start to goal for the given terrain
	bool FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, int mapYSize, int mapXSize, I3DEngine* myEngine, vector<vector<IModel*>> myMapDisplay);

};

//bool checkOpenList(deque<unique_ptr<SNode>>& myList, unique_ptr <SNode>& findMe)
//{
//	deque <unique_ptr <SNode> >::iterator p;
//
//	for (p = myList.begin(); p != myList.end(); p++)
//	{
//		if ((*p)->x == findMe->x && (*p)->y == findMe->y)
//		{
//			return true;
//		}
//	}
//	return false;
//}

//void printSearch(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr <SNode>& current)
//{
//	deque <unique_ptr <SNode> >::iterator p;
//
//	cout << "current: " << current->x << " " << current->y << endl;
//
//	cout << "Open List:" << endl;
//	for (p = openList.begin(); p != openList.end(); p++)
//	{
//		cout << (*p)->x << " " << (*p)->y << endl;
//	}
//	cout << endl;
//
//	cout << "Closed List:" << endl;
//	for (p = closedList.begin(); p != closedList.end(); p++)
//	{
//		cout << (*p)->x << " " << (*p)->y << endl;
//	}
//	cout << endl;
//}