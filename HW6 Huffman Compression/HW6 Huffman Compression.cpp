#include<iostream>
#include<string>
using namespace std;

class Node
{
friend class Tree;
public:
	Node(): count(0), left(NULL), right(NULL){};
    Node(int c, char l): count(c), letter(l), left(NULL), right(NULL){};
private:
    Node* left;
    Node* right;
	int count;
	char letter;
};

class Tree
{
public:
	Tree(): root(NULL){};
	~Tree(){
		freeTree(root);
	}
	void freeTree(Node*);
	void constructTree(int);
	void setcode(Node*);
	string getcode(int);
private:
	Node* root;
	Node* num[26];
	string code[26];
	string tempcode;
};

void sort(int);
int cnt[27] = {0};
char let[27];
 
void Tree::freeTree(Node *root)
{
    if(root!=NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
} 
 
void Tree::constructTree(int size)
{
	int letcur = 1, numcur = 1, numsize = 1;
	
	while(numsize<size){		 
		num[numsize] = new Node;
		if((num[numcur]->count==0 || cnt[letcur]<=num[numcur]->count) && letcur<=size){
			num[numsize]->left = new Node(cnt[letcur], let[letcur]);
			letcur++;
		}
		else if(numsize<size){
			num[numsize]->left = num[numcur];
			numcur++;
		}
		if((num[numcur]->count==0 || cnt[letcur]<=num[numcur]->count) && letcur<=size){
			num[numsize]->right = new Node(cnt[letcur], let[letcur]);
			letcur++;
		}
		else if(numsize<size){
			num[numsize]->right = num[numcur];
			numcur++;	
		}
		if(size>1) num[numsize]->count = num[numsize]->left->count + num[numsize]->right->count;
		else num[numsize]->count = num[numsize]->left->count;
		numsize++; 
	}
	
	if(size>1) root = num[size-1];
	else root = num[size];
	
	setcode(root);
}

void Tree::setcode(Node* temp)
{
	if(temp->left==NULL && temp->right==NULL){
		code[temp->letter-'a'] = tempcode;
	}
	if(temp->left!=NULL){
		tempcode.push_back('0');
		setcode(temp->left);
	}
	if(temp->right!=NULL){
		tempcode.push_back('1');
		setcode(temp->right);
	}
	if(tempcode[0]!='\0') tempcode.pop_back();
}

string Tree::getcode(int i)
{
	return code[i];
}

main()
{
	int n, i, j, size;
	char comma;
	string word, text;
	
	cin>>n>>comma>>word;
	getline(cin,text);
	
	while(n>0){
		getline(cin,text);
		for(i=0; i<text.size(); i++){
			if(text[i]!=' '){
				for(j=1; let[j]!=NULL; j++){
					if(text[i]==let[j]){
						cnt[j]++;
						break;
					}
				}
				if(cnt[j]==0){
					let[j] = text[i];
					cnt[j] = 1;
					size = j;
				}
			}
		}
		n--;
	}
		
	sort(size);
	
	Tree huffman;
	huffman.constructTree(size);
	
	for(int i=0; word[i]!='\0'; i++){
		cout<<huffman.getcode(word[i]-'a');
	}
	cout<<endl;
}

void sort(int size)
{	
	for(int i=2; i<=size; i++){
		cnt[0] = cnt[i];
		let[0] = let[i];
		for(int j=1; j<i; j++){
			if(cnt[0]<cnt[j]){
				for(int k=i; k>j; k--){
					cnt[k] = cnt[k-1];
					let[k] = let[k-1];
				}
				cnt[j] = cnt[0];
				let[j] = let[0];
				break;
			} 
		}
	}
} 
