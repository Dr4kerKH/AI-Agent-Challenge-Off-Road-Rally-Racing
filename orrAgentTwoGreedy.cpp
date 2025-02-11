// CS 4318, spring 2023
// Agent Challenge 3: Off-road rally
//
// Here's an example agent function.  You can do much better than this.

#include "orr.h"

vector<drivingDirection> orrAgentTwoGreedy(TerrainMap &tm)
{
   // Take the fastest single move, then look for the finish in one more move from there.
   drivingDirection bestMove, moveToTry;
   int bestTime, next;
   vector<drivingDirection> route;

   const int start = tm.getStartHex();
   const int finish = tm.getFinishHex();

   route.clear();
   bestMove = driveE;
   bestTime = INT_MAX;
   // Consider each possible move one by one.
   for (moveToTry = driveW;
        moveToTry <= driveE;
        moveToTry = static_cast<drivingDirection>(moveToTry + 1))
   {
      next = tm.getNeighborHex(start, moveToTry);
      if (next == finish)
      {
         // If it reaches the finish, add it to the route and return it.
         route.push_back(moveToTry);
         return route;
      }
      else if (tm.getMoveTime(start, moveToTry) < bestTime)
      {
         // Remember the fastest move available.
         bestMove = moveToTry;
         bestTime = tm.getMoveTime(start, moveToTry);
      }
   }
   // Add the fastest move available to the route.
   route.push_back(bestMove);
   next = tm.getNeighborHex(start, bestMove);
   // Consider each possible next move.
   for (moveToTry = driveW;
        moveToTry <= driveE;
        moveToTry = static_cast<drivingDirection>(moveToTry + 1))
   {
      if (tm.getNeighborHex(next, moveToTry) == finish)
      {
         // If it reaches the finish, add it to the route and return it.
         route.push_back(moveToTry);
         return route;
      }
   }
   return route;
}
