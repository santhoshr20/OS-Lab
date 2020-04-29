#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct File
{
    char name[25];
    int start_address;
} File;
#define MAX 100
#define MAX_DIR 3
#define MAX_FILE 3
typedef struct Directory
{
    char name[25];
    struct Directory *subdir[MAX_DIR];
    File *f[MAX_FILE];
} Directory;
void init_dir(Directory *dir)
{
    strcpy(dir->name, "");
    for (int i = 0; i < 3; i++)
        dir->f[i] = dir->subdir[i] = NULL;
}
void insertFileSingleLevel(File *root[])
{
    File *tmp = (File *)malloc(sizeof(File));
    printf("Enter the name of the file: ");
    scanf("%[^\n]", tmp->name);
    tmp->start_address =250 * (random() % 20);

    int found = 0;

    for (int i = 0; i < MAX; i++)
        if (root[i] == NULL)
        {
            root[i] = tmp;
            break;
        }
        else if (strcmp(root[i]->name, tmp->name) == 0)
        {
            found = 1;
            break;
        }

    if (found)
        printf("File already exists!\n");
    else
        printf("File has been added successfully!\n");
}
void displaySingleLevel(File *root[])
{
    if (!root[0])
        printf("Empty Directory!\n");
    else
    {
        
        printf("\n           File Name          Start Address  \n");
        printf("---------------------------------------------\n");
        for (int i = 0; i < MAX && root[i]; i++)
            printf("   %-25s       %-4d       \n", root[i]->name, root[i]->start_address);
        printf("---------------------------------------------\n");
    }
}
void insertDirectoryTree(Directory *root)
{
    char path[100];
    printf("Enter path to directory ([root/.../...]): ");
    scanf("%[^\n]", path);

    char *dir, *new_dir;
    Directory *cd = root;

    int found = 0, created = 0;

    dir = strtok(path, "/");
    if (strcmp(path, "root"))
    {
        printf("Path doesn't start with root!\n");
        return;
    }
    dir = strtok(NULL, "/");
    if (!dir)
    {
        printf("\nInvalid Directory Name!\n");
        return;
    }
    while (dir != NULL)
    {
        for (int i = 0; i < MAX_DIR; i++)
        {
            if (cd->subdir[i])
                if (strcmp(dir, cd->subdir[i]->name) == 0)
                {
                    cd = cd->subdir[i];
                    found = 1;
                    break;
                }
        }
        new_dir = dir;
        dir = strtok(NULL, "/");
        if (!found)
            break;
    }
    if (dir == NULL)
    {
        for (int i = 0; i < MAX_DIR; i++)
            if (!cd->subdir[i])
            {
                cd->subdir[i] = (Directory *)malloc(sizeof(Directory));
                init_dir(cd->subdir[i]);
                strcpy(cd->subdir[i]->name, new_dir);
                created = 1;
                break;
            }
            else if (strcmp(cd->subdir[i]->name, new_dir) == 0)
                break;
    }

    if (created)
        printf("Directory has been added successfully!\n");
    else
        printf("Unable to create directory!\n");
}
void insertFileTree(Directory *root)
{
    char path[100];
    printf("Enter path to files([root/.../...]): ");
    scanf("%[^\n]", path);

    char *dir, *new_file;
    Directory *cd = root;

    int found = 0, created = 0;

    dir = strtok(path, "/");
    if (strcmp(path, "root"))
    {
        printf("Path doesn't start with root!\n");
        return;
    }
    dir = strtok(NULL, "/");
    while (dir != NULL)
    {
        for (int i = 0; i < MAX_DIR; i++)
        {
            if (cd->subdir[i])
                if (strcmp(dir, cd->subdir[i]->name) == 0)
                {
                    cd = cd->subdir[i];
                    found = 1;
                    break;
                }
        }
        new_file = dir;
        dir = strtok(NULL, "/");
        if (!found)
            break;
    }
    if (dir == NULL)
    {
        for (int i = 0; i < MAX_DIR; i++)
            if (!cd->f[i])
            {
                cd->f[i] = (File *)malloc(sizeof(File));
                strcpy(cd->f[i]->name, new_file);
                created = 1;
                break;
            }
            else if (strcmp(cd->f[i]->name, new_file) == 0)
                break;
    }

    if (created)
        printf("File has been added succesfully!\n");
    else
        printf("Error in creating File!\n");
}
void displayTree( Directory *dir, char path[100])
{
    for (int i = 0; i < MAX_FILE; i++)
        if (dir->f[i])
            printf("   %-25s   %-35s  \n", dir->f[i]->name, path);

    for (int i = 0; i < MAX_DIR; i++)
        if (dir->subdir[i])
        {
            strcat(path, "/");
            strcat(path, dir->subdir[i]->name);
            displayTree(dir->subdir[i], path);
        }
}
int main()
{
    int choice, count = 0;
    char name[30];
    char path[100];

    File *arr[MAX], *tmp = NULL;
    for (int i = 0; i < MAX; i++)
        arr[i] = NULL;

    Directory root;
    init_dir(&root);
    strcpy(root.name,"root");

    while (1)
    {
        printf("\n\tFile Organisation techinques\n");
        printf("1.Single Level Directory\n");
        printf("2.Tree Structure Directory\n");
        printf("3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            while (1)
            {
                printf("\n\n\tSingle Level Directory\n");
                printf("1.Create a file\n");
                printf("2.List all files\n");
                printf("3.Back\n");
                printf("Enter choice: ");
                scanf("%d", &choice);
                getchar();
                if (choice == 3)
                    break;

                switch (choice)
                {
                case 1:
                    insertFileSingleLevel(arr);
                    break;
                case 2:
                    displaySingleLevel(arr);
                    break;
                default:
                    printf("Invalid Input!\n");
                }
            }
            break;
        case 2:
            while (1)
            {
                printf("\n\n\tTree Structure Directory\n");
                printf("1.Create a file\n");
                printf("2.Create a directory\n");
                printf("3.List all files\n");
                printf("4.Back\n");
                printf("Enter your choice:");
                scanf("%d", &choice);
                getchar();
                if (choice == 4)
                    break;

                switch (choice)
                {
                case 1:
                    insertFileTree(&root);
                    break;
                case 2:
                    insertDirectoryTree(&root);
                    break;
                case 3:
                    strcpy(path, "/root");
                    
                    printf("           File Name                      Path                \n");
                    printf("-------------------------------------------------------------------\n");
                    displayTree(&root, path);
                    printf("-------------------------------------------------------------------\n");
                    break;
                default:
                    printf("Invalid Input!\n");
                }
            }
            break;
		case 3:
            exit(0);
        
        default:
            printf("Invalid Input!\n");
            break;
        }
    }
}

