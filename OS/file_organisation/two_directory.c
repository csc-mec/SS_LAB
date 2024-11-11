#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max_users 15
#define max_files 100

struct File
{
    char name[25];
};

struct User_dir
{
    char username[25];
    struct File files[max_files];
    int filecount;
};

struct User_dir directory[max_users];
int usercount = 0;

void adduser(char *username)
{
    if(usercount<max_users)
    {
        strcpy(directory[usercount].username,username);
        directory[usercount].filecount=0;
        printf("User: %s has been added to directory\n",username);
        usercount++;
    }
    else
    {
        printf("Maximum amount of users reached\n");
        return;
    }
}

void addfileuser(char *file, char *username)
{
    for(int i=0; i<usercount; i++)
    {
        if(strcmp(directory[i].username,username) == 0)
        {
            if(directory[i].filecount < max_files)
            {
                strcpy(directory[i].files[directory[i].filecount].name,file);
                directory[i].filecount++;
                printf("The file %s has been added to user directory %s\n",file,username);
                return;
            }
            else
            {
                printf("User Directory is full\n");
                return;
            }
        }
    }
    printf("User not found\n");
}

void Files_user(char *username)
{
    for(int i=0; i<usercount; i++)
    {
        if(strcmp(directory[i].username,username) == 0)
        {
            printf("Files in User directory %s: \n",username);
            for(int j=0; j<directory[i].filecount;j++)
            {
                printf("%s\n",directory[i].files[j].name);
            }
            return;
        }
    }
    printf("User not found\n");
}

void main()
{
    adduser("Alice");
    adduser("Luna");
    addfileuser("file1.txt","Alice");
    addfileuser("file2.txt","Luna");
    Files_user("Luna");
    Files_user("Alice");
}