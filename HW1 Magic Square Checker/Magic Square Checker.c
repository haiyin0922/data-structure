#include<stdio.h>
int num;
int n[25], square[25][25][25];

int main()
{
	int i, j, k;
	
	scanf("%d", &num);
	
	for(i=0; i<num; i++){
		scanf("%d", &n[i]);
		for(j=0; j<n[i]; j++){
			for(k=0; k<n[i]; k++){
				scanf("%d", &square[i][j][k]);
			} 
		}
	}
	check(0);
}

void check(int checknum)
{
	int i, j, k, l;
	int sum = 0, sumright = 0;
	int flag = 0, judge = 0;
	int m = n[checknum];
	int sumrow[25] = {0}, sumcol[25] = {0}, sumdia[2] = {0};
	int temprow[2], tempcol[2];
	
	if(checknum==num)
		return;		 
	else{
		for(j=0; j<m; j++){
			for(k=0; k<m; k++){
				sumrow[j] += square[checknum][j][k];	
			}				
		}
		
		for(j=0; j<m; j++){
			sum += sumrow[j];
		}
		sumright = sum/m;
		
		//check row的sum是否相等 
		for(j=0; j<m; j++){
			if(sumrow[j]!=sumright){
				flag = 1;
			}
		}
		 
		//cloumn的sum
		for(k=0; k<m; k++){
			for(j=0; j<m; j++){
				sumcol[k] += square[checknum][j][k];	
			}				
		}
		
		//check column的sum是否相等
		for(j=0; j<m; j++){
			if(sumcol[j]!=sumright){
				flag = 1;
			}
		}
		
		//diagonal的sum
		for(j=0; j<m; j++){
			sumdia[0] += square[checknum][j][j];
		} 
		for(k=0; k<m; k++){
			sumdia[1] += square[checknum][k][m-k-1];				
		}

		if(flag==0 && sumdia[0]!=sumdia[1]){ 
			printf("bad\n");
			goto next;
		} 

		if(flag==0){
			printf("good %d\n", sumright);
			goto next;
		}

		if(flag!=0){
			i=0;
			for(j=0; j<m; j++){
				if(sumrow[j]!=sumright){
					temprow[i] = j;
					i++;
				}
			}	

			l=0;
			for(k=0; k<m; k++){
				if(sumcol[k]!=sumright){
					tempcol[l] = k;
					l++;
				}	
			}
		
			if(i!=0 && i!=2 || l!=0 && l!=2){
				printf("bad\n");
				goto next;
			}
			
			if(i==2 && l==0){
				for(k=0; k<m; k++){
					if(sumrow[temprow[0]]-square[checknum][temprow[0]][k]+square[checknum][temprow[1]][k]==sumright &&
					   sumrow[temprow[1]]-square[checknum][temprow[1]][k]+square[checknum][temprow[0]][k]==sumright){
					   	judge = 1;
					 	swap(&square[checknum][temprow[0]][k], &square[checknum][temprow[1]][k], checknum, sumright,
						 	 temprow[0], k, temprow[1], k);
						 	 goto next;
					}
				}
			}
			
			if(i==0 && l==2){
				for(k=0; k<m; k++){
					if(sumcol[tempcol[0]]-square[checknum][k][tempcol[0]]+square[checknum][k][tempcol[1]]==sumright &&
					   sumcol[tempcol[1]]-square[checknum][k][tempcol[1]]+square[checknum][k][tempcol[0]]==sumright){
					   	judge = 1;
					 	swap(&square[checknum][k][tempcol[0]], &square[checknum][k][tempcol[1]], checknum, sumright,
						 	 k, tempcol[0], k, tempcol[1]);
					 	 goto next;
					}
				}
			}
			
			if(i==2 && l==2){
				if(sumrow[temprow[0]]-square[checknum][temprow[0]][tempcol[0]]+square[checknum][temprow[1]][tempcol[1]]==sumright &&
				   sumrow[temprow[1]]-square[checknum][temprow[1]][tempcol[1]]+square[checknum][temprow[0]][tempcol[0]]==sumright && 
				   sumcol[tempcol[0]]-square[checknum][temprow[0]][tempcol[0]]+square[checknum][temprow[1]][tempcol[1]]==sumright &&
				   sumcol[tempcol[1]]-square[checknum][temprow[1]][tempcol[1]]+square[checknum][temprow[0]][tempcol[0]]==sumright){
				    judge = 1; 
					swap(&square[checknum][temprow[0]][tempcol[0]], &square[checknum][temprow[1]][tempcol[1]], checknum, sumright,
						 temprow[0], tempcol[0], temprow[1], tempcol[1]);
					goto next;
				}
				if(sumrow[temprow[1]]-square[checknum][temprow[1]][tempcol[0]]+square[checknum][temprow[0]][tempcol[1]]==sumright &&
				   sumrow[temprow[0]]-square[checknum][temprow[0]][tempcol[1]]+square[checknum][temprow[1]][tempcol[0]]==sumright &&
				   sumcol[tempcol[0]]-square[checknum][temprow[1]][tempcol[0]]+square[checknum][temprow[0]][tempcol[1]]==sumright &&
				   sumcol[tempcol[1]]-square[checknum][temprow[0]][tempcol[1]]+square[checknum][temprow[1]][tempcol[0]]==sumright){
				   	judge = 1;
					swap(&square[checknum][temprow[0]][tempcol[1]], &square[checknum][temprow[1]][tempcol[0]], checknum, sumright,
						 temprow[0], tempcol[1], temprow[1], tempcol[0]);
					goto next;
				}
			}
			
			if(judge==0){	 	 
				printf("bad\n");
			} 
		}
		 
		next: check(checknum+1);	
	}
}

void swap(int *a, int *b, int checknum, int rightrow, int one, int two, int three, int four)
{
	int temp;
	int j, k;
	int sumdia[2] = {0};
		
	temp = *a;
	*a = *b;
	*b = temp;
	
	for(j=0; j<n[checknum]; j++){
		sumdia[0] += square[checknum][j][j];
	} 
	for(k=0; k<n[checknum]; k++){
		sumdia[1] += square[checknum][k][n[checknum]-k-1];				
	}
	
	if(sumdia[0]!=sumdia[1]){ 
		printf("bad\n");
	}
	if(sumdia[0]==sumdia[1]){
		printf("fixable %d\n", rightrow);
		for(j=0; j<n[checknum]; j++){
			for(k=0; k<n[checknum]; k++){
				if(j==one && k==two || j==three && k==four){
					if(square[checknum][j][k]>=100)
						printf(" ");
					if(square[checknum][j][k]<100 && square[checknum][j][k]>=10)
						printf("  ");
					if(square[checknum][j][k]<10)
						printf("   ");
					printf("(%d)", square[checknum][j][k]);	
				}
				else
					printf("%6d", square[checknum][j][k]);
			}
			printf("\n");
		}
	} 
}
