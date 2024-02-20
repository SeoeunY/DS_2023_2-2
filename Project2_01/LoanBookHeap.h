#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;
    int size;

public:
    LoanBookHeap() {
        this->root = NULL;
        size = 0;
    }
    ~LoanBookHeap() {
        if (root == NULL)
            return;
        deallocate(root);
        this->root = NULL;
        size = 0;
    }

    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    LoanBookHeapNode* getRoot() { return root; }
    int getSize() { return size; }
    void reduceSize() { size--; }

    void heapifyUp(LoanBookHeapNode* pN);//insert
    void heapifyDown(LoanBookHeapNode* pN);//delete

    bool Insert(LoanBookData* data);

    void deallocate(LoanBookHeapNode* curNode) {
        if (curNode != NULL) {
            deallocate(curNode->getLeftChild());
            deallocate(curNode->getRightChild());
            delete curNode;
        }
    };
};
