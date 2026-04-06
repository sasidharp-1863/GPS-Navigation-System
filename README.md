# GPS Navigation System using Graph

## Team Members
- P.Sasidhar
- VSB.Varun

## Problem Statement
To design a GPS navigation system that finds the shortest path between locations using a graph data structure.

## Data Structure Used
Graph (Adjacency List)

## Algorithm used
 (Dijkstra’s Algorithm)
 
## Algorithm Explanation (Dijkstra’s Algorithm)
The GPS Navigation System uses Dijkstra’s Algorithm to find the shortest path between two locations in a graph.

Steps:
1. Initialize distances of all nodes as infinity except the source (0).
2. Mark all nodes as unvisited.
3. Select the node with the smallest distance.
4. Update distances of its neighboring nodes.
5. Repeat until the destination node is reached.

This ensures the shortest path is found efficiently.

## Compilation and Execution
Step 1: Compile the program
gcc src/main.c -o project

Step 2: Run the program
./project

## Features
- Add Location
- Add Road
- Delete Location
- Delete Road
- Update Location
- Update Road
- Display Map
- Find Shortest Path

## Sample Output
Refer sample_output.txt
