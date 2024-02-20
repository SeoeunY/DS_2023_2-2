#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
using namespace std;

class Manager
{
private:
	ifstream	fcmd;
	ofstream	flog;
	bool Load;//LOAD ÁøÀ§ÆÄ¾Ç
	MemberQueue q;
	TermsLIST T_list;
	NameBST Name_BST;

public:
	Manager();
	~Manager();

	void run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	bool LOAD();
	// ADD
	bool ADD(string name, string date, int age, char term);
	// QPOP
	bool QPOP();
	// SEARCH
	bool SEARCH(string name);
	// PRINT
	bool PRINT(string name);
	void PrintName(NameBSTNode* curNode);
	void PrintTerm(TermsBSTNode* curNode);
	// DELETE
	bool DELETE(string comm, string name);
};
