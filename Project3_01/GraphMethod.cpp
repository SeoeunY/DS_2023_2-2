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
#define infinite 0x3f3f3f3f

struct Edge {
public:
	int from;
	int to;
	int weight;
	Edge(int a, int b, int weight) {
		this->from = a;
		this->to = b;
		this->weight = weight;
	}
};

bool BFS(Graph* graph, string option, int vertex, ofstream *fout)
{
	int size = graph->getSize();

	if (vertex<1 || vertex>size)
		return false;

	*fout << "========BFS========" << endl;
	if (option == "Y")
		*fout << "Directed Graph BFS result" << endl;
	else
		*fout << "Undirected Graph BFS result" << endl;
	*fout << "startvertex: " << vertex << endl;

	bool* visit = new bool[size];
	for (int i = 0; i < size; i++)
		visit[i] = false;

	queue <int>q;
	q.push(vertex - 1);//move with index
	visit[vertex - 1] = true;

	map<int, int> m;
	while (!q.empty()) {
		int ver = q.front();
		q.pop();

		*fout << ver + 1;
		if(option=="Y")
			graph->getAdjacentEdgesDirect(ver + 1, &m);//vertex num���� ��
		else
			graph->getAdjacentEdges(ver + 1, &m);//vertex num���� ��

		for (auto iter = m.begin(); iter != m.end(); iter++) {
			if (visit[iter->first] == 0) {
				q.push(iter->first);
				visit[iter->first] = true;
			}
		}
		if (q.size() != 0)
			*fout << " -> ";

		m.clear();
	}

	*fout << endl << "=====================" << endl << endl;

	delete[] visit;
	return true;
}

bool DFS(Graph* graph, string option, int vertex, ofstream* fout)
{
	int size = graph->getSize();

	if (vertex<1 || vertex>size)
		return false;

	*fout << "========DFS========" << endl;
	if (option == "Y")
		*fout << "Directed Graph DFS result" << endl;
	else
		*fout << "Undirected Graph DFS result" << endl;
	*fout << "startvertex: " << vertex << endl;

	bool* visit = new bool[size];
	for (int i = 0; i < size; i++)
		visit[i] = false;

	stack<int>s;
	s.push(vertex - 1);//move with index
	visit[vertex - 1] = true;
	vector<int>arr;
	arr.push_back(vertex);

	map<int, int> m;
	while (!s.empty()) {
		int ver = s.top();
		s.pop();
		
		if (option == "Y")
			graph->getAdjacentEdgesDirect(ver + 1, &m);//vertex num���� ��
		else
			graph->getAdjacentEdges(ver + 1, &m);//vertex num���� ��
		bool breaked = false;
		for (auto iter = m.begin(); iter != m.end(); iter++) {
			if (visit[iter->first] == false) {
				arr.push_back(iter->first + 1);
				visit[iter->first] = true;
				s.push(ver);
				s.push(iter->first);

				break;
			}
		}

		m.clear();
	}
	
	for (int i = 0; i < arr.size(); i++) {//print
		*fout << arr[i];
		if (i != arr.size() - 1)
			*fout << " -> ";
	}

	*fout << endl << "=====================" << endl << endl;

	delete[] visit;
	return true;
 }

void InsertionSort(vector<Edge>* v,int low, int high) {
	for (int i = low + 1; i <= high; i++) {
		Edge key = v->at(i);
		int j = i - 1;
		while (j >= 0 && (v->at(j)).weight > key.weight) {
			v->at(j + 1) = v->at(j);
			j--;
		}
		v->at(j + 1) = key;
	}
}

int partition(vector<Edge>* v, int left, int right) {
	int pivot = left;
	int i = left + 1;
	int j = right;

	while (i <= j) {
		while (i <= right) {
			if ((v->at(i).weight <= v->at(pivot).weight))
				i++;
			else
				break;
		}
		while ((v->at(j).weight >= v->at(pivot).weight) && (j > left))
			j--;
		if (i > j) {
			Edge temp = v->at(j);
			v->at(j) = v->at(pivot);
			v->at(pivot) = temp;
		}
		else {
			Edge temp = v->at(j);
			v->at(j) = v->at(i);
			v->at(i) = temp;
		}
	}

	return j;
}

