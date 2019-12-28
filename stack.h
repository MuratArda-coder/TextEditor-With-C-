#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
using namespace std;



class StringSLLNode {
	public:
		string line;
		StringSLLNode * next;
	
		StringSLLNode() {
			next = 0;
		}	
		StringSLLNode(string sentence,StringSLLNode *ptr=0) {
			line = sentence;
			next = ptr;
		}
};

class StringLinkedList {
	private :
		StringSLLNode * head;
		StringSLLNode * tail;
	public:
		StringLinkedList() {
			head = tail = 0;
		}
		
		void deleteFromHead();
		void addToHead(string s);
		string headInfo();
		int headExist();

};

void StringLinkedList::deleteFromHead() {
    StringSLLNode *tmp = head;
    if (head == tail) 
	head = tail = 0;
    else 
	head = head->next;
    delete tmp;
}

void StringLinkedList::addToHead(string s) {
    head = new StringSLLNode(s,head);
    if (tail == 0)
       tail = head;
}

string StringLinkedList::headInfo() {
	return head->line;
}

int StringLinkedList::headExist() {
	if(head == 0)
		return 0;
	else
		return 1;
}


class CommandStack {
	private:
		StringLinkedList commandList;
	public:
		void push(string command);
		void pop();
		string top();
		bool isEmpty();
		void makeEmpty();
};

////////////////////////////////////////////////////////////

void CommandStack::push(string command) {
	commandList.addToHead(command);
}
void CommandStack::pop() {
	if(!isEmpty())
		commandList.deleteFromHead();
}
string CommandStack::top() {
	return commandList.headInfo();
}
bool CommandStack::isEmpty() {
	if(commandList.headExist()==0)//if no head then no list
		return true;
	else
		return false;
}

void CommandStack::makeEmpty() {
	while(commandList.headExist()==1)
		commandList.deleteFromHead();
}
