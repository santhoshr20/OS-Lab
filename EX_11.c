#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
int n;
int avg;
int min;
int max; /* this data is shared by the thread(s) */
void *average(void *param);
void *minimum(void *param);
void *maximum(void *param); /* threads call this function */
int main(int argc,char* argv[])
{
pthread_t tid; /* the thread identifier */
pthread_t tid1;
pthread_t tid2;
pthread_attr_t attr; /* set of thread attributes */

n = argc;
int *arr;
arr=(int *)malloc(sizeof(int)*n);
for(int i=0;i<n;i++)
	arr[i] = atoi(argv[i]);
/* get the default attributes */
pthread_attr_init(&attr);
/* create the thread */
pthread_create(&tid,&attr,average,(void *)arr);
/* wait for the thread to exit */
pthread_join(tid,NULL);

pthread_attr_init(&attr);
pthread_create(&tid1,&attr,minimum,(void *)arr);
pthread_join(tid1,NULL);

pthread_attr_init(&attr);
pthread_create(&tid2,&attr,maximum,(void *)arr);
pthread_join(tid2,NULL);

printf("Average = %d\n",avg);
printf("Minimum = %d\n",min);
printf("Maximum = %d\n",max);
}
/* The thread will begin control in this function */
void *average(void *param)
{
int *par;
par=(int *)param;
int i;
avg = 0;
for (i = 1; i <n; i++)
avg += par[i];
avg /= n-1;
pthread_exit(0);
}

void *minimum(void *param)
{
int *par;
par=(int *)param;
int i;
min = 999;
for (i = 1; i <n; i++)
{
	if(min > par[i])
		min = par[i];

}
pthread_exit(0);
}

void *maximum(void *param)
{
int *par;
par=(int *)param;
int i;
max = 0;
for (i = 1; i <n; i++)
{
	if(max < par[i])
		max = par[i];

}
pthread_exit(0);
}


/*

OUTPUT:

santhosh@Sandy:~$ cd Desktop/
santhosh@Sandy:~/Desktop$ cd OS_Lab/
santhosh@Sandy:~/Desktop/OS_Lab$ gcc 185001135-EX_11.c -lpthread -o 185001135-EX_11out
santhosh@Sandy:~/Desktop/OS_Lab$ ./185001135-EX_11out 90 81 78 95 79 72 85
Average = 82
Minimum = 72
Maximum = 95
santhosh@Sandy:~/Desktop/OS_Lab$ 


*/