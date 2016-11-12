#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<sys/wait.h>
#include<pthread.h>

int MIN= 999999;
int SIZE= 5000;
int NUM_THREADS= 3;

pthread_t *tid;


void* get_lowest(void *input){
	pthread_t id = pthread_self();
	int *array = (int *)input;
	int c,d,swap;

	for(c=0;c<SIZE-1;c++){
		for(d=0;d<SIZE-c-1; d++){
			if(array[d]>array[d+1]){
				swap=array[d];
				array[d]=array[d+1];
				array[d+1]=swap;
			}
		}
	}

	int *ret = malloc(sizeof(int));
	*ret = array[0];
	pthread_exit(ret);
}

int interval_random(int min, int max){
	return min + rand() / (RAND_MAX / (max- min +1) +1);
}

int main(int argc, char *argv[]){
int i,j, err;
struct timeval t1,t2;
double elapsedTime;


if(argc==2){
	SIZE = atoi(argv[1]);
} else if(argc==3){
	SIZE = atoi(argv[1]);
	NUM_THREADS=atoi(argv[2]);
}

printf("\nPocet prvkov je: %d", SIZE);
printf("\nPocet vlakien je: %d", NUM_THREADS);
printf("\nPocet poli je: %d\n", NUM_THREADS);

tid = malloc(sizeof(pthread_t)*NUM_THREADS);

gettimeofday(&t1, NULL);
srand(time(NULL));

int **arr = (int **)malloc(NUM_THREADS*sizeof(int *));

if(arr==NULL){
	printf("FAIL!");
	return -1;
}

for(i=0;i<NUM_THREADS;i++){
	arr[i] = (int *)malloc(SIZE*sizeof(int));
	if(arr[i]==NULL){
		printf("FAIL!");
		return -1;

	}
}


for(i=0;i<NUM_THREADS;i++){
	for(j=0;j<SIZE;j++){
		arr[i][j] = rand();
	}
}


i=0;
while(i<NUM_THREADS) {
	err = pthread_create(&(tid[i]), NULL, &get_lowest, arr[i]);

	if(err != 0)
		printf("error: %d\n", err);
	i++;
}

intptr_t retvals[NUM_THREADS];

for(i=0;i<NUM_THREADS; i++){
	void *returnValue;
	pthread_join(tid[i], &returnValue);
	retvals[i] = *((intptr_t *)returnValue);
}


for(i=0;i<NUM_THREADS;i++)
	printf("Vysledok %d: = %ld\n", i, retvals[i]);

gettimeofday(&t2, NULL);

elapsedTime = (t2.tv_sec - t1.tv_sec);

printf("\nTIME:%.2lfs\n", elapsedTime);

for(i=0;i<NUM_THREADS;i++)
	free(arr[i]);


return 0;
}
