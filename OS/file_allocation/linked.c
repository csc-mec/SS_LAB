#include<stdio.h>
#include<stdlib.h>

#define disk_size 100

int disk[disk_size];
int f_link[disk_size];

int linked(int start, int blocks[], int numb)
{
    int curr = start;
    int flag = 0;

    if(disk[curr] == 0)
    {
        for(int i=0; i<numb; i++)
        {
            if(disk[curr] == 0)
            {
                disk[curr] = 1;
                printf("Block %d has been allocated\n",curr);
                f_link[i] = blocks[i];
                curr = blocks[i];
            }
            else
            {
                printf("Block %d cannot be allocated.\nAllocation Failed\n");
                flag=1;
                return flag;
            }
        }
        f_link[curr] = -1;
        printf("The EOF is at Block %d\n",curr);
    }
    else
    {
        printf("The Starting Block cannot be allocated.\nAllocation Failed\n");
        flag=1;
        return flag;
    }

    return flag;
}

void main()
{
    printf("Linked Allocation of files\n");

    int start,numb;

    printf("Enter the starting block: ");
    scanf("%d",&start);

    printf("Enter the number of blocks for file: ");
    scanf("%d",&numb);

    int blocks[numb];

    printf("Enter the sequence of blocks: ");
    for (int i = 0; i < numb; i++)
    {
        scanf("%d",&blocks[i]);
    } 

    for(int i=0;i<disk_size;i++)
    {
        disk[i] = 0;
    }

    int flag = 0;
    flag = linked(start,blocks,numb);


    if(flag == 0)
    {
        printf("The Block link:\t\t");
        printf("%d(start)->",start);
        for(int i=0; i<numb; i++)
        {
            printf("%d->",f_link[i]);
        }
        printf("EOF");
    }

}