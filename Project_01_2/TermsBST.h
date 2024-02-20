#pragma once
#include "TermsBSTNode.h"

class TermsBST
{
private:
	TermsBSTNode* root;
	int size;

public:
	TermsBST();
	~TermsBST();

	void setRoot(TermsBSTNode* node);
	TermsBSTNode* getRoot();
	int getSize();

	// insert
	void insert(string name, string date1, string date2, int age);
	void search(string name);
	// delete
	void deleteNode(TermsBSTNode* curNode, TermsBSTNode* parent);
	void POST(TermsBSTNode* curNode, string date, TermsBSTNode* parent);

	void deallocate(TermsBSTNode* curNode);
};