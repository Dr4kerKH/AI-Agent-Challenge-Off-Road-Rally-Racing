// YOUR NAME: Sonpaorong Muchhim
//
// CS 4318, spring 2023
// Agent Challenge 3: Off-road rally

//  nice bash orrBuild.bash
//  nice ./orrRunSim

#include "orr.h"
namespace
{
// Struct current state
struct State {
    int hex;
    float cost;
	float heuristic; // Added heuristic value
    // Constructor
	State(int h, float c, float hValue) : hex(h), cost(c), heuristic(hValue) {}
    bool operator>(const State &G) const {return (cost + heuristic) > (G.cost + G.heuristic);} 
	// Rewrite the comparison for compare cost of trails
};
// Struct for data in Trail Vector
struct Triple {
    drivingDirection first; // Direction point from parent
    float second; // Cumulative Route Cost
	uint third; // Isolated Roughness of current position
    // Constructor
    Triple(drivingDirection f, float s, uint t) : first(f), second(s), third(t) {}
};
// Function for reverse vector
template <typename T>
void reverseVector(vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n / 2; ++i) {
        swap(v[i], v[n - i - 1]);
    }
}
// Function to edit Priority Queue Cost
void updatePQ (priority_queue<State, vector<State>, greater<State>> &status, float updateCost, const int pos) {
	priority_queue<State, vector<State>, greater<State>> update;
	while (!status.empty()) {
		update.push(State(status.top()));
		status.pop();
	}
	while (!update.empty()) {
		if (update.top().hex == pos){
			status.push(State(update.top().hex, updateCost, update.top().heuristic));
			update.pop();
		}
		else {
			status.push(State(update.top()));
			update.pop();
		}
	}
}
// Function to return OppositeDirection
drivingDirection getOppositeDirection(drivingDirection move) {
    switch (move) {
        case driveW: {return driveE;}
        case driveK: {return driveX;}
        case driveS: {return driveN;}
        case driveN: {return driveS;}
        case driveX: {return driveK;}
        case driveE: {return driveW;}
    }
	return move;
}

#include<cmath>
// Heuristic function for A*, Implementing Manhattan Distance
float calculateHeuristic(int currentHex, int finishHex, TerrainMap &tm, int size) {
    int currentRow = currentHex / size;
    int currentCol = currentHex % size;
    int finishRow = finishHex / size;
    int finishCol = finishHex % size;
	float distance = abs(currentRow - finishRow) + abs(currentCol - finishCol);
    return distance;
}
// Function to get roughness, from visited hex
uint getRoughnessHex(vector<Triple> &trail, int pos, int moveTime, const int start) {
	uint roughness;
	if (pos == start)
		roughness = moveTime - 1;
	else
		roughness = moveTime - trail[pos].third;
	return roughness;
}
}

vector<drivingDirection> orrAgentBraxton(TerrainMap &tm)
{
    // Setting up, start position, finish position, and size of terrain
	int start = tm.getStartHex();
    int finish = tm.getFinishHex();
    int size = tm.getSize();

    // Priority queue to store the states with cost, implementing Uniform Cost Search
    priority_queue<State, vector<State>, greater<State>> status;
    // Vector visited hex in map
	vector<bool> visited(size * size, false);
	// Vector trail storing (direction from parent, cumulative route cost, roughness)
    vector<Triple> trail(size * size, Triple(driveX, 0.0, 0));

	// Initializing the starting hex position for search
    status.push(State(start, 0, calculateHeuristic(start, finish, tm, size)));
    visited[start] = true;

    while (!status.empty()) {
        State currentState = status.top();
        status.pop();

        int currentPos = currentState.hex;
        float currentCost = currentState.cost;

        // Check if the finish hex is reached
        if (currentPos == finish) {
            
			// Reconstruct the path by treverse back the tracking trail
            vector<drivingDirection> path;
            int hex = finish;
            
			while (hex != start) {
                // Due trail stores the drive direction to come, add the opposition direction to hex
				path.push_back(trail[hex].first);
                hex = tm.getNeighborHex(hex, getOppositeDirection(path.back()));
            }
			// Due to path being store from finish to start, reverse Path for travel route
            reverseVector(path);
            return path;
        }

        // Explore neighbors from current position
        for (int dir = driveE; dir >= driveW; --dir) {
            
			drivingDirection move = static_cast<drivingDirection>(dir);
			int neighborHex = tm.getNeighborHex(currentPos, move);
			
			// Checking if the neighborHex is not already visited
            if (!visited[neighborHex]) {
				
				//if condition true, set neighborHex to visited
				visited[neighborHex] = true;
				int moveTime = tm.getMoveTime(currentPos, move); // moveTime function call
				
				// Get roughness through moveTime - currentPos roughness
				uint lvl_roughness = getRoughnessHex(trail, currentPos, moveTime, start);
				float heuristic = calculateHeuristic(neighborHex, finish, tm, size); // Calculate H(n)
                
				// Push route to PQ, and update data to trail
                status.push(State(neighborHex, currentCost + moveTime, heuristic));
				trail[neighborHex] = {move, currentCost + moveTime, lvl_roughness};
            }
			else { // if neighborHex already visited, check if current route is an improvement
				
				float previousCost = trail[neighborHex].second;
				uint nextRoughness = trail[neighborHex].third;
				uint currentRoughness = trail[currentPos].third;
				
				// if it's true, update PQ and update trail.
				if (currentCost + nextRoughness + currentRoughness < previousCost) {
					updatePQ(status, currentCost + nextRoughness + currentRoughness, neighborHex);
					trail[neighborHex] = {move, currentCost + nextRoughness + currentRoughness, nextRoughness};
				}
			}
        }
    }
    // If no path is found, return an empty vector
    return vector<drivingDirection>();
}

