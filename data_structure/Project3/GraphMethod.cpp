#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>
using namespace std;

// breadth first search
bool BFS(Graph* graph, char option, int vertex)
{
    if (graph == nullptr)
    {
        throw "bool BFS(Graph *graph, char option, int vertex) - invalid graph.";
        return false;
    }

    // get size of graph
    int size = graph->getSize() + 1;
    if (vertex >= size)
    {
        throw "bool BFS(Graph *graph, char option, int vertex) - invalid vertex.";
        return false;
    }

    // open log.txt
    ofstream fout("log.txt", ios::app);

    // create visit list
    bool* visited = new bool[size];
    for (int i = 0; i < size; i++)
        visited[i] = false;

    // create queue to save next visit vertex
    queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    // breadth first search
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        // print visited vertex
        fout << curr;

        // create adjacency list
        map<int, int> edges;

        // get adjacency edges
        if (option == 'Y')
            graph->getAdjacentEdgesDirect(curr, &edges);
        else if (option == 'N')
            graph->getAdjacentEdges(curr, &edges);
        else
        {
            throw "bool BFS(Graph *graph, char option, int vertex) - invalid option.";
            delete[] visited;
            fout.close();
            return false;
        }

        // insert next visit vertex into queue
        for (const auto& edge : edges)
        {
            int neighbor = edge.first;
            if (visited[neighbor] == false)
            {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }

        // print ->
        if (!q.empty())
            fout << " -> ";
    }
    fout << endl;

    fout.close();
    delete[] visited;
    return true;
}

// depth first search
bool DFS(Graph* graph, char option, int vertex)
{
    if (graph == nullptr)
    {
        throw "bool DFS(Graph *graph, char option, int vertex) - invalid graph.";
        return false;
    }

    int size = graph->getSize() + 1;
    if (vertex >= size)
    {
        throw "bool DFS(Graph *graph, char option, int vertex) - vertex is over than size.";
        return false;
    }

    // open log.txt
    ofstream fout("log.txt", ios::app);

    // create visit list
    bool* visited = new bool[size];
    for (int i = 1; i < size; i++)
        visited[i] = false;

    // create stack to remember backtracking vertex
    stack<int> s;
    s.push(vertex);

    // counter for printing ->
    int counter = 0;

    while (!s.empty())
    {
        int curr = s.top();
        s.pop();

        if (visited[curr] == false)
        {
            fout << curr;
            visited[curr] = true;
            counter++;
        }
        else
            continue;

        map<int, int> edges;

        // get adjacency edges
        if (option == 'Y')
            graph->getAdjacentEdgesDirect(curr, &edges);
        else if (option == 'N')
            graph->getAdjacentEdges(curr, &edges);
        else
        {
            throw "bool BFS(Graph *graph, char option, int vertex) - invalid option.";
            delete[] visited;
            fout.close();
            return false;
        }

        for (const auto& edge : edges)
        {
            int neighbor = edge.first;
            if (visited[neighbor] == false)
                s.push(neighbor);
        }

        // print ->
        if (!s.empty() && counter < size - 1)
            fout << " -> ";
    }
    fout << endl;

    delete[] visited;
    fout.close();
    return true;
}

// disjoint sets type
struct DisjointSet {
    int parent;
    int rank;
};

// find operation
int findSets(DisjointSet* sets, int i)
{
    if (sets[i].parent != i)
        sets[i].parent = findSets(sets, sets[i].parent);
    return sets[i].parent;
}

// union operation
void unionSets(DisjointSet* sets, int x, int y)
{
    int rootX = findSets(sets, x);
    int rootY = findSets(sets, y);

    if (rootX != rootY)
    {
        if (sets[rootX].rank < sets[rootY].rank)
            sets[rootX].parent = rootY;
        else if (sets[rootX].rank > sets[rootY].rank)
            sets[rootY].parent = rootX;
        else
        {
            sets[rootY].parent = rootX;
            sets[rootX].rank++;
        }
    }
} 

