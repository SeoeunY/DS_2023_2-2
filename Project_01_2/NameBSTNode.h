#pragma once
#include <string>
using namespace std;

class NameBSTNode
{
private:
	string name, date1, date2;
	int age;
	char term;
	NameBSTNode* left;
	NameBSTNode* right;


public:
	NameBSTNode() {
		name = "";
		date1 = "";
		date2 = "";
		age = 0;
		term = NULL;
		left = NULL;
		right = NULL;
	}
	~NameBSTNode() {
		name = "";
		date1 = "";
		date2 = "";
		age = 0;
		term = NULL;
		left = NULL;
		right = NULL;
	}

	void setValue(string name, string date1, string date2, int age, char term) {
		this->name = name;
		this->date1 = date1;
		this->date2 = date2;
		this->age = age;
		this->term = term;
	}
	string getName() { return name; }
	string getD1() { return date1; }
	string getD2() { return date2; }
	int getAge() { return age; }
	char getTerm() { return term; }

	NameBSTNode* getLeft() { return left; }
	NameBSTNode* getRight() { return right; }
	void setLeft(NameBSTNode* left) { this->left = left; }
	void setRight(NameBSTNode* right) { this->right = right; }
};