#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
	this->m_Type = type;
	this->m_Size = size;
	m_Mat = new int* [size];
	for (int i = 0; i < size; i++) {
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, size);
	}
}

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < m_Size; ++i) {
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
	m_Mat = nullptr;
	m_Type = 0;
	m_Size = 0;
}

vector<int>* MatrixGraph::getKw_graph() {
	return NULL;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m) //Definition of getAdjacentEdges(No Direction == Undirected)
{	
	for (int i = 0; i < m_Size; i++) {
		if (m_Mat[vertex - 1][i] != 0)
			m->insert({ i,m_Mat[vertex - 1][i] });//move with index
	}

	for (int i = 0; i < m_Size; i++) {
		if (i == vertex - 1)
			continue;
		else {
			if (m_Mat[i][vertex - 1] != 0)
				m->insert({ i,m_Mat[i][vertex - 1] });//move with index
		}
	}
}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	for (int i = 0; i < m_Size; i++) {
		if (m_Mat[vertex - 1][i] != 0)
			m->insert({ i,m_Mat[vertex - 1][i] });
	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
	m_Mat[from][to] = weight;//move with index
}

bool MatrixGraph::printGraph(ofstream *fout)	
{
	*fout << "========PRINT========" << endl;
	*fout << "\t";
	for (int i = 0; i < m_Size; i++)
		*fout << "[" << i + 1 << "]" << "\t";
	*fout << endl;

	for (int i = 0; i < m_Size; i++) {
		*fout << "[" << i + 1 << "]\t";
		for (int j = 0; j < m_Size; j++) {
			*fout << m_Mat[i][j] << "\t";
		}
		*fout << endl;
	}
	*fout << "=====================" << endl << endl;
	return true;
}
