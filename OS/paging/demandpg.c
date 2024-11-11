#include<stdio.h>
#include<stdlib.h>

#define maxpg 4
#define maxfr 2

int pagetb[maxpg];
int frametb[maxfr];
int pagefaults = 0;
int curr_frame = 0;

void faulthandle(int pagenum)
{
    printf("Pagefault at occured for page %d\n",pagenum);
    pagefaults++;

    if(frametb[curr_frame] != -1) //resetting pagenumber to -1 in page table as the page is removed from frame
    {
        pagetb[frametb[curr_frame]] = -1;
    }

    frametb[curr_frame] = pagenum;
    pagetb[pagenum] = curr_frame;
    curr_frame = (curr_frame + 1) % maxfr; 
}

void getpage(int pagenum)
{
    if(pagetb[pagenum] == -1)
    {
        faulthandle(pagenum);
    }
    else
        printf("The page %d is in frame %d\n",pagenum,pagetb[pagenum]);
}

void main()
{
    for(int i=0; i<maxfr; i++)
    {
        frametb[i] = -1;
    }
    for(int i=0; i<maxpg; i++)
    {
        pagetb[i] = -1;
    }


    getpage(0);
    getpage(1);
    getpage(2);
    getpage(0);

    printf("Total number of pagefaults: %d\n",pagefaults);

}


