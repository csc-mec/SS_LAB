#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
char hex(int a)
{
    switch (a)
    {
        case 0   :return '0';
        case 1   :return '1';
        case 10  :return '2';
        case 11  :return '3';
        case 100 :return '4';
        case 101 :return '5';
        case 110 :return '6';
        case 111 :return '7';
        case 1000:return '8';
        case 1001:return '9';
        case 1010:return 'A';
        case 1011:return 'B';
        case 1100:return 'C';
        case 1101:return 'D';
        case 1110:return 'E';
        case 1111:return 'F';
        default  :return '0';
    }
}
void main()
{
    char loc[10],opcode[10],label[10],operand[10],mnemonic[10],code[10],addr[10],objectcode[10];
    FILE *input,*output,*symtab,*optab,*ofile;
    int locctr,start,length,end; 
    bool err = false,found_opcode,found_symbol;
    input=fopen("intermediate.txt","r");
    output=fopen("objectcode.txt","w");
    optab=fopen("optab.txt","r");
    symtab=fopen("symtab.txt","r");
    ofile=fopen("objectfile.txt","w");

    fscanf(input,"%s\t%s\t%s\t%s",loc,label,opcode,operand);
    if(strcmp(opcode,"START")==0)
    {
        fprintf(output,"%s\t%s\t%s\t%s\t-\n",loc,label,opcode,operand);
        fprintf(ofile,"H^%s^%s",label,operand);
        start=atoi(operand);
        fscanf(input,"%s\t%s\t%s\t%s",loc,label,opcode,operand);

    }
    else{fprintf(ofile,"H^-^%s",loc);start=atoi(loc);}
    while(strcmp(opcode,"END")!=0)
    {
        end=atoi(loc);
        strcpy(objectcode,"-");
        fseek(optab,SEEK_SET,0);
        fscanf(optab,"%s\t%s",code,mnemonic);
        found_opcode=false;
        fprintf(output,"%s\t%s\t%s\t%s\t",loc,label,opcode,operand);
        while(strcmp(code,"END")!=0)
        {
            if(strcmp(code,opcode)==0)
            {
                if(strcmp(operand,"-")!=0)
                {
                    found_symbol=false;
                    char symbol[10],loc[10];
                    fseek(symtab,SEEK_SET,0);
                    do
                    {
                        fscanf(symtab,"%s\t%s",symbol,loc);
                        if(strcmp(symbol,operand)==0)
                        {
                            strcpy(addr,loc);
                            found_symbol=true;
                            break;
                        }
                    }while(!feof(symtab));
                    if(!found_symbol)
                    {
                        err=true;
                        printf("Invalid Symbol %s\n",operand);
                        exit(0);
                    }
                }
                else{strcpy(addr,"0000");}
                found_opcode=true;
                end+=3;
                fprintf(output,"%s%s",mnemonic,addr);
                break;
            }
            fscanf(optab,"%s\t%s",code,mnemonic);
        }
        if(strcmp(opcode,"BYTE")==0)
        {
            if(operand[0]=='X')
            {
                strncpy(objectcode,operand+2,2);
                fprintf(output,"%s",objectcode);
                end+=1;
            }
            else
            {
                char temp[10];
                strncpy(temp,operand+2,strlen(operand)-3);
                if(strlen(operand)-3<3){
                    for(int i=0;i<3-strlen(operand)+3;i++){
                        fprintf(output,"00");
                    }
                }
                for (int i=0;i<strlen(operand)-3;i=i+1)
                {
                    int ascii=temp[i];
                    int arr[8];
                    int x=0 , ind=0;
                    while(ascii>0){
                        arr[ind]=ascii%2;
                        ind+=1;
                        ascii/=2;
                    }
                    while(ind>-1){
                        x=x*10+arr[ind];
                        ind--;
                    }
                    printf("%c\n",ascii);
                    fprintf(output,"%c%c",hex(x/10000),hex(x%10000));
                }
                end+=strlen(operand)-3;
            }
        }
        else if(strcmp(opcode,"WORD")==0)
        {
            int x = atoi(operand);
            char bin[40]="",word[10]="",temp3[40]="";
            while(x != 0)
            {
                strcpy(temp3,(x%2==0?"0":"1"));
                strcat(temp3,bin);
                strcpy(bin,temp3);
                x=x/2;
            }
            int index=strlen(bin)-1;
            while(index>=3)
            {
                char nibble[5];
                nibble[4]='\0';
                strncpy(nibble,bin+(index-3),4);
                char temp[10];
                char temp2[2]="\0";
                temp2[0]=hex(atoi(nibble));
                strcpy(temp,temp2);
                strcat(temp,word);
                strcpy(word,temp);
                index=index-4;
            }
            char nibble[index+1];
            nibble[index]='\0';
            strncpy(nibble,bin,index+1);
            char temp[10];
            char temp2[2]="\0";
            temp2[0]=hex(atoi(nibble));
            strcpy(temp,temp2);
            strcat(temp,word);
            strcpy(word,temp);
            int len2=strlen(word);
            if(len2<6)
            {
                for(int i=0;i<6-len2;i=i+1)
                {
                    fprintf(output,"0");
                }
            }
            fprintf(output,"%s",word);
            end+=3;
        }
        else if(strcmp(opcode,"RESB")==0){
            fprintf(output,"-");
            end+=atoi(operand);
        }
        else if(strcmp(opcode,"RESW")==0){
            fprintf(output,"-");
            end+=3*atoi(operand);
        }
        fprintf(output,"\n");
        //printf("done\n");
        fscanf(input,"%s\t%s\t%s\t%s",loc,label,opcode,operand);
    }
    fprintf(output,"%s\t%s\t%s\t%s\t-\n",loc,label,opcode,operand);
    fclose(input);
    fclose(output);
    fclose(symtab);
    fclose(optab);
    length=end-start;
    output=fopen("objectcode.txt","r");
    fprintf(ofile,"^%d\n",length);
    char arr[10][10];
    int index=0;
    fscanf(output,"%s\t%s\t%s\t%s\t%s",loc,label,opcode,operand,objectcode);
    if(strcmp(opcode,"START")==0){fscanf(output,"%s\t%s\t%s\t%s\t%s",loc,label,opcode,operand,objectcode);}
    while(strcmp(opcode,"END")!=0 && !feof(output))
    {
        strcpy(arr[index++],objectcode);
        if(index==1){
            fprintf(ofile,"T^%s^",loc);
        }
        else if(index==10){
            fprintf(ofile,"1E");
            for(int i=0;i<index;i++){
                fprintf(ofile,"^%s",arr[i]);
            }
            fprintf(ofile,"\n");
            index=0;
        }
        fscanf(output,"%s\t%s\t%s\t%s\t%s",loc,label,opcode,operand,objectcode);
    }
    int ascii=index;
    int arr1[8];
    int x=0 , ind=0;
    while(ascii>0){
        arr1[ind]=ascii%2;
        ind+=1;
        ascii/=2;
    }
    while(ind>-1){
        x=x*10+arr1[ind];
        ind--;
    }
    fprintf(ofile,"%c%c",hex(x/10000),hex(x%10000));
    for(int i=0;i<index;i++){
        fprintf(ofile,"^%s",arr[i]);
    }
    fprintf(ofile,"\n");
    fprintf(ofile,"E^%d",start);
    fclose(ofile);
    fclose(output);
}

/*
INTERMEDIATE FILE

-	-	START	2000
2000	-	LDA	FIVE
2003	-	STA	ALPHA
2006	-	LDCH	CHARZ
2009	-	STCH	C1
2012	ALPHA	RESW	2
2018	FIVE	WORD	5
2021	CHARZ	BYTE	C'Z'
2022	C1	RESB	1
-	-	END	-

OPCODE TABLE

LDA 03
STA	0F
LDCH	53
STCH	57
END -

SYMTAB

ALPHA	2012
FIVE	2018
CHARZ	2021
C1	2022

OBJECT CODE

-	-	START	2000	-
2000	-	LDA	FIVE	032018
2003	-	STA	ALPHA	0F2012
2006	-	LDCH	CHARZ	532021
2009	-	STCH	C1	572022
2012	ALPHA	RESW	2	-
2018	FIVE	WORD	5	000005
2021	CHARZ	BYTE	C'Z'	00005A
2022	C1	RESB	1	
-	-	END	-	-

OBJECT FILE

H^-^2000^23
T^2000^08^032018^0F2012^532021^572022^-^000005^00005A^-
E^2000

*/