void quicksort(vector<Edge>* v, int low, int high) {
	if (low < high) {
		if (high - low + 1 <= 6)
			InsertionSort(v, low, high);
		else {
			int pivot = partition(v, low, high);
			quicksort(v, low, pivot - 1);
			quicksort(v, pivot + 1, high);
		}
	}
}

int getParent(int vertex, int* visit) {
	if (visit[vertex] == vertex) return vertex;
	return getParent(visit[vertex], visit);
}

void unionParent(int vertex1, int vertex2, int* visit) {
	vertex1 = getParent(vertex1, visit);
	vertex2 = getParent(vertex2, visit);
	if (vertex1 < vertex2) visit[vertex2] = vertex1;
	else visit[vertex1] = vertex2;
}

bool isCycle(int vertex1, int vertex2, int* visit) {
	vertex1 = getParent(vertex1, visit);
	vertex2 = getParent(vertex2, visit);
	if (vertex1 == vertex2) return true;
	else return false;
}

bool Kruskal(Graph* graph, ofstream* fout)
{
	vector<Edge>v;
	map<int, int>m;
	for (int i = 0; i < graph->getSize(); i++) {
		graph->getAdjacentEdges(i + 1, &m);
		if (m.size() == 0)
			return false;
		for (auto iter = m.begin(); iter != m.end(); iter++)
			v.push_back(Edge(i, iter->first, iter->second));//insert with key -> weight
		m.clear();
	}

	int size = graph->getSize();
	
	quicksort(&v, 0, v.size() - 1);
	
	int* visit = new int[size];
	for (int i = 0; i < size; i++)
		visit[i] = i;

	int sum = 0;
	int cnt = 0;
	map<int, int>* result = new map<int, int>[size];

	for (auto iter = v.begin(); iter != v.end(); iter++) {
		if (!isCycle(iter->from, iter->to, visit)) {
			sum += iter->weight;
			cnt++;
			result[iter->from].insert({ iter->to,iter->weight });
			result[iter->to].insert({ iter->from,iter->weight });
			unionParent(iter->from, iter->to, visit);
		}
	}

	if (cnt != graph->getSize() - 1)
		return false;
	
	*fout << "====== Kruskal =======" << endl;
	for (int i = 0; i < size; i++) {
		*fout << "[" << i + 1 << "] ";

		for (auto iter = result[i].begin(); iter != result[i].end(); iter++)
			*fout << iter->first + 1 << "(" << iter->second << ") ";
		*fout << endl;
	}
	*fout << "cost: " << sum << endl;
	*fout << "=====================" << endl << endl;
	
	for (int i = 0; i < size; i++)
		result[i].clear();
	delete[] result;
	delete[] visit;
	return true;
}

bool Dijkstra(Graph* graph, string option, int vertex, ofstream* fout)
{
	int size = graph->getSize();
	
	if (vertex<1 || vertex>size)
		return false;

	map<int, int>m;
	for (int i = 0; i < size; i++) {
		if (option == "Y")
			graph->getAdjacentEdgesDirect(i + 1, &m);
		else
			graph->getAdjacentEdges(i + 1, &m);

		for (auto iter = m.begin(); iter != m.end(); iter++) {
			if (iter->second < 0)
				return false;
		}
		m.clear();
	}

	int* d = new int[size];
	for (int i = 0; i < size; i++)//initialize
		d[i] = infinite;

	int* prev = new int[size];
	for (int i = 0; i < size; i++)
		prev[i] = 0;

	priority_queue < pair<int, int> > q;

	q.push({ 0,vertex - 1 });//move with index
	d[vertex - 1] = 0;

	while (!q.empty()) {
		int dist = -q.top().first;
		int v = q.top().second;
		q.pop();

		if (d[v] < dist)
			continue;

		if (option == "Y")
			graph->getAdjacentEdgesDirect(v + 1, &m);
		else
			graph->getAdjacentEdges(v + 1, &m);
		for (auto iter = m.begin(); iter != m.end(); iter++) {
			int cost = dist + iter->second;

			if (cost < d[iter->first]) {
				d[iter->first] = cost;
				prev[iter->first] = v;
				q.push({ -cost,iter->first });
			}
		}
	}

	*fout << "====== Dijkstra =======" << endl;
	if (option == "Y")
		*fout << "Directed Graph Dijkstra result" << endl;
	else
		*fout << "Undirected Graph Dijkstra result" << endl;
	*fout << "startvertex: " << vertex << endl;
	for (int i = 0; i < size; i++) {
		if (i == vertex - 1)
			continue;
		
		if (d[i] == infinite) {
			*fout << "[" << i + 1 << "] x" << endl;
			continue;
		}
		*fout << "[" << i + 1 << "] " << vertex << " -> ";

		vector<int>path;
		int p = prev[i];
		while (p != vertex - 1) {
			path.push_back(p + 1);
			p = prev[p];
		}

		for (int j = path.size() - 1; j >= 0; j--) {
			*fout << path[j] << " -> ";
		}
		*fout << i + 1 << " (" << d[i] << ")" << endl;
		path.clear();
	}

	*fout << "=====================" << endl << endl;

	delete[]d;
	delete[]prev;
	return true;
}

bool Bellmanford(Graph* graph, string option, int s_vertex, int e_vertex, ofstream* fout)
{
	multimap<int, pair<int, int>>v;
	map<int, int>m;
	for (int i = 0; i < graph->getSize(); i++) {
		if (option == "Y")
			graph->getAdjacentEdgesDirect(i + 1, &m);
		else
			graph->getAdjacentEdges(i + 1, &m);
		for (auto iter = m.begin(); iter != m.end(); iter++)
			v.insert({ i, { iter->first,iter->second } });
		m.clear();
	}

	int* dist = new int[graph->getSize()];
	for (int i = 0; i < graph->getSize(); i++)
		dist[i] = infinite;

	int* prev = new int[graph->getSize()];
	for (int i = 0; i < graph->getSize(); i++)
		prev[i] = 0;

	dist[s_vertex - 1] = 0;
	int from, to, weight;
	for (int i = 0; i < graph->getSize(); i++) {
		for (auto iter = v.begin(); iter != v.end(); iter++) {
			from = iter->first;
			to = iter->second.first;
			weight = iter->second.second;

			if (dist[from] == infinite)
				continue;
			if (dist[to] > dist[from] + weight) {
				dist[to] = dist[from] + weight;
				prev[to] = from;
			}
		}
	}

	for (auto iter = v.begin(); iter != v.end(); iter++) {
		from = iter->first;
		to = iter->second.first;
		weight = iter->second.second;

		if (dist[from] == infinite)
			continue;
		if (dist[to] > dist[from] + weight) {
			return false;//negative cycle
		}
	}

	*fout << "====== Bellman-Ford =======" << endl;
	if (option == "Y")
		*fout << "Directed Graph Bellman-Ford result" << endl;
	else
		*fout << "Undirected Graph Bellman-Ford result" << endl;

	if (dist[e_vertex - 1] >= infinite) {
		*fout << "x" << endl;
		*fout << "=====================" << endl << endl;

		delete[]dist;
		delete[]prev;
		return true;
	}

	vector<int>path;
	int p = prev[e_vertex - 1];
	while (p != s_vertex - 1) {
		path.push_back(p + 1);
		p = prev[p];
		if (p == e_vertex - 1) {
			*fout << "x" << endl;
			*fout << "=====================" << endl << endl;

			delete[]dist;
			delete[]prev;
			path.clear();
			return true;
		}
	}
	path.push_back(p + 1);

	for (int j = path.size() - 1; j >= 0; j--) {
		*fout << path[j] << " -> ";
	}
	*fout << e_vertex << endl;

	*fout << "cost: " << dist[e_vertex - 1] << endl;

	*fout << "=====================" << endl << endl;
	
	delete[]dist;
	delete[]prev;
	path.clear();
	return true;
}

bool FLOYD(Graph* graph, string option, ofstream* fout)
{
	int size = graph->getSize();
	int** arr = new int*[size];
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
		for (int j = 0; j < size; j++)
			arr[i][j] = 0;
	}

	//put edge information in arr
	map<int, int>m;
	for (int i = 0; i < size; i++) {
		if (option == "Y")
			graph->getAdjacentEdgesDirect(i + 1, &m);
		else
			graph->getAdjacentEdges(i + 1, &m);

		for (auto iter = m.begin(); iter != m.end(); iter++) {
			arr[i][iter->first] = iter->second;
		}
		m.clear();
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j)
				continue;
			if (arr[i][j] == 0)
				arr[i][j] = infinite;
		}
	}

	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int temp = arr[i][k] + arr[k][j];
				if (temp < arr[i][j]) {
					if (arr[i][k] == infinite || arr[k][j] == infinite)
						continue;
					arr[i][j] = temp;
				}
			}
		}
	}

	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int temp = arr[i][k] + arr[k][j];
				if (temp < arr[i][j]) {
					if (arr[i][k] == infinite || arr[k][j] == infinite)
						continue;
					for (int i = 0; i < size; i++)
						delete arr[i];
					delete[] arr;
					return false;
				}
			}
		}
	}


	*fout << "====== FLOYD =======" << endl;
	if (option == "Y")
		*fout << "Directed Graph FLOYD result" << endl;
	else
		*fout << "Undirected Graph FLOYD result" << endl;

	*fout << "\t";
	for (int i = 0; i < size; i++)
		*fout << "[" << i + 1 << "]" << "\t";
	*fout << endl;

	for (int i = 0; i < size; i++) {
		*fout << "[" << i + 1 << "]\t";
		for (int j = 0; j < size; j++) {
			if (arr[i][j] == infinite)
				*fout << "x\t";
			else
				*fout << arr[i][j] << "\t";
		}
		*fout << endl;
	}
	*fout << "=====================" << endl << endl;


	for (int i = 0; i < size; i++)
		delete arr[i];
	delete[] arr;
	return true;
}

bool KWANGWOON(Graph* graph, int vertex, ofstream* fout) {
	vector<int> result;
	int cnt = 0;
	vector<int>* edge = graph->getKw_graph();

	bool* visit = new bool[graph->getSize() + 1];
	for (int i = 0; i < graph->getSize() + 1; i++)
		visit[i] = false;

	int v = 1;
	int key, k, next;
	bool done = false;

	for (int i = 0; i < graph->getSize(); i++) {
		visit[v] = true;
		cnt++;
		result.push_back(v);

		if (edge[v].size() == 0)
			break;
		
		if (i == graph->getSize() - 1)
			break;

		//sort
		for (int j = 0; j < edge[v].size(); j++) {
			key = edge[v][j];

			for (k = j - 1; k >= 0 && edge[v][k] > key; k--)
				edge[v][k + 1] = edge[v][k];

			edge[v][k + 1] = key;
		}

		int z = 0;
		for (int j = 0; j < edge[v].size(); j++) {
			if (visit[edge[v][j]]==true)
				z++;
		}

		if (z == edge[v].size())
			break;

		z = edge[v].size() - z;

		if (z % 2 == 0) {//even (small)
			z = 0;
			next = edge[v][z];
			while (visit[next] == true) {
				z++;
				if (z > edge[v].size()) {
					done = true;
					break;
				}
				next = edge[v][z];
			}
		}
		else {//odd (big)
			z = edge[v].size() - 1;
			next = edge[v][z];
			while (visit[next] == true) {
				z--;
				if (z < 0) {
					done = true;
					break;
				}
				next = edge[v][z];
			}
		}
		if (done == true)
			break;
		v = next;
	}

	*fout << "======== KWANGWOON ========" << endl;
	*fout << "startvertex: 1" << endl;
	for (int i = 0; i < result.size(); i++) {
		*fout << result[i];
		if (i != result.size() - 1)
			*fout << " -> ";
	}
	*fout << endl << "============================" << endl<<endl;

	delete[] visit;
	return true;
}