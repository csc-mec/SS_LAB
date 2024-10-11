#include<stdio.h>
#include<stdlib.h>

#define page_size 4096 // page size is 4kb ---- not used practically in the code
#define memory_size 16384 // memory size is 16kb ---- not used practically in the code
#define pagenum 10
#define framenum 10

int pagetable[pagenum];

void initialize()
{
    for(int i=0; i<pagenum; i++)
    {
        pagetable[i] = -1;
    }
}

void loadpage(int pgnum, int frnum)
{
    if(pgnum < pagenum)
    {
        pagetable[pgnum] = frnum;
    }
    else
    {
        printf("Page number out of bounds\n");
    }
}

int printfr(int pgnum)
{
    if(pagetable[pgnum] != -1)
    {
        return pagetable[pgnum];
    }
    else
        return -1;
}

void main()
{
    initialize();

    loadpage(0,7);
    loadpage(3,4);

    for(int i=0; i<pagenum; i++)
    {
        if(printfr(i) != -1)
        {
            printf("The page %d has been assigned to frame %d\n",i,printfr(i));
        }
    }
}