# Dijkstra-and-Floyd
Write a C++ program that implements the Dijkstra and Floyd algorithms to find the shortest distance between pairs of nodes in a directed graph.

The program must read a number n followed by n x n nonnegative integer values ​​that represent an adjacency matrix of a directed graph.
The first number represents the number of nodes, the following values ​​in the array, the value at position i,j represent the weight of the arc from node i to node j. If there is no arc between node i and node j, the value in the array must be -1

The output of the program is, first with Dijkstra's algorithm, the distance from node i to node j for all nodes, and then, the result matrix of Floyd's algorithm

 

Input example:

4
0 2 -1 3
-1 0 1 5
2 3 0 -1
3 -1 4 0

 

Output example:

Dijkstra:
node 1 to node 2 : 2
node 1 to node 3 : 3
node 1 to node 4 : 3
node 2 to node 1 : 3
...

node 4 to node 2 : 5
node 4 to node 3 : 4

Floyd:
0 2 3 3
3 0 1 5
2 3 0 5
3 5 4 0

 


Your program should be called main.cpp and should compile using the g++ command in a linux environment.


Your program must be able to run using redirected input in a linux environment
(./a.out < in.txt)
