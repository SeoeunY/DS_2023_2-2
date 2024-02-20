#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData, SelectionTree* stree) {
	if (root == NULL) {//first insert
		BpTreeDataNode* dataNode = new BpTreeDataNode;
		dataNode->insertDataMap(newData->getName(),newData);
		root = dataNode;
	}
	else {
		BpTreeNode* curNode = searchDataNode(newData->getName());
		
		auto iter = curNode->getDataMap()->begin();
		bool update = false;

		while (iter != curNode->getDataMap()->end()) {
			if (iter->first == newData->getName()) {
				update = true;
				iter->second->updateCount();//update loan count
				delete newData;//deallocate
				if (iter->second->getCode() < 300 && iter->second->getLoanCount() == 3) {
					//delete from b+tree and insert to selection tree
					Delete(iter->first, stree);
				}
				else if (iter->second->getCode() < 500 && iter->second->getCode() > 299 && iter->second->getLoanCount() == 4) {
					//delete from b+tree and insert to selection tree
					Delete(iter->first, stree);
				}
				else if (iter->second->getCode() < 701 && iter->second->getCode() > 499 && iter->second->getLoanCount() == 2) {
					//delete from b+tree and insert to selection tree
					Delete(iter->first, stree);
				}
				break;
			}
			iter++;
		}

		if (update == false) {
			curNode->insertDataMap(newData->getName(), newData);
			if (excessDataNode(curNode) == true)
				splitDataNode(curNode);
		}
	}

	return true;
}

//크기 확인
bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

