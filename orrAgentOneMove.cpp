// CS 4318, spring 2023
// Agent Challenge 3: Off-road rally
//
// Here's an example agent function.  You can do much better than this.

#include "orr.h"

vector<drivingDirection> orrAgentOneMove(TerrainMap &tm)
{
   // Try to get to the finish in just one move.
   drivingDirection moveToTry;
   vector<drivingDirection> route;

   const int start = tm.getStartHex();
   const int finish = tm.getFinishHex();

   route.clear();
   // Consider each possible move one by one.
   for (moveToTry = driveW;
        moveToTry <= driveE;
        moveToTry = static_cast<drivingDirection>(moveToTry + 1))
   {
      if (tm.getNeighborHex(start, moveToTry) == finish)
      {
         // If it reaches the finish, add it to the route and return it.
         route.push_back(moveToTry);
         return route;
      }
   }

   // If one move isn't enough to reach the finish, return an empty route.
   return route;
}
