#include "orr.h"
namespace
{
// Struct current state
struct State {
    int hex;
    float cost;
	float heuristic; // Added heuristic value
    State(int h, float c, float hValue) : hex(h), cost(c), heuristic(hValue) {}
    bool operator>(const State &G) const {return (cost + heuristic) > (G.cost + G.heuristic);} // Rewrite the comparison for compare cost of trails
};
// Function for reverse vector
template <typename T>
void reverseVector(vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n / 2; ++i) {
        swap(v[i], v[n - i - 1]);
    }
}
float searchPQ(priority_queue<State, vector<State>, greater<State>> &status, const int pos) {
    float returnCost = -1;
    priority_queue<State, vector<State>, greater<State>> tempQueue;

    while (!status.empty()) {
        if (status.top().hex == pos) {
            returnCost = status.top().cost;
            break;
        }
        tempQueue.push(status.top());
        status.pop();
    }
    // Restore the original priority queue
    while (!tempQueue.empty()) {
        status.push(tempQueue.top());
        tempQueue.pop();
    }
    return returnCost;
}
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
// Heuristic function for A*
float calculateHeuristic(int currentHex, int finishHex, TerrainMap &tm, int size)
{
    int currentRow = currentHex / size;
    int currentCol = currentHex % size;
    int finishRow = finishHex / size;
    int finishCol = finishHex % size;
	float distance = abs(currentRow - finishRow) + abs(currentCol - finishCol);
    return distance;
	//https://www.redblobgames.com/grids/hexagons/#distances
}
}


vector<drivingDirection> orrAgentZulu(TerrainMap &tm)
{
    // Setting up, start position, finish position, and size of terrain
	int start = tm.getStartHex();
    int finish = tm.getFinishHex();
    int size = tm.getSize();

    // Priority queue to store the states with cost, implementing Uniform Cost Search
    priority_queue<State, vector<State>, greater<State>> status;
    // Vectors for holding the visited hex in map, and tracking trail
	vector<bool> visited(size * size, false);
    vector<drivingDirection> trail(size * size);

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
				path.push_back(trail[hex]);
                hex = tm.getNeighborHex(hex, getOppositeDirection(path.back()));
            }
			// Due to path being store from finish to start, reverse Path for travel route
            reverseVector(path);
            return path;
        }

        // Explore neighbors from current position
        for (int dir = driveW; dir <= driveE; ++dir) {
            
			drivingDirection move = static_cast<drivingDirection>(dir);
			int neighborHex = tm.getNeighborHex(currentPos, move);
			int moveTime = tm.getMoveTime(currentPos, move);
			
			// Checking if the neighborHex is not already visited and it is not wander off the map
            if (!visited[neighborHex]) {
                
				//if condition true, set it to visited, and add the move to trail
				visited[neighborHex] = true;
                trail[neighborHex] = move;
                // Calculate cost based on move time of trails
				float heuristic = calculateHeuristic(neighborHex, finish, tm, size);
                status.push(State(neighborHex, currentCost + moveTime, heuristic));
            }
			else {
				float previousCost = searchPQ(status, neighborHex);
				if (currentCost + moveTime < previousCost) {
					updatePQ(status, currentCost + moveTime, neighborHex);
					trail[neighborHex] = move;
				}
			}
        }
    }

    // If no path is found, return an empty vector
    return vector<drivingDirection>();
}