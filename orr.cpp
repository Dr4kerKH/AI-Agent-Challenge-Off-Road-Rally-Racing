// CS 4318, spring 2023
// Agent Challenge 3: Off-road rally
//
// Here are the functions available to each agent.

#include "orr.h"

Terrain::Terrain(int size)
{
   // Create a new random terrain to race over.
   int hex, r;
   if (size < 2)
   {
      size = 9;
   }
   this->size = size;
   roughness = vector<int>(size * size);
   for (hex = 0; hex < size * size; hex += 1)
   {
      r = 1;
      while (randomInt(3) > 0)
      {
         r = r % 9 + 1;
      }
      if (randomInt(3) == 0)
      {
         r = 10 - r;
      }
      roughness.at(hex) = r;
   }
   startHex = randomInt(size * size);
   roughness.at(startHex) = 1;
   do
   {
      finishHex = randomInt(size * size);
   }
   while (startHex == finishHex);
   roughness.at(finishHex) = 1;
}

bool Terrain::doesRouteFinish(const vector<drivingDirection> &route) const
{
   // Return true if and only if the given route moves into the finish hex.
   int currentHex, whichMove;
   currentHex = startHex;
   for (whichMove = 0; whichMove < static_cast<int>(route.size()); whichMove += 1)
   {
      currentHex = getNeighborHex(currentHex, route.at(whichMove));
      if (currentHex == finishHex)
      {
         return true;
      }
   }
   return false;
}

int Terrain::getMoveTime(int fromHex, drivingDirection move) const
{
   // Return the driving time of one specific move.
   const int toHex = getNeighborHex(fromHex, move);
   return roughness.at(fromHex) + roughness.at(toHex);
}

int Terrain::getNeighborHex(int fromHex, drivingDirection move) const
{
   // Return the hex reached by driving from fromHex in the given direction.
   int column, row;
   column = fromHex / size;
   row = fromHex % size;
   switch (move)
   {
   case driveW:
      column -= 1;
      return column >= 0 ? size * column + row : fromHex;
   case driveK:
      column -= 1;
      row += 1;
      return column >= 0 && row < size ? size * column + row : fromHex;
   case driveS:
      row -= 1;
      return row >= 0 ? size * column + row : fromHex;
   case driveN:
      row += 1;
      return row < size ? size * column + row : fromHex;
   case driveX:
      column += 1;
      row -= 1;
      return column < size && row >= 0 ? size * column + row : fromHex;
   case driveE:
      column += 1;
      return column < size ? size * column + row : fromHex;
   }
   return fromHex;
}

int Terrain::getRouteTime(const vector<drivingDirection> &route) const
{
   // Return the total driving time that the given route takes.
   int currentHex, totalTime, whichMove;
   currentHex = startHex;
   totalTime = 0;
   for (whichMove = 0; whichMove < static_cast<int>(route.size()); whichMove += 1)
   {
      totalTime += getMoveTime(currentHex, route.at(whichMove));
      currentHex = getNeighborHex(currentHex, route.at(whichMove));
   }
   return totalTime;
}

void Terrain::printTerrain() const
{
   // Print out the whole terrain in a diamond shape.
   int column, row;
   for (row = size - 1; row >= 0; row -= 1)
   {
      cout << setw(row) << "";
      for (column = 0; column < size; column += 1)
      {
         const int hex = size * column + row;
         if (hex == startHex)
         {
            cout << setw(2) << right << '*';
         }
         else if (hex == finishHex)
         {
            cout << setw(2) << right << '@';
         }
         else
         {
            cout << setw(2) << right << roughness.at(hex);
         }
      }
      cout << "\n";
   }
}

int Terrain::randomInt(int n)
{
   // Return a random nonnegative integer less than n.
   int r;
   if (n <= 0)
   {
      return 0;
   }
   do
   {
      r = random();
   }
   while (r >= INT_MAX / n * n);
   return r / (INT_MAX / n);
}

TerrainMap::TerrainMap(Terrain *terrain)
{
   // Create a map based on the given terrain.
   this->terrain = terrain;
   numLooksAtMap = 0;
}

int TerrainMap::getMoveTime(int fromHex, drivingDirection move)
{
   // Look up the driving time of one potential move.
   numLooksAtMap += 1;
   return terrain->getMoveTime(fromHex, move);
}

int TerrainMap::getNeighborHex(int fromHex, drivingDirection move) const
{
   // Look up the hex reached by driving from fromHex in the given direction.
   return terrain->getNeighborHex(fromHex, move);
}
