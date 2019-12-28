#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include "stack.h"
using namespace std;

class SLLNode {
	public:
		string line;
		SLLNode * next;
	
		SLLNode() {
			next = 0;
		}	
		SLLNode(string sentence,SLLNode *ptr=0) {
			line = sentence;
			next = ptr;
		}
};

class LinklineList {
	
	private :
		SLLNode * head;
		SLLNode * tail;
		CommandStack commands;
		int page;

	public:
		LinklineList() {
			head = tail = 0;
			page=1;
		}
		
		bool openFile(string fileName);
		void displayLine();
		void deleteLineN(int n);//1
		void moveNtoM(int n,int m);//2
		void insertNText(string text,int line);//3
		void replaceNText(string text,int line);//4
		void saveFile(string fileName);//5
		void next();//6
		void Prev();//7
		void undo();
};


////////////////////////////////////////////////////////////

bool LinklineList::openFile (string fileName) {	
	string sentence;
	char letter;
	char name[100];
	for(int i=0;i<fileName.size();i++)
		name[i]=fileName[i];
	ifstream file(name);
	if(!file) {
		cout<<"No such File!!!"<<endl;
		return true;
	}
	else {
		while(file.get(letter)) {
			if(letter == '\n') {
				if (tail != 0) {
					tail->next = new SLLNode(sentence);
					tail = tail->next;
    				}
				else 
					head = tail = new SLLNode(sentence);
				sentence = "";
			}
			else
				sentence = sentence+letter;
		}
		file.close();
	}
	return false;
}

void LinklineList::saveFile(string fileName) {//5
	ofstream file;
	char name[100];
	for(int i=0;i<fileName.size();i++)
		name[i]=fileName[i];
	file.open(name);
	SLLNode * tmp;
	if (file.is_open()) {
		for(tmp=head;tmp!=0;tmp=tmp->next) {
			file<<tmp->line;
			file<<"\n";
		}
		file.close();
	}
	else cout << "Unable to open file";
	commands.makeEmpty();
}

void LinklineList::displayLine() {
	SLLNode * tmp1=head;
	int line=0;bool flag=false;
	int count=0;int lineNum=page*10;
	for(tmp1;tmp1!=0;tmp1=tmp1->next) {
		if(count==lineNum-10) {
			line=count+10;
			flag=true;
		}
		if(count < lineNum-10)
			count++;
		else {
			cout<<count+1<<") "<<tmp1->line<<endl;
			count++;
		}
		if(count>line-1 && flag)
			break;
	}
	cout<<endl;
	cout<<"--- page "<<page<<" ---"<<endl;
}

void LinklineList::deleteLineN(int n) {//1
	SLLNode * tmp1;
	SLLNode * tmp2;
	int count = 1;
	string command;
	stringstream s1;
	s1<<n;
	if(n==1) {//delete head
		SLLNode *tmp = head;
		head = head->next;
		if (head == tail)     // if only one node on the list;
			head = tail = 0;
		else head = head->next;
		command ="1 "+tmp->line+s1.str();
		delete tmp; 
	}
	else {
		for(tmp1=head,tmp2=head->next; tmp2!=0; tmp1=tmp1->next,tmp2=tmp2->next) {
		
			if(count == n-1) {
				if(tmp2 == tail) {//delete tail
					command ="1 "+tmp2->line+" "+s1.str();
					delete tail;
					tail = tmp1;
				}
				else {
					command ="1 "+tmp2->line+" "+s1.str();
					tmp1->next=tmp2->next;
					delete tmp2;
				}
			
			}
			count++;
		}
	}
	commands.push(command);	
}

void LinklineList::moveNtoM(int n,int m) {//2
	SLLNode * tmp1=head;
	string text;
	int count;
	int size=0;

	for(tmp1=head;tmp1!=0;tmp1=tmp1->next) 
		size++;
	if(size<n || size<m)
		cout<<"out of range!!!"<<endl;
	if(m==n)
		cout<<"no change possible"<<endl;
	else {
		tmp1=head;
		for(count=1;count<n;count++) {
			tmp1=tmp1->next;
		}
		cout<<"info "<<n<<":"<<tmp1->line<<endl;
		text = tmp1->line;
		insertNText(text,m+1);
		deleteLineN(n);
		commands.pop();
		commands.pop();
	}
	
	stringstream s1,s2;
	s1<<n;s2<<m;
	string command="2 "+s1.str()+" "+s2.str();
	commands.push(command);
}

void LinklineList::insertNText(string text,int line) {//3
	int count = 2;
	SLLNode * tmp;
	SLLNode * tmpPrev;
	SLLNode * newNode;
	stringstream s1;
	s1<<line;
	string command="3 "+s1.str();
	bool flag = true;
	int pretail;
	if(line == 1) {
		SLLNode *newNode = new SLLNode;
		SLLNode *tmp1=head;
		newNode->line=text;
		head = newNode;
		newNode->next=tmp1;
	}
	else {
		for(tmp=head->next,tmpPrev=head;tmp!=0;tmp=tmp->next,tmpPrev=tmpPrev->next) {
			if(count == line) {
				SLLNode *newNode = new SLLNode;
				newNode->line = text;
				tmpPrev->next = newNode;
				newNode->next = tmp;
				flag = false;
				command += " 0";
			}
			count++;
		}
		if(flag) {
			pretail = count;
			stringstream s2;
			s2<<count;
			command += " "+s2.str();
			for(count;count<=line;count++) {
				if(count == line) {
					tail->next = new SLLNode(text);
					tail = tail->next;
				}
				else {
					tail->next = new SLLNode("");
					tail = tail->next;
				}
			}

		}
	}
	commands.push(command);
}

