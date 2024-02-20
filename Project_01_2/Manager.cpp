#include "Manager.h"

Manager::Manager()
{
    Load = false;
}
Manager::~Manager()
{

}

void Manager::run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Run command
    string comm, name, date;
    int age;
    char term;
    while (!fcmd.eof()) {
        fcmd >> comm;//¶ç¾î¾²±â Æ÷ÇÔ X
        if (comm == "LOAD") {
            bool suc = LOAD();
            if (suc == true) {
                ifstream data;
                data.open("data.txt");
                flog << "===== LOAD =====" << endl;
                while (!data.eof()) {
                    data >> name >> age >> date >> term;
                    if (name == comm)
                        break;
                    flog << name << "/" << age << "/" << date << "/" << term << endl;
                    comm = name;
                }
                flog << "===============" << endl << endl;
            }
            else
                PrintErrorCode(100);
        }
        else if (comm == "ADD") {
            getline(fcmd, comm);
            int i = 0;
            int cnt = 0;
            while (comm[i] != '\0') {
                if (comm[i] == ' ')
                    cnt++;
                i++;
            }
            if (cnt != 4) {
                PrintErrorCode(200);
                continue;
            }

            i = 1;
            name.clear();
            date.clear();
            while (comm[i] != ' ') {
                name.push_back(comm[i]);
                i++;
            }
            i++;

            string age_string;
            while (comm[i] != ' ') {
                age_string.push_back(comm[i]);
                i++;
            }
            i++;
            age = stoi(age_string);

            date.clear();
            while (comm[i] != ' ') {
                date.push_back(comm[i]);
                i++;
            }
            i++;

            term = comm[i];
            bool suc = ADD(name, date, age, term);
            if (suc == true) {
                flog << "===== ADD =====" << endl;
                flog << name << "/" << age << "/" << date << "/" << term << endl;
                flog << "===============" << endl << endl;
            }
        }
        else if (comm == "QPOP") {
            bool suc = QPOP();
            if (suc == false)
                PrintErrorCode(300);
            else
                PrintSuccess("QPOP");
        }
        else if (comm == "SEARCH") {
            fcmd >> name;
            bool suc = SEARCH(name);
            if (suc == false)
                PrintErrorCode(400);
        }
        else if (comm == "PRINT") {
            fcmd >> name;
            bool suc = PRINT(name);
            if (suc == false)
                PrintErrorCode(500);
        }
        else if (comm == "DELETE") {
            fcmd >> comm >> name;
            bool suc = DELETE(comm, name);
            if (suc == true)
                PrintSuccess("DELETE");
            else
                PrintErrorCode(600);
        }
        else if (comm == "EXIT") {
            q.deallocate();
            Name_BST.deallocate(Name_BST.getRoot());
            T_list.deallocate(T_list.getHead());
            PrintSuccess("EXIT");
            break;
        }
        else {
            PrintErrorCode(1000);
            continue;
        }
    }


    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============" << endl << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============" << endl << endl;
}

// LOAD
bool Manager::LOAD() {
    ifstream data;
    data.open("data.txt");

    if (!data || Load == true) {
        return false;
    }

    Load = true;
    string comm, name, date;
    int age;
    char term;
    bool suc = true;
    while (!data.eof()) {
        data >> name >> age >> date >> term;
        if (name == comm)
            break;
        suc = q.push(name, age, date, term);
        if (suc == false)
            exit(1);
        comm = name;
    }

    data.close();
    return true;
}

// ADD
bool Manager::ADD(string name, string date, int age, char term) {
    bool suc = q.push(name, age, date, term);
    if (suc == false)
        exit(1);
    return true;
}

// QPOP
bool Manager::QPOP() {
    string name, date1, date2;
    int age = 0;
    int year, month, day;
    char term = NULL;
    if (q.empty() == true)
        return false;
    else {
        while (q.empty() != true) {
            MemberQueueNode* node = q.pop();
            name = node->getName();
            date1 = node->getDate();
            term = node->getTerm();
            age = node->getAge();

            year = (date1[0] - '0') * 1000 + (date1[1] - '0') * 100 + (date1[2] - '0') * 10 + (date1[3] - '0');
            month = (date1[5] - '0') * 10 + (date1[6] - '0');
            day = (date1[8] - '0') * 10 + (date1[9] - '0');

            if (term == 'A') {
                month += 6;
                if (month > 12) {
                    month -= 12;
                    year++;
                }
            }
            else if (term == 'B')
                year++;
            else if (term == 'C')
                year += 2;
            else
                year += 3;

            //0 »ðÀÔ
            date2 = "";
            date2 += to_string(year);
            date2 += "-";
            if (month < 10)
                date2 += "0";
            date2 += to_string(month);
            date2 += "-";
            if (day < 10)
                date2 += "0";
            date2 += to_string(day);

            delete node;

            T_list.insert(term, name, date1, date2, age);
            Name_BST.insert(name, date1, date2, age, term);
        }
    }
    return true;
}

