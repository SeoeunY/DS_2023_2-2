#pragma once
#include <string>
using namespace std;

class TermsBSTNode
{
private:
	string name;
	string date1;
	string date2;
	int age;

	TermsBSTNode* left;
	TermsBSTNode* right;


public:
	TermsBSTNode() {
		this->name = "";
		this->date1 = "";
		this->date2 = "";
		this->age = 0;

		this->left = NULL;
		this->right = NULL;
	}
	~TermsBSTNode() {
		this->name = "";
		this->date1 = "";
		this->date2 = "";
		this->age = 0;

		this->left = NULL;
		this->right = NULL;
	}

	TermsBSTNode* getLeft() { return left; }
	TermsBSTNode* getRight() { return right; }
	void setLeft(TermsBSTNode* left) { this->left = left; }
	void setRight(TermsBSTNode* right) { this->right = right; }

	void setValue(string name, string date1, string date2, int age) {
		this->name = name;
		this->date1 = date1;
		this->date2 = date2;
		this->age = age;
	}
	string getName() { return name; }
	int getAge() { return age; }
	string getD1() { return date1; }
	string getD2() { return date2; }
};