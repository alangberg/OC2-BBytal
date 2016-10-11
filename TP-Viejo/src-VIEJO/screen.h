/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

#include "colors.h"
#include "defines.h"
#include "game.h"
/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

extern ca* tablaDebug[VIDEO_COLS];

extern unsigned char systemClock;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

void imprimirJuego(unsigned int vidaP1, unsigned int vidaP2, unsigned int ptosP1, unsigned int ptosP2);

void imprimirTeclado(char codigo);

void imprimirError(int gs, int fs, int es, int ds, int esp, int ebp, int edi, int esi, int edx, int ecx, int ebx, int eax, int errorCode, int eip, int cs, int eflags, int espTss,  int ss);   

void imprimirTareasSanas();

void imprimirTareasJugador(tipoTarea j);

void relojJug(int jugador, int i);

void relojH(int i);

void actualizarPantalla();

void imprimirDataJugadores();

void printRegisters(int gs, int fs, int es, int ds, int esp, int ebp, int edi, int esi, int edx, int ecx, int ebx, int eax, int errorCode, int eip, int cs, int eflags, int espTss, int ss);	

void tirameEsteNumero(unsigned int n);

#endif  /* !__SCREEN_H__ */
