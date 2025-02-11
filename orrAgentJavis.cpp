#include "orr.h"

namespace
{
    // If you need to define any new types or functions, put them here in
    // this unnamed namespace.  But no variables allowed!

    // Struct to represent a state in the search space with cost
    struct State
    {
        int hex;
        int cost;
        double heuristic; // Added heuristic value

        State(int h, int c, double hValue) : hex(h), cost(c), heuristic(hValue) {}

        // Define comparison for priority queue
        bool operator>(const State &other) const
        {
            // Compare total cost (actual cost + heuristic)
            return (cost + heuristic) > (other.cost + other.heuristic);
        }
    };
template <typename T>
void reverseVector(vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n / 2; ++i) {
        swap(v[i], v[n - i - 1]);
    }
}

// Heuristic function for A* (you can modify this based on your problem)
double calculateHeuristic(int currentHex, int finishHex, TerrainMap &tm)
{
    int currentRow = currentHex / tm.getSize();
    int currentCol = currentHex % tm.getSize();
    int finishRow = finishHex / tm.getSize();
    int finishCol = finishHex % tm.getSize();

	double middleLine = abs(currentRow - finishRow) + abs(currentCol - finishCol);

    return middleLine/2.4;
	
	//https://www.redblobgames.com/grids/hexagons/#distances
}
}

// Rename and complete this agent function.
vector<drivingDirection> orrAgentJavis(TerrainMap &tm)
{
    int startHex = tm.getStartHex();
    int finishHex = tm.getFinishHex();
    int size = tm.getSize();

    // Priority queue to store the states with cost and heuristic
    priority_queue<State, vector<State>, greater<State>> stateQueue;

    // Vector to store the visited status of each hex
    vector<bool> visited(size * size, false);

    // Vector to store the predecessor direction for each hex
    vector<drivingDirection> trail(size * size);

    // Enqueue the starting hex with cost 0 and heuristic estimate
    stateQueue.push(State(startHex, 0, calculateHeuristic(startHex, finishHex, tm)));
    visited[startHex] = true;

    while (!stateQueue.empty())
    {
        State currentState = stateQueue.top();
        stateQueue.pop();

        int currentHex = currentState.hex;
        int currentCost = currentState.cost;

        // Check if the finish hex is reached
        if (currentHex == finishHex)
        {
            // Reconstruct the path
            vector<drivingDirection> path;
            int hex = finishHex;
            while (hex != startHex)
            {
                path.push_back(trail[hex]);
                switch (path.back())
                {
                case driveW:
                    hex = tm.getNeighborHex(hex, driveE);
                    break;
                case driveK:
                    hex = tm.getNeighborHex(hex, driveX);
                    break;
                case driveS:
                    hex = tm.getNeighborHex(hex, driveN);
                    break;
                case driveN:
                    hex = tm.getNeighborHex(hex, driveS);
                    break;
                case driveX:
                    hex = tm.getNeighborHex(hex, driveK);
                    break;
                case driveE:
                    hex = tm.getNeighborHex(hex, driveW);
                    break;
                }
            }
            reverseVector(path);
            return path;
        }

        // Explore neighbors
        for (int dir = driveW; dir <= driveE; ++dir)
        {
            int neighborHex = tm.getNeighborHex(currentHex, static_cast<drivingDirection>(dir));
            if (!visited[neighborHex] && currentHex != neighborHex)
            {
                visited[neighborHex] = true;
                trail[neighborHex] = static_cast<drivingDirection>(dir);
                // Calculate cost based on move time
                int moveTime = tm.getMoveTime(currentHex, static_cast<drivingDirection>(dir));
                // Calculate heuristic estimate
                double heuristic = calculateHeuristic(neighborHex, finishHex, tm);
                stateQueue.push(State(neighborHex, currentCost + moveTime, heuristic));
            }
        }
    }

    // If no path is found, return an empty vector
    return vector<drivingDirection>();
}