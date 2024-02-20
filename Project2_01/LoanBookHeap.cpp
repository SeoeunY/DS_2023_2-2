#include "LoanBookHeap.h"
#include <stack>
//heap insert
void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    LoanBookHeapNode* curNode = pN;
    LoanBookHeapNode* parent = pN->getParent();

    if (parent == NULL)
        return;

    while (parent != NULL) {
        if (parent->getBookData()->getName() > curNode->getBookData()->getName()) {
            LoanBookData* temp = parent->getBookData();
            parent->setBookData(curNode->getBookData());
            curNode->setBookData(temp);

            curNode = parent;
            parent = parent->getParent();
        }
        else
            break;
    }
}

//heap delete
//pN=root
//pN은 새로 들어온 노드
void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    if (pN == NULL)
        return;

    LoanBookHeapNode* curNode = pN;
    LoanBookHeapNode* Lchild = pN->getLeftChild();
    LoanBookHeapNode* Rchild = pN->getRightChild();
    if (Lchild == NULL)
        return;

    while (Lchild != NULL || Rchild != NULL) {
        if (Lchild != NULL && Rchild != NULL) {//자식노드 2개
            if (Lchild->getBookData()->getName() < Rchild->getBookData()->getName()) {
                if (Lchild->getBookData()->getName() < curNode->getBookData()->getName()) {
                    //left랑 swap
                    LoanBookData* temp = Lchild->getBookData();
                    Lchild->setBookData(curNode->getBookData());
                    curNode->setBookData(temp);

                    curNode = Lchild;
                    Lchild = curNode->getLeftChild();
                    Rchild = curNode->getRightChild();
                }
                else
                    break;
            }
            else {
                if (Rchild->getBookData()->getName() < curNode->getBookData()->getName()) {
                    //right랑 swap
                    LoanBookData* temp = Rchild->getBookData();
                    Rchild->setBookData(curNode->getBookData());
                    curNode->setBookData(temp);

                    curNode = Rchild;
                    Lchild = curNode->getLeftChild();
                    Lchild = curNode->getLeftChild();
                    Rchild = curNode->getRightChild();
                }
                else
                    break;
            }
        }
        else if (Lchild != NULL) {
            if (Lchild->getBookData()->getName() < curNode->getBookData()->getName()) {
                LoanBookData* temp = Lchild->getBookData();
                Lchild->setBookData(curNode->getBookData());
                curNode->setBookData(temp);
                break;
            }
            else
                break;
        }
        else {//Rchild!=NULL
            if (Rchild->getBookData()->getName() < curNode->getBookData()->getName()) {
                LoanBookData* temp = Rchild->getBookData();
                Rchild->setBookData(curNode->getBookData());
                curNode->setBookData(temp);
                break;
            }
            else
                break;
        }
    }

}

bool LoanBookHeap::Insert(LoanBookData* data) {
    size++;
    int num = size;
    stack<int> s;
    int a = 0;
    while (num != 0) {
        a = num % 2;
        s.push(a);
        num /= 2;
    }

    LoanBookHeapNode* parent = getRoot();
    LoanBookHeapNode* prev = NULL;
    s.pop();
    while (s.empty() != true && parent != NULL) {
        a = s.top();
        s.pop();
        if (a == 0) {
            prev = parent;
            parent = parent->getLeftChild();
        }
        else {
            prev = parent;
            parent = parent->getRightChild();
        }
    }

    parent = prev;
    if (parent == NULL) {
        LoanBookHeapNode* newNode = new LoanBookHeapNode;
        newNode->setBookData(data);
        root = newNode;
    }
    else if (parent->getLeftChild() == NULL) {//left insert
        LoanBookHeapNode* newNode = new LoanBookHeapNode;
        newNode->setBookData(data);
        parent->setLeftChild(newNode);
        newNode->setParent(parent);
        heapifyUp(newNode);
    }
    else {//right insert
        LoanBookHeapNode* newNode = new LoanBookHeapNode;
        newNode->setBookData(data);
        parent->setRightChild(newNode);
        newNode->setParent(parent);
        heapifyUp(newNode);
    }

    return true;
}