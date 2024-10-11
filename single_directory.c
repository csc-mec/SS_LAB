#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max_files 100

struct File
{
    char name[25];
};

struct Directory
{
    struct File files[max_files];
    int filecount;
};

struct Directory directory;

void addfile(char *filename)
{
    if(directory.filecount<max_files)
    {
        strcpy(directory.files[directory.filecount].name, filename);
        printf("File %s has been added\n",filename);
        directory.filecount++;
    }
    else
        printf("Directory is full\n");
}

void printfiles()
{
    printf("The files present in the directory are:\n");
    for(int i=0; i<directory.filecount; i++)
    {
        printf("%s\n",directory.files[i].name);
    }
}

void main()
{
    directory.filecount=0;
    addfile("file1.txt");
    addfile("file2.asm");
    printfiles();
}