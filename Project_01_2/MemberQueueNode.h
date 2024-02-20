#include <string>
using namespace std;
#pragma once

class MemberQueueNode
{
private:
	string name;
	int age;
	string date;
	char term;

	MemberQueueNode* next;
	MemberQueueNode* prev;

public:
	MemberQueueNode() {
		name = "";
		age = 0;
		date = "";
		next = NULL;
		prev = NULL;
	}
	~MemberQueueNode() {
		name = "";
		age = 0;
		date = "";
		next = NULL;
		prev = NULL;
	}

	void setValue(string name, int age, string date, char term) {
		this->name = name;
		this->age = age;
		this->date = date;
		this->term = term;
	}
	//getValue
	string getName() { return name; }
	string getDate() { return date; }
	int getAge() { return age; }
	char getTerm() { return term; }

	void setNext(MemberQueueNode* nextNode) { this->next = nextNode; }
	MemberQueueNode* getNext() { return this->next; }
	void setPrev(MemberQueueNode* prevNode) { this->prev = prevNode; }
	MemberQueueNode* getPrev() { return this->prev; }

};