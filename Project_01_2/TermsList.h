#pragma once
#include "TermsListNode.h"

class TermsLIST
{
private:
	TermsListNode* head;
	TermsListNode* tail;
	int arr[4];

public:
	TermsLIST();
	~TermsLIST();

	TermsListNode* getHead();



	// insert
	void insert(char term, string name, string date1, string date2, int age);

	void deleteNode(char term);

	void deallocate(TermsListNode* curNode);
};
