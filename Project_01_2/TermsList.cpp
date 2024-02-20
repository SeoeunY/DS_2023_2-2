#include "TermsList.h"
#include "TermsBST.h"

TermsLIST::TermsLIST() : head(nullptr)
{
	head = nullptr;
	tail = nullptr;
	for (int i = 0; i < 4; i++) {
		arr[i] = 0;
	}
}
TermsLIST::~TermsLIST()
{
	//deallocate
}

TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert
void TermsLIST::insert(char term, string name, string date1, string date2, int age) {
	int num = term - 'A';
	if (arr[num] == 0) {//첫 삽입
		arr[num]++;
		TermsListNode* newNode = new TermsListNode;
		TermsBST* newBST = new TermsBST;
		newNode->setBST(newBST);
		newNode->setValue(1, term);
		if (head == nullptr) {
			head = tail = newNode;
			newNode->setNext(NULL);
		}
		else {
			tail->setNext(newNode);
			tail = newNode;
		}
		newBST->insert(name, date1, date2, age);
	}
	else {//이미 노드 존재
		TermsListNode* node = head;
		while (node != NULL) {
			if (node->getTerm() == term) {
				int number = node->getNum();
				node->setValue(++number, term);
				TermsBST* cur = node->getTermBST();
				cur->insert(name, date1, date2, age);
				break;
			}
			else
				node = node->getNext();
		}

	}
}

//delete TermsLIST Node
void TermsLIST::deleteNode(char term) {
	TermsListNode* curNode = head;

	while (curNode != NULL) {
		if (curNode->getTerm() == term)
			break;
		curNode = curNode->getNext();
	}

	if (curNode == head) {
		if (curNode->getNext() != NULL) {
			head = curNode->getNext();
			delete curNode;
		}
		else {
			delete curNode;
			head = tail = NULL;
		}
	}
	if (curNode->getNext() == NULL) {
		TermsListNode* prev = head;
		while (prev->getNext() != curNode) {
			prev = prev->getNext();
		}
		tail = prev;
		prev->setNext(NULL);
		delete curNode;
	}
	else {
		TermsListNode* prev = head;
		while (prev->getNext() != curNode) {
			prev = prev->getNext();
		}
		prev->setNext(curNode->getNext());
		delete curNode;
	}
}

void TermsLIST::deallocate(TermsListNode* curNode) {
	while (curNode != NULL) {
		TermsListNode* del = curNode;
		del->getTermBST()->deallocate(del->getTermBST()->getRoot());
		curNode = curNode->getNext();
		delete del;
	}
}