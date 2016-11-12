#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<sys/wait.h>
#include<pthread.h>

pthread_t tid1;
pthread_t tid2;
pthread_t tid3;

int MIN = 999999;
int SIZE = 100000;
int NUM_THREADS = 3;

void* get_lowest(void *input){
	pthread_t id = pthread_self();
	int *array = (int *)input;

	int n,c,d,swap;
	for(c=0;c<(SIZE-1);c++){
		for(d=0;d<SIZE-c-1;d++){
			if(array[d]>array[d+1]){
				swap = array[d];
				array[d]=array[d+1];
				array[d+1]=swap;
			}
		}
	}

	int *ret = malloc(sizeof(int));
	*ret = array[0];
	printf("min: %d", *ret);
	pthread_exit(ret);
}

int main(){
int i,j, err;
struct timeval t1,t2;
double elapsedTime;

gettimeofday(&t1, NULL);
srand(time(NULL));

int r = 3;
int *arr1, *arr2, *arr3;
arr1 = (int *)malloc(SIZE*sizeof(int));
arr2 = (int *)malloc(SIZE*sizeof(int));
arr3 = (int *)malloc(SIZE*sizeof(int));

for(j=0;j<SIZE;j++)
	arr1[j] = rand();
for(j=0;j<SIZE;j++)
	arr2[j] = rand();
for(j=0;j<SIZE;j++)
	arr3[j] = rand();

pthread_create(&tid1, NULL, &get_lowest, arr1);
pthread_create(&tid2, NULL, &get_lowest, arr2);
pthread_create(&tid3, NULL, &get_lowest, arr3);

pthread_join(tid1, NULL);
pthread_join(tid2, NULL);
pthread_join(tid3, NULL);

gettimeofday(&t2, NULL);

elapsedTime = (t2.tv_sec - t1.tv_sec);

printf("\n\n\nCAS:%.2lfs\n\n\n", elapsedTime);

return 0;
}
