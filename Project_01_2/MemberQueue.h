#pragma once
#include "MemberQueueNode.h"

class MemberQueue
{
private:
	MemberQueueNode* front1;
	MemberQueueNode* rear;
	int size;

public:
	MemberQueue();
	~MemberQueue();

	bool empty();
	bool full();
	bool push(string name, int age, string date, char term);
	MemberQueueNode* pop();
	MemberQueueNode* front();

	void deallocate();
};

