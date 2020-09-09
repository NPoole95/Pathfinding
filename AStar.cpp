// AStar.cpp
// ======^^^^^^====
//
// Implementation of Search class for Breadth-First algorithm
//

#pragma once
#include "AStar.h" // Declaration of this class

// This function takes ownership of the start and goal pointers that are passed in from the calling code.
// Ownership is not returned at the end, so the start and goal nodes are consumed.
// The Path is returned through the reference parameter.

int manhattanDistance(int currentX, int currentY, int startX, int startY);
void changeParent(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr<SNode>* current);
bool compare(const unique_ptr<SNode>& a, const  unique_ptr<SNode>& b);

bool CAStar::FindPath(TerrainMap& terrain, unique_ptr<SNode> start, unique_ptr<SNode> goal, NodeList& path, int mapYSize,int mapXSize, I3DEngine* myEngine, vector<vector<IModel*>> myMapDisplay)
{
	bool goalStateFound = false;
	bool onOpenList = false;
	bool lowerFvalue = false;

	deque <unique_ptr < SNode > > openList;
	deque <unique_ptr < SNode > > closedList;
	unique_ptr <SNode> temp(new SNode);
	unique_ptr <SNode> current(new SNode);

	unique_ptr<SNode> startXY(new SNode);
	startXY->x = start->x;
	startXY->y = start->y;

	start->score = 0;
	start->g = 0;
	start->h = manhattanDistance(start->x, start->y, goal->x, goal->y);
	start->f = start->g + start->h;
	start->parent = nullptr;
	if (terrain[start->x][start->y] != 0)
	{
		openList.push_back(move(start));
	}
	else
	{
		cout << "Starting location is inacessible, please try new coordinates" << endl;
	}

	int count = openList.size();


	while (!openList.empty() || goalStateFound == true)
	{
		frameTime = myEngine->Timer();

		sort(openList.begin(), openList.end(), compare);
		sortCounter(counter); 

		current = move(openList.front()); // sets current to the first item on the open list
		openList.pop_front();

		if (current->x == goal->x && current->y == goal->y)
		{
			goalStateFound = true;
			path = printPath(startXY, current);
			return true;
		}

		///// checks the square above
		if (current->y < mapYSize - 1)
		{
			temp->x = current->x;
			temp->y = current->y + 1;
			temp->score = terrain[temp->x][temp->y];
			temp->g = (current->g + temp->score);
			temp->h = manhattanDistance(temp->x, temp->y, goal->x, goal->y);
			temp->f = temp->g + temp->h;

			if (temp->score != 0) // stops the algorithm checking a square beyond the top of the map
			{
				//
				//
				//

				/*if (temp->x == goal->x && temp->y == goal->y)
				{
					goalStateFound = true;
					temp->parent = current.get();
					printPath(startXY, temp);
					openList.push_back(move(temp));
					return true;
				}*/

				onOpenList = checkLists(openList, closedList, temp);
				lowerFvalue = checkListsFValue(openList, closedList, temp);

				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
				else if (onOpenList == true && lowerFvalue == true)
				{
					//temp->parent = current.get();
					changeParent(openList, closedList, &temp);
					openList.push_back(move(temp));
				}
				//
			}
			temp.reset(new SNode);
		}
		///////// Checks the square to the right
		if (current->x < mapXSize + 1)
		{

			temp->x = current->x + 1;
			temp->y = current->y;
			temp->score = terrain[temp->x][temp->y];
			temp->g = (current->g + temp->score);
			temp->h = manhattanDistance(temp->x, temp->y, goal->x, goal->y);
			temp->f = temp->g + temp->h;

			if (temp->score != 0)  // stops the algorithm checking a square beyond the right of the map
			{
				//
				//
				//
				//
				//

				/*if (temp->x == goal->x && temp->y == goal->y)
				{
					goalStateFound = true;
					temp->parent = current.get();
					printPath(startXY, temp);
					openList.push_back(move(temp));
					return true;
				}*/

				onOpenList = checkLists(openList, closedList, temp);
				lowerFvalue = checkListsFValue(openList, closedList, temp);

				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
				else if (onOpenList == true && lowerFvalue == true)
				{
					//temp->parent = current.get();
					changeParent(openList, closedList, &temp);
					openList.push_back(move(temp));
				}
				//
			}
			temp.reset(new SNode);
		}

		///////// Checks the square below
		if (current->y > 0)
		{
			temp->x = current->x;
			temp->y = current->y - 1;
			temp->score = terrain[temp->x][temp->y];
			temp->g = (current->g + temp->score);
			temp->h = manhattanDistance(temp->x, temp->y, goal->x, goal->y);
			temp->f = temp->g + temp->h;

			if (temp->score != 0)  // stops the algorithm checking a square below the bottom of the map
			{
				//
				//
				//
				//

				/*if (temp->x == goal->x && temp->y == goal->y)
				{
					goalStateFound = true;
					temp->parent = current.get();
					printPath(startXY, temp);
					openList.push_back(move(temp));
					return true;
				}*/
				
				onOpenList = checkLists(openList, closedList, temp);
				lowerFvalue = checkListsFValue(openList, closedList, temp);

				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
				else if (onOpenList == true && lowerFvalue == true)
				{
					//temp->parent = current.get();
					changeParent(openList, closedList, &temp);
					openList.push_back(move(temp));
				}
			}
			temp.reset(new SNode);
		}

		/////// Checks the square to the left
		if (current->x > 0)
		{
			temp->x = current->x - 1;
			temp->y = current->y;
			temp->score = terrain[current->x - 1][current->y];
			temp->g = (current->g + temp->score);
			temp->h = manhattanDistance(temp->x, temp->y, goal->x, goal->y);
			temp->f = temp->g + temp->h;

			if (temp->score != 0)  // stops the algorithm checking a square to the left of the map
			{

				//
				//
				//

			/*	if (temp->x == goal->x && temp->y == goal->y)
				{
					goalStateFound = true;
					temp->parent = current.get();
					printPath(startXY, temp);
					openList.push_back(move(temp));
					return true;
				}*/

				onOpenList = checkLists(openList, closedList, temp);
				lowerFvalue = checkListsFValue(openList, closedList, temp);

				if (onOpenList == false)
				{
					//*temp->parent = (*current);
					temp->parent = current.get();
					openList.push_back(move(temp));
				}
				else if (onOpenList == true && lowerFvalue == true)
				{
					//temp->parent = current.get();
					changeParent(openList, closedList, &temp);
					openList.push_back(move(temp));
				}
				//
			}
			temp.reset(new SNode);
		}

		printSearch(openList, closedList, current);

		closedList.push_back(move(current));
	
		updateScene(openList, closedList, myMapDisplay);

		myEngine->DrawScene();

		for (float i = 0; i < 0.5f; i += frameTime)
		{
			// wait for 1 second
			frameTime = myEngine->Timer();
		}

		current.reset(new SNode);

		if (goalStateFound == false && openList.empty())
		{
			cout << "No Path could be found." << endl;
		}
	}
	return false;
}
