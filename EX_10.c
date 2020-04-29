#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
int stsize;
int *frames;
int *refstr;
int fsize;
int pr[N];


void initialise();
void read_input();
void frprint();
int check(int f);
int min();
int max();
void FIFO();
void Optimal();
void LRU();
void LFU();


void main()
{

	printf("\nPage Replacement Algorithms\n\n");
	int choice;
	while(1)
	{
		printf("1.Read_Input\n2.FIFO\n3.Optimal\n4.LRU\n5.LFU\n6.Exit\n\nEnter your Option : ");
		scanf("%d",&choice);
		if(choice == 6)
			exit(0);
		if(choice == 1)
			read_input();
		if(choice == 2)
			FIFO();
		if(choice == 3)
			Optimal();
		if(choice == 4)
			LRU();
		if(choice == 5)
			LFU();

	}


}


void initialise()
{
	for (int i = 0; i < fsize; ++i)
		frames[i] = -1;

	for (int i = 0; i < N; ++i)
		pr[i] = 0;
}

void read_input()
{
	printf("Enter size of reference string : ");
	scanf("%d",&stsize);

	refstr = (int*)malloc(stsize*sizeof(int));
	printf("Enter reference string : ");
	for (int i = 0; i < stsize; ++i)
	{
		scanf("%d",&refstr[i]);
	}
	printf("Enter number of frames : ");
	scanf("%d",&fsize);
	frames = (int*)malloc(fsize*sizeof(int));

}

void frprint()
{
	printf("|");
	for (int i = 0; i < fsize; ++i)
	{
		int x = frames[i];
		if(x==-1)
			printf(" %2s ","-");
		else
			printf(" %2d ", x);
	}
	printf("|");

}

int check(int f)
{
	for (int i = 0; i < fsize; ++i)
	{
		if(frames[i]==f)
			return 1;
	}
	return 0;
}

int min()
{
	int min = 999;
	int amin = -1;

	for (int i = 0; i < fsize; ++i)
	{
		if(frames[i]!=-1 && min>pr[frames[i]]) {
			min = pr[frames[i]];
			amin = i;
		}
	}

	return amin;
}

int max()
{
	int max = 0;
	int amax = -1;

	for (int i = 0; i < fsize; ++i)
	{
		if(frames[i]!=-1 && max<pr[frames[i]]) {
			max = pr[frames[i]];
			amax = i;
		}
	}

	return amax;
}

void FIFO()
{
	printf("\t FIFO Page Replacement Algorithm\n\nPage ref-> memory		-> PF\n\n");
	int count = 0;
	int empty,flag;
	initialise();
	for (int i = 0; i < stsize; ++i)
	{
		empty = flag = 0;
		for (int j = 0; j < fsize; ++j)
		{
			if(frames[j]==-1) {
				empty = 1;
				frames[j] = refstr[i];
				pr[refstr[i]] = i;
				++count;
				flag = 1;
				break;
			}
		}

		if(!empty && !check(refstr[i])) {
			int x = min();
			frames[x] = refstr[i];
			pr[refstr[i]] = i;
			++count;
			flag = 1;
		}

		printf("%2d -> ",refstr[i]);
		frprint();

		if(flag)
			printf(" -> %3d\n", count);
		else
			printf(" -> %3s\n","NO FAULT");

		
	}

	printf("\nTotal number of page faults : %d\n\n\n",count );
}

void Optimal()
{
	printf("\t Optimal Page Replacement Algorithm\n\nPage ref-> memory	-> PF\n\n");
	int count = 0;
	int empty,flag;
	initialise();

	for (int i = 0; i < stsize; ++i)
		++pr[refstr[i]];

	for (int i = 0; i < stsize; ++i)
	{
		empty = flag = 0;
		for (int j = 0; j < fsize; ++j)
		{
			if(frames[j]==-1) {
				empty = 1;
				frames[j] = refstr[i];
				--pr[refstr[i]];
				++count;
				flag = 1;
				break;
			}
		}

		if(!empty && !check(refstr[i])) {
			int x = min();
			frames[x] = refstr[i];
			--pr[refstr[i]];
			++count;
			flag = 1;
		}
		printf("%2d -> ",refstr[i]);
		frprint();

		if(flag)
			printf(" -> %3d\n", count);
		else
			printf(" -> %3s\n","NO FAULT");

		
	}

	printf("\nTotal number of page faults : %d\n\n\n",count );
}


void LRU()
{
	printf("\t LRU Page Replacement Algorithm\n\nPage ref-> memory		-> PF\n\n");
	int count = 0;
	int empty,flag;
	initialise();
	for (int i = 0; i < stsize; ++i)
	{
		empty = flag = 0;
		for (int j = 0; j < fsize; ++j)
		{
			if(frames[j]==-1) {
				empty = 1;
				frames[j] = refstr[i];
				pr[refstr[i]] = i;
				++count;
				flag = 1;
				break;
			}
		}
		if(!empty && !check(refstr[i])) {
			int x = min();
			frames[x] = refstr[i];
			pr[refstr[i]] = i;
			++count;
			flag = 1;
		}

		pr[refstr[i]] = i;
		printf("%2d -> ",refstr[i]);
		frprint();

		if(flag)
			printf(" -> %3d\n", count);
		else
			printf(" -> %3s\n","NO FAULT");

		
	}

	printf("\nTotal number of page faults : %d\n\n\n",count );
}

void LFU()
{
	printf("\t LFU Page Replacement Algorithm\n\nPage ref-> memory		-> PF\n\n");
	int count = 0;
	int empty,flag;
	initialise();
	for (int i = 0; i < stsize; ++i)
	{
		empty = flag = 0;
		for (int j = 0; j < fsize; ++j)
		{
			if(frames[j]==-1) {
				empty = 1;
				frames[j] = refstr[i];
				++count;
				flag = 1;
				break;
			}
		}

		if(!empty && !check(refstr[i])) {
			int x = min();
			int old = frames[x];
			frames[x] = refstr[i];

			pr[old] = 0;
			++count;
			flag = 1;
		}

		pr[refstr[i]] += 1;
		printf("%2d -> ",refstr[i]);
		frprint();

		if(flag)
			printf(" -> %3d\n", count);
		else
			printf(" -> %3s\n","NO FAULT");

		
	}

	printf("\nTotal number of page faults : %d\n\n\n",count );
}

/*

OUTPUT :

santhosh@Sandy:~$ cd Desktop/
santhosh@Sandy:~/Desktop$ cd OS_Lab/
santhosh@Sandy:~/Desktop/OS_Lab$ gcc 185001135-EX_10.c -o 185001135-EX_10out
santhosh@Sandy:~/Desktop/OS_Lab$ ./185001135-EX_10out

Page Replacement Algorithms

1.Read_Input
2.FIFO
3.Optimal
4.LRU
5.LFU
6.Exit

Enter your Option : 1
Enter size of reference string : 20
Enter reference string : 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
Enter number of frames : 4
1.Read_Input
2.FIFO
3.Optimal
4.LRU
5.LFU
6.Exit
Enter your Option : 2
	 FIFO Page Replacement Algorithm

Page ref-> memory		-> PF

 7 -> |  7   -   -   - | ->   1
 0 -> |  7   0   -   - | ->   2
 1 -> |  7   0   1   - | ->   3
 2 -> |  7   0   1   2 | ->   4
 0 -> |  7   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | ->   5
 0 -> |  3   0   1   2 | -> NO FAULT
 4 -> |  3   4   1   2 | ->   6
 2 -> |  3   4   1   2 | -> NO FAULT
 3 -> |  3   4   1   2 | -> NO FAULT
 0 -> |  3   4   0   2 | ->   7
 3 -> |  3   4   0   2 | -> NO FAULT
 2 -> |  3   4   0   2 | -> NO FAULT
 1 -> |  3   4   0   1 | ->   8
 2 -> |  2   4   0   1 | ->   9
 0 -> |  2   4   0   1 | -> NO FAULT
 1 -> |  2   4   0   1 | -> NO FAULT
 7 -> |  2   7   0   1 | ->  10
 0 -> |  2   7   0   1 | -> NO FAULT
 1 -> |  2   7   0   1 | -> NO FAULT

Total number of page faults : 10


1.Read_Input
2.FIFO
3.Optimal
4.LRU
5.LFU
6.Exit

Enter your Option : 3
	 Optimal Page Replacement Algorithm

Page ref-> memory	-> PF

 7 -> |  7   -   -   - | ->   1
 0 -> |  7   0   -   - | ->   2
 1 -> |  7   0   1   - | ->   3
 2 -> |  7   0   1   2 | ->   4
 0 -> |  7   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | ->   5
 0 -> |  3   0   1   2 | -> NO FAULT
 4 -> |  4   0   1   2 | ->   6
 2 -> |  4   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | ->   7
 0 -> |  3   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | -> NO FAULT
 2 -> |  3   0   1   2 | -> NO FAULT
 1 -> |  3   0   1   2 | -> NO FAULT
 2 -> |  3   0   1   2 | -> NO FAULT
 0 -> |  3   0   1   2 | -> NO FAULT
 1 -> |  3   0   1   2 | -> NO FAULT
 7 -> |  7   0   1   2 | ->   8
 0 -> |  7   0   1   2 | -> NO FAULT
 1 -> |  7   0   1   2 | -> NO FAULT

Total number of page faults : 8


1.Read_Input
2.FIFO
3.Optimal
4.LRU
5.LFU
6.Exit

Enter your Option : 4
	 LRU Page Replacement Algorithm

Page ref-> memory		-> PF

 7 -> |  7   -   -   - | ->   1
 0 -> |  7   0   -   - | ->   2
 1 -> |  7   0   1   - | ->   3
 2 -> |  7   0   1   2 | ->   4
 0 -> |  7   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | ->   5
 0 -> |  3   0   1   2 | -> NO FAULT
 4 -> |  3   0   4   2 | ->   6
 2 -> |  3   0   4   2 | -> NO FAULT
 3 -> |  3   0   4   2 | -> NO FAULT
 0 -> |  3   0   4   2 | -> NO FAULT
 3 -> |  3   0   4   2 | -> NO FAULT
 2 -> |  3   0   4   2 | -> NO FAULT
 1 -> |  3   0   1   2 | ->   7
 2 -> |  3   0   1   2 | -> NO FAULT
 0 -> |  3   0   1   2 | -> NO FAULT
 1 -> |  3   0   1   2 | -> NO FAULT
 7 -> |  7   0   1   2 | ->   8
 0 -> |  7   0   1   2 | -> NO FAULT
 1 -> |  7   0   1   2 | -> NO FAULT

Total number of page faults : 8


1.Read_Input
2.FIFO
3.Optimal
4.LRU
5.LFU
6.Exit

Enter your Option : 5
	 LFU Page Replacement Algorithm

Page ref-> memory		-> PF

 7 -> |  7   -   -   - | ->   1
 0 -> |  7   0   -   - | ->   2
 1 -> |  7   0   1   - | ->   3
 2 -> |  7   0   1   2 | ->   4
 0 -> |  7   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | ->   5
 0 -> |  3   0   1   2 | -> NO FAULT
 4 -> |  4   0   1   2 | ->   6
 2 -> |  4   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | ->   7
 0 -> |  3   0   1   2 | -> NO FAULT
 3 -> |  3   0   1   2 | -> NO FAULT
 2 -> |  3   0   1   2 | -> NO FAULT
 1 -> |  3   0   1   2 | -> NO FAULT
 2 -> |  3   0   1   2 | -> NO FAULT
 0 -> |  3   0   1   2 | -> NO FAULT
 1 -> |  3   0   1   2 | -> NO FAULT
 7 -> |  7   0   1   2 | ->   8
 0 -> |  7   0   1   2 | -> NO FAULT
 1 -> |  7   0   1   2 | -> NO FAULT

Total number of page faults : 8


1.Read_Input
2.FIFO
3.Optimal
4.LRU
5.LFU
6.Exit

Enter your Option : 6
santhosh@Sandy:~/Desktop$ cd OS_Lab/


*/
