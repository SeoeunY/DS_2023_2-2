#include "Graph.h"

Graph::Graph(bool type, int size)
{
	m_Type = type;
	m_Size = size;
}

Graph::~Graph()	
{
	m_Type = 0;
	m_Size = 0;
}


bool Graph::getType(){return m_Type;}	
int Graph::getSize(){return m_Size;}
