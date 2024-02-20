#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager{	
private:
	Graph* graph;	
	ofstream fout;	
	int load;

public:
	Manager();	
	~Manager();	

	void run(const char * command_txt);
	
	bool LOAD(string filename);	
	bool PRINT();	
	bool mBFS(string option, int vertex);
	bool mDFS(string option, int vertex);
	bool mDIJKSTRA(string option, int vertex);
	bool mKRUSKAL();	
	bool mBELLMANFORD(string option, int s_vertex, int e_vertex);
	bool mFLOYD(string option);
	bool mKwangWoon(int vertex);
	void printErrorCode(int n); 
};

#endif