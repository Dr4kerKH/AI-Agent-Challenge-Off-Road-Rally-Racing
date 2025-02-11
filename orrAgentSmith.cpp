// YOUR NAME: ___
//
// CS 4318, spring 2023
// Agent Challenge 3: Off-road rally
//
// Rename this file and the function below.  For example, if your agent name
// is Jones, rename this orrAgentSmith.cpp file to orrAgentJones.cpp and the
// orrAgentSmith function below to orrAgentJones.  Complete your agent
// function and turn it in on Blackboard.  Random-number generation is not
// allowed; your agent must be entirely deterministic.  Feel free to create
// other agents--each in a separate .cpp file--for yours to race against,
// but turn in only one.  Test your agent(s) with
//
//    nice bash orrBuild.bash
//
// and then
//
//    nice ./orrRunSim
//
// Each submitted agent will race on each of at least 100 terrains, with
// sizes ranging from 3x3 to 30x30, to determine the standings, which will
// be posted soon after the agents are due.

#include "orr.h"

namespace
{
   // If you need to define any new types or functions, put them here in
   // this unnamed namespace.  But no variables allowed!
}

// Rename and complete this agent function.
vector<drivingDirection> orrAgentSmith(TerrainMap &tm)
{
   // Your function must end up returning a vector of moves.
   // No random-number generation allowed!
   // tm.getSize() gives the size of the terrain: 6 for a 6x6 terrain, etc.
   // tm.getStartHex() gives the number of the start hex.
   // tm.getFinishHex() gives the number of the finish hex.
   // tm.getMoveTime(fromHex, move) gives the driving time of one move.
   // tm.getNeighborHex(fromHex, move) gives the hex got to by one move.

   vector<drivingDirection> route;
   route.clear();

   // Replace this return statement with your agent code.
   return route;
}

/*

 - First, carefully comment your code above to clarify how it works.
 - Here, describe your approach and analyze it.  How exactly did you develop
   and test it?  What are its strengths and weaknesses?  Why do you expect
   it to do well against the other submitted agents?
 - Also make a note here if you talked about the assignment with anyone or
   gave or received any kind of help.

*/
