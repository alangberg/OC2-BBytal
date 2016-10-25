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


unsigned int mmu_inicializar_dir_tarea(unsigned int* codigo) {
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

	return (unsigned int)page_directory_tarea;
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char us) {

}

/*Desmapea la pagina fisica en el esquema de paginacion cr3.*/
unsigned int mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3) {
	return 0;
}
