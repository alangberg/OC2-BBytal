/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"
#include "gdt.h"

#define CANT_TAREAS 25

extern unsigned short sch_tareas[CANT_TAREAS];

unsigned short sched_proximo_indice();


#endif	/* !__SCHED_H__ */
