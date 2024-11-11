#include<stdio.h>
#include<stdlib.h>

#define disk_size 100

int disk[disk_size];


void sequential(int start, int size)
{
    for (int i = start; i < start + size; i++) {
        if (i >= disk_size) {
            printf("Block %d is out of disk bounds. Allocation Failed\n", i);
            return;
        }
        if (disk[i] != 0) {
            printf("Block %d is not free to allocate.\nAllocation Failed\n", i);
            return; 
        }
    }

    for (int i = start; i < start + size; i++) {
        disk[i] = 1; 
        printf("Block %d has been successfully allocated to file\n", i);
    }
}


void main()
{
    printf("Sequential File allocation\n");
    
    for(int i=0;i<disk_size;i++)
    {
        if(i%3 == 0)
        {
            disk[i] = 1;
        }
        else
            disk[i] = 0;
    }

    int start,size;
    
    printf("Enter the starting block: ");
    scanf("%d",&start);
    printf("Enter the size of the file: ");
    scanf("%d",&size);

    sequential(start,size);

}