//Francisco Rocha
//Iker Guerrero
//Juan Carlos Llanos
#include "stdc++.h"

// C++ implementation to find the
// shortest path in a directed
// graph from source vertex to
// the destination vertex
#define infi 1000000000
using namespace std;

// Class of the node
class Node {
public:
    int vertexNumber;

    // Adjacency list that shows the
    // vertexNumber of child vertex
    // and the weight of the edge
    vector<pair<int, int> > children;

    //Constructor
    Node(int vertexNumber)
    {
        this->vertexNumber = vertexNumber;
    }

    // Function to add the child for
    // the given node
    void add_child(int vNumber, int length)
    {
        pair<int, int> p;
        p.first = vNumber;
        p.second = length;
        children.push_back(p);
    }
};

// Function to find the distance of
// the node from the given source
// vertex to the destination vertex
vector<int> dijkstraDist(
        vector<Node*> g,
        int s, vector<int>& path)
{
    // Stores distance of each
    // vertex from source vertex
    vector<int> dist(g.size());

    // Boolean array that shows
    // whether the vertex 'i'
    // is visited or not
    bool visited[g.size()];
    for (int i = 0; i < g.size(); i++) {
        visited[i] = false;
        path[i] = -1;
        dist[i] = infi;
    }
    dist[s] = 0;
    path[s] = -1;
    int current = s;

    // Set of vertices that has
    // a parent (one or more)
    // marked as visited
    unordered_set<int> sett;
    while (true) {

        // Mark current as visited
        visited[current] = true;
        for (int i = 0;
             i < g[current]->children.size();
             i++) {
            int v = g[current]->children[i].first;
            if (visited[v])
                continue;

            // Inserting into the
            // visited vertex
            sett.insert(v);
            int alt
                    = dist[current]
                      + g[current]->children[i].second;

            // Condition to check the distance
            // is correct and update it
            // if it is minimum from the previous
            // computed distance
            if (alt < dist[v]) {
                dist[v] = alt;
                path[v] = current;
            }
        }
        sett.erase(current);
        if (sett.empty())
            break;

        // The new current
        int minDist = infi;
        int index = 0;

        // Loop to update the distance
        // of the vertices of the graph
        for (int a: sett) {
            if (dist[a] < minDist) {
                minDist = dist[a];
                index = a;
            }
        }
        current = index;
    }
    return dist;
}


// Driver Code
int main()
{
    vector<Node*> v;
    //Source graph
    int s = 0;

    int n;
    cin >> n;
    int arr[n][n], i, j;

    // Loop to create the nodes
    for (int i = 0; i < n; i++) {
        Node* a = new Node(i);
        v.push_back(a);
    }

    cout << "\n Enter " << n << "*" << n << " Array Elements : \n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << " ";
            cin >> arr[i][j];
        }
    }

    //Let´s create the cycle to add childs
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            // Creating directed
            // weighted edges
            if (arr[i][j] != 0 && arr[i][j] != -1){
                v[i]->add_child(j, arr[i][j]);
            }
        }
        cout << "\n";
    }
    //Graph creation is done

    //We need to iterate n times to calculate distance for every node to each node

    do {
        // code block to be executed
        vector<int> path(v.size());
        vector<int> dist
                = dijkstraDist(v, s, path);

        // Loop to print the distance of
        // every node from source vertex
        for (int i = 0; i < dist.size(); i++) {
            if (dist[i] == infi) {
                cout <<"node "<< s
                << " to node "
                << i << " : "
                << -1 << endl;
                continue;
            }
            cout << "node " << s
                 << " to node "
                 << i << " : "
                 << dist[i] << endl;
        }

        s++;
    }
    while (s < n);



    return 0;
}
