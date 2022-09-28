//Francisco Rocha
//Iker Guerrero
//Juan Carlos Llanos

//Complexity

/*The Floyd-Warshall all-pairs shortest path runs in O(n3) time, which is asymptotically
 * no better than n calls to Dijkstra’s algorithm. However, the loops are so tight and
 * the program so short that it runs better in practice. It is notable as one of the rare
 * graph algorithms that work better on adjacency matrices than adjacency lists.*/

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

    cout<<"Enter number of vertex: ";
    int n;
    cin >> n;
    int arr[n][n], i, j,k;

    // Loop to create the nodes
    for (int i = 0; i < n; i++) {
        Node* a = new Node(i);
        v.push_back(a);
    }

    cout << "\n Enter " << n << "*" << n << " Adjacency List Elements : \n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == -1){
                arr[i][j] = 1000000000;
            }
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

    //Implementation of Floyd Algorithm

    /* dist[][] will be the output matrix
    that will finally have the shortest
    distances between every pair of vertices */
    int dist[n][n];

    /* Initialize the solution matrix same
    as input graph matrix. Or we can say
    the initial values of shortest distances
    are based on shortest paths considering
    no intermediate vertex. */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            dist[i][j] = arr[i][j];

    /* Add all vertices one by one to
    the set of intermediate vertices.
    ---> Before start of an iteration,
    we have shortest distances between all
    pairs of vertices such that the
    shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as
    intermediate vertices.
    ----> After the end of an iteration,
    vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, ..
    k} */
    for (k = 0; k < n; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < n; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < n; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of
                // dist[i][j]
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != infi
                        && dist[i][k] != infi))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    cout << endl;

    //Print the solution of Floyd´s algorithm
    cout << "The following matrix shows the shortest "
            "distances"
            " between every pair of vertices \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == infi)
                cout << "-1"
                     << "     ";
            else
                cout << dist[i][j] << "     ";
        }
        cout << endl;
    }


    return 0;
}
