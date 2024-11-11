#include<stdio.h>
#include<stdlib.h>

#define disk_size 100

int disk[disk_size];

void indexed(int indexb,int blocks[],int numb)
{
    if(disk[indexb] == 0)
    {
        printf("The Index Block has been allocated\n");
        for(int i=0; i<numb; i++)
        {
            if(disk[blocks[i]] == 0)
            {
                disk[blocks[i]] = 1;
                printf("Block %d has been allocated.\n",blocks[i]);
            }
            else
            {
                printf("Block %d cannot be allocated.\nAllocation Failed\n",blocks[i]);
                return;
            }
        }
    }
    else
    {
        printf("The Index block cannot be allocated.\nAllocation Failed\n");
        return;
    }
}

void main()
{
    printf("Indexed Allocation of Files\n");

    int indexb,numb;

    printf("Enter the indexblock number: ");
    scanf("%d",&indexb);

    printf("Enter the number of blocks needed for the file: ");
    scanf("%d",&numb);

    int blocks[numb];
    
    printf("Enter the sequence of indexes: ");
    for (int i = 0; i < numb; i++)
    {
        scanf("%d",&blocks[i]);
    }
    
    for(int i=0;i<disk_size;i++)
    {
        disk[i] = 0;
    }

    indexed(indexb,blocks,numb);

}