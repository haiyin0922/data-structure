#include<iostream> 
using namespace std;

void path(int start_r, int start_c, int dim);
bool IsVowel(char cell);
bool TwoConsonants(char cell1, char cell2);

class Stack{
public:
	Stack(int stackCapacity = 10);	//�ؤ@�Ӱ_�lcapacity��10��empty stack
	~Stack();						//�Ѻc�l 
	bool IsEmpty() const;			//if stack cell�Ӽ�=0, �^��true 
	char& Top() const;				//return stack������cell 
	void Push(const char& cell);	//�Ncell���Jstack������ 
	void Pop();						//�R��stack���ݪ�cell 
	int gettop();					//���Xtop���Ʀr 
	void printstack();				//��stack�L�X�� 
private:
	char* stack;					//�s��stack��array 
	int top;						//top�����barray����m 
	int capacity;					//stack array��capacity 
};

Stack::Stack(int stackCapacity):capacity(stackCapacity)
{
	stack = new char[capacity];
	top = -1;
}

Stack::~Stack()
{
	delete []stack;
}

void ChangeSize(char*& oldStack, const int oldSize, const int newSize)
{
	char* temp = new char[newSize];
	int number = min(oldSize, newSize);
	copy(oldStack, oldStack+number, temp);
	delete[]oldStack;
	oldStack = temp;
}

inline bool Stack::IsEmpty() const
{
	return top==-1;
}

char& Stack::Top() const
{
	return stack[top];
}

void Stack::Push(const char& cell)
{
	if(top==capacity-1){
		ChangeSize(stack, capacity, 2*capacity);
		capacity *= 2;
	}
	
	top++;
	stack[top] = cell;
}

void Stack::Pop()
{
	top--;
}

int Stack::gettop()
{
	return top;
}

void Stack::printstack()
{
	for(int i=0; i<=top; i++){
		cout<<stack[i];
	}
	cout<<" ";
	
	for(int i=0; i<=top; i++){
		if(IsVowel(stack[i])==1)
			cout<<stack[i];
	}
	for(int i=0; i<=top; i++){
		if(IsVowel(stack[i])==0)
			cout<<stack[i];
	}
	cout<<endl;	
}

char** matrix;
int** mark;
int* temp_dir_r, *temp_dir_c;

main()
{
	int dim;
	
	cin>>dim;
	
	matrix = new char*[dim];
	for(int i=0; i<dim; i++)
    	matrix[i] = new char[dim];
    	
    for(int i=0; i<dim; i++){
    	for(int j=0; j<dim; j++){
    		cin>>matrix[i][j];
		}
	}
	
	mark = new int*[dim];
	for(int i=0; i<dim; i++)
    	mark[i] = new int[dim];
    	
    for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			mark[i][j] = 0;
		}
	}
	
	temp_dir_r = new int[dim*dim];
	temp_dir_c = new int[dim*dim];
	
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			path(i, j, dim);
		}
	}
	   
	for(int i=0; i<dim; i++)
   		delete []matrix[i];
   	delete []matrix;
	   
	for(int i=0; i<dim; i++)
    	delete []mark[i];
	delete []mark;
	
	delete []temp_dir_r;
	delete []temp_dir_c;
}

void path(int start_r, int start_c, int dim)
{
	int cur_r = start_r, cur_c = start_c, dir_r = 1, dir_c = 0;
	int count = 0;
	Stack word;

	if(IsVowel(matrix[start_r][start_c]))
		return;
	else{
		word.Push(matrix[start_r][start_c]);
		mark[start_r][start_c] = 1;
		
		while(!word.IsEmpty()){
			if(cur_r+dir_r==dim || cur_r+dir_r<0 || cur_c+dir_c==dim || cur_c+dir_c<0 || mark[cur_r+dir_r][cur_c+dir_c]==1 ||
			   TwoConsonants(word.Top(), matrix[cur_r+dir_r][cur_c+dir_c])){
				if(dir_r==1){ //�V�U����N�V�k 
					dir_r = 0;
					dir_c = 1;
				}
				else if(dir_c==1){ //�V�k����N�V�W 
					dir_c = 0;
					dir_r = -1;
				}
				else if(dir_r==-1){ //�V�W����N�V�� 
					dir_r = 0;
					dir_c = -1;
				}
				else if(dir_c==-1){ //�V���٬O����NPop�� 
					if(!IsVowel(word.Top())) count--;
					word.Pop();
					mark[cur_r][cur_c] = 0;
					if(word.IsEmpty()) return;
					while(temp_dir_c[word.gettop()]==-1){
						if(!IsVowel(word.Top())) count--;
						word.Pop();
						cur_c++;
						mark[cur_r][cur_c] = 0;
					}
					if(temp_dir_r[word.gettop()]==1){
						cur_r--;
						dir_r = 0;
						dir_c = 1;
					}
					else if(temp_dir_c[word.gettop()]==1){
						cur_c--; 
						dir_r = -1;
						dir_c = 0;
					}
					else if(temp_dir_r[word.gettop()]==-1){
						cur_r++;
						dir_r = 0;
						dir_c = -1;
					}
				}
			}
			else{
				cur_r += dir_r;
				cur_c += dir_c;
				mark[cur_r][cur_c] = 1;
				temp_dir_r[word.gettop()] = dir_r;
				temp_dir_c[word.gettop()] = dir_c;
				word.Push(matrix[cur_r][cur_c]);
				dir_r = 1; 
				dir_c = 0;
				if(!IsVowel(matrix[cur_r][cur_c])){
					count++;
					if(count>=2){
						word.printstack();
					}
				}
			}	
		}
	}
	
	return;
}

bool IsVowel(char cell)
{
	return (cell=='a' || cell=='e' || cell=='i' || cell=='o' || cell=='u');
}

bool TwoConsonants(char cell1, char cell2)
{
	return (IsVowel(cell1)==0 && IsVowel(cell2)==0);
} 
