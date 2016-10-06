/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "screen.h"
#include "tss.h"

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ARB = 0xA33, ABA = 0x883  } direccion;

typedef struct str_tarea {
	// Posición de cada tarea dentro del mapa, separada entre jugadores y sanas
	posicion posMapa;			//Posicion estatica de las tareas.
	posicion pos;				//Posicion dinamica de las tareas.
	tipoTarea type;				//"Dueño de la tarea"
	tipoTarea viruseada;		//Infectada por....
	unsigned short gdtEntry;	//Indice de la TSS ligada a la tarea
	unsigned char vivo; 		//Para decir si esta viva o no
	unsigned int cr3;			//Direccion del Page Directory asociado a la tarea
	unsigned int estadoReloj;	//Clock de la tarea
	unsigned int posEnArreglo;
} tarea;

typedef struct str_jugador {
	posicion pos; 					//Posición actual de cursor
	unsigned int vida; 				//Vidas restantes	
	unsigned int puntos;			//Puntaje actual
	unsigned short tareaActual;		//Tarea actual corriendo.
	unsigned short cantidadVivas;	
 	tarea task[5];
} jugador;

typedef struct str_system {
	tarea* taskActual; 				//Tarea que está siendo actualmente ejecutada. Una forma de acceder a la siguiente tarea
	jugador jugadores[2];			//[jugadorA,jugadorB]
	unsigned int jugadorActual;		// 0 == H; 1 == A; 2 == B
	unsigned int itH;				// iterador al arreglo de tareas H. 
	tarea Htask[15];

	unsigned short debugMode;
} system;

extern system MainSystem;

extern unsigned char debugFlag;

void game_lanzar(unsigned int jugador);

void game_soy(unsigned int soy);

void game_donde(short* pos);

void game_mover_cursor(int jugador, direccion dir);

void game_init();

tarea tareaNueva(unsigned int* codigo, tipoTarea tipo, posicion pos, unsigned int posEnArreglo);

void debugMode(int gs, int fs, int es, int ds, int esp, int ebp, int edi, int esi, int edx, int ecx, int ebx, int eax, int errorCode, int eip, int cs, int eflags, int espTss, int ss);

void matarTarea();

unsigned int contarInfectados(tipoTarea j);

unsigned int newrand(unsigned int *val);

void sumarPuntos();

// unsigned int noHayNadaMapeadoAca(posicion posAux, tipoTarea j);

#endif  /* !__GAME_H__ */
