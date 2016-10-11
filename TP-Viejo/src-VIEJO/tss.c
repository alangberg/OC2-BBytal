/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"
#include "gdt.h"
#include "mmu.h"
#include "screen.h"


tss tss_idle;
tss tss_inicial;
gdt_entry gdt[GDT_COUNT];

void tss_nueva_tarea(unsigned int* code, posicion pos, unsigned short* gdtEntry, unsigned int* cr3) {

    tss* tss_nueva = (tss*) mmu_proxima_pagina_fisica_libre();
    unsigned int i = tarea_gdt_libre();

    unsigned int nuevaCR3 = mmu_inicializar_dir_tarea(code, pos);
    tss_nueva->esp0 = mmu_proxima_pagina_fisica_libre() + PAGE_SIZE;    //Prox pagina fisica libre
    tss_nueva->ss0 = GDT_POSICION_DATA_KERNEL;  
    tss_nueva->cr3 = nuevaCR3;
    tss_nueva->eip = DIR_VIRTUAL_TAREA;
    tss_nueva->esp = DIR_VIRTUAL_TAREA + 0x1000;
    tss_nueva->ebp = DIR_VIRTUAL_TAREA + 0x1000;
    tss_nueva->eflags = 0x202;
    tss_nueva->es = (GDT_POSICION_DATA_USER | 0x3);
    tss_nueva->cs = (GDT_POSICION_CODE_USER | 0x3);
    tss_nueva->ss = (GDT_POSICION_DATA_USER | 0x3);
    tss_nueva->ds = (GDT_POSICION_DATA_USER | 0x3);
    tss_nueva->fs = (GDT_POSICION_DATA_USER | 0x3);
    tss_nueva->gs = (GDT_POSICION_DATA_USER | 0x3);

    *gdtEntry = (unsigned short) i << 3;
    *cr3 = (unsigned int) nuevaCR3;
    
    gdt[i] = (gdt_entry) {
        (unsigned short)    sizeof(tss)-1,                          /* limit[0:15]  */ 
        (unsigned short)    (unsigned int) tss_nueva,               /* base[0:15]   */
        (unsigned char)     ((unsigned int) tss_nueva >> 16),       /* base[23:16]  */
        (unsigned char)     0x09,                                   /* type         */
        (unsigned char)     0x00,                                   /* s            */
        (unsigned char)     0x00,                                   /* dpl          */
        (unsigned char)     0x01,                                   /* p            */
        (unsigned char)     0x00,//(sizeof(tss)-1) >> 16,           /* limit[16:19] */
        (unsigned char)     0x00,                                   /* avl          */
        (unsigned char)     0x00,                                   /* l            */
        (unsigned char)     0x01,                                   /* db           */
        (unsigned char)     0x00,                                   /* g            */
        (unsigned char)     ((unsigned int) tss_nueva >> 24),       /* base[31:24]  */
    };

}


unsigned int tarea_gdt_libre(){
    
    unsigned int i = 11;
    while (i < 50 && gdt[i].p == 1) i++;
    return i;
}


void tss_inicializar_idle() {
//seteo campos tss_idle
    tss_idle.cr3 = 0x27000;
    tss_idle.eip = 0x10000;
    tss_idle.eflags = 0x202;
    tss_idle.esp = 0x27000;
    tss_idle.ebp = tss_idle.esp;
    tss_idle.es = GDT_POSICION_DATA_KERNEL;
    tss_idle.cs = GDT_POSICION_CODE_KERNEL;
    tss_idle.ss = GDT_POSICION_DATA_KERNEL;
    tss_idle.ds = GDT_POSICION_DATA_KERNEL;
    tss_idle.fs = GDT_POSICION_DATA_KERNEL;
    tss_idle.gs = GDT_POSICION_DATA_KERNEL;
    //tss_idle.iomap = 0xFFFF;

//DESCRIPTOR TAREA INICIAL
    gdt[9] = (gdt_entry) {
        (unsigned short)    sizeof(tss)-1,                                  /* limit[0:15]  */ 
        (unsigned short)    (unsigned int) &tss_inicial,                    /* base[0:15]   */
        (unsigned char)     (unsigned int) &tss_inicial >> 16,              /* base[23:16]  */
        (unsigned char)     0x09,                                           /* type         */
        (unsigned char)     0x00,                                           /* s            */
        (unsigned char)     0x00,                                           /* dpl          */ 
        (unsigned char)     0x01,                                           /* p            */
        (unsigned char)     (sizeof(tss)-1) >> 16,                          /* limit[16:19] */
        (unsigned char)     0x00,                                           /* avl          */
        (unsigned char)     0x00,                                           /* l            */
        (unsigned char)     0x01,                                           /* db           */
        (unsigned char)     0x00,                                           /* g            */
        (unsigned char)     (unsigned int) &tss_inicial >> 24,              /* base[31:24]  */
    };
//DESCRIPTOR IDLE
    gdt[10] = (gdt_entry) {
        (unsigned short)    sizeof(tss)-1,                                  /* limit[0:15]  */ 
        (unsigned short)    (unsigned int) &tss_idle,                       /* base[0:15]   */
        (unsigned char)     (unsigned int) &tss_idle >> 16,                 /* base[23:16]  */
        (unsigned char)     0x09,                                           /* type         */
        (unsigned char)     0x00,                                           /* s            */
        (unsigned char)     0x00,                                           /* dpl          */
        (unsigned char)     0x01,                                           /* p            */
        (unsigned char)     (sizeof(tss)-1) >> 16,                          /* limit[16:19] */
        (unsigned char)     0x00,                                           /* avl          */
        (unsigned char)     0x00,                                           /* l            */
        (unsigned char)     0x01,                                           /* db           */
        (unsigned char)     0x00,                                           /* g            */
        (unsigned char)     (unsigned int) &tss_idle >> 24,                 /* base[31:24]  */
    };

//DESCRIPTORES TAREAS   
    int j;
    for (j = 11; j < 50; ++j){
		gdt[j].p = 0;
	}
}






