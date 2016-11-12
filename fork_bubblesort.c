#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<sys/wait.h>
int MIN = 999999;
int SIZE = 20000;
int NUM_FORKS = 3;

int get_lowest(int *array){
	int n,c,d,swap;
	for(c=0;c<SIZE-1;c++){
		for(d=0;d<SIZE-c-1;d++){
			if(array[d]>array[d+1]){
				swap = array[d];
				array[d]=array[d+1];
				array[d+1]=swap;
			}
		}
	}
	return array[0];
}

int main(){
int i,j;
struct timeval t1,t2;
double elapsedTime;

gettimeofday(&t1, NULL);
srand(time(NULL));

int r = 3, c = SIZE;
int *arr[r];
for(i=0;i<r;i++){
	arr[i] = (int *)malloc(c*sizeof(int));
}
for(i=0;i<r;i++){
	for(j=0;j<c;j++){
		arr[i][j] = rand();
	}
}

pid_t pids[NUM_FORKS];
int n = NUM_FORKS;

for(i=0;i<n;++i){
	if((pids[i]=fork())<0){
		perror("fork");
		abort();
	} else if(pids[i]==0){
		printf("LOWEST %d: %d\n",i , get_lowest(arr[i]));
		exit(0);
	}
}

int status;
pid_t pid;
while(n>0) {
	pid=wait(&status);
	printf("\nchild with pid %d exited with status 0x%x.\n", pid, status);
	--n;
}

gettimeofday(&t2, NULL);

elapsedTime = (t2.tv_sec - t1.tv_sec);

printf("\n\n\nCAS%.2lf\n\n\n", elapsedTime);

return 0;
}
