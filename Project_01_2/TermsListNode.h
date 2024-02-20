#pragma once
#include <iostream>
#include "NameBST.h"
#include "TermsBST.h"
using namespace std;

class TermsListNode
{
private:
	int num;
	char term;
	TermsListNode* next;
	TermsBST* Term_BST;

public:
	TermsListNode() {
		num = 0;
		next = NULL;
		Term_BST = NULL;
	}
	~TermsListNode() {
		num = 0;
		next = NULL;
		Term_BST = NULL;
	}

	void setValue(int num, char term) {
		this->num = num;
		this->term = term;
	}
	int getNum() { return num; }
	char getTerm() { return term; }
	void increaseNum() { num++; }
	void setNext(TermsListNode* next) { this->next = next; }
	TermsListNode* getNext() { return next; }

	void setBST(TermsBST* BST) { Term_BST = BST; }
	TermsBST* getTermBST() { return Term_BST; }
};