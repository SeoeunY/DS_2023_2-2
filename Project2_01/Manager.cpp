#include "Manager.h"

void Manager::run(const char* command) 
{
	fin.open(command);
	if(!fin)//fail to open command.txt file
	{
		flog << "File Open Error" << endl;
		return;
	}

	string comm;//command
	//flog.open("log.txt");//log txt file open
	flog.open("log.txt", ios::app);


	bool suc;

	while (!fin.eof())//command.txt file
	{
		fin >> comm;
		if (comm == "LOAD") {
			suc = LOAD();
			if (suc)
				printSuccessCode(comm);
			else
				printErrorCode(100);
		}
		else if (comm == "ADD") {
			string s;
			getline(fin, s);

			suc = ADD(s);
			if (suc == false)
				printErrorCode(200);
		}
		else if (comm == "SEARCH_BP") {
			string s;
			getline(fin, s);
			bool exception = false;
			if (s[0] == '\0')//exception
				printErrorCode(300);
			else {
				string start, end, token;
				int num = 0;
				for (int i = 1; i < s.length()+1; i++) {
					if (s[i] == '\t' || s[i] == '\0') {
						if (num == 0) {
							start = token;
							token.clear();
							num++;
							if (s[i] == '\0')
								break;
						}
						else if (num == 1) {
							end = token;
							token.clear();
							num++;
							if (s[i] == '\0')
								break;
						}
						else {
							printErrorCode(300);
							exception = true;
						}
					}
					else
						token.push_back(s[i]);
				}
				if (exception == true)
					continue;

				if (num == 1) {//search book
					suc = SEARCH_BP_BOOK(start);
					if (suc == false)
						printErrorCode(300);
				}
				else if (num == 2) {//search range
					suc = SEARCH_BP_RANGE(start, end);
					if (suc == false)
						printErrorCode(300);
				}
			}
		}
		else if (comm == "PRINT_BP") {
			suc = PRINT_BP();
			if (suc == false)
				printErrorCode(400);
		}
		else if (comm == "PRINT_ST") {
			fin >> comm;
			suc = stree->printBookData(stoi(comm));
			if (suc == false)
				printErrorCode(500);
		}
		else if (comm == "DELETE") {
			suc = stree->Delete();
			if (suc == true)
				printSuccessCode(comm);
			else
				printErrorCode(600);
		}
		else if (comm == "EXIT") {
			printSuccessCode(comm);
			delete this->bptree;
			delete this->stree;
				break;
		}
		else
			continue;
	}	
	fin.close();
	return;
}

bool Manager::LOAD()
{
	ifstream data;
	data.open("loan_book.txt");
	if (!data || load == true)
		return false;
	
	load = true;
	string name, author;
	int code, year, loan_count;
	while (!data.eof()) {
		string s;
		getline(data, s);
		string token;
		int k = 0;

		if (s[0] == '\0')
			break;

		//data parsing
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == '\t'||s[i]=='\0') {
				if (k == 0)//name
					name = token;
				else if (k == 1)
					code = stoi(token);
				else if (k == 2)
					author = token;
				else if (k == 3)
					year = stoi(token);
				k++;
				token.clear();
			}
			else {
				token.push_back(s[i]);
			}
		}
		
		loan_count = stoi(token);
		LoanBookData* data_node = new LoanBookData;
		data_node->setBookData(name, code, author, year, loan_count);

		if (code == 0&& loan_count ==3) {
			stree->Insert(data_node);
			//selectiontree
		}
		else if(code==100&& loan_count ==3){
			stree->Insert(data_node);
			//selectiontree
		}
		else if (code == 200 && loan_count == 3) {
			stree->Insert(data_node);
			//selectiontree
		}
		else if (code == 300 && loan_count == 4) {
			stree->Insert(data_node);
			//selectiontree
		}
		else if (code == 400 && loan_count == 4) {
			stree->Insert(data_node);
			//selectiontree
		}
		else if (code == 500 && loan_count == 2) {
			stree->Insert(data_node);
			//selectiontree
		}
		else if (code == 600 && loan_count == 2) {
			stree->Insert(data_node);
			//selectiontree
		}
		else if (code == 700 && loan_count == 2) {
			stree->Insert(data_node);
			//selectiontree
		}
		else {//insert b+-tree
			bptree->Insert(data_node, stree);
		}
	}

	return true;
}

bool Manager::ADD(string s)
{
	string name, author, token;
	int k = 0;
	int code, year;

	//exception
	for (int i = 1; i < s.length(); i++) {
		if (s[i] == '\t' || s[i] == '\0')
			k++;
	}
	if (k != 3)
		return false;

	//data parsing
	k = 0;
	for (int i = 1; i < s.length(); i++) {
		if (s[i] == '\t' || s[i] == '\0') {
			if (k == 0)//name
				name = token;
			else if (k == 1)
				code = stoi(token);
			else if (k == 2)
				author = token;
			k++;
			token.clear();
		}
		else {
			token.push_back(s[i]);
		}
	}
	year = stoi(token);

	LoanBookData* data_node = new LoanBookData;
	data_node->setBookData(name, code, author, year, 0);
	bptree->Insert(data_node, stree);

	flog << "========ADD========" << endl;
	flog << name << "/";
	if (code == 0)
		flog << "000";
	else
		flog << code;
	flog << "/" << author << "/" << year << endl;
	flog << "====================" << endl << endl;

	return true;
}

bool Manager::SEARCH_BP_BOOK(string book) 
{
	BpTreeNode* curNode = bptree->searchDataNode(book);

	auto iter = curNode->getDataMap()->begin();
	while (iter != curNode->getDataMap()->end()) {
		if (iter->first == book) {
			//print
			flog << "========SEARCH_BP========" << endl;
			flog << iter->second->getName() << "/";
			if (iter->second->getCode() == 0)
				flog << "000";
			else
				flog << iter->second->getCode();
			flog << "/" << iter->second->getAuthor() << "/" << iter->second->getYear() << "/" << iter->second->getLoanCount() << endl;
			flog << "=======================" << endl << endl;
			return true;
		}
		else
			iter++;
	}

	return false;
}

bool Manager::SEARCH_BP_RANGE(string s, string e) 
{
	bool suc;
	suc = bptree->searchRange(s, e);

	return suc;
}

bool Manager::PRINT_BP() 
{
	if (bptree->getRoot() == NULL)
		return false;

	BpTreeNode* curNode = bptree->getRoot();

	while (curNode->getMostLeftChild() != NULL)
		curNode = curNode->getMostLeftChild();

	//curNode==most left data node

	flog << "========PRINT_BP========" << endl;
	while (curNode->getNext() != NULL) {
		auto iter = curNode->getDataMap()->begin();
		while (iter != curNode->getDataMap()->end()) {
			flog << iter->second->getName() << "/";
			if (iter->second->getCode() == 0)
				flog << "000";
			else
				flog << iter->second->getCode();
			flog << "/" << iter->second->getAuthor() << "/" << iter->second->getYear() << "/" << iter->second->getLoanCount() << endl;
			iter++;
		}
		curNode = curNode->getNext();
	}
	//last datanode
	auto iter = curNode->getDataMap()->begin();
	while (iter != curNode->getDataMap()->end()) {
		flog << iter->second->getName() << "/";
		if (iter->second->getCode() == 0)
			flog << "000";
		else
			flog << iter->second->getCode();
		flog << "/" << iter->second->getAuthor() << "/" << iter->second->getYear() << "/" << iter->second->getLoanCount() << endl;
		iter++;
	}
	flog << "====================" << endl << endl;

	return true;
}

bool Manager::PRINT_ST() 
{
	return true;
}

bool Manager::DELETE() 
{
	return true;
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT
	flog << "========ERROR========" << endl;
	flog << n << endl;
	flog << "====================" << endl << endl;
}

void Manager::printSuccessCode(string a) {//SUCCESS CODE PRINT 
	flog << "========" << a << "========" << endl;
	flog << "Success" << endl;
	flog << "====================" << endl << endl;
}

