#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>
#include <queue>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;
    SelectionTreeNode* arr[8];

public:
    SelectionTree(ofstream* fout) {
        this->root = NULL;
        this->fout = fout;
        
        for (int i = 0; i < 8; i++)
            arr[i] = new SelectionTreeNode;

        //ºó Æ®¸® ±¸Ãà
        queue<SelectionTreeNode*>q;
        SelectionTreeNode* newNode = new SelectionTreeNode;
        root = newNode;
        q.push(newNode);
        int level = 0;

        while (q.empty() != true) {
            if (level == 7)
                break;
            SelectionTreeNode* curNode = q.front();
            q.pop();
            SelectionTreeNode* Lchild = new SelectionTreeNode;
            SelectionTreeNode* Rchild = new SelectionTreeNode;

            curNode->setLeftChild(Lchild);
            curNode->setRightChild(Rchild);
            Lchild->setParent(curNode);
            Rchild->setParent(curNode);
            q.push(Lchild);
            q.push(Rchild);
            level++;
        }

        arr[0] = root->getLeftChild()->getLeftChild()->getLeftChild();
        LoanBookHeap* newHeap0 = new LoanBookHeap;
        arr[0]->setHeap(newHeap0);
        arr[1] = root->getLeftChild()->getLeftChild()->getRightChild();
        LoanBookHeap* newHeap1 = new LoanBookHeap;
        arr[1]->setHeap(newHeap1);
        arr[2]= root->getLeftChild()->getRightChild()->getLeftChild();
        LoanBookHeap* newHeap2 = new LoanBookHeap;
        arr[2]->setHeap(newHeap2);
        arr[3] = root->getLeftChild()->getRightChild()->getRightChild();
        LoanBookHeap* newHeap3 = new LoanBookHeap;
        arr[3]->setHeap(newHeap3);
        arr[4] = root->getRightChild()->getLeftChild()->getLeftChild();
        LoanBookHeap* newHeap4 = new LoanBookHeap;
        arr[4]->setHeap(newHeap4);
        arr[5] = root->getRightChild()->getLeftChild()->getRightChild();
        LoanBookHeap* newHeap5 = new LoanBookHeap;
        arr[5]->setHeap(newHeap5);
        arr[6] = root->getRightChild()->getRightChild()->getLeftChild();
        LoanBookHeap* newHeap6 = new LoanBookHeap;
        arr[6]->setHeap(newHeap6);
        arr[7] = root->getRightChild()->getRightChild()->getRightChild();
        LoanBookHeap* newHeap7 = new LoanBookHeap;
        arr[7]->setHeap(newHeap7);
    }
    ~SelectionTree() {

        for (int i = 0; i < 8; i++) {
            delete arr[i]->getHeap();
            arr[i]->setHeap(NULL);
        }

        deallocate(root);

    }

    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    SelectionTreeNode* getRoot() { return root; }

    bool Insert(LoanBookData* newData);
    bool Delete();
    bool printBookData(int bookCode);

    void deallocate(SelectionTreeNode* curNode) {
        if (curNode != NULL) {
            deallocate(curNode->getLeftChild());
            deallocate(curNode->getRightChild());
            delete curNode;
        }
    }
};