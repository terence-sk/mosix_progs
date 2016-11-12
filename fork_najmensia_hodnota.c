#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<sys/wait.h>
int MIN = 999999;
int SIZE = 10000000;
int NUM_FORKS = 3;

int get_lowest(int *array){
	int i, min;
	min = MIN;
	for(i=0;i<SIZE;i++)
		if(array[i]<min)
			min=array[i];
	return min;
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
printf("ok 1");
for(i=0;i<r;i++){
	for(j=0;j<c;j++){
		arr[i][j] = rand();
	}
}
printf("ok 2");

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
printf("ok 3");

int status;
pid_t pid;
while(n>0) {
	pid=wait(&status);
	printf("\nchild with pid %d exited with status 0x%x.\n", pid, status);
	--n;
}
printf("ok 4");

gettimeofday(&t2, NULL);

elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;

printf("\n\n\nCAS%lf\n\n\n", elapsedTime);

return 0;
}