// Kruskal MST generation
bool Kruskal(Graph* graph)
{
    if (graph == nullptr)
    {
        throw "bool Kruskal(Graph *graph) - invalid graph.";
        return false;
    }

    // Get the size of the graph
    int size = graph->getSize() + 1;

    // initialize disjoint sets
    DisjointSet* sets = new DisjointSet[size];
    for (int i = 0; i < size; i++)
    {
        sets[i].parent = i;
        sets[i].rank = 0;
    }

    // create a vector to store edges of graph
    vector<pair<int, pair<int, int>>> edges;

    // get edges
    for (int i = 1; i < size; i++)
    {
        map<int, int> edgeMap;
        graph->getAdjacentEdges(i, &edgeMap);

        for (const auto& edge : edgeMap)
        {
            int to = edge.first;
            int weight = edge.second;
            edges.push_back({ weight, {i, to} });
        }
    }

    // sort edges in ascending order of weight
    sort(edges.begin(), edges.end());

    // Open log.txt
    ofstream fout("log.txt", ios::app);

    // Kruskal's algorithm
    int cost = 0;
    for (int i = 1; i < size; i++)
    {
        fout << "[" << i << "]  ";

        for (const auto& edge : edges)
        {
            int from = edge.second.first;
            int to = edge.second.second;
            int weight = edge.first;

            if (from == i && findSets(sets, from) != findSets(sets, to))
            {
                fout << to << "(" << weight << ") ";
                unionSets(sets, from, to);
                cost += weight;
            }
        }
        fout << endl;
    }
    fout << "cost: " << cost << endl;

    fout.close();
    delete[] sets;
    return true;
}

// Dijkstra
bool Dijkstra(Graph* graph, char option, int vertex)
{
    if (graph == nullptr)
    {
        throw "bool Dijkstra(Graph *graph, char option, int vertex) - invalid graph.";
        return false;
    }

    int size = graph->getSize() + 1;
    if (vertex >= size)
    {
        throw "bool DFS(Graph *graph, char option, int vertex) - vertex is over than size.";
        return false;
    }

    // create a priority queue to store vertices with their distances
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // create a vector to store distances from the source vertex
    vector<int> dist(size, INT_MAX);
    dist[vertex] = 0;

    // create a vector to store the previous vertex on the shortest path
    vector<int> prev(size, -1);

    // insert source vertex into priority queue
    pq.push({ 0, vertex });

    while (!pq.empty())
    {
        int curr = pq.top().second;
        int curr_dist = pq.top().first;
        pq.pop();

        // Skip if this vertex has been processed already
        if (curr_dist > dist[curr])
            continue;

        // Create adjacency list
        map<int, int> edges;

        // Get adjacency edges
        if (option == 'Y')
            graph->getAdjacentEdgesDirect(curr, &edges);
        else if (option == 'N')
            graph->getAdjacentEdges(curr, &edges);
        else
        {
            throw "bool Dijkstra(Graph *graph, char option, int vertex) - invalid option.";
            return false;
        }

        // Relaxation step
        for (const auto& edge : edges)
        {
            int neighbor = edge.first;
            int weight = edge.second;

            if (weight < 0)
            {
                throw "bool Dijkstra(Graph* graph, char option, int vertex) - negative weight detected.";
                return false;
            }

            if (dist[curr] + weight < dist[neighbor])
            {
                dist[neighbor] = dist[curr] + weight;
                prev[neighbor] = curr;
                pq.push({ dist[neighbor], neighbor });
            }
        }
    }

    // open log.txt
    ofstream fout("log.txt", ios::app);

    // Output the result
    for (int i = 1; i < size; ++i)
    {
        if (i == vertex)
            fout << "[" << i << "]x" << endl;
        else
        {
            fout << "[" << i << "]";
            // Print the shortest path
            int p = i;
            while (p != -1)
            {
                fout << p;
                if (prev[p] != -1)
                    fout << " -> ";
                p = prev[p];
            }
            fout << " (" << dist[i] << ")" << endl;
        }
    }

    fout.close();
    return true;
}

// BellmanFord
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex)
{
    if (graph == nullptr)
    {
        throw "bool Bellmanford(Graph *graph, char option, int s_vertex, int e_vertex) - invalid graph.";
        return false;
    }

    int size = graph->getSize() + 1;

    vector<int> dist(size, INT_MAX);
    dist[s_vertex] = 0;

    vector<int> prev(size, -1);

    // Bellman-Ford algorithm
    for (int i = 1; i < size - 1; i++)
    {
        for (int j = 1; j < size; j++)
        {
            map<int, int> edges;

            if (option == 'Y')
                graph->getAdjacentEdgesDirect(j, &edges);
            else if (option == 'N')
                graph->getAdjacentEdges(j, &edges);
            else
            {
                throw "bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) - invalid option.";
                return false;
            }

            for (const auto& edge : edges)
            {
                int neighbor = edge.first;
                int weight = edge.second;

                if (dist[j] != INT_MAX && dist[j] + weight < dist[neighbor])
                {
                    dist[neighbor] = dist[j] + weight;
                    prev[neighbor] = j;
                }
            }
        }
    }

    // check for negative cycles
    for (int i = 1; i < size; i++)
    {
        map<int, int> edges;

        if (option == 'Y')
            graph->getAdjacentEdgesDirect(i, &edges);
        else if (option == 'N')
            graph->getAdjacentEdges(i, &edges);
        else
        {
            throw "bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) - invalid option.";
            return false;
        }

        for (const auto& edge : edges)
        {
            int neighbor = edge.first;
            int weight = edge.second;

            if (dist[i] != INT_MAX && dist[i] + weight < dist[neighbor])
            {
                throw "bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) - negative cycle detected.";
                return false;
            }
        }
    }

    // open log.txt
    ofstream fout("log.txt", ios::app);

    // stack for backtracking
    stack<int> s;
    int curr = e_vertex;
    while (curr != -1)
    {
        s.push(curr);
        curr = prev[curr];
    }

    // print path
    while (!s.empty())
    {
        fout << s.top();
        s.pop();
        if (!s.empty())
            fout << " -> ";
    }
    fout << endl;

    // print cost
    fout << "cost: ";
    if (dist[e_vertex] == INT_MAX)
        fout << "x";
    else
        fout << dist[e_vertex];
    fout << endl;

    fout.close();
    return true;
}

