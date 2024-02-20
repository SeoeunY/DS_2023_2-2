#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

Manager::Manager()	
{
	graph = nullptr;	
	//fout.open("log.txt", ios::app);
	fout.open("log.txt");
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode
		
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}

	string comm, sub_comm;
	int start_vertex = 0;
	bool suc;

	while (!fin.eof()) {
		fin >> comm;

		if (comm == "LOAD") {
			fin >> sub_comm;
			suc = LOAD(sub_comm);
			if (suc == false)
				printErrorCode(100);
			else {
				fout << "========LOAD=======" << endl;
				fout << "Success" << endl;
				fout << "====================" << endl << endl;
			}
		}
		else if (comm == "PRINT") {
			suc = PRINT();
			if (suc == false)
				printErrorCode(200);

		}
		else if (comm == "BFS") {
			getline(fin, sub_comm);

			if (sub_comm.length() == 2)//didn't write vertex
				printErrorCode(300);
			else {
				string temp;
				for (int i = 1; i < sub_comm.length(); i++) {
					if (sub_comm[i] == ' ') {
						sub_comm.erase(0, i);
						start_vertex = stoi(sub_comm);
					}
					else
						temp.push_back(sub_comm[i]);
				}

				suc = mBFS(temp, start_vertex);
				if (suc == false)
					printErrorCode(300);
			}
		}
		else if (comm == "DFS") {
			getline(fin, sub_comm);

			if (sub_comm.length() == 2)//didn't write vertex
				printErrorCode(400);
			else {
				string temp;
				for (int i = 1; i < sub_comm.length(); i++) {
					if (sub_comm[i] == ' ') {
						sub_comm.erase(0, i);
						start_vertex = stoi(sub_comm);
					}
					else
						temp.push_back(sub_comm[i]);
				}

				suc = mDFS(temp, start_vertex);
				if (suc == false)
					printErrorCode(400);
			}
		}
		else if (comm == "KRUSKAL") {
			suc = mKRUSKAL();
			if (suc == false)
				printErrorCode(600);
		}
		else if (comm == "DIJKSTRA") {
			getline(fin, sub_comm);

			if (sub_comm.length() == 2)//didn't write vertex
				printErrorCode(700);
			else {
				string temp;
				for (int i = 1; i < sub_comm.length(); i++) {
					if (sub_comm[i] == ' ') {
						sub_comm.erase(0, i);
						start_vertex = stoi(sub_comm);
					}
					else
						temp.push_back(sub_comm[i]);
				}

				suc = mDIJKSTRA(temp, start_vertex);
				if (suc == false)
					printErrorCode(700);
			}
		}
		else if (comm == "BELLMANFORD") {
			getline(fin, sub_comm);

			vector<string>a;
			string temp;
			for (int i = 1; i < sub_comm.size(); i++) {
				if (sub_comm[i] == ' ') {
					a.push_back(temp);
					temp.clear();
				}
				else
					temp.push_back(sub_comm[i]);
			}
			a.push_back(temp);

			if (a.size() != 3)
				printErrorCode(800);
			else {
				if (a[0] != "Y" && a[0] != "N")
					printErrorCode(800);
				else if (graph == NULL)
					printErrorCode(800);
				else {
					int size = graph->getSize();
					int start = stoi(a[1]);
					int end = stoi(a[2]);
					if (start<1 || end>size)
						printErrorCode(800);
					else {
						suc = mBELLMANFORD(a[0], start, end);
						if (suc == false)
							printErrorCode(800);
					}
				}
			}

		}
		else if (comm == "FLOYD") {
			getline(fin, sub_comm);
			sub_comm.erase(0, 1);
			
			if (sub_comm.length() != 1)
				printErrorCode(900);
			else if (sub_comm != "Y" && sub_comm != "N")
				printErrorCode(900);
			else {
				suc = mFLOYD(sub_comm);
				if (suc == false)
					printErrorCode(900);
			}
		}
		else if (comm == "KWANGWOON") {
			if (graph == NULL)
				printErrorCode(500);
			else if (graph->getType() == 1)
				printErrorCode(500);
			else {
				suc = mKwangWoon(1);
				if (suc == false)
					printErrorCode(500);
			}
		}
		else if (comm == "EXIT") {
			fout<<"===== EXIT ====="<<endl;
			fout<<"Success"<<endl;
			fout<<"===============";
			break;
		}
		else
			continue;
	}

	fin.close();
	return;
}

