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

#define PAGE_DIRECTORY_KERNEL   0x27000
#define PAGE_TABLE_KERNEL_1		0x28000
#define PAGE_TABLE_KERNEL_2     0x30000    
#define PAGE_SIZE				0x1000
#define INICIO_PAGINAS_LIBRES	0x100000
#define DIR_VIRTUAL_TAREA		0x40000000
#define PAGINA_MAPEADA		    0x40001000
#define TASK_SIZE               2 * 4096


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */

#define GDT_0_NULL_KERNEL          0
#define GDT_1_NULL_RESERVED        1
#define GDT_2_NULL_RESERVED        2
#define GDT_3_NULL_RESERVED        3
#define GDT_4_NULL_RESERVED        4
#define GDT_5_NULL_RESERVED        5
#define GDT_6_NULL_RESERVED        6
#define GDT_7_NULL_RESERVED        7
#define GDT_8_NULL_RESERVED        8
#define GDT_9_NULL_RESERVED        9
#define GDT_10_NULL_RESERVED       10
#define GDT_11_NULL_RESERVED       11
#define GDT_11_NULL_RESERVED       11
#define GDT_12_NULL_RESERVED       12
#define GDT_13_NULL_RESERVED       13
#define GDT_14_NULL_RESERVED       14
#define GDT_15_NULL_RESERVED       15
#define GDT_16_NULL_RESERVED       16
#define GDT_17_NULL_RESERVED       17

#define GDT_18_CODE_KERNEL         18
#define GDT_19_DATA_KERNEL  	   19
#define GDT_20_CODE_USER	 	   20
#define GDT_21_DATA_USER	       21
#define GDT_22_VIDEO_KERNEL	       22



/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define BOOTSECTOR              0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                  0x00001200 /* direccion fisica de comienzo del kernel */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */

/* Direcciones virtuales de código, pila y datos */
/* -------------------------------------------------------------------------- */
#define TASK_CODE               0x40000000 /* direccion virtual del codigo */

#define TASK_IDLE_CODE          0x40000000 /* direccion virtual del codigo de la tarea idle */
#define TASK_IDLE_STACK         0x003D0000 /* direccion virtual de la pila de la tarea idle */
#define TASK_IDLE_STACK_RING_0  0x0002B000 /* direccion fisica de la pila de la tarea idle */

#define TASK_ANCLA              0x40002000
#define TASK_ANCLA_FIS          0x00000000

#define AREA_TIERRA_INICIO      0x00000000  /* 0.0 MB     */
#define AREA_TIERRA_FIN         0x000FFFFF  /* 1.0 MB - 1 */
#define AREA_MAR_INICIO         0x00100000  /* 1.0 MB     */
#define AREA_MAR_FIN            0x0077FFFF  /* 7.5 MB - 1 */

/* Direcciones fisicas de codigos */
/* -------------------------------------------------------------------------- */
/* En estas direcciones estan los códigos de todas las tareas. De aqui se
 * copiaran al destino indicado por TASK_<i>_CODE_ADDR.
 */
#define TASK_1_CODE_SRC_ADDR    0x00010000
#define TASK_2_CODE_SRC_ADDR    0x00012000
#define TAKS_3_CODE_SRC_ADDR    0x00014000
#define TASK_4_CODE_SRC_ADDR    0x00016000
#define TASK_5_CODE_SRC_ADDR    0x00018000
#define TASK_6_CODE_SRC_ADDR    0x0001A000
#define TASK_7_CODE_SRC_ADDR    0x0001C000
#define TASK_8_CODE_SRC_ADDR    0x0001E000

#define TASK_IDLE_CODE_SRC_ADDR 0x00020000

typedef struct str_pos {
	unsigned short x;
	unsigned short y;
} posicion;


#endif  /* !__DEFINES_H__ */