//크기 확인
bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {//3 element DataNode
	BpTreeDataNode* newNode = new BpTreeDataNode;

	auto iter = pDataNode->getDataMap()->begin();
	iter++;//middle
	string move_parent = iter->first;//name that move upward

	while (iter != pDataNode->getDataMap()->end()) {//newNode move data
		LoanBookData* data = iter->second;//book data
		newNode->insertDataMap(data->getName(), data);
		iter++;
	}
	//link datanode
	if (pDataNode->getNext() == NULL) {
		pDataNode->setNext(newNode);
		newNode->setPrev(pDataNode);
	}
	else {//양방향 연결
		newNode->setNext(pDataNode->getNext());
		pDataNode->getNext()->setPrev(newNode);
		pDataNode->setNext(newNode);
		newNode->setPrev(pDataNode);
	}
	
	//pDataNode element deletion
	iter = newNode->getDataMap()->begin();
	while (iter != newNode->getDataMap()->end()) {//delete element from pDataNode
		pDataNode->getDataMap()->erase(iter->first);
		iter++;
	}

	//insert at indexnode
	BpTreeNode* parentNode = pDataNode->getParent();
	if (parentNode == NULL) {
		BpTreeNode* newRoot = new BpTreeIndexNode;
		newRoot->insertIndexMap(move_parent, newNode);
		newRoot->setMostLeftChild(pDataNode);
		pDataNode->setParent(newRoot);
		newNode->setParent(newRoot);
		root = newRoot;
	}
	else {
		parentNode->insertIndexMap(move_parent, newNode);
		newNode->setParent(parentNode);
		if (excessIndexNode(pDataNode->getParent()) == true)
			splitIndexNode(pDataNode->getParent());
	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
	BpTreeNode* newNode = new BpTreeIndexNode;
	if (pIndexNode->getParent() != NULL) {
		auto iter3 = pIndexNode->getIndexMap()->rbegin();
		newNode->insertIndexMap(iter3->first, iter3->second);//newIndexNode (sibling with pIndexNode)
		iter3->second->setParent(newNode);

		auto iter = pIndexNode->getIndexMap()->begin();
		iter++;//middle
		iter->second->setParent(newNode);//양방향 연결
		newNode->setMostLeftChild(iter->second);

		pIndexNode->getParent()->insertIndexMap(iter->first, newNode);
		newNode->setParent(pIndexNode->getParent());

		//delete
		auto iter2 = pIndexNode->getIndexMap()->begin();
		iter2++;
		auto iter4 = pIndexNode->getIndexMap()->rbegin();
		pIndexNode->getIndexMap()->erase(iter4->first);
		pIndexNode->getIndexMap()->erase(iter2->first);

		//재귀 확인
		if (excessIndexNode(pIndexNode->getParent()) == true)
			splitIndexNode(pIndexNode->getParent());
	}
	else {//root split
		BpTreeIndexNode* newRoot = new BpTreeIndexNode;

		auto iter3 = pIndexNode->getIndexMap()->rbegin();//last
		newNode->insertIndexMap(iter3->first, iter3->second);//newIndexNode (sibling with pIndexNode)
		auto iter = pIndexNode->getIndexMap()->begin();
		iter++;//middle
		iter->second->setParent(newNode);//양방향 연결
		newNode->setMostLeftChild(iter->second);

		newRoot->insertIndexMap(iter->first, newNode);
		newRoot->setMostLeftChild(pIndexNode);
		root = newRoot;
		//역방향 연결
		pIndexNode->setParent(newRoot);
		newNode->setParent(newRoot);

		auto iter2 = pIndexNode->getIndexMap()->rbegin();
		iter2->second->setParent(newNode);

		auto iter4 = pIndexNode->getIndexMap()->begin();
		iter4++;
		pIndexNode->getIndexMap()->erase(iter2->first);
		pIndexNode->getIndexMap()->erase(iter4->first);
	}
}

BpTreeNode* BpTree::searchDataNode(string name) {
	BpTreeNode* pCur = root;

	while (pCur != NULL) {
		if (pCur->getMostLeftChild() == NULL) {//data node
			break;
		}
		else {//index node
			bool mappointer = false;
			auto iter = pCur->getIndexMap()->rbegin();
			while (iter != pCur->getIndexMap()->rend()) {
				BpTreeNode* next = iter->second;
				if (iter->first <= name) {
					pCur = next;
					mappointer = true;
					break;
				}
				iter++;
			}

			if (mappointer == false)
				pCur = pCur->getMostLeftChild();
		}
	}

	return pCur;
}

bool BpTree::searchBook(string name) {
	BpTreeNode* dataNode = searchDataNode(name);
	map<string, LoanBookData*>::iterator iter = dataNode->getDataMap()->begin();
	bool print = false;
	while (iter != dataNode->getDataMap()->end()) {
		if (iter->first == name) {
			print = true;
			*fout << "========SEARCH_BP========" << endl;
			*fout << iter->second->getName() << "/";
			if (iter->second->getCode() == 0)
				*fout << "000";
			else
				*fout << iter->second->getCode();
			*fout << "/" << iter->second->getAuthor() << "/" << iter->second->getYear() << "/" << iter->second->getLoanCount() << endl;
			*fout << "=======================" << endl;
		}
		else
			iter++;
	}

	if (print == false)
		return false;

	return true;
}

bool BpTree::searchRange(string start, string end) {
	char temp_end = end[0];
	temp_end++;
	string end_letter(1, temp_end);
	bool print = false;

	BpTreeNode* dataNode = searchDataNode(start);

	while (dataNode != NULL) {
		map<string, LoanBookData*>::iterator iter = dataNode->getDataMap()->begin();
		while (iter != dataNode->getDataMap()->end()) {
			if (iter->first < end_letter && iter->first >= start) {
				//print
				if (print == false)
					*fout << "========SEARCH_BP========" << endl;
				print = true;
				*fout << iter->second->getName() << "/";
				if (iter->second->getCode() == 0)
					*fout << "000";
				else
					*fout << iter->second->getCode();
				*fout << "/" << iter->second->getAuthor() << "/" << iter->second->getYear() << "/" << iter->second->getLoanCount() << endl;
				iter++;
			}
			else
				break;
		}
		dataNode = dataNode->getNext();
	}
	if (print == true)
		*fout << "=======================" << endl << endl;
	else
		return false;
	return true;
}

void BpTree::Delete(string name, SelectionTree* stree) {
	BpTreeNode* delNode = searchDataNode(name);
	
	auto iter = delNode->getDataMap()->begin();

	LoanBookData* info = NULL;
	while (iter != delNode->getDataMap()->end()) {
		if (iter->first == name) {
			info = iter->second;
			break;
		}
		iter++;
	}

	if (info == NULL)
		return;

	delNode->deleteMap(name);

	stree->Insert(info);
	//selection tree insert 
}