#include<iostream>
#include<string>
#include "structures.h"
using namespace std;

void menu() {
	cout<<"1)"<<"deleteLineN ";//+
	cout<<"2)"<<"moveNtoM ";//+
	cout<<"3)"<<"insertNText ";//+
	cout<<"4)"<<"replaceNText ";//+
	cout<<"5)"<<"saveFile ";//+
	cout<<"6)"<<"next ";//+
	cout<<"7)"<<"Prev ";//+
	cout<<"8)"<<"undo ";//
	cout<<"9)"<<"exit "<<endl;
}

int main() {
	
	int command;
	string fileName;
	LinklineList Lines;
	int n;
	int m;
	string text;
	cout<<"Enter FileName:"<<endl;
	getline(cin,fileName);
	while(Lines.openFile(fileName)) {
		cout<<"Enter FileName:"<<endl;
		getline(cin,fileName);
	}
	while(command!=9) {
		if(command==1) {
			cout<<"delete Line N=>?";
			cin>>n;
			Lines.deleteLineN(n);
		}
		else if(command==2) {
			cout<<"N=>?";
			cin>>n;
			cout<<"M=>?";
			cin>>m;
			Lines.moveNtoM(n,m);
		}
		else if(command==3) {
			cout<<"N=>?";
			cin>>n;
			getline(cin,text);
			cout<<"text=>?";
			getline(cin,text);
			Lines.insertNText(text,n);
		}
		else if(command==4) {
			cout<<"N=>?";
			cin>>n;
			getline(cin,text);
			cout<<"text=>?";
			getline(cin,text);
			Lines.replaceNText(text,n);
		}
		else if(command==5) {
			Lines.saveFile(fileName);
		}
		else if(command==6) {
			Lines.next();
		}
		else if(command==7) {
			Lines.Prev();
		}
		else if(command==8) {
			Lines.undo();
		}
		cout<<"******************************************"<<endl;
		Lines.displayLine();
		cout<<"******************************************"<<endl;
		menu();
		cin >> command;	
	}
	cout<<"System Terminated"<<endl;
}