/*

OUTPUT:



santhosh@Sandy:~/Desktop/OS_Lab$ gcc 185001135-EX_13.c -o 185001135-EX_13out
santhosh@Sandy:~/Desktop/OS_Lab$ ./185001135-EX_13out
	File Organisation techinques
1.Single Level Directory
2.Tree Structure Directory
3.Exit
Enter your choice: 1


	Single Level Directory
1.Create a file
2.List all files
3.Back
Enter choice: 1
Enter the name of the file: Inception.c
File has been added successfully!


	Single Level Directory
1.Create a file
2.List all files
3.Back
Enter choice: 1
Enter the name of the file: Interstellar.c
File has been added successfully!


	Single Level Directory
1.Create a file
2.List all files
3.Back
Enter choice: 1
Enter the name of the file: Memento.txt
File has been added successfully!


	Single Level Directory
1.Create a file
2.List all files
3.Back
Enter choice: 1   
Enter the name of the file: Interstellar.c
File already exists!


	Single Level Directory
1.Create a file
2.List all files
3.Back
Enter choice: 2

           File Name          Start Address  
---------------------------------------------
   Inception.c                     750        
   Interstellar.c                  1500       
   Memento.txt                     4250       
---------------------------------------------


	Single Level Directory
1.Create a file
2.List all files
3.Back
Enter choice: 3

	File Organisation techinques
1.Single Level Directory
2.Tree Structure Directory
3.Exit
Enter your choice: 2


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:1
Enter path to files([root/.../...]): root/hi.txt  
File has been added succesfully!


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:3
           File Name                      Path                
-------------------------------------------------------------------
   hi.txt                      /root                                
-------------------------------------------------------------------


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:2      
Enter path to directory ([root/.../...]): root/Screenplay
Directory has been added successfully!


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:1
Enter path to files([root/.../...]): root/Screenplay/Inception.txt
File has been added succesfully!


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:3
           File Name                      Path                
-------------------------------------------------------------------
   hi.txt                      /root                                
   Inception.txt               /root/Screenplay                     
-------------------------------------------------------------------


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:1
Enter path to files([root/.../...]): root/Handcricket.py
File has been added succesfully!


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:2
Enter path to directory ([root/.../...]): root/Screenplay/Favourite   
Directory has been added successfully!


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:1
Enter path to files([root/.../...]): root/Screenplay/Favourite/Dunkirk.txt
File has been added succesfully!


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:3
           File Name                      Path                
-------------------------------------------------------------------
   hi.txt                              /root                                
   Handcricket.py             /root                                
   Inception.txt               /root/Screenplay                     
   Dunkirk.txt                 /root/Screenplay/Favourite           
-------------------------------------------------------------------


	Tree Structure Directory
1.Create a file
2.Create a directory
3.List all files
4.Back
Enter your choice:4

	File Organisation techinques
1.Single Level Directory
2.Tree Structure Directory
3.Exit
Enter your choice: 3
santhosh@Sandy:~/Desktop/OS_Lab/

*/