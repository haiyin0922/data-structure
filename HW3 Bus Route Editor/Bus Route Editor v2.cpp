#include <iostream>
#include <string>
using namespace std;

typedef struct _Node{
    string name;
    struct _Node* gofrom;
    struct _Node* backfrom;
    struct _Node* go;
    struct _Node* back;
}Node;

Node* createNode(string data);
void INSERT();
void DELETE();
void printList(int reverse);
Node* head;
int reverse = 0;

main()
{
	char operation[7];
	int N;
	
	head = createNode("NTHU");
	head->go = createNode("TSMC");
	head->go->back = head;
	head->backfrom = head->go;
	head->go->gofrom = head;
	
	cin>>N;
	
	while(N>0){
		cin>>operation;
		if(operation[0]=='I') INSERT();
		else if(operation[0]=='D') DELETE();
		else reverse++;
		N--;
	}

	printList(reverse%2);
}

Node* createNode(string data)
{
	Node* node = new Node;
	node->name = data;
	node->gofrom = NULL;
	node->backfrom = NULL;
	node->go = NULL; 
	node->back = NULL;
	
    return node;
}

void INSERT()
{
	Node* temp, *stop;
	int method, flag = 0;
	string src, dst, newstop;
	
	if(reverse%2==0) cin>>src>>dst>>newstop>>method;
	else cin>>dst>>src>>newstop>>method;
	
	for(temp=head; temp->go!=NULL; temp=temp->go){
		if(src.compare(temp->name)==0 && dst.compare(temp->go->name)==0){
			flag = 1;
			break;
		}
		else
			flag = 0;
	}
	
	if(flag==0){
		for( ; temp->back!=NULL; temp=temp->back){
			if(src.compare(temp->name)==0) break;
		}
		stop = createNode(newstop);
		stop->back = temp->back;
		stop->backfrom = temp;
		stop->back->backfrom = stop;
		temp->back = stop;
		if(method==2 && stop->back->go==temp){
			stop->back->go = stop;
			stop->go = temp;
			stop->gofrom = stop->back;
			temp->gofrom = stop;
		}
	}
	else if(flag==1){
		stop = createNode(newstop);
		stop->go = temp->go;
		stop->gofrom = temp;
		stop->go->gofrom = stop;
		temp->go = stop;
		if(method==2 && stop->go->back==temp){
			stop->go->back = stop;
			stop->back = temp;
			stop->backfrom = stop->go;
			temp->backfrom = stop;
		}
	}
}

void DELETE()
{
	Node* temp, *temp2, *temp1;
	int flag = 0;
	string deletename;
	
	cin>>deletename;
	
	for(temp=head; temp->go!=NULL; temp=temp->go){
		if(deletename.compare(temp->go->name)==0){
			flag = 1;
			temp2 = temp->go;
			break;
		}
	}
	
	if(flag==0){
		for( ; temp->back!=NULL; temp=temp->back){
			if(deletename.compare(temp->back->name)==0) break;
		}
		temp2 = temp->back;
		temp->back = temp2->back;
		temp->back->backfrom = temp;
	}
	else{
		if(temp2->go==NULL){
			temp->go = NULL;
			temp->backfrom = NULL;
			if(temp2->back!=temp){
				temp->back = temp2->back;
				temp->back->backfrom = temp;
			}
		}
		else{
			temp->go = temp2->go;
			temp->go->gofrom = temp;
			if(temp2->back!=NULL){
				for(temp1=temp2; temp1->go!=NULL; temp1=temp1->go){
				}
				for(; temp1->back!=NULL; temp1=temp1->back){
					if(temp1->back==temp2){
						temp1->back = temp2->back;
						temp1->back->backfrom = temp1;
					}
				}
			}
		}
	}
	delete temp2;
}

void printList(int reverse)
{
	Node* temp, *temp2;
	
	temp = head;
	if(reverse==0){
		while(temp->go!=NULL){
			cout<<temp->name<<"->";
			temp2 = temp;
			temp = temp->go;
			if(temp2!=head && temp2->back==NULL)
				delete temp2;
		}
	
		while(temp!=NULL){
			cout<<temp->name;
			if(temp!=head) cout<<"->";
			temp2 = temp;
			temp = temp->back;
			delete temp2;
		}
	}
	else{
		while(temp->backfrom!=NULL){
			cout<<temp->name<<"->";
			temp2 = temp;
			temp = temp->backfrom;
			if(temp2!=head && temp2->gofrom==NULL)
				delete temp2;
		}
		while(temp!=NULL){
			cout<<temp->name;
			if(temp!=head) cout<<"->";
			temp2 = temp;
			temp = temp->gofrom;
			delete temp2;
		}
	}
	cout<<endl;
}
