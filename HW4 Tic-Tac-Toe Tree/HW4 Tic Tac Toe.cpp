#include<iostream>
using namespace std;

class Node
{
friend class Tree;
public:
	Node(): left(NULL), right(NULL), parent(NULL){};
    Node(int x, int y, char mark): x(x), y(y), mark(mark), left(NULL), right(NULL), parent(NULL){};
private:
    Node* left;
    Node* right;
    Node* parent;
	int x;
	int y;
	char mark;
};

class Tree
{
public:
	Tree(): root(NULL){};
	Tree(int);
	~Tree();
	void constructTree(int , int , int , int , char);
	void playgame(Node*);
	void checkgame();
	void printTree(Node*);
	Node* getroot();
	bool getwin();
private:
	Node* root;
	Node** NodeList;
	char OX[3][3];
	int win;
};

Tree::Tree(int num)
{
	root = NULL;
	NodeList = new Node*[num];
	win = 0;
	
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			OX[i][j] = '_';
		}
	}
}

Tree::~Tree()
{
	delete[] NodeList;
}

Node* Tree::getroot()
{
	return root;
}

bool Tree::getwin()
{
	return win;
}

void Tree::constructTree(int id, int parid, int x, int y, char mark)
{
	if(parid<0){
		NodeList[id] = new Node(x, y, mark);
		root = NodeList[id];
	}
	else{
		NodeList[id] = new Node(x, y, mark);
		NodeList[id]->parent = NodeList[parid];
		if(NodeList[parid]->left==NULL)
			NodeList[parid]->left = NodeList[id];
		else
			NodeList[parid]->right = NodeList[id];
	}
}

void Tree::playgame(Node* temp)
{	
	if(win==0 && temp->left==NULL && temp->right==NULL){
		Node* cur = temp;
		while(cur!=root){
			OX[cur->x][cur->y] = cur->mark;
			cur = cur->parent;
		}
		OX[cur->x][cur->y] = cur->mark;
		checkgame();
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				OX[i][j] = '_';
			}
		}	
	}
	if(temp->left!=NULL){
		playgame(temp->left);
	}
	
	if(temp->right!=NULL){
		playgame(temp->right);
	}
}

void Tree::checkgame()
{ 
	for(int i=0; i<3; i++){ //橫線 
		if(OX[i][0]!='_' && OX[i][0]==OX[i][1] && OX[i][0]==OX[i][2]) win = 1;
	}
	for(int i=0; i<3; i++){ //直線 
		if(OX[0][i]!='_' && OX[0][i]==OX[1][i] && OX[0][i]==OX[2][i]) win = 1;
	}
	if(OX[0][0]!='_' && OX[0][0]==OX[1][1] && OX[0][0]==OX[2][2] || //對角線 
	   OX[0][2]!='_' && OX[0][2]==OX[1][1] && OX[0][2]==OX[2][0]) win = 1;
	
	if(win==1){
		cout<<"Win"<<endl;
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				cout<<OX[j][i];
				if(j!=2) cout<<" ";
			}
			cout<<endl;
		}
	}	
}

void Tree::printTree(Node* root)
{	
	if(root!=NULL){
		printTree(root->left);
		printTree(root->right);
		cout<<root->x<<" "<<root->y<<" "<<root->mark<<endl;
	}
}

main()
{
	int num, id, parid, x, y;
	char mark;
	
	cin>>num;
	Tree TTT(num);
	
	while(num){
		cin>>id>>parid>>x>>y>>mark;
		TTT.constructTree(id, parid, x, y, mark);
		num--;
	}
	
	TTT.playgame(TTT.getroot());
	
	if(!TTT.getwin()){
		cout<<"Tie"<<endl;
		TTT.printTree(TTT.getroot());
	}
}
