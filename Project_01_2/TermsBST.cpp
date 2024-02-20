#include "TermsBST.h"

TermsBST::TermsBST() : root(nullptr)
{
	size = 0;
}
TermsBST::~TermsBST()
{
	size = 0;
	root = NULL;
}

void TermsBST::setRoot(TermsBSTNode* node) {
	root = node;
}

TermsBSTNode* TermsBST::getRoot()
{
	return root;
}

int TermsBST::getSize() {
	return size;
}

// insert
void TermsBST::insert(string name, string date1, string date2, int age) {
	size++;
	TermsBSTNode* curNode = root;
	while (1) {
		if (root == NULL) {
			TermsBSTNode* node = new TermsBSTNode;
			node->setValue(name, date1, date2, age);
			root = node;
			break;
		}
		else {
			if (curNode->getD2() > date2) {
				if (curNode->getLeft() == NULL) {
					TermsBSTNode* newNode = new TermsBSTNode;
					newNode->setValue(name, date1, date2, age);
					curNode->setLeft(newNode);
					break;
				}
				else
					curNode = curNode->getLeft();
			}
			else if (curNode->getD2() <= date2) {
				if (curNode->getRight() == NULL) {
					TermsBSTNode* newNode = new TermsBSTNode;
					newNode->setValue(name, date1, date2, age);
					curNode->setRight(newNode);
					break;
				}
				else
					curNode = curNode->getRight();
			}
		}
	}
}

void TermsBST::search(string name) {
	TermsBSTNode* curNode = root;
	TermsBSTNode* parent = NULL;
	while (curNode != NULL) {
		if (curNode->getName() == name) {
			//delete
			deleteNode(curNode, parent);
			break;
		}
		else if (curNode->getName() > name) {
			parent = curNode;
			curNode = curNode->getLeft();
		}
		else if (curNode->getName() < name) {
			parent = curNode;
			curNode = curNode->getRight();
		}
	}
}

void TermsBST::deleteNode(TermsBSTNode* curNode, TermsBSTNode* parent) {
	size--;
	//degree 0 
	if (curNode->getLeft() == NULL && curNode->getRight() == NULL) {
		if (curNode == root) {
			delete root;
			root = NULL;
			return;
		}
		else {
			if (parent->getLeft() == curNode) {
				delete curNode;
				curNode = NULL;
				parent->setLeft(NULL);
				return;
			}
			else if (parent->getRight() == curNode) {
				delete curNode;
				curNode = NULL;
				parent->setRight(NULL);
				return;
			}
		}
	}

	//degree 1
	else if (curNode->getLeft() == NULL || curNode->getRight() == NULL) {
		if (curNode == root) {
			if (root->getLeft() != NULL) {
				TermsBSTNode* temp = root->getLeft();
				delete root;
				root = temp;
				return;
			}
			else {
				TermsBSTNode* temp = root->getRight();
				delete root;
				root = temp;
				return;
			}
		}
		else {
			if (parent->getLeft() == curNode) {
				if (curNode->getLeft() != NULL) {
					parent->setLeft(curNode->getLeft());
					delete curNode;
					curNode = NULL;
					return;
				}
				else {
					parent->setLeft(curNode->getRight());
					delete curNode;
					curNode = NULL;
					return;
				}
			}
			else {//parent->getRight()==curNode
				if (curNode->getLeft() != NULL) {
					parent->setRight(curNode->getLeft());
					delete curNode;
					curNode = NULL;
					return;
				}
				else {
					parent->setRight(curNode->getRight());
					delete curNode;
					curNode = NULL;
					return;
				}
			}
		}
	}

	//degree 2
	else if (curNode->getLeft() != NULL && curNode->getRight() != NULL) {
		TermsBSTNode* rsmall = curNode->getRight();
		TermsBSTNode* rsmallp = curNode;

		if (rsmall->getLeft() == NULL) {
			if (curNode == root) {
				rsmall->setLeft(root->getLeft());
				root = rsmall;
				delete curNode;
				curNode = NULL;
				return;
			}
			else {
				rsmall->setLeft(curNode->getLeft());
				if (parent->getLeft() == curNode)
					parent->setLeft(rsmall);
				else
					parent->setRight(rsmall);
				delete curNode;
				curNode = NULL;
				return;
			}
		}
		else {//rsmall->getLeft()!=NULL
			while (rsmall->getLeft() != NULL) {
				rsmallp = rsmall;
				rsmall = rsmall->getLeft();
			}

			if (curNode == root) {
				if (rsmall->getRight() == NULL) {
					rsmallp->setLeft(NULL);
				}
				else {
					rsmallp->setLeft(rsmall->getRight());
				}
				rsmall->setLeft(curNode->getLeft());
				rsmall->setRight(curNode->getRight());
				delete curNode;
				curNode = NULL;
				root = rsmall;
				return;
			}
			else {
				if (rsmall->getRight() == NULL) {
					rsmallp->setLeft(NULL);
				}
				else {
					rsmallp->setLeft(rsmall->getRight());
				}
				rsmall->setLeft(curNode->getLeft());
				rsmall->setRight(curNode->getRight());
				parent->setRight(rsmall);
				delete curNode;
				curNode = NULL;
				return;
			}
		}
	}
}

void TermsBST::POST(TermsBSTNode* curNode, string date, TermsBSTNode* parent) {
	if (curNode == NULL)
		return;
	POST(curNode->getLeft(), date, curNode);
	POST(curNode->getRight(), date, curNode);

	if (curNode->getD2() < date)
		deleteNode(curNode, parent);
}

void TermsBST::deallocate(TermsBSTNode* curNode) {
	if (curNode == nullptr)
		return;
	deallocate(curNode->getLeft());
	deallocate(curNode->getRight());
	TermsBSTNode* delNode = curNode;
	delete delNode;
}