// FLOYD
bool FLOYD(Graph* graph, char option)
{
    if (graph == nullptr)
    {
        throw "bool FLOYD(Graph *graph, char option) - invalid graph";
        return false;
    }

    int size = graph->getSize() + 1;

    // create and initialize distance matrix
    vector<vector<int>> dist(size, vector<int>(size, INT_MAX));

    for (int i = 1; i < size; i++)
    {
        map<int, int> edges;

        // get edges
        if (option == 'Y')
            graph->getAdjacentEdgesDirect(i, &edges);
        else if (option == 'Y')
            graph->getAdjacentEdges(i, &edges);
        else
        {
            throw "bool FLOYD(Graph* graph, char option) - invalid option";
            return false;
        }

        for (const auto& edge : edges)
        {
            int neighbor = edge.first;
            int weight = edge.second;
            dist[i][neighbor] = weight;
        }

        // Floyd algorithm
        for (int k = 1; k < size; k++)
        {
            for (int i = 1; i < size; i++)
            {
                for (int j = 1; j < size; j++)
                {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX
                        && dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        // check for negative cycles
        for (int i = 1; i < size; ++i)
        {
            if (dist[i][i] < 0)
            {
                throw"bool FLOYD(Graph* graph, char option) - negative cycle detected.";
                return false;
            }
        }
    }

    // open log.txt
    ofstream fout("log.txt", ios::app);

    // print result of FLOYD
    fout << "   ";
    for (int i = 1; i < size; i++)
        fout << "[" << i << "] ";
    fout << endl;

    for (int i = 1; i < size; i++)
    {
        fout << "[" << i << "] ";
        for (int j = 1; j < size; j++)
        {
            if (dist[i][j] == INT_MAX)
                fout << 0;
            else
                fout << dist[i][j];

            if (j < size - 1)
                fout << "   ";
        }
        fout << endl;
    }
   
    fout.close();
    return true;
}

// KWANGWOON
bool KWANGWOON(Graph* graph, int vertex)
{
    if (graph == nullptr || graph->getType() == true)
    {
        throw "bool KWANGWOON(Graph *graph, int vertex) - invalid graph";
        return false;
    }

    int size = graph->getSize() + 1;
    if (vertex > size)
    {
        throw "bool KWANGWOON(Graph* graph, int vertex) - invalid vertex.";
        return false;
    }

    // open log.txt
    ofstream fout("log.txt", ios::app);

    // create to get kw_graph's edge vector
    vector<int> edges;

    // create visit list
    bool* visited = new bool[size];
    for (int i = 0; i < size; i++)
        visited[i] = false;

    // create queue to save next visit vertex
    queue<int> q;
    q.push(vertex);
    visited[vertex] = true;

    // breadth first search
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        // print visited vertex
        fout << curr;

        // create adjacency list
        vector<int> edges;

        // get adjacency edges
        graph->getKwGraphEdges(curr, &edges);
        
        if(edges.empty())
        {
            throw "bool KWANGWOON(Graph* graph, int vertex) - invalid option.";
            delete[] visited;
            fout.close();
            return false;
        }

        // KWANGWOON algorithm
        int next = (edges.size() % 2 == 0) ? edges[0] : edges[edges.size() - 1];

        if (visited[next] == false)
        {
            visited[next] = true;
            q.push(next);

            // print ->
            if (!q.empty())
                fout << " -> ";
        }
    }
    fout << endl;
    
    delete[] visited;
    fout.close();
    return true;
}