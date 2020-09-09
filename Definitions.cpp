#pragma once
#include "Definitions.h"
#include "SearchFactory.h"
#include <iostream>

int counter;
float frameTime;

string loadFile(string filePrefix)
{
	cout << "Please enter the file prefix" << endl;			// asks user for a file name
	cin >> filePrefix;										// reads in a users entry to a variable

	return filePrefix;									    // returns this name
}





char mapName()
{
	bool choiceMade = false;
	char searchchoice;

	cout << "Please enter the first letter of the algorithm you would like to use" <<
		endl << "A : AStar" << endl << "B : Breadth First" << endl;

	cin >> searchchoice;

	while (choiceMade != true)
	{
		if (searchchoice == 'a')
		{
			choiceMade = true;
			return 'a';
		}
		else if (searchchoice == 'b')
		{
			choiceMade = true;
			return 'b';
		}
		else
		{
			cout << "Your selection was not valid, please only enter a single character." << endl;
			cin >> searchchoice;
		}
	}
}

int readCoords(int coordTotal, int startEnd[], string &filePrefix)
{
	bool fileOpened = false;

	string fileName;
	filePrefix = loadFile(filePrefix);
	fileName = filePrefix + "Coords.txt";
	
	ifstream fileInput;
	fileInput.open(fileName); // opens the input file
	int half = 2;

	while (fileOpened == false) // this while loop will catch invalid inputs and uintil a user enters a prefix that will load a header file it will keep requesting one
	{
		if (fileInput.is_open()) // Checks to see that the file has been opened sucessfully
		{
			fileOpened = true;
			for (int i = 0; i < coordTotal; i++)
			{
				fileInput >> startEnd[i];
			}
		}
		else
		{

			cout << "Could not open file, please try again by entering a single letter prefix:" << endl;

			filePrefix = loadFile(filePrefix);
			fileName = filePrefix + "Coords.txt";

			//ifstream fileInput;
			fileInput.open(fileName); // opens the input file

		}
	}
	

#if _DEBUG
	for (int i = 0; i < coordTotal / half; i++) // outputs the start X and Y coordinates
	{
		cout << startEnd[i] << " ";
	}
	cout << endl;

	for (int i = half; i < coordTotal; i++)  // outputs the goal X and Y coordinates
	{
		cout << startEnd[i] << " ";
	}
	cout << endl;
#endif // DEBUG

	return startEnd[coordTotal];
}

void savePathToFile(NodeList &path, int counter)
{
	string outputFileName = "output.txt";
	ofstream fileOutput(outputFileName);

	deque <unique_ptr <SNode> >::iterator p;

	for (p = path.begin(); p != path.end(); p++)
	{
		fileOutput << (*p)->x << " " << (*p)->y << endl;
	}

	if (path.empty())
	{
		fileOutput << "No Path could be generated" << endl;
	}

	if (counter != 0)
	{
		fileOutput << "Number of sorts used: " << counter << endl;
	}

}
// turned off precompiled headers to solve error 

TerrainMap readMapTwo(TerrainMap myMap, int &mapXSize, int &mapYSize, string &filePrefix)
{
	int num; //integer used to read in numbers from the file

	ifstream fileInput;
	string fileName = filePrefix + "Map.txt";
	fileInput.open(fileName); // opens the input file

	ETerrainCost terrainCost;
	vector<ETerrainCost> xCoordLine; // one dimentional vector of nodes, the be pushed onto the 2d vector to create the map

	if (fileInput.is_open()) // Checks to see that the file has been opened sucessfully
	{

		fileInput >> mapXSize; // reads in the first number in the map file, the maps X size
		fileInput >> mapYSize; // reads in the second number in the map file, the maps Y size

		
		for (int y = mapYSize - 1 ; y >= 0; y--) // runs the Y coordinates backwards, altered to match array syntax 
		{
			for (int x = 0; x < mapXSize; x++) // cycles through the X coordinates
			{
				num = fileInput.get();  // Reads in the next digit in the file

				if (!isdigit(num)) // checks if the digit read in is not a number (eg a space)
				{
					num = fileInput.get(); // if so, reads in again, skipping the space
				}
				if (num - '0' == 0) // - '0' converts from ascii value to base 10 value 
				{					// the following 4 else if's check the value that is read in and selects the appropriate enum value
					terrainCost = Wall;  
				}
				else if (num - '0' == 1)
				{
					terrainCost = Clear;
				}
				else if (num - '0' == 2)
				{
					terrainCost = Wood;
				}
				else if (num - '0' == 3)
				{
					terrainCost = Water;
				}

				xCoordLine.push_back(terrainCost); // push each individual coordinate for 1 line of the y axis onto the inner vector
			}
			// push this line onto the stack of the outer vector
			myMap.insert(myMap.begin(), xCoordLine);
			xCoordLine.clear(); // clears the inner vector so it can be reused in the next iteration of the loop
		}
		myMap = transposeMap(myMap, mapXSize, mapYSize); // runs a function that transposes the map, so that [0][0] in the vector alignes with [0][0] on the map coords
	}

#if _DEBUG // This loop outputs the map to the console when in debug mode, allowing the programmer to check it has been read in and manipulated correctly
	for (int y = mapYSize - 1; y >= 0; y--)
	{
		for (int x = 0; x < mapXSize; x++)
		{
			cout << myMap[x][y] << " ";

		}
		cout << endl;
	}
#endif

	return myMap;
}

TerrainMap transposeMap(TerrainMap myMap, int mapXSize, int mapYSize) // function used to correct the positions of the coordinates in the 2d vector. (meaning position 0,0 of the map is in position 0,0 in the vector)
{
	TerrainMap manipulationMap;
	ETerrainCost terrainCost;
	vector<ETerrainCost> xCoordLine;
		
	for (int x = mapXSize -1; x >= 0; x--) // This for loop cycles through the map and transposes it, so that [0][0] in the vector alignes with [0][0] on the map coords
	{
		for (int y = 0; y < mapYSize; y++)
		{	
			xCoordLine.push_back(myMap[y][x]);		
		}
		manipulationMap.insert(manipulationMap.begin(), xCoordLine);
		xCoordLine.clear();
	}
	return manipulationMap;
}

bool checkLists(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr <SNode>& findMe)
{

	deque <unique_ptr <SNode> >::iterator p;

	for (p = openList.begin(); p != openList.end(); p++)
	{
		if ((*p)->x == findMe->x && (*p)->y == findMe->y)
		{
			return true;
		}
	}
	for (p = closedList.begin(); p != closedList.end(); p++)
	{
		if ((*p)->x == findMe->x && (*p)->y == findMe->y)
		{
			return true;
		}
	}
	return false;
}

bool checkListsFValue(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr <SNode>& findMe)
{

	deque <unique_ptr <SNode> >::iterator p;

	for (p = openList.begin(); p != openList.end(); p++)
	{
		if ((*p)->x == findMe->x && (*p)->y == findMe->y &&  findMe->f < (*p)->f) // returns if the node already on the open list has a HIGHER f value
		{
			return true;
		}
	}
	for (p = closedList.begin(); p != closedList.end(); p++)
	{
		// returns if the node already on the closed list has a HIGHER f value
		if ((*p)->x == findMe->x && (*p)->y == findMe->y && findMe->f < (*p)->f)
		{
			return true;
		}
	}
	return false;
}

void printSearch(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr<SNode> &current)
{
	deque <unique_ptr <SNode> >::iterator p;

	cout << "current: " << current->x << " " << current->y << endl;
}

NodeList printPath(unique_ptr<SNode>& start, unique_ptr<SNode>& pathNode)
{
	bool foundStart = false;
	deque<unique_ptr<SNode>> path;
	unique_ptr <SNode> temp(new SNode);
	unique_ptr <SNode> tempTwo(new SNode);

	cout << "Path:" << endl;

	temp = move(pathNode);

	do {
		if (temp->parent == nullptr)
		{
			foundStart = true;
		}
		else
		{
			tempTwo->x = temp->x;
			tempTwo->y = temp->y;
			tempTwo->parent = temp->parent;

			path.push_front(move(tempTwo));

			temp->x = temp->parent->x;
			temp->y = temp->parent->y;
			temp->parent = temp->parent->parent;

			tempTwo = unique_ptr<SNode>(new SNode);
		}
	} while (!foundStart);

	path.push_front(move(start));

	NodeList::iterator p;
	for (p = path.begin(); p != path.end(); p++)
	{
		cout << (*p)->x << " " << (*p)->y << endl;
	}
	cout << endl;

	return path;

}


int manhattanDistance(int currentX, int currentY, int startX, int startY)
{
	int manhattanDistance = abs(startX - currentX) + abs(startY - currentY);

	return manhattanDistance;
}


void changeParent(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, unique_ptr<SNode>* current)
{
	deque <unique_ptr <SNode> >::iterator p;

	for (p = openList.begin(); p != openList.end(); p++)
	{
		if ((*p)->x == (*current)->x && (*p)->y == (*current)->y)
		{
			(*current)->parent = (*p)->parent;
		}
	}
	for (p = closedList.begin(); p != closedList.end(); p++)
	{
		if ((*p)->x == (*current)->x && (*p)->y == (*current)->y)
		{
			(*current)->parent = (*p)->parent;
		}
	}
}

bool compare(const unique_ptr<SNode>& a, const  unique_ptr<SNode>& b)
{
	return ((*a).f < (*b).f);
}

int sortCounter(int &counter)
{
	counter++;
	return counter;
}

void updateScene(deque<unique_ptr<SNode>>& openList, deque<unique_ptr<SNode>>& closedList, vector<vector<IModel*>> myMapDisplay)
{

	deque <unique_ptr <SNode> >::iterator p;

	for (p = closedList.begin(); p != closedList.end(); p++)
	{
		myMapDisplay[(*p)->x][(*p)->y]->SetSkin("c.jpg");
	}

	for (p = openList.begin(); p != openList.end(); p++)
	{
		myMapDisplay[(*p)->x][(*p)->y]->SetSkin("o.jpg");
	}
}

void colourPath(deque<unique_ptr<SNode>>& path, /* IModel* cube[kNumXCoords][kNumYCoords] */ vector<vector<IModel*>> myMapDisplay)
{
	deque <unique_ptr <SNode> >::iterator p;

	for (p = path.begin(); p != path.end(); p++)
	{
		myMapDisplay[(*p)->x][(*p)->y]->SetSkin("path.jpg");
	}
}