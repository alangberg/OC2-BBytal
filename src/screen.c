/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"


void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}

void imprimirJuego_inicial() {
    int x;
    for (x = 0; x < 160; x++) print(" ", x, 0, 0);  //Pintamos el marco superior en negro

    int y = 1;
    x = 0;
    while (y < 45) { // Se Pinta la pantalla de Gris    
        print(" ", x, y, (7 << 4) | (0 & 0x0F));
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }

    while (y < 50) { //Pinto barra inferior
        if (x > 47 && x < 55) {
            print(" ", x, y, (4 << 4) | (0 & 0x0F)); // Pinto todo de rojo para el P1
        } else if (x > 54 && x < 62) {
            print(" ", x, y, (1 << 4) | (0 & 0x0F)); // Pinto todo de azul para el P2
        } else {
            print(" ", x, y, 0); // Si no es de ningún jugador, pinto en negro
        }

        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }

    print("vidas", 41, 46, (0 << 4) | (15 & 0x0F));
    print("vidas", 64, 46, (0 << 4) | (15 & 0x0F));

    print("<A", 12, 46, (0 << 4) | (15 & 0x0F));
    print("B>", 19, 46, (0 << 4) | (15 & 0x0F));

    print("Los Recursantes", 28, 0, (0 << 4) | (15 & 0x0F));

}
