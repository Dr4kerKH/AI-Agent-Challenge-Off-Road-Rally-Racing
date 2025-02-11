// CS 4318, spring 2023
// Agent Challenge 3: Off-road rally
//
// Here are the #includes and definitions available to each agent.

#ifndef ORR_H
#define ORR_H

#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

// The six allowed driving directions for moves: west, northwest, south,
// north, southeast, east.
enum drivingDirection {driveW, driveK, driveS, driveN, driveX, driveE};

// The underlying terrain for agents to race over.
class Terrain
{
private:
   int finishHex; // Hex that agents must reach.
   vector<int> roughness; // Difficulty of driving across each hex.
   int size; // How many hexes tall and wide.
   int startHex; // Hex that agents start at.
   static int randomInt(int n);
public:
   Terrain(int size = 9);
   bool doesRouteFinish(const vector<drivingDirection> &route) const;
   int getFinishHex() const {return finishHex;}
   int getMoveTime(int fromHex, drivingDirection move) const;
   int getNeighborHex(int fromHex, drivingDirection move) const;
   int getRouteTime(const vector<drivingDirection> &route) const;
   int getSize() const {return size;}
   int getStartHex() const {return startHex;}
   void printTerrain() const;
};

// The aspects of the terrain that an agent can ask about.
class TerrainMap
{
private:
   int numLooksAtMap; // Number of times getMoveTime function has been called.
   Terrain *terrain; // Underlying terrain being raced over.
   TerrainMap(const TerrainMap &other);
   TerrainMap &operator=(const TerrainMap &other);
public:
   TerrainMap(Terrain *terrain);
   int getFinishHex() const {return terrain->getFinishHex();}
   int getMoveTime(int fromHex, drivingDirection move);
   int getNeighborHex(int fromHex, drivingDirection move) const;
   int getNumLooksAtMap() const {return numLooksAtMap;}
   int getSize() const {return terrain->getSize();}
   int getStartHex() const {return terrain->getStartHex();}
};

#endif // #ifndef ORR_H
