#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include<unordered_map>
using namespace std;

class token{
    public:
        string lexin;
        string type;
};
class Node {
public:
    token data;
    Node* next;
    Node()
    {
        data.lexin = "";
        data.type = "";
        next = NULL;
    }
    Node(string a, string b)
    {
        this->data.lexin = a;
        this->data.type = b;
        this->next = NULL;
    }
};
class TokenList {
    Node* head;
public:
    TokenList() { head = NULL; }
    void insertToken(string, string);
    void outList();
};
void TokenList::insertToken(string a, string b)
{
    Node* newNode = new Node(a, b);
    if (head == NULL) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}
void TokenList::outList()
{
    Node* temp = head;
    ofstream fout("Token.txt");
    if (head == NULL) {
        cout << "List empty" << endl;
        return;
    }
    while (temp != NULL) {
        fout <<"<"<<temp->data.lexin << " , "<< temp->data.type <<">"<<endl;
        temp = temp->next;
    }
    fout.close();
}

int getCommaCount(char *inp)
{
    int count = 0;
    int val = int(',');
    for (int x = 0; x < strlen(inp); ++x)
        if (inp[x] == val)
            ++count;
    return count;
}

void invalidSymbol(ofstream& fout, int line, char sym){
    fout<<"Unknown symbol '"<<sym<< "' is found on line : "<<line<<endl; 
}

void printError(ofstream& fout, int line, string s, int state)
{
    //-100 for Number Errors.
    //-101 for operator Errors.
    //-102 for ID errors.

    if(state == -100)
        fout<<"On line "<<line<<" "<<s<<" is invlalid Number in Language"<<endl;
    if(state == -101)
        fout<<"On line "<<line<<" "<<s<<" is invlalid Operator in Language"<<endl;
    if(state == -102)
        fout<<"On line "<<line<<" "<<s<<" is invlalid ID in Language"<<endl;
}