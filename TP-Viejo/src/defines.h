/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_H                 	15
#define CANT                    5
#define SIZE_W                  80
#define SIZE_H                  44
#define PAGE_DIRECTORY_KERNEL   0x27000
#define PAGE_TABLE_KERNEL		0x28000
#define PAGE_SIZE				0x1000
#define INICIO_PAGINAS_LIBRES	0x100000
#define DIR_VIRTUAL_TAREA		0x8000000
#define PAGINA_MAPEADA		    0x8001000

/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 100 //REVISAR AL FINAL 

#define GDT_IDX_NULL_KERNEL          0
#define GDT_IDX_NULL_DESC1           1
#define GDT_IDX_NULL_DESC2           2
#define GDT_IDX_NULL_DESC3           3

#define GDT_0_CODE_KERNEL      	   	 4
#define GDT_0_DATA_KERNEL  	   	     5
#define GDT_1_CODE_USER	 	         6
#define GDT_1_DATA_USER	             7
#define GDT_2_VIDEO_USER	         8
#define GDT_TSS_INICIAL	        	 9
#define GDT_TSS_IDLE	        	 10

#define GDT_POSICION_CODE_KERNEL	GDT_0_CODE_KERNEL << 3
#define GDT_POSICION_DATA_KERNEL	GDT_0_DATA_KERNEL << 3
#define GDT_POSICION_CODE_USER		0x30	
#define GDT_POSICION_DATA_USER		0x38
#define GDT_POSICION_TSS_INICIAL	0x48
#define GDT_POSICION_TSS_IDLE		0x50


/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO_SCREEN            0x000B8000 /* direccion fisica del buffer de video */

typedef struct str_pos {
	unsigned short x;
	unsigned short y;
} posicion;

typedef enum type_task { H = 0, A = 1, B = 2 } tipoTarea;
#endif  /* !__DEFINES_H__ */