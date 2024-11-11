DATA SEGMENT
    msg1 db 10,13, 'Enter string:$'
    msg2 db 10,13, 'String is Palindrome$'
    msg3 db 10,13, 'String is not Palindrome$'
    str1 db 50 dup(?)
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE,DS:DATA
START:
    MOV AX,DATA
    MOV DS,AX
    LEA DX,msg1
    MOV AH,09H
    INT 21H
     
    LEA SI,str1
    LEA DI,str1

NEXT:
    MOV AH,01H      
    INT 21H          
    CMP AL,13        
    JE TERMINATE     
    MOV [DI],AL      
    INC DI           
    JMP NEXT         


TERMINATE:
    MOV AL,'$'
    MOV [DI],AL
    DEC DI
    MOV BX,DI

DOTHIS:
    MOV AL,[SI]
    CMP AL,[DI]
    JNE NOTPALINDROME
    INC SI
    DEC DI
    CMP SI,DI
    JL DOTHIS

PALINDROME:
    LEA DX,msg2
    MOV AH,09H
    INT 21H
    JMP ENDPROGRAM

NOTPALINDROME:
    LEA DX,msg3
    MOV AH,09H
    INT 21H

ENDPROGRAM:
    MOV AH,4CH
    INT 21H

CODE ENDS
END START
