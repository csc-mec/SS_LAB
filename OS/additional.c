#include<stdio.h>
int main(){
    int n,m;
    printf("Enter no. of Processes:");
    scanf("%d",&n);
    printf("Enter no. of resources:");
    scanf("%d",&m);
    int Allocation[n][m],Max[n][m],Available[m],Need[n][m],Work[m],Finish[n],safesequence[n],ind=0,completed=0;
    printf("Enter Allocation matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&Allocation[i][j]);
        }
    }
    printf("Enter Maximum matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&Max[i][j]);
        }
    }
    printf("Enter Available Resources:");
    for(int i=0;i<m;i++){
        scanf("%d",&Available[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            Need[i][j]=Max[i][j]-Allocation[i][j];
        }
    }
    for(int i=0;i<n;i++){
        Finish[i]=0;
    }
    for(int i=0;i<m;i++){
        Work[i]=Available[i];
    }
while(completed!=n){
    for(int i=0;i<n;i++){
        if(Finish[i]==0){
            int flag=0;
            for(int j=0;j<m;j++){
                if(Need[i][j]>Work[j]){
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                safesequence[ind++]=i;
                for(int k=0;k<m;k++){
                    Work[k]+=Allocation[i][k];
                }
                Finish[i]=1;
                completed++;
            }
        }
    }
}
    printf("Need Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",Need[i][j]);
        }
        printf("\n");
    }
    printf("Safe Sequence:");
    for(int i=0;i<n;i++){
        printf("%d\t",safesequence[i]);
    }
}



//Scan algorithm.

#include <stdio.h>
#include <stdlib.h>


void main()
{
    int n, total_move = 0, intial, direction;
    printf("Enter the number of sequences :");
    scanf("%d",&n);
    int rs[n];
    printf("Enter the request string");
    for (int i=0 ; i<n; i++)
    {
        scanf("%d",&rs[i]);
    }
    printf("Enter the initial position :");
    scanf("%d",&intial);

    printf("Enter the direction for movement :(0-low or 1-high)");
    scanf("%d",&direction);
    int left[n], right[n], left_size=0, right_size=0;

    for (int i=0; i<n; i++)
    {
        if (rs[i] < intial)
        left[left_size++] = rs[i];
        else
        right[right_size++] = rs[i];
    }

    for(int i=0 ; i<left_size-1; i++)
    {
        for (int j=0 ; j<left_size-1-i; j++)
        {
            if (left[j]>left[j+1])
            {
                int temp = left[j+1];
                left[j+1] = left[j];
                left[j] = temp;
            }
        }
    }

    for(int i=0 ; i<right_size-1; i++)
    {
        for (int j=0 ; j<right_size-1-i; j++)
        {
            if (right[j]>right[j+1])
            {
                int temp = right[j+1];
                right[j+1] = right[j];
                right[j] = temp;
            }
        }
    }

    printf("Prining the sorted array's\n");

    for(int i=0 ; i<left_size; i++)
    printf("%d\t",left[i]);

    printf("\n");

    for(int i=0 ; i<right_size; i++)
    printf("%d\t",right[i]);

    if (direction==1)
    {

        for (int i=0 ; i<right_size; i++)
        {
            total_move += abs(right[i]-intial);
            intial = right[i];
        }
        

        for (int i=left_size-1; i>=0; i--)
        {
            total_move += abs(left[i]- intial);
            intial = left[i];
        }

        printf("Total movement : %d",total_move);
    }
    else
    {
        for (int i=left_size-1 ; i>=0; i--)
        {
            total_move+= abs(left[i]-intial);
            intial = left[i];
        }

        for (int j=0; j<right_size; j++)
        {
            total_move += abs(right[j]-intial);
            intial = right[j];
        }
        printf("Total movement : %d",total_move);
    }
}



//CSCAN 

#include <stdio.h>
#include <stdlib.h>

void main ()
{
     int n, total_move = 0, initial, direction, disk_size;
    printf("Enter the number of sequences :");
    scanf("%d",&n);
    int rs[n];
    printf("Enter the request string");
    for (int i=0 ; i<n; i++)
    {
        scanf("%d",&rs[i]);
    }
    printf("Enter the initial position and the disk size:");
    scanf("%d%d",&initial,&disk_size);

    int left[n], right[n], left_size=0, right_size=0;

    for (int i=0; i<n; i++)
    {
        if (rs[i]<initial)
        {
            left[left_size++] = rs[i];
        }
        else
        right[right_size++] = rs[i];
    }

    for(int i=0 ; i<left_size-1; i++)
    {
        for (int j=0 ; j<left_size-1-i; j++)
        {
            if (left[j]>left[j+1])
            {
                int temp = left[j+1];
                left[j+1] = left[j];
                left[j] = temp;
            }
        }
    }

    for(int i=0 ; i<right_size-1; i++)
    {
        for (int j=0 ; j<right_size-1-i; j++)
        {
            if (right[j]>right[j+1])
            {
                int temp = right[j+1];
                right[j+1] = right[j];
                right[j] = temp;
            }
        }
    }

    printf("Printing the sorted array's\n");

    for(int i=0 ; i<left_size; i++)
    printf("%d\t",left[i]);

    printf("\n");

    for(int i=0 ; i<right_size; i++)
    printf("%d\t",right[i]);

    for(int i=0 ; i< right_size; i++)
    {
        total_move+= abs(right[i]- initial);
        initial = right[i];
    }

    total_move += abs(disk_size-1-initial);
    initial = 0;

    for (int i=0 ; i<left_size; i++)
    {
        total_move+= abs(left[i]-initial);
        initial = left[i];
    }


    printf("The total head movement is : %d", total_move);

}


//LRU 

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 
#define MAX_PAGES 20 

int frames[MAX_FRAMES];
int counter[MAX_FRAMES]; 

void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; 
        counter[i] = 0;
    }
}

void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int findLRU() {
    int max = counter[0];
    int lru_frame = 0;

    for (int i = 1; i < MAX_FRAMES; i++) {
        if (counter[i] > max) {
            max = counter[i];
            lru_frame = i;
        }
    }

    return lru_frame;
}

void LRU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                printf("page %d is already there \n",page);
                break;
            }
        }

        if (!found) {
            int lru_frame = findLRU();
            printf("page %d is loaded in frame %d\n",page,lru_frame);
            frames[lru_frame] = page;
            counter[lru_frame] = 0;
            page_faults++;
        }

        for (int j = 0; j < MAX_FRAMES; j++) {
            counter[j]++;
        }

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                counter[j] = 0;
                break;
            }
        }
        displayFrames();
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES]; 

    int n;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    initialize(); 
    LRU(pages, n);

    return 0;
}

//LFU

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 
#define MAX_PAGES 20 

int frames[MAX_FRAMES]; 
int counts[MAX_FRAMES]; 

void initialize() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        counts[i] = 0; 
    }
}

void displayFrames() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int findLFU() {
    int min = counts[0];
    int lfu_frame = 0;

    for (int i = 1; i < MAX_FRAMES; i++) {
        if (counts[i] < min) {
            min = counts[i];
            lfu_frame = i;
        }
    }

    return lfu_frame;
}

void LFU(int pages[], int n) {
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                counts[j]++;
                printf("page %d is already in memory\n",page);
                break;
            }
        }

        if (!found) {
            int lfu_frame = findLFU();
            frames[lfu_frame] = page;
            counts[lfu_frame] = 1;
            page_faults++;
            printf("page %d is loaded in frame %d\n",page,lfu_frame);
        }
        displayFrames();
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[MAX_PAGES];

    int n;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    initialize(); 
    LFU(pages, n);

    return 0;
}

