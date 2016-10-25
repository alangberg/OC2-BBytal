/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "screen.h"

//Macros
#define PDE_INDEX(virtual) virtual >> 22
#define PTE_INDEX(virtual) (virtual >> 12) & 0x3FF
#define ALIGN(dir)
#define PG_READ_WRITE 0x00000002
#define PG_USER 0x00000004
#define PG_PRESENT 0x00000001

void mmu_inicializar_dir_kernel(){
	int* page_directory = (int*) PAGE_DIRECTORY_KERNEL;  // PAGE_DIRECTORY_KERNEL = 0x27000
	page_directory[0] = PAGE_TABLE_KERNEL_1 + 0x3;		 // PAGE_TABLE_KERNEL_1 = 0x28000, seteo p=1 y r/w=1
	page_directory[1] = PAGE_TABLE_KERNEL_2 + 0x3;       // PAGE_TABLE_KERNEL_2 = 0x30000
 	
	int i;
	for (i = 2; i < 1024; ++i) { //pongo todo el resto de las posiciones en cero.
		page_directory[i]= 0x0;
	}

	int* page_table_1 = (int*) PAGE_TABLE_KERNEL_1;
	for (i = 0; i < 1024; ++i) {
		page_table_1[i] = ((i << 12) | 3);
	}

	int* page_table_2 = (int*) PAGE_TABLE_KERNEL_2;
	for (i = 0; i < 1024; ++i) {
		if(i<768){
			page_table_2[i] = (((i+1024) << 12) | 3);	
		}else{
			page_table_2[i] = 0x0;
		}
	}
}

unsigned int proxima_pagina_libre;
void mmu_inicializar() {
	proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	return pagina_libre;
}

unsigned int mmu_inicializar_dir_tarea(unsigned int* codigo, posicion pos) {
	pde_entry* page_directory_tarea = (pde_entry*) mmu_proxima_pagina_fisica_libre(); //Armo el directorio de la nueva tarea (todo el directorio entra en una pagina de 4K)

	int i;
	for (i = 0; i < 1024; i++) {
	    page_directory_tarea[i].present = 0;
	    page_directory_tarea[i].rw = 0;
	    page_directory_tarea[i].us = 0;
	    page_directory_tarea[i].pwt = 0;
	    page_directory_tarea[i].pcd = 0;
	    page_directory_tarea[i].a = 0;
	    page_directory_tarea[i].d = 0;
	    page_directory_tarea[i].pat = 0;
	    page_directory_tarea[i].g = 0;
	    page_directory_tarea[i].disponible = 0;
	    page_directory_tarea[i].base = 0;
	}
	page_directory_tarea[0].present = 1;
	page_directory_tarea[0].rw = 1;
	
	pte_entry* page_table_tarea = (pte_entry*) mmu_proxima_pagina_fisica_libre(); //Armo la primer tabla de paginas	
	for (i = 0; i < 1024; i++) {
	
		page_table_tarea[i].present = 1;
		page_table_tarea[i].rw = 1;
		page_table_tarea[i].us = 1;
		page_table_tarea[i].base = (unsigned int) i;  // = ((i << 12) | 3)
	}

	page_directory_tarea[0].base = (unsigned int) page_table_tarea >> 12; //Linkeo la tabla de paginas al PD

	unsigned int* fisica =  (unsigned int*) game_dame_fisica_de_mar(pos);
	unsigned int* fisica_ancla =  (unsigned int*) TASK_ANCLA_FIS;

	mmu_mapear_pagina(DIR_VIRTUAL_TAREA, (unsigned int) page_directory_tarea, (unsigned int) fisica, 1, 1); //DIR_VIRTUAL????
	mmu_mapear_pagina(DIR_VIRTUAL_TAREA + 0x1000, (unsigned int) page_directory_tarea, (unsigned int) fisica + 0x1000, 1, 1);
	mmu_mapear_pagina(TASK_ANCLA, (unsigned int) page_directory_tarea, (unsigned int) fisica_ancla, 1, 0);

	int j;
	for (j = 0; j < 2048; j++) {
		fisica[j] = codigo[j];
	}

	return (unsigned int)page_directory_tarea;
}

unsigned int game_dame_fisica_de_mar(posicion pos){
	return (AREA_MAR_INICIO + (pos.y*80 + pos.x)*0x1000);
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char us, unsigned char rw){
	// Agarro los 1ros 20bits de la CR3 que corresponden a la direccion base del directorio de paginas
	pde_entry* CR3 = (pde_entry*)(cr3 & 0xFFFFF000); //Direccion base del Page Directory, limpie los attr.
	pde_entry* PDE = &(CR3[PDE_INDEX(virtual)]);     //Tomo de la direccion virtual los 10b mas significativos (PDE)

	// si PRESENT es 0
	if (!(PDE->present)){
		// pongo la dir 0
		PDE->base = mmu_proxima_pagina_fisica_libre() >> 12;

		// la igualo con el resultado de la funcion (me da un numero de 32bits donde los primeros 12 son 0s asi que esta todo re piolanga)
		// le pongo en 1 el PRESENT y el RW como dice la diapo
		PDE->present = 1;
		PDE->rw = rw;
		PDE->us = 1;
		// dejo el resto de la tabla en 0
		pte_entry* pte_indice = (pte_entry*) ((PDE->base) << 12);
		
		int i;
		for (i = 0; i < 1024; i++){
			pte_indice[i].present = 0;
			pte_indice[i].us = 0;
		}
	}

	pte_entry* PTable = (pte_entry*) ((PDE->base) << 12);
	pte_entry* PTE = (pte_entry*) &(PTable[PTE_INDEX(virtual)]);

	PTE->base = fisica >> 12;
	PTE->present = 1;
	PTE->rw = rw;
	PTE->us = us;

	tlbflush();
}

