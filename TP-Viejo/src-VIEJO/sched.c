/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"
#include "game.h"
#include "screen.h"

tipoTarea siguienteTarea(tipoTarea actual) {
	switch (actual) {
		case A:
			if (MainSystem.jugadores[1].cantidadVivas > 0) return B;
			else return H;
		case B:
			return H;
		case H:
			if (MainSystem.jugadores[0].cantidadVivas > 0) return A;
			else return B;
	}
	return 0;
}

unsigned short sched_proximo_indice() {
	#define TAREAS_JUG_SIGUIENTE MainSystem.jugadores[k]
	
	tipoTarea typeSiguiente = siguienteTarea(MainSystem.taskActual->type);

	if (typeSiguiente != H) {
		int i;
		int k = (typeSiguiente != A);

		i = (TAREAS_JUG_SIGUIENTE.tareaActual + 1) % 5;
		while (i != TAREAS_JUG_SIGUIENTE.tareaActual && !TAREAS_JUG_SIGUIENTE.task[i].vivo){
			i = (i + 1) % 5;
		}
		
		if (i != TAREAS_JUG_SIGUIENTE.tareaActual || TAREAS_JUG_SIGUIENTE.task[i].vivo) { // el negado de esto es q no hay ninguno vivo
			relojJug(k, i);
			MainSystem.jugadorActual = typeSiguiente;
			TAREAS_JUG_SIGUIENTE.tareaActual = i;
			MainSystem.taskActual = &(TAREAS_JUG_SIGUIENTE.task[i]);
			//breakpoint();
			return MainSystem.taskActual->gdtEntry;
		}
	}
	/* 		Si la siguiente es H o no hay A o B vivas 	*/
	int j;
	j = (MainSystem.itH + 1) % 15;

	while (j != MainSystem.itH && !MainSystem.Htask[j].vivo) j = (j + 1) % 15;

	if (j != MainSystem.itH || MainSystem.Htask[j].vivo) {
		MainSystem.jugadorActual = H;
		relojH(j);
		MainSystem.itH = j;
		MainSystem.taskActual = &(MainSystem.Htask[j]);
		return MainSystem.taskActual->gdtEntry;
	}
	return 0;
}