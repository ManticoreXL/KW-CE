#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

// constructor of matrix graph
MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
    // dynamic allocation of adjacent matrix
    m_Mat = new int* [size + 1];
    for (int i = 0; i < size + 1; i++)
    {
        m_Mat[i] = new int[size + 1];
        for (int j = 0; j < size + 1; j++)
            m_Mat[i][j] = 0; // initialize by 0 (no edge)
    }
}

// constructor of matrix graph
MatrixGraph::~MatrixGraph()
{
    if (m_Mat)
    {
        // delete 2D array
        for (int i = 0; i < m_Size + 1; i++)
            delete[] m_Mat[i];
        delete[] m_Mat;
    }
}

// get undirected adjacent edges at vertex
void MatrixGraph::getAdjacentEdges(int vertex, map<int, int> *m)
{
    if (m_Mat == nullptr)
    {
        throw "void MatrixGraph::getAdjacentEdges(int vertex, map<int, int> *m) - graph is empty.";
        return;
    }

    // insert adjacent edges into map
    for (int i = 1; i < m_Size + 1; i++)
    {
        if (i == vertex) // add original edges
        {
            if (m_Mat[vertex][i] != 0)
                m->insert(pair<int, int>(i, m_Mat[vertex][i]));
        }
        else // add opposite direction edges
        {
            if (m_Mat[i][vertex] != 0)
                m->insert(pair<int, int>(i, m_Mat[i][vertex]));
        }
    }
}

// get directed adjacent edges at vertex
void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int> *m)
{
    if (m_Mat == nullptr)
    {
        throw "void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int> *m) - graph is empty.";
        return;
    }

    // insert adjacent edges into map
    for (int i = 1; i < m_Size + 1; i++)
        if (m_Mat[vertex][i] != 0)
            m->insert(pair<int, int>(i, m_Mat[vertex][i]));
}

void MatrixGraph::getKwGraphEdges(int vertex, vector<int>* m)
{
    throw"void MatrixGraph::getKwGraphEdges(int vertex, vector<int>* m) - matrix graph cannot execute KWANGWOON.";
    return;
}

// insert new edge into m_Mat
void MatrixGraph::insertEdge(int from, int to, int weight)
{
    if (from > m_Size || to > m_Size)
    {
        throw "void MatrixGraph::insertEdge(int from, int to, int weight) - out of range";
        return;
    }
    // set (from, to) = weight
    m_Mat[from][to] = weight;
}

// print matrix graph
bool MatrixGraph::printGraph(ofstream *fout)
{
    if (m_Mat == nullptr)
    {
        throw "bool MatrixGraph::printGraph(ofstream *fout) - matrix is empty.";
        return false;
    }

    // display to_vertex of matrix
    *fout << "   ";
    for (int i = 1; i < m_Size + 1; i++)
        *fout << "[" << i << "] ";
    *fout << endl;

    // display from_vertex and adjaceny matrix
    for (int i = 1; i < m_Size+1; i++)
    {
        *fout << "[" << i << "] ";
        for (int j = 1; j < m_Size + 1; j++)
            *fout << m_Mat[i][j] << "   ";
        *fout << endl;
    }

    return true;
}