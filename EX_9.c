#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
// structure for physical memory..
struct physical
{
	int mem_size;
	int frames;
	int *holes;
};
// structure for process....
struct logical
{
	char id[10];
	int size;
	int pages;
	int *page_table;
	int flag;
};
struct queue
{
	int *free_frames,front,rear,size,capacity;
};
struct queue* initialize(int frames,int filled)
{
	struct queue *q;
	//initializing the queue
	q=(struct queue*)malloc(sizeof(struct queue));
	q->front=0;
	q->capacity=frames-filled;
	q->free_frames=(int*)malloc(sizeof(int)*q->capacity);
	q->rear=0;
	q->size=0;
	return q;

}
void enqueue(struct queue *q,int x)
{
	q->free_frames[q->rear]=x;
	q->rear=q->rear+1%q->capacity;
	q->size++;

}
int dequeue(struct queue *q)
{
	int x=q->free_frames[q->front];
	q->front=q->front+1%q->capacity;
	q->size--;
	return x;
}
void print_queue(struct queue *q)
{
	int i;
	int start=q->front%q->capacity;
	printf("\nThe Free frames are:");
	for(i=0;i<q->size;i++)
	{
		printf("%d  ",q->free_frames[start]);
		start=start+1%q->capacity;
	}
}
return l;

void main()
{
	struct physical p;
	struct logical l[20];
	struct queue *q;
	int n=0,i,choice;
	int page_size;
	int x;
	printf("\n\n---------------------Implementation of Paging Technique---------------------\n\n");
	printf("\nEnter memory size:");
	scanf("%d",&p.mem_size);
	printf("\nEnter the page size:");
	scanf("%d",&page_size);
	p.frames=p.mem_size/page_size;
	printf("\nPhysical memory is divided into %d frames",p.frames);
	p.holes=(int*)malloc(sizeof(int)*p.frames);
	for(i=0;i<p.frames;i++)
	{
		p.holes[i]=0;
	}
	srand(time(0));
	int filled=rand()%32;
	int count=0;
	for(i=0;i<filled;i++)
	{
		x=rand()%32;
		if(p.holes[x]==1)
			continue;
		else
		{
			p.holes[x]=1;
			count++;
		}
	}
	filled=count;
	printf("\nThe no of filled spaces are %d ",count);
	q=initialize(p.frames,filled);
	for(i=0;i<p.frames;i++)
	{
		if(p.holes[i]==0)
		{
			//printf("%d    ",i+1);
			enqueue(q,i+1);
		}
	}
	print_queue(q);
	while(1)
	{
		printf("\n\n\n-------------------------\n1.Process request\n2.Deallocation\n3.Page Table display for all input process\n4.Free Frames list display\n5.Exit\nEnter the choice:");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("\nEnter the process requirement:\nEnter the id:");
			scanf("%s",l[n].id);
			printf("\nEnter the size:");
			scanf("%d",&l[n].size);
			l[n].pages=l[n].size/page_size;
			l[n].page_table=(int*)malloc(sizeof(int)*l[n].pages);
			printf("\nThe Process is divided into %d pages",l[n].pages);
			//l=allocate(q,l);
			//creating page table
			printf("\nThe page table for %s",l[n].id);
			for(i=0;i<l[n].pages;i++)
			{
				l[n].page_table[i]=dequeue(q);
				printf("\nPage %d : Frame %d",i,l[n].page_table[i]);
			}
				printf("\n\n");
				print_queue(q);
				l[n].flag=0;
			n++;	
		}
		else if(choice==2)
		{
			//deallocating the process.....
			char pid[10];
			int index,i;
			printf("\nEnter the process id:");
			scanf("%s",pid);
			for(i=0;i<n;i++)
			{
				if(strcmp(pid,l[i].id)==0)
					index=i;
			}
			for(i=0;i<l[index].pages;i++)
			{
				enqueue(q,l[index].page_table[i]);
				l[index].page_table[i]=-1;
			}
			l[index].flag=1;
			print_queue(q);
		}
		else if(choice==3)
		{
			int j;
			for(i=0;i<n;i++)
			{
				if(l[i].flag==0)
				{
					printf("\nThe Process is divided into %d pages",l[i].pages);
					printf("\nThe page table for %s",l[i].id);
					for(j=0;j<l[i].pages;j++)
					{
						printf("\nPage %d : Frame %d",j,l[i].page_table[j]);
					}
					printf("\n\n");
				}	
			}	
		}
		else if(choice==4)
		{
			print_queue(q);
		}
		else if(choice==5)
		{
			break;
		}
		else
		{
			printf("\nInvalid Option");
		}

	}

}
/*Output:
santhosh@Sandy:~$ cd Desktop/
santhosh@Sandy:~/Desktop$ cd OS_Lab/
santhosh@Sandy:~/Desktop/OS_Lab$ gcc 185001135-EX_9.c -o 185001135-EX_9out
santhosh@Sandy:~/Desktop/OS_Lab$ ./185001135-EX_9out

---------------------Implementation of Paging Technique---------------------

Enter memory size:32

Enter the page size:1

Physical memory is divided into 32 frames
The no of filled spaces are 22
The Free frames are:1  2  3  4  6  9  16  18  26  28

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:1

Enter the process requirement:
Enter the id:p1

Enter the size:4

The Process is divided into 4 pages
The page table for p1
Page 0 : Frame 1
Page 1 : Frame 2
Page 2 : Frame 3
Page 3 : Frame 4


The Free frames are:6  9  16  18  26  28

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:1

Enter the process requirement:
Enter the id:p2

Enter the size:2

The Process is divided into 2 pages
The page table for p2
Page 0 : Frame 6
Page 1 : Frame 9


The Free frames are:16  18  26  28

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:2

Enter the process id:p1

The Free frames are:16  18  26  28  1  2  3  4

-------------------------\n1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:3

The Process is divided into 2 pages
The page table for p2
Page 0 : Frame 6
Page 1 : Frame 9

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:1

Enter the process requirement:
Enter the id:p1

Enter the size:3

The Process is divided into 3 pages
The page table for p1
Page 0 : Frame 16
Page 1 : Frame 18
Page 2 : Frame 26


The Free frames are:28  1  2  3  4

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:4

The Free frames are:28  1  2  3  4

-------------------------\n1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:3

The Process is divided into 2 pages
The page table for p2
Page 0 : Frame 6
Page 1 : Frame 9


The Process is divided into 3 pages
The page table for p1
Page 0 : Frame 16
Page 1 : Frame 18
Page 2 : Frame 26

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:1

Enter the process requirement:
Enter the id:p3

Enter the size:4

The Process is divided into 4 pages
The page table for p3
Page 0 : Frame 28
Page 1 : Frame 1
Page 2 : Frame 2
Page 3 : Frame 3


The Free frames are:4

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:3

The Process is divided into 2 pages
The page table for p2
Page 0 : Frame 6
Page 1 : Frame 9


The Process is divided into 3 pages
The page table for p1
Page 0 : Frame 16
Page 1 : Frame 18
Page 2 : Frame 26


The Process is divided into 4 pages
The page table for p3
Page 0 : Frame 28
Page 1 : Frame 1
Page 2 : Frame 2
Page 3 : Frame 3

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:2

Enter the process id:p3

The Free frames are:4  6  9  16  18

-------------------------
1.Process request
2.Deallocation
3.Page Table display for all input process
4.Free Frames list display
5.Exit
Enter the choice:5
santhosh@Sandy:~/Desktop$ cd OS_Lab/

*/
