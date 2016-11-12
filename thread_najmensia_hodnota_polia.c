#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<sys/wait.h>
#include<pthread.h>
#define MIN 999999
#define SIZE 24000000
#define NUM_THREADS 3

pthread_t tid[NUM_THREADS];


void* get_lowest(void *input){
	pthread_t id = pthread_self();
	int *array = (int *)input;
	int i, min;
	min = MIN;

	for(i=0;i<SIZE;i++)
		if(array[i]<min)
			min=array[i];

	int *ret = malloc(sizeof(int));
	*ret = min;
	pthread_exit(ret);
}

int main(){
int i,j, err;
struct timeval t1,t2;
double elapsedTime;

gettimeofday(&t1, NULL);
srand(time(NULL));

int r = 3, c = SIZE;
int *arr[r];

for(i=0;i<r;i++)
	arr[i] = (int *)malloc(c*sizeof(int));

for(i=0;i<r;i++)
	for(j=0;j<c;j++)
		arr[i][j] = rand();

i=0;
while(i<NUM_THREADS) {
	err = pthread_create(&(tid[i]), NULL, &get_lowest, arr[i]);

	if(err != 0)
		printf("error: %d\n", err);
	i++;
}

int retvals[NUM_THREADS];

for(i=0;i<NUM_THREADS; i++){
	void *returnValue;
	pthread_join(tid[i], &returnValue);
	retvals[i] = (intptr_t)returnValue;
}


for(i=0;i<NUM_THREADS;i++)
	printf("%d\t", retvals[i]);

gettimeofday(&t2, NULL);

elapsedTime = (t2.tv_sec - t1.tv_sec);

printf("\nTIME:%.2lfs\n", elapsedTime);

return 0;
}
