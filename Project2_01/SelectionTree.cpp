#include "SelectionTree.h"
#include <stack>
#include <queue>
#include <map>

bool SelectionTree::Insert(LoanBookData* newData) {
	int code = newData->getCode();
	//알맞은 자리 찾아서 heap insert
	LoanBookData* a = NULL;
	LoanBookData* b = NULL;

	if (code != 0) {
		code /= 100;
	}

	if (arr[code]->getHeap()->getSize() > 0) {
		a = arr[code]->getHeap()->getRoot()->getBookData();
	}
	
	arr[code]->getHeap()->Insert(newData);
	arr[code]->setBookData(arr[code]->getHeap()->getRoot()->getBookData());
	b = arr[code]->getHeap()->getRoot()->getBookData();

	if (a == b)
		return true;

	arr[code]->setBookData(arr[code]->getHeap()->getRoot()->getBookData());
	//selection tree 재정렬
	SelectionTreeNode* curNode = arr[code];
	SelectionTreeNode* parent = arr[code]->getParent();
	SelectionTreeNode* sibling;

	while (parent != NULL) {
		if (parent->getLeftChild() == curNode)
			sibling = parent->getRightChild();
		else
			sibling = parent->getLeftChild();

		string curName = curNode->getBookData()->getName();
		if (sibling->getBookData() == NULL) {
			parent->setBookData(curNode->getBookData());
			curNode = parent;
			parent = parent->getParent();
			continue;
		}

		string sibName = sibling->getBookData()->getName();
		if (curName < sibName) {
			parent->setBookData(curNode->getBookData());
		}
		else {
			parent->setBookData(sibling->getBookData());
		}
		curNode = parent;
		parent = parent->getParent();
	}

	return true;
}

bool SelectionTree::Delete() {
	if (root->getBookData() == NULL)//selection tree null
		return false;

	SelectionTreeNode* curNode = root;
	while (curNode->getHeap() == NULL) {//삭제해야 할 heap 탐색
		if (curNode->getLeftChild()->getBookData() == curNode->getBookData()) {
			curNode->setBookData(NULL);
			curNode = curNode->getLeftChild();
		}
		else {
			curNode->setBookData(NULL);
			curNode = curNode->getRightChild();
		}
	}
	//curNode=delete할 heap 저장되어 있는 selection tree node

	curNode->setBookData(NULL);
	int size = curNode->getHeap()->getSize();
	
	LoanBookHeapNode* cur = curNode->getHeap()->getRoot();
	LoanBookHeapNode* prev = NULL;

	if (size == 1) {
		LoanBookHeapNode* delheap = curNode->getHeap()->getRoot();
		delete delheap;
		curNode->getHeap()->setRoot(NULL);
		//NULL로 selection tree 재정렬
		//cur==null
	}
	else {
		stack<int> s;
		int a = 0;
		while (size != 0) {
			a = size % 2;
			s.push(a);
			size /= 2;
		}

		s.pop();
		while (s.empty() != true && cur != NULL) {
			a = s.top();
			s.pop();
			if (a == 0) {
				prev = cur;
				cur = cur->getLeftChild();
			}
			else {
				prev = cur;
				cur = cur->getRightChild();
			}
		}

		//cur=새로 root가 될 노드

		LoanBookHeapNode* rooot = curNode->getHeap()->getRoot();//new root
		rooot->setBookData(cur->getBookData());

		if (prev->getLeftChild() == cur)
			prev->setLeftChild(NULL);
		else
			prev->setRightChild(NULL);

		curNode->getHeap()->heapifyDown(curNode->getHeap()->getRoot());
		curNode->setBookData(curNode->getHeap()->getRoot()->getBookData());
		cur->setBookData(NULL);
		delete cur;
	}

	curNode->getHeap()->reduceSize();

	//selection tree 재정렬
	//SelectionTreeNode* curNode = arr[code];
	//curNode=delete할 heap 저장되어 있는 selection tree node
	SelectionTreeNode* parent=curNode->getParent();
	SelectionTreeNode* sibling;

	while (parent != NULL) {
		if (parent->getLeftChild() == curNode)
			sibling = parent->getRightChild();
		else
			sibling = parent->getLeftChild();
		//sibling 찾기

		if (curNode->getBookData() == NULL) {
			parent->setBookData(sibling->getBookData());
			curNode = parent;
			parent = parent->getParent();
			continue;
		}

		string curName = curNode->getBookData()->getName();
		if (sibling->getBookData() == NULL) {
			parent->setBookData(curNode->getBookData());
			curNode = parent;
			parent = parent->getParent();
			continue;
		}

		string sibName = sibling->getBookData()->getName();
		if (curName < sibName) {
			parent->setBookData(curNode->getBookData());
		}
		else {
			parent->setBookData(sibling->getBookData());
		}
		curNode = parent;
		parent = parent->getParent();
	}

	return true;
}

bool SelectionTree::printBookData(int bookCode) {
	bool suc = false;
	int check[8] = { 0,100,200,300,400,500,600,700 };
	for (int i = 0; i < 8; i++) {
		if (bookCode == check[i])
			suc = true;
	}
	
	if (suc == false)
		return false;
	
	LoanBookHeap* print;
	if (bookCode == 0) {
		//print 000
		print = arr[0]->getHeap();
	}
	else {
		bookCode /= 100;
		//print bookCode
		print = arr[bookCode]->getHeap();
	}


	map<string, LoanBookData*>m;
	queue<LoanBookHeapNode*>q;

	LoanBookHeapNode* curNode = print->getRoot();

	if (curNode == NULL)
		return false;

	q.push(curNode);

	while (q.size() != 0) {
		LoanBookHeapNode* now = q.front();
		q.pop();
		if (now->getLeftChild() != NULL)
			q.push(now->getLeftChild());
		if (now->getRightChild() != NULL)
			q.push(now->getRightChild());
		m.insert({ now->getBookData()->getName(),now->getBookData() });
	}//heap 다 들어가있겠징

	*fout << "========PRINT_ST========" << endl;
	for (auto iter = m.begin(); iter != m.end(); iter++) {
		*fout << iter->first << "/" << iter->second->getCode() << "/" << iter->second->getAuthor() << "/" << iter->second->getYear() << "/" << iter->second->getLoanCount() << endl;
	}
	*fout<<"========================="<<endl<<endl;

	return true;
}