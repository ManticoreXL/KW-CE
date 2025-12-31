#include "Graph.h"

// constructor of Graph
Graph::Graph(bool type, int size)
{
	m_Type = type; // true: matrix, false: list
	m_Size = size;
}

// destructor of Graph
Graph::~Graph() {}

bool Graph::getType() { return m_Type; }
int Graph::getSize() { return m_Size; }