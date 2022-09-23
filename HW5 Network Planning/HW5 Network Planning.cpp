#include<iostream>
#define MAX 10000;
using namespace std;

class Graph
{
public:
	Graph(int);
	void InsertEdge(int, int, int ,int);
	void MinLatency();
	void MaxBandwidth();
	int chooseMin();
	int chooseMax();
	int getmin(int);
	int getmax(int);	
private:
	int n;	//vertice個數 
	int** latency;	//egde的latency 
	int** bandwidth;	//edge的bandwidth 
	int* minLat;	//vertice的minLatency 
	int* maxBan;	//vertice的maxBandwidth 
	bool* s;		//vertice
};

Graph::Graph(int ver)
{
	n = ver;
	 
	latency = new int*[n];
	bandwidth = new int*[n];
	minLat = new int[n];
	maxBan = new int[n];
	s = new bool[n];
	
	for(int i=0; i<n; i++){
    	latency[i] = new int[n];
    	bandwidth[i] = new int[n];
	}
    	
    for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			latency[i][j] = MAX;
			bandwidth[i][j] = 0;
		}
	}
}

void Graph::InsertEdge(int from, int to, int lat, int ban)
{
	latency[from][to] = lat;
	bandwidth[from][to] = ban;
}

void Graph::MinLatency()
{
	for(int i=1; i<n; i++){	//初始化 
		s[i] = false;
		minLat[i] = latency[0][i];
	}
	s[0] = true;
	minLat[0] = 0;
	
	for(int i=0; i<n-1; i++){
		int k = chooseMin();
		s[k] = true;
	
		for(int j=1; j<n; j++){
			if(!s[j] && minLat[k]+latency[k][j] < minLat[j])
				minLat[j] = minLat[k]+latency[k][j];
		}
	}
}

void Graph::MaxBandwidth()
{
	for(int i=1; i<n; i++){	//初始化 
		s[i] = false;
		maxBan[i] = bandwidth[0][i];
	}
	s[0] = true;
	maxBan[0] = MAX;
	
	for(int i=0; i<n-1; i++){
		int k = chooseMax();
		s[k] = true;
	
		for(int j=1; j<n; j++){
			if(!s[j] && bandwidth[k][j]>0){
				if(maxBan[k]>maxBan[j] && bandwidth[k][j]>maxBan[j]){
					if(maxBan[k] > bandwidth[k][j])
						maxBan[j] = bandwidth[k][j];
					else
						maxBan[j] = maxBan[k];
				}
			}
		}
	}
}

int Graph::chooseMin()
{
	int i, k, min = MAX;
	
	for(i=1; i<n; i++){
		if(!s[i] && minLat[i]<min){
			min = minLat[i];
			k = i;
		}
	}
	
	return k;
}

int Graph::chooseMax()
{
	int i, k, max = 0;
	
	for(i=1; i<n; i++){
		if(!s[i] && maxBan[i]>max){
			max = maxBan[i];
			k = i;
		}
	}
	
	return k;
}

int Graph::getmin(int i)
{
	return minLat[i];
}

int Graph::getmax(int i)
{
	return maxBan[i];
}

main()
{
	int ver, edge, from, to, lat, ban;
		
	cin>>ver>>edge;
	Graph network(ver);
	
	while(edge){
		cin>>from>>to>>lat>>ban;
		network.InsertEdge(from, to, lat, ban);
		edge--;
	}
	
	network.MinLatency();
	network.MaxBandwidth();
	
	for(int i=1; i<ver; i++){
		cout<<i<<" ";
		if(network.getmin(i)==10000) cout<<"inf 0";
		else cout<<network.getmin(i)<<" "<<network.getmax(i);
		cout<<endl;
	}
}