void LinklineList::replaceNText(string text,int line) {//4
	int count = 1;
	SLLNode * tmp;
	bool flag = true;
	stringstream s1;
	s1<<line;
	string command;
	for(tmp=head;tmp!=0;tmp=tmp->next) {
		if(count == line) {
			command = "4 "+tmp->line+" "+s1.str();
			tmp->line = text;
			flag = false;
			commands.push(command);
		}
		count++;
	}
	if(flag)
		cout<<"İnvalid Line!!!"<<endl;
}

void LinklineList::next() {//6
	int count=1;
	string command="6 ";
	for(SLLNode *tmp=head;tmp->next!=0;tmp=tmp->next)
		count++;
	if (page<=count/10+1)
		page++;
	commands.push(command);
}

void LinklineList::Prev() {//7
	string command="7 ";
	if(page>1)
		page--;
	commands.push(command);
}

void LinklineList::undo() {
	char preCommand;int line;
	string prev;int count;
	stringstream s1;SLLNode * tmp=head;
	string text,text2;
	char name[100];
	if(commands.isEmpty()) {
		cout<<"No previously command!!!"<<endl;
	}
	else {
		prev = commands.top();
		for(int i=0;i<prev.size();i++)
			name[i]=prev[i];
		preCommand = prev[0];
	
		if(preCommand=='1') {//preCommand = deleteLineN(int n);+++++++++++++
			for(count=2;name[count]!=' ';count++) {
				text = text+name[count];
			}
			for(count;count<prev.size();count++) {
				text2=text2+name[count];
			}
			stringstream ss(text2);ss>>line;

			int count = 2;
			SLLNode * tmp;
			SLLNode * tmpPrev;
			SLLNode * newNode;
			bool flag = true;
			if(line == 1) {
				SLLNode *newNode = new SLLNode;
				SLLNode *tmp1=head;
				newNode->line=text;
				head = newNode;
				newNode->next=tmp1;
			}
			else {
				for(tmp=head->next,tmpPrev=head;tmp!=0;tmp=tmp->next,tmpPrev=tmpPrev->next) {
					if(count == line) {
						SLLNode *newNode = new SLLNode;
						newNode->line = text;
						tmpPrev->next = newNode;
						newNode->next = tmp;
						flag = false;
					}
					count++;
				}
				if(flag) {
					for(count;count<=line;count++) {
						if(count == line) {
							tail->next = new SLLNode(text);
							tail = tail->next;
						}
						else {
							tail->next = new SLLNode("");
							tail = tail->next;
						}
					}

				}
			}	
		}
		else if(preCommand=='2') {//preCommand = moveNtoM(int n,int m);+++++++++++++
			for(count=2;name[count]!=' ';count++) {
				text = text+name[count];
			}
			for(count;count<prev.size();count++) {
				text2=text2+name[count];
			}
			stringstream sn(text);
			int n;sn>>n;
			stringstream sm(text2);
			int m;sm>>m;
			SLLNode *tmp=head;
			for(int i=1;i<m;i++)
				tmp=tmp->next;
			text = tmp->line;
			cout<<"text "<<text<<endl;
			insertNText(text,n);
			deleteLineN(m+1);
		
			commands.pop();
			commands.pop();
		}
		else if(preCommand=='3') {//preCommand = insertNText(string text,int line);+++++++++++++
			string text2;
			for(count=2;name[count]!=' ';count++) {
				text2 = text2+name[count];
			}
			stringstream ss(text2);ss>>line;
			int count = 2;
			SLLNode * tmp;
			SLLNode * tmp1;
			SLLNode * tmp2;
			SLLNode * tmpPrev;
			SLLNode * newNode;
			bool flag = true;


			if(name[prev.size()-1]=='0') {
				if(line==1) {//delete head
					SLLNode *tmp = head;
					head = head->next;
					if (head == tail)     // if only one node on the list;
						head = tail = 0;
					else head = head->next;
					delete tmp; 
				}
				else {
					count=1;
					for(tmp1=head,tmp2=head->next; tmp2!=0; tmp1=tmp1->next,tmp2=tmp2->next) {
		
						if(count == line-1) {
							if(tmp2 == tail) {//delete tail
								delete tail;
								tail = tmp1;
							}
							else {
								tmp1->next=tmp2->next;
								delete tmp2;
							}
			
						}
						count++;
					}
				}
			}
			else {
				string text3;
				for(count=2;name[count]!='\0';count++) {
				text3 = text3+name[count];
				}
				stringstream textLine(text3);
				int n;textLine>>n;
				for(int i=0;i<n;i++)
					tmp=tmp->next;
				tail=tmp;
				for(tmp->next;tmp!=0;tmp=tmp->next)
					delete tmp;
			}
		}
		else if(preCommand=='4') {//preCommand = replaceNText(string text;int line);+++++++++++++
			for(count=2;name[count]!=' ';count++) {
				text = text+name[count];
			}
			string text2;
			for(count;count<prev.size();count++) {
				text2=text2+name[count];
			}
			stringstream ss(text2);ss>>line;

			int count = 1;
			SLLNode * tmp;
			for(tmp=head;tmp!=0;tmp=tmp->next) {
				if(count == line) {
					tmp->line = text;
				}
				count++;
			}
		}
		else if(preCommand=='6') {//preCommand = next();+++++++++++++
			if(page>1)
				page--;
		}
		else if(preCommand=='7') {//preCommand = Prev();+++++++++++++
			int count=1;
			for(SLLNode *tmp=head;tmp->next!=0;tmp=tmp->next)
				count++;
			if (page<=count/10+1)
				page++;
		}
		else {
			cout<<"No pre-Action"<<endl;
		}
		commands.pop();
	}
}

////////////////////////////////////////////////////////////

