#include<iostream>
using namespace std;
bool no_two_queens(bool map[8][8]);

bool place_a_queen (bool map[8][8], int row)
{
  if(row==8){ return true; } 
  else{
    for(int i=0; i<8; i++){
		map[row][i] = true;
		if(no_two_queens(map)){
			if(place_a_queen(map, row+1)){
				return true;
			}
		}
		map[row][i] = false; 
	}
	return false;
  }
}
int main()
{
  bool map[8][8];
  for(int i=0; i<8; i++){
  for(int j=0; j<8; j++){
    map[i][j] = false;
  }}
  if(place_a_queen(map, 0)){
    for(int i=0; i<8; i++){
      for(int j=0; j<8; j++){
        if(map[i][j]) cout << " Q";
        else cout << " .";
      }
      cout << endl;
    }
  }
}
bool no_two_queens(bool map[8][8])
{
  for(int i=0; i<8; i++){
    bool tmp = false;
    for(int j=0; j<8; j++){
      if(tmp && map[i][j]) return false;
      if(map[i][j]){
        tmp = true;
        for(int k=1; k<8; k++){
          if(i+k<8  && j+k<8  && map[i+k][j+k]) return false;
          if(i-k>=0 && j+k<8  && map[i-k][j+k]) return false;
          if(i+k<8  && j-k>=0 && map[i+k][j-k]) return false;
          if(i-k>=0 && j-k>=0 && map[i-k][j-k]) return false;
          if(i+k<8            && map[i+k][j  ]) return false;
          if(i-k>=0           && map[i-k][j  ]) return false;
        }
      }
    }
  }
  return true;
}
