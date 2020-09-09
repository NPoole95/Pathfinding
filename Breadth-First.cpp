// Breadth-First.cpp
// ======^^^^^^====
//
// Implementation of Search class for Breadth-First algorithm
//

#pragma once
#include "Breadth-First.h" // Declaration of this class

// This function takes ownership of the start and goal pointers that are passed in from the calling code.
// Ownership is not returned at the end, so the start and goal nodes are consumed.
// The Path is returned through the reference parameter.

bool CBreadthFirst::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, int mapYSize, int mapXSize, I3DEngine* myEngine, vector<vector<IModel*>> myMapDisplay)
{
	bool goalStateFound = false;
	bool onOpenList = false;
	deque <unique_ptr < SNode > > openList;
	deque <unique_ptr < SNode > > closedList;
	unique_ptr <SNode> temp(new SNode);
	unique_ptr <SNode> current;

	unique_ptr<SNode> startXY(new SNode);
	startXY->x = start->x;
	startXY->y = start->y;

	if (terrain[start->x][start->y] != 0)
	{
		openList.push_back(move(start));
	}
	else
	{
		cout << "Starting location is inacessible, please try new coordinates" << endl;
	}

	while (!openList.empty() || goalStateFound == true)
	{
		current = move(openList.front()); // sets current to the first item on the open list
		openList.pop_front();
		if (current->x == goal->x && current->y == goal->y)
		{
			goalStateFound = true;
			path = printPath(startXY, current);
			return true;
		}

		///// Checks the square above
		if (current->y < mapYSize - 1) // stops the algorithm checking a square beyond the top of the map
		{
			temp->x = current->x;
			temp->y = current->y + 1;
			temp->score = terrain[temp->x][temp->y];

			if (temp->score != 0)
			{
				onOpenList = checkLists(openList, closedList, temp);

				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
			}
			temp.reset(new SNode);
		}

		///////// Checks the square to the right
		if (current->x < mapXSize - 1)  // stops the algorithm checking a square beyond the right of the map
		{
			temp->x = current->x + 1;
			temp->y = current->y;
			temp->score = terrain[temp->x][temp->y];

			if (temp->score != 0)
			{
				onOpenList = checkLists(openList, closedList, temp);
				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
			}
			temp.reset(new SNode);
		}

		///////// Checks the square below
		if (current->y > 0)  // stops the algorithm checking a square below the bottom of the map
		{
			temp->x = current->x;
			temp->y = current->y - 1;
			temp->score = terrain[temp->x][temp->y];

			if (temp->score != 0)
			{
				onOpenList = checkLists(openList, closedList, temp);
				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
			}
			temp.reset(new SNode);
		}

		/////// Checks the square to the left
		if (current->x > 0)  // stops the algorithm checking a square to the left of the map
		{
			temp->x = current->x - 1;
			temp->y = current->y;
			temp->score = terrain[current->x - 1][current->y];

			if (temp->score != 0)
			{
				onOpenList = checkLists(openList, closedList, temp);
				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
			}
			temp.reset(new SNode);
		}

		printSearch(openList, closedList, current);

		closedList.push_back(move(current));
		current.reset(new SNode);

		updateScene(openList, closedList, myMapDisplay);

		myEngine->DrawScene();

		for (float i = 0; i < 1.0f; i += frameTime)
		{
			// wait for 1 second
			frameTime = myEngine->Timer();
		}

	}
	if (goalStateFound == false && openList.empty())
	{
		cout << "No Path could be found." << endl;
	}
	return false;
}