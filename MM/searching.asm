data segment
    msg1 db 10,13, 'Enter the character to search: $'
    msg2 db 10,13, 'Character found in the string$'
    msg3 db 10,13, 'Character not found in the string $'
    search_char db ?
    msg4 db 10,13, 'Starting the program$'
    string db 10,13, 'Hello, World$'
data ends

code segment
ASSUME  cs:code, ds:data

start:
    mov ax, data
    mov ds, ax
    
    lea dx, msg4      ; printing starting the program
    mov ah, 09h
    int 21h       
    
    lea dx , msg1   ; printing to input the character
    mov ah , 09h
    int 21h  
    
    mov ah, 01h       ; accepting user input for the character
    int 21h
    mov search_char, al  
    
    lea si, string     ;loading the string 'hello world' into si
    
search_loop:    
    mov al , [si]
    cmp al , '$'            ; comparing with end of string
    je not_found
    cmp al , search_char
    je found
    inc si
    jmp search_loop

found:
    lea dx , msg2
    mov ah , 09h
    int 21h
    jmp end

not_found:
    lea dx, msg3
    mov ah, 09h
    int 21h
    jmp end

end:
    mov ah, 4ch
    int 21h
    
    