/*
Steps of building agent
**************************************************************************************************************
Version 1: BFS

Constructing the first agent and applying BFS goes according to plan, with the exception of the route's total cost.
**************************************************************************************************************
Version 2: UCS (optimization failed)

constructing a second agent and implementing UCS with the help of internet articles and pseudocode.
https://plainenglish.io/blog/uniform-cost-search-ucs-algorithm-in-python-ec3ee03fca9f
https://www.redblobgames.com/grids/hexagons/#distances 
https://www.youtube.com/watch?v=aKYlikFAV4k&t=671s
https://ursinus-cs477-f2023.github.io/CoursePage/ClassExercises/Week3_PrioritySearch/#consistency

Explain The Approach:
- It uses a priority queue to rank the status with the lowest cumulative cost and applies Uniform-Cost-Search(UCS)
to discover the best route from the start to the end hex.
- The driving direction needed to get from one hex to its neighbor is stored in a trail.
- To acquire the rebuilt path, follow the trail back from the finish hex to the start hex. Using the reversed 
path, choose the best route from the start hex to the finish hex.
- Because the trail stores the directions to come from, the driving directions are changed to point in the 
opposite directions.

Analyze & Weaknesses:
The method employs a uniform cost search for every step from its tree, which might not be appropriate in every 
situation because it is not as efficient as the A* search. Using A* search effectively and with the right 
heuristic function can increase productivity. 
However, I shall identify the ideal h(n) for future development to get higher performance.
In addition, the time spent examining the map is a disadvantage of employing uniform cost search (UCS) in this challenge.

Helps:
Relearning all the searching algorithm, how it works,in AI by watching tons of Youtube videos as well as reserach 
about A*, Yet, still need more time for implement a good heuristic function in A* to beat Uniform-Cost-Search.
**************************************************************************************************************
Version 3 Mark I: A* (failed the optimality)

The initial A* algorithm agent seemed to doing worst than UCS as it should be about the heuristic function.
I had tried to swtich between the distance calculation such as Manhattan or Euclidean, yet the results were never 
above UCS.
**************************************************************************************************************
Version 4 Mark I: A* (Completely Optimal)

Fixing the bug that has been there since developing the BFS agent. The Bug itself was quick to put an end to 
revaluate the previous cost from other roots with the current best rout, missing out the optimal path to finish.
Adding the else statement after if when the neighborHex already visited, compare the cost of this route vs
the last route it took. If the route is better, update the pq and trail to connect to best route.

Adding more functions such as: 
- SearchPQ() = to browse through the pq to find the hex.cost.
- UpdatePQ() = once the new cost is better than its previous cost, make an update to pq.
- GetOppositeDirection() = converting the switch case in main() to a function.

>>> Fully Optimal Route, Look Map count roughly 750K times.
**************************************************************************************************************
Version 4 Mark II: A* Optimal (reducing getMoveTime() or Look Map times)

Upgrading the trail vector to hold more value: move from parent, cumulativeCost, roughness level;
Adding function:
- GetRoughnessHex(): function to return the roughness level on the neighbor hex that already visted, preventing
another call. 
(using the retrace back with SumTotalCost = Sum(A+B) + Sum(B+C) + Sum(C+D).......)
Where the fourth element of trail caculate roughness of next hex by 
Sum(start+A) = getMoveTime from start--A - start roughness.

>>> Result: Greatly improve the Look Map by 580K times dropping from 750K times AVG to about 150k times.
**************************************************************************************************************
*/
