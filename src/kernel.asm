; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start


extern GDT_DESC
extern IDT_DESC
extern idt_inicializar
extern mmu_inicializar
extern mmu_inicializar_dir_kernel
extern resetear_pic
extern habilitar_pic
extern imprimirJuego_inicial




%define PAGE_DIRECTORY_KERNEL   0x27000
%define PAGE_TABLE_KERNEL_1     0x28000
%define PAGE_TABLE_KERNEL_2     0x68000
%define PANTALLA_MAPA           0x400000



;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; xchg bx, bx

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0xC, 0, 0

    ; habilitar A20
    call habilitar_A20

    ; cargar la GDT
    lgdt [GDT_DESC]

    ; setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 1 
    mov cr0, eax

    ; pasar a modo protegido
    jmp 0x90:modoProtegido
BITS 32
modoProtegido:

    ; acomodar los segmentos
    xor ax, ax
    mov ax, 0x98 ;indice del segmento de datos * 8
    mov ds, ax      
    mov ss, ax      
    mov es, ax      
    mov fs, ax      
    xor ax, ax
    mov ax, 0xB0 ;indice del segmento de video * 8
    mov gs, ax

    ; setear la pila
    mov esp, 0x27000
    mov ebp, esp

    ; pintar pantalla, todos los colores, que bonito!
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0xC, 2, 0

    mov edi, 10
    mov esi, 10

    push edi
    push esi

    add esp, 2*4


    ; inicializar el manejador de memoria
    call mmu_inicializar
    ; inicializar el directorio de paginas
    call mmu_inicializar_dir_kernel
    mov eax, PAGE_DIRECTORY_KERNEL
    mov cr3, eax

    ; inicializar memoria de tareas

    ; habilitar paginacion
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    ; inicializar tarea idle

    ; inicializar todas las tsss

    ; inicializar entradas de la gdt de las tsss

    ; inicializar el scheduler

    ; inicializar la IDT
    call idt_inicializar
    LIDT [IDT_DESC]
    ; configurar controlador de interrupciones
    call resetear_pic
    call habilitar_pic

    ; cargar la tarea inicial

    ; saltar a la primer tarea
    
    ;call imprimirJuego_inicial


    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
