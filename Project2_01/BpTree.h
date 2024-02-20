#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include "SelectionTree.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <map>

class BpTree {
private:
	BpTreeNode* root;
	int			order;		// m children
	ofstream* fout;
public:
	BpTree(ofstream *fout, int order = 3) {
		root = NULL;
		this->order = order;
		this->fout = fout;
	}
	~BpTree() {
		BpTreeNode* curNode = root;
		while (curNode->getMostLeftChild() != NULL)
			curNode = curNode->getMostLeftChild();

		//remove data node
		while (curNode != NULL) {
			auto iter = curNode->getDataMap()->begin();
			
			curNode->getParent()->setMostLeftChild(NULL);
			while (iter != curNode->getDataMap()->end()) {
				delete iter->second;
				iter++;
			}

			BpTreeNode* delNode = curNode;
			curNode = curNode->getNext();
			delete delNode;
		}

		queue<BpTreeNode*>q;
		multimap<string,BpTreeNode*>m;
		q.push(root);
		curNode = root;
		while (q.size() != 0) {
			curNode = q.front();
			q.pop();
			if (curNode->getMostLeftChild() != NULL) {//curNode==index node
				q.push(curNode->getMostLeftChild());
				auto iter = curNode->getIndexMap()->begin();
				while (iter != curNode->getIndexMap()->end()) {
					q.push(iter->second);
					iter++;
				}
			}
			m.insert({ "a",curNode });
		}

		auto iter2 = m.begin();
		iter2++;
		auto iter_prev = m.begin();

		while (iter2 != m.end()) {
			delete iter_prev->second;
			iter_prev = iter2;
			iter2++;
		}

		root = NULL;
	}
	/* essential */
	bool		Insert(LoanBookData* newData, SelectionTree* stree);
	bool		excessDataNode(BpTreeNode* pDataNode);
	bool		excessIndexNode(BpTreeNode* pIndexNode);
	void		splitDataNode(BpTreeNode* pDataNode);
	void		splitIndexNode(BpTreeNode* pIndexNode);
	BpTreeNode* getRoot() { return root; }
	BpTreeNode* searchDataNode(string name);

	bool searchBook(string name);
	bool searchRange(string start, string end);


	void Delete(string name, SelectionTree* stree);

};

#endif
