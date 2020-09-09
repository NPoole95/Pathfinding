// Pathfinding 3D.cpp: A program using the TL-Engine

#pragma once
//#include "stdafx.h"
#include "Search.h" 
#include "SearchFactory.h" 
#include "Definitions.h" 

//#include <algorithm> 
#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;



void main()
{
	
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "D:\\ProgramData\\TL-Engine\\Media" );

	/**** Set up your scene here ****/

	ICamera* myCamera;															// Creates the camera
	myCamera = myEngine->CreateCamera(kManual);
	myCamera->Move(100, 300, 100);												// moves the camera back into third person view
	myCamera->RotateX(90);														// rotates the gamera 20 degrees to look down


	IMesh* floorMesh = myEngine->LoadMesh("floor.x");//Mesh to set up the ground
	IModel* floor = floorMesh->CreateModel(0.0f, 0.0f, 0.0f);//Creates the floor model
	IMesh* cubeMesh = myEngine->LoadMesh("cube.x");

	const float kCubeYPosition = 0.5f;  // The y value in the world for every cube, making them generate on the same level


	IMesh* shipMesh = myEngine->LoadMesh("Sphere.x");//Mesh to set up the ground
	IModel* ship = shipMesh->CreateModel(0.0f, -5.0f, 0.0f);//Creates the floor model
	
	///// Runs the console application to load files //////////////////////////

	int startEnd[coordTotal]; // array storing all 4 start/goal coords (startX 0, startY 1, goalX 2, goalY 3)

	float hoverHeight = 15.0f;  // The height of the marbel that follows the path
	float timer = 5.0f;         // timer used to stop the marbel getting stuck on a single node
	int mapXSize = 0;			// width of the map	
	int mapYSize = 0;			// height of the map
	string filePrefix = " ";	// the first leter of both map.txt and coords.txt

	

	unique_ptr<SNode> start(new SNode); // starting point of the path
	unique_ptr<SNode> goal(new SNode);  // goal of the path

	startEnd[coordTotal] = readCoords(coordTotal, startEnd, filePrefix);
	start->x = startEnd[0];
	start->y = startEnd[1];
	goal->x = startEnd[2];
	goal->y = startEnd[3];

	TerrainMap myMap;
	myMap = readMapTwo(myMap, mapXSize, mapYSize, filePrefix);
	

	vector<vector<IModel*>> myMapDisplay;
	vector<IModel*>xModelLine;

	for (int x = mapXSize - 1; x >= 0; x--)
	{
		for (int z = 0; z < mapYSize; z++)
		{
			xModelLine.push_back(cubeMesh->CreateModel(x * 15.0f, kCubeYPosition, z * 15.0f));
		}
		myMapDisplay.insert(myMapDisplay.begin(), xModelLine);
		xModelLine.clear();
	}

	/////////////////////////////////////////////////////////////////////////////
	//int currentCube = 0;

	// The following for loop goes through every cube generated for each node and skins them according to their cost
	for (int y = 0; y < mapYSize; y++)
	{
		for (int x = 0; x < mapXSize; x++)
		{
			ETerrainCost cubeSkin = myMap[x][y];
			if (cubeSkin == Clear)
			{
				myMapDisplay[x][y]->SetSkin("green.png");
			}
			else if (cubeSkin == Water)
			{
				myMapDisplay[x][y]->SetSkin("blue.png");
			}
			else if (cubeSkin == Wood)
			{
				myMapDisplay[x][y]->SetSkin("trees_vetka_green_3v.png");
			}
			else if (cubeSkin == Wall)
			{
				myMapDisplay[x][y]->SetSkin("brick1.jpg");
			}
			if (x == startEnd[0] && y == startEnd[1])
			{
				myMapDisplay[x][y]->SetSkin("tiles_bright.jpg");
			}
			if (x == startEnd[2] && y == startEnd[3])
			{
				myMapDisplay[x][y]->SetSkin("tiles_green.jpg");
			}
		}
	}
	char algorithmChoice = mapName();
	ESearchType algorithm;

	if (algorithmChoice == 'a')
	{
		algorithm = AStar;
	}
	else if (algorithmChoice == 'b')
	{
		algorithm = BreadthFirst;
	}
	

	ISearch* PathFinder = NewSearch(algorithm);
	NodeList path;

	myEngine->Timer();

	PathFinder->FindPath(myMap, move(start), move(goal), path, mapYSize, mapXSize, myEngine, myMapDisplay);
	colourPath(path, myMapDisplay);

	savePathToFile(path, counter);

	deque <unique_ptr <SNode> >::iterator followPath = path.begin() + 1;
	if (path.size() != 0)
	{
		ship->Move(path[0]->x * 15, hoverHeight, path[0]->y * 15);
	}
	
	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		float shipSpeed = 0.02f;


		if (followPath != path.end() && path.size() != 0)
		{
			/*if ((static_cast<int>(ship->GetX() + 1) == ((*followPath)->x * 15)))
			{
				ship->SetX(static_cast<int>(ship->GetX() + 1));
			}*/


			if ((static_cast<int>(ship->GetX()) == ((*followPath)->x * 15)) && (static_cast<int>(ship->GetZ()) == ((*followPath)->y * 15)) && (followPath + 1) != path.end())
			{
				if (timer <= 0)
				{
					followPath++;
					timer = 5.0f;
				}
			}

			ship->LookAt((*followPath)->x * 15, hoverHeight, (*followPath)->y * 15);
			ship->MoveLocalZ(shipSpeed / 2);
		}

		timer -= 0.01f;


		/**** Update your scene each frame here ****/

		if (myEngine->KeyHeld(Key_W))
		{
			//myCamera->MoveZ(0.05f);
			myCamera->RotateX(0.1);
		}
		if (myEngine->KeyHeld(Key_S))
		{
			//myCamera->MoveZ(-0.05f);
			myCamera->RotateX(-0.1);
		}
		if (myEngine->KeyHeld(Key_A))
		{
			//myCamera->MoveX(-0.05f);
			myCamera->RotateX(-0.1);
		}
		if (myEngine->KeyHeld(Key_D))
		{
			myCamera->MoveX(0.05f);
		}
		if (myEngine->KeyHeld(Key_LControl))
		{
			myCamera->MoveY(-0.05f);
		}
		if (myEngine->KeyHeld(Key_LShift))
		{
			myCamera->MoveY(0.05f);
		}
		//myCamera->RotateY(myEngine->GetMouseMovementX()/20);  // rotates the camera according to mouse movement
		//myCamera->RotateX(myEngine->GetMouseMovementY() / 20);
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}


