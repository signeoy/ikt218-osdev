global loadGDT ; gloabal, loadGDT() can be called in other files

loadGDT:
    mov eax, [esp+4] 
    lgdt [eax]       
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    jmp 0x08:.flush

.flush:
    ret