// SEARCH
bool Manager::SEARCH(string name) {
    NameBSTNode* curNode = Name_BST.getRoot();

    if (curNode == nullptr)
        return false;

    while (curNode != NULL) {
        if (curNode->getName() == name) {
            flog << "===== " << "SEARCH" << " =====" << endl;
            flog << curNode->getName() << "/" << curNode->getAge() << "/" << curNode->getD1() << "/" << curNode->getD2() << endl;
            flog << "===============" << endl << endl;
            return true;
        }
        else if (curNode->getName() > name)
            curNode = curNode->getLeft();
        else if (curNode->getName() < name)
            curNode = curNode->getRight();
    }
    return false;
}

void Manager::PrintName(NameBSTNode* curNode) {
    if (curNode == NULL)
        return;
    PrintName(curNode->getLeft());
    flog << curNode->getName() << "/" << curNode->getAge() << "/" << curNode->getD1() << "/" << curNode->getD2() << endl;
    PrintName(curNode->getRight());
}

void Manager::PrintTerm(TermsBSTNode* curNode) {
    if (curNode == NULL)
        return;
    PrintTerm(curNode->getLeft());
    flog << curNode->getName() << "/" << curNode->getAge() << "/" << curNode->getD1() << "/" << curNode->getD2() << endl;
    PrintTerm(curNode->getRight());
}

bool Manager::PRINT(string input) {
    if (input == "NAME") {
        if (Name_BST.getRoot() == NULL)
            return false;
        flog << "===== PRINT =====" << endl;
        flog << "Name_BST" << endl;
        PrintName(Name_BST.getRoot());
        flog << "===============" << endl << endl;
        return true;
    }
    else {
        TermsListNode* curNode = T_list.getHead();
        while (curNode != NULL) {
            string s;
            s.push_back(curNode->getTerm());
            if (s == input) {
                if (curNode->getNum() == 0)
                    return false;
                if (curNode->getTermBST() == NULL || curNode->getTermBST()->getRoot() == NULL)
                    return false;
                flog << "===== PRINT =====" << endl;
                flog << "Terms_BST " << input << endl;
                PrintTerm(curNode->getTermBST()->getRoot());
                flog << "===============" << endl << endl;
                return true;
            }
            else
                curNode = curNode->getNext();
        }
    }
    return false;
}

// DELETE
bool Manager::DELETE(string comm, string name) {
    if (comm == "NAME") {
        char term;
        //delete NameBSTNode
        if (Name_BST.getRoot() == NULL)
            return false;
        NameBSTNode* curNode = Name_BST.getRoot();
        NameBSTNode* parent = NULL;
        bool suc = false;
        while (curNode != NULL) {
            if (curNode->getName() == name) {
                //delete
                term = curNode->getTerm();
                Name_BST.deleteNode(curNode,parent);
                suc = true;
                break;
            }
            else if (curNode->getName() > name) {
                parent = curNode;
                curNode = curNode->getLeft();
            }
            else if (curNode->getName() < name) {
                parent = curNode;
                curNode = curNode->getRight();
            }
        }
        if (suc == false)
            return false;

        //delete TermsBSTNode
        TermsListNode* node = T_list.getHead();
        while (node->getTerm() != term)//certainly exist
            node = node->getNext();
        node->getTermBST()->search(name);//search and link to delete
        int size = node->getNum();
        node->setValue(--size, term);//update size of BST into T_List node
        if (node->getNum() == 0)
            T_list.deleteNode(term);//delete T_list node
        return true;
    }
    else {//delete with DATE
        //delete NameBSTNode
        Name_BST.POST(Name_BST.getRoot(), name, NULL);
        //searh with post order and link to delete

        //delete TermsBSTNode
        TermsListNode* node = T_list.getHead();
        while (node != NULL) {
            node->getTermBST()->POST(node->getTermBST()->getRoot(), name, NULL);
            if (node->getTermBST()->getSize() == 0) {
                TermsListNode* del = node;
                node = node->getNext();
                T_list.deleteNode(del->getTerm());
            }
            else
                node = node->getNext();
        }
        return true;
    }
}