bool Manager::LOAD(string filename)
{
	ifstream mat;
	if (load != 0) {
		delete graph;
	}

	if (filename == "graph_L.txt") {
		mat.open(filename);

		if (!mat)//file not exist
			return false;
		if (mat.eof())//empty file
			return false;

		string com;
		int from, to, weight;
		for (int i = 0; !mat.eof(); i++) {
			if (i == 0) {
				mat >> com;
				continue;
			}
			if (i == 1) {
				mat >> from;
				if (load != 0) {
					Graph* new_graph = new ListGraph(0,from);
					graph = new_graph;
				}
				else {
					load++;
					graph = new ListGraph(0, from);
				}
				getline(mat, com);
			}
			else {
				getline(mat, com);
				
				int cnt = 0;
				int j;
				for (j = 0; j < com.length(); j++) {
					if (com[j] == ' ') {
						cnt++;
						break;
					}
				}

				if (cnt == 0) {
					from = stoi(com);
				}
				else if (cnt == 1) {
					string temp;
					temp.append(com, 0, j);
					to = stoi(temp);
					com.erase(0, j);
					weight = stoi(com);

					graph->insertEdge(from, to, weight);//vertex
				}
			}
		}
	}
	else if (filename == "graph_M.txt") {
		mat.open(filename);

		if (!mat)
			return false;

		if (mat.eof())
			return false;

		string com;
		mat >> com;
		mat >> com;
		if (load != 0) {
			Graph* new_graph = new MatrixGraph(1, stoi(com));
			graph = new_graph;
			load = 0;
		}
		else
			graph = new MatrixGraph(1, stoi(com));
		load = 1;
		getline(mat, com);

		//control with vertex num
		int i;
		string temp;
		for (i = 0; i < graph->getSize(); i++) {
			getline(mat, com);

			int j = 0;
			for (int k = 0; k < com.length(); k++) {
				if (com[k] != ' ')
					temp.push_back(com[k]);
				else {
					graph->insertEdge(i, j, stoi(temp));
					temp.clear();
					j++;
				}
			}
			graph->insertEdge(i, j, stoi(temp));
			temp.clear();
		}
	}
	else
		return false;

	return true;
}

bool Manager::PRINT()	
{
	if (graph == nullptr)
		return false;
	return graph->printGraph(&fout);
}

bool Manager::mBFS(string option, int vertex)	
{
	if (graph == NULL)
		return false;
	return BFS(graph, option, vertex, &fout);
}

bool Manager::mDFS(string option, int vertex)
{
	if (graph == NULL)
		return false;
	return DFS(graph, option, vertex, &fout);
}

bool Manager::mDIJKSTRA(string option, int vertex)
{
	if (graph == NULL)
		return false;
	return Dijkstra(graph, option, vertex, &fout);
}

bool Manager::mKRUSKAL()
{
	if (graph == NULL)
		return false;
	return Kruskal(graph, &fout);
}

bool Manager::mBELLMANFORD(string option, int s_vertex, int e_vertex)
{
	return Bellmanford(graph, option, s_vertex, e_vertex, &fout);
}

bool Manager::mFLOYD(string option)
{
	if (graph == NULL)
		return false;
	return FLOYD(graph, option, &fout);
}

bool Manager::mKwangWoon(int vertex)
{
	return KWANGWOON(graph, vertex, &fout);
}

void Manager::printErrorCode(int n)
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


