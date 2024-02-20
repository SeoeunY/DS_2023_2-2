#pragma once
#include "NameBSTNode.h"

class NameBST
{
private:
	NameBSTNode* root;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();

	// insert
	void insert(string name, string date1, string date2, int age, char term);
	// search
	// print
	// delete
	void deleteNode(NameBSTNode* curNode, NameBSTNode* parent);

	void POST(NameBSTNode* curNode, string name, NameBSTNode* parent);

	void deallocate(NameBSTNode* curNode);
};