	#include "MemberQueue.h"

MemberQueue::MemberQueue()
{
	this->front1 = NULL;//초기화
	this->rear = NULL;
	this->size = 0;
}
MemberQueue::~MemberQueue()
{
	this->front1 = NULL;//초기화
	this->rear = NULL;
	this->size = 0;
}

bool MemberQueue::empty()
{
	if (size == 0)
		return true;
	else
		return false;
}
bool MemberQueue::full()
{
	if (size == 100)
		return true;
	else
		return false;
}
bool MemberQueue::push(string name, int age, string date, char term)
{
	if (full() == true)
		return false;
	MemberQueueNode* newNode = new MemberQueueNode;
	newNode->setValue(name, age, date, term);

	if (empty() == true) {
		front1 = rear = newNode;
		size++;
	}
	else {
		rear->setNext(newNode);
		newNode->setPrev(rear);
		rear = newNode;
		size++;
	}
	return true;
}
MemberQueueNode* MemberQueue::pop()
{
	//main에서 사이즈 확인 후 pop 함수 호출
	MemberQueueNode* popNode = front1;
	if (size == 1) {
		rear = front1 = NULL;
	}
	else {
		front1 = front1->getNext();
	}
	size--;
	popNode->setNext(NULL);
	popNode->setPrev(NULL);
	return popNode;
}
MemberQueueNode* MemberQueue::front()
{
	return front1;
}

void MemberQueue::deallocate() {
	while (empty() == false) {
		pop();
	}
}