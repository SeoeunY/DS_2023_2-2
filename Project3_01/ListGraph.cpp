#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
	this->m_Type = type;
	this->m_Size = size;

	m_List = new map < int, int >[size];
	kw_graph = new vector<int>[size + 1];
}

ListGraph::~ListGraph()	
{
	for (int i = 0; i < m_Size; i++)
		m_List[i].clear();
	delete[] m_List;
	for (int i = 0; i < m_Size+1; i++)
		kw_graph[i].clear();
	delete[] kw_graph;
	m_List = nullptr;
	kw_graph=nullptr;
	m_Type = 0;
	m_Size = 0;
}

vector<int>* ListGraph::getKw_graph() {
	return kw_graph;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
	for (auto iter = m_List[vertex - 1].begin(); iter != m_List[vertex - 1].end(); iter++)
		m->insert({ iter->first,iter->second });

	for (int i = 0; i < m_Size; i++) {
		if (i == vertex - 1)
			continue;

		auto j = m_List[i].find(vertex - 1);
		if (j != m_List[i].end())
			m->insert({ i,j->second });
	}
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
	for (auto iter = m_List[vertex - 1].begin(); iter != m_List[vertex - 1].end(); iter++)
		m->insert({ iter->first,iter->second });
}

void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
	m_List[from - 1].insert({ to - 1,weight });//map index
	kw_graph[from].push_back(to);
	kw_graph[to].push_back(from);
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
	*fout << "========PRINT========" << endl;
	for (int i = 0; i < m_Size; i++) {
		*fout << "[" << i + 1 << "]";
		for (auto j = m_List[i].begin(); j != m_List[i].end(); j++) {
			*fout << " -> (" << j->first + 1 << "," << j->second << ")";
		}
		*fout << endl;
	}
	*fout << "=====================" << endl << endl;
	return true;
}