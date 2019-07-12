#include "types.h"      
#include "user.h"       

#define N 21
#define size 10

int mata[size][size]={{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10}};
int matb[size][size]={{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10},{1,2,3,4,5,6,7,8,9,10}};
int matc[size][size];

void loop(){
    int x, i = 0;

    for(x=0; x<123456; x++){
        i--;
    }

    for(x=0; x<123456; x++){
        i--;
    }

}

int main(){
    int pid;
    int i,j,k,g;
    for (g=1;g<=N;g++){
        pid=fork();
	int times=10000;
	if(pid == 0){
        printf(1,"pid %d is running (%d times)!.\n",getpid(),times);
			while (times -->0){
			  for (i=0; i < size ; i++)
			   {
			      for(j=0; j<size; j++){
				  matc[i][j]=0;
				  for(k=0; k<size; k++){
				      matc[i][j]+=mata[i][k]*matb[k][j];
				  } 
			      }
			   }
			  for(i=0; i<size; i++){
			     for(j=0; j<size; j++)
			       mata[i][j]=matb[i][j]=matc[i][j];
			   }
			}
			printf(1,"pid %d done!.\n",getpid()); 
        	exit();    
	}
    }
   while(1){
        pid=wait();
        if(pid<0)break;
    }



    exit();
}
