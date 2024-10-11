#include<stdio.h>
#include<stdlib.h>


#define num_seg 2
#define seg_size 2
#define page_size 4096
#define memory_size 16384  // number of frames = 16384/4096 = 4 frames

int segtb[num_seg][seg_size];
int frametb[memory_size/page_size];
int curr_fr = 0;
int pagefaults = 0;

void initialize()
{
    for(int i=0; i<num_seg; i++)
    {
        for (int j = 0; j<seg_size; j++)
        {
            segtb[i][j] = -1;
        }
        
    }
    for (int j = 0; j<(memory_size/page_size); j++)
    {
        frametb[j] = -1;
    }
}

void faulthandle(int segnum,int pagenum)
{
    printf("Pagefault at occured for segement %d, page %d\n",segnum,pagenum);
    pagefaults++;

    if(frametb[curr_fr] != -1) //resetting pagenumber to -1 in page table as the page is removed from frame
    {
        segtb[segnum][frametb[curr_fr]] = -1;
    }

    frametb[curr_fr] = segnum*seg_size+pagenum; //
    segtb[segnum][pagenum] = curr_fr;

    curr_fr = (curr_fr + 1) % (memory_size/page_size);
}

void getpage(int segnum,int pagenum)
{
    if(segtb[segnum][pagenum] == -1)
    {
        faulthandle(segnum,pagenum);
    }
    else
        printf("The page %d is in frame %d\n",pagenum,segtb[segnum][pagenum]);
}

void main()
{
    initialize();

    getpage(0,0);
    getpage(0,1);
    getpage(0,0);
    getpage(1,1);

    printf("Total number of pagefaults: %d\n",pagefaults);
}