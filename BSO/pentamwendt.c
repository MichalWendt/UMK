section .data
PodajLiczbe      db      "Podaj liczbe N: ", 0xa
PodajLiczbeLen equ $ - PodajLiczbe
PoprWynik     db      "Liczba pentagonalna dla N wynosi: ", 0xa
PoprWynikLen equ $ - PoprWynik
ZleWejscie     db      "Nie podano prawidlowej liczby ", 0xa
ZleWejscieLen equ $ - ZleWejscie

SECTION .bss
liczba:      RESW    1       ; reserve space for 1 word

SECTION .text
global  _start

_start:

; Zapytanie o liczbe
    mov     rdx, 17     ; number of bytes to write - one for each letter plus 0xa (line feed character)
    mov     rcx, msg    ; move the memory address of our message string into ecx
    mov     rbx, 1      ; write to the STDOUT file
    mov     rax, 4      ; invoke SYS_WRITE (kernel opcode 4)
    call    odczyt
    mov edx, liczba     ; move value to a register before comparing

    cmp edx, 0
    jl invalidInput

    call    penta       ; call our function to calculate the length of the string
    call    wynik
    int     80h

odczyt:
    mov     rdx, 5          ; number of bytes to read
    mov     rbx, 0          ; write to the STDIN file
    mov     rcx, liczba     ; reserved space to store our input (known as a buffer)
    mov     rax, 3          ; invoke SYS_READ (kernel opcode 3)
    int     80h


penta:
    mov al, [liczba]
    mov bl, [liczba]
    sub al, '0'
    sub bl, '0'
    mul al
    mul ax

    sub ax, bl

    mov ebx, 2          ; move our second number into ebx
    div ebx

    add ax, '0'

    mov [result], ax    ; move the result

wynik:                  ; Print on screen the result
    mov eax, 4
    mov ebx, 1
    mov ecx, result
    mov edx, 1
    int 80h

invalidInput:
    mov rdx, 30             ; message length
    mov rcx, msg3           ; message to write
    mov rbx, 1              ; file descriptor for stdout
    mov rax, 4              ; system call for sys_write
    int 0x80                ; call kernel


    mov rdx, 34             ; message length
    mov rcx, msg2           ; message to write
    mov rbx, 1              ; file descriptor for stdout
    mov rax, 4              ; system call for sys_write
    int 0x80
    mov     rbx, 0      ; return 0 status on exit - 'No Errors'
    mov     rax, 1      ; invoke SYS_EXIT (kernel opcode 1)
    int     80h
