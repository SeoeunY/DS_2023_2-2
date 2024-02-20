#include "NameBST.h"

NameBST::NameBST() : root(nullptr)
{
	root = nullptr;
}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot()
{
	return root;
}

// insert
void NameBST::insert(string name, string date1, string date2, int age, char term) {
	//while¹® µ¹ÀÚ
	NameBSTNode* curNode = root;
	while (1) {
		if (root == NULL) {
			NameBSTNode* node = new NameBSTNode;
			node->setValue(name, date1, date2, age, term);
			root = node;
			break;
		}
		else {
			if (curNode->getName() > name) {
				if (curNode->getLeft() == NULL) {
					NameBSTNode* newNode = new NameBSTNode;
					newNode->setValue(name, date1, date2, age, term);
					curNode->setLeft(newNode);
					break;
				}
				else {
					curNode = curNode->getLeft();
				}
			}
			else if (curNode->getName() < name) {
				if (curNode->getRight() == NULL) {
					NameBSTNode* newNode = new NameBSTNode;
					newNode->setValue(name, date1, date2, age, term);
					curNode->setRight(newNode);
					break;
				}
				else {
					curNode = curNode->getRight();
				}
			}
		}
	}
}

//delete
void NameBST::deleteNode(NameBSTNode* curNode, NameBSTNode* parent) {
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
				NameBSTNode* temp = root->getLeft();
				delete root;
				root = temp;
				return;
			}
			else {
				NameBSTNode* temp = root->getRight();
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
		NameBSTNode* rsmall = curNode->getRight();
		NameBSTNode* rsmallp = curNode;

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
				else {//rsmall->getRight()!=NULL
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

void NameBST::POST(NameBSTNode* curNode, string name, NameBSTNode* parent) {
	if (curNode == NULL)
		return;
	POST(curNode->getLeft(), name, curNode);
	POST(curNode->getRight(), name, curNode);

	if (curNode->getD2() < name)
		deleteNode(curNode, parent);
}

void NameBST::deallocate(NameBSTNode* curNode) {
	if (curNode == nullptr)
		return;
	deallocate(curNode->getLeft());
	deallocate(curNode->getRight());
	NameBSTNode* delNode = curNode;
	delete delNode;
}