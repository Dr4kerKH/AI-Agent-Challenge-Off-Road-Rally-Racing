# AI-Agent-Challenge-Off-Road-Rally-Racing

The AI Agent Challenge: Off-Road Rally Racing is a competitive project where participants develop AI agents to navigate through randomly generated mazes using various pathfinding algorithms. The maze is designed using a hexagonal grid structure, providing six possible movement directions at each step, which adds complexity compared to traditional square-based grids. Maze sizes vary from 3x3 to 9x9, with both the starting and ending points randomly placed within the maze.

### Challenge Objective

The primary goal of the challenge is to implement an AI agent capable of traversing the maze efficiently while finding the lowest-cost path from the starting point to the destination. Each hexagonal tile in the maze has an associated movement cost, which the AI must consider to avoid higher-cost routes and optimize traversal. The map dynamically provides information on the cost of adjacent moves, requiring the agent to make informed decisions at every step.

### Algorithms Utilized

Participants are tasked with implementing and comparing the performance of various pathfinding algorithms, including:
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Dijkstra’s Algorithm
- A (A-Star) Algorithm*

Each algorithm’s effectiveness will be measured based on factors such as path cost, speed of traversal, and computational efficiency.

### Competition Context

The challenge involves 20+ competing AI agents developed by other students. AI agents will be tested across multiple maze configurations, with race results recorded on a leaderboard highlighting:
- Number of races won
- Average traversal cost
- Overall completion time
- Perfect AI agent in giving **Optimized Route** in race.

In addition to race outcomes, agents will be evaluated by the professor for an overall performance score, taking into account code quality, algorithm optimization, and strategic decision-making.

### Scoring & Ranking

- Primary Metrics: Lowest-cost path, speed of solution, documentation of algorithm, and accuracy.
- Secondary Metrics: Code elegance, use of heuristics, readable code, and innovative approaches.
- Final Standings: Determined by cumulative race results and professor’s evaluation.
