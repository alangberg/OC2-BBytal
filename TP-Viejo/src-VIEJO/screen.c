/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"
#include "game.h"

ca* tablaDebug[VIDEO_COLS];

void imprimirTeclado(char codigo) {
    if (!debugFlag || codigo == 0x15) {
        switch (codigo) {
            case 0x11:
                print("W", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(1, 0xA33);
                break;
            case 0x1e:
                print("A", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(1, 0xAAA);
                break;
            case 0x1f:
                print("S", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(1, 0x883);
                break;
            case 0x20:
                print("D", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(1, 0x441);
                break;
            case 0x2a:
                print("LShift", 74, 0, (0 << 4) | (15 & 0x0F));
                game_lanzar(0);
                break;
            case 0x17:
                print("I", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(2, 0xA33);
                break;
            case 0x24:
                print("J", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(2, 0xAAA);
                break;
            case 0x25:
                print("K", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(2, 0x883);
                break;
            case 0x26:
                print("`", 79, 0, (0 << 4) | (15 & 0x0F));
                game_mover_cursor(2, 0x441);
                break;
            case 0x36:
                print("RShift", 74, 0, (0 << 4) | (15 & 0x0F));
                game_lanzar(1);
                break;
            case 0x15:
                MainSystem.debugMode = !MainSystem.debugMode;
                if (MainSystem.debugMode) print("DEBUG MODE ON", 55, 0, C_FG_WHITE);
                else {
                    print("             ", 55, 0, C_FG_WHITE);
                    if (debugFlag){
                        ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
                        
                        int y;
                        int x;
                        
                        for (y = 7; y < 43; y++) {
                            for (x = 24; x < 55; x++) p[y][x] = tablaDebug[y - 7][x - 24];
                        }
                        debugFlag = 0;
                    }
                }
                break;
            default:
                print("      ", 74, 0, (0 << 4));
                break;
        }
    }
}

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

void relojJug(int jugador, int i) {
    char* reloj[4] = {"|","/","-","\\"};

    int j = MainSystem.jugadores[jugador].task[i].estadoReloj;

    if (MainSystem.jugadores[jugador].task[i].vivo == 1){

        if (jugador == 0) print(reloj[j], 10 - 2*i, 46, (0 << 4) | (15 & 0x0F));
        else print(reloj[j], 22 + 2*i, 46, (0 << 4) | (15 & 0x0F));

        MainSystem.jugadores[jugador].task[i].estadoReloj++;

        if (MainSystem.jugadores[jugador].task[i].estadoReloj == 4) MainSystem.jugadores[jugador].task[i].estadoReloj = 0;
    } else {
        MainSystem.jugadores[jugador].task[i].estadoReloj = 2;
        print(" ", 22 + 2*i, 46, (0 << 4) | (15 & 0x0F));
    }
}
void relojH(int i) {
    char* reloj[4] = {"|","/","-","\\"};

    int j = (MainSystem.Htask[i].estadoReloj);

    if (MainSystem.Htask[i].vivo) print(reloj[j], 2 + 2*i , 48, (0 << 4) | (15 & 0x0F));
    else { 
        MainSystem.Htask[i].estadoReloj = 2;        
        print(reloj[j], 2 + 2*i , 48, (0 << 4) | (15 & 0x0F));
    }

    MainSystem.Htask[i].estadoReloj++;
    if (MainSystem.Htask[i].estadoReloj == 4) MainSystem.Htask[i].estadoReloj = 0;
}

void actualizarPantalla() {
    imprimirDataJugadores();
    imprimirTareasJugador(A);
    imprimirTareasJugador(B);
    imprimirTareasSanas();
}

void imprimirJuego(unsigned int vidaP1, unsigned int vidaP2, unsigned int ptosP1, unsigned int ptosP2) {
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

    imprimirDataJugadores();

    print("<A", 12, 46, (0 << 4) | (15 & 0x0F));
    print("B>", 19, 46, (0 << 4) | (15 & 0x0F));

    print("*", MainSystem.jugadores[0].pos.x, MainSystem.jugadores[0].pos.y, (4 << 4) | (15 & 0x0F));
    print("*", MainSystem.jugadores[1].pos.x, MainSystem.jugadores[1].pos.y, (1 << 4) | (15 & 0x0F));
    print("El que no llora no mama", 28, 0, (0 << 4) | (15 & 0x0F));

    imprimirTareasSanas();
}


void imprimirDataJugadores() {
    sumarPuntos();

    print("  ", 43, 48, (0 << 4) | (15 & 0x0F));
    printear("  ", 66, 48, (0 << 4) | (15 & 0x0F));

    print_int(MainSystem.jugadores[0].vida, 43, 48, (0 << 4) | (15 & 0x0F));
    print_int(MainSystem.jugadores[1].vida, 66, 48, (0 << 4) | (15 & 0x0F));


    print("", 51, 47, (4 << 4) | (15 & 0x0F));
    print("", 58, 47, (1 << 4) | (15 & 0x0F));

    print_int(MainSystem.jugadores[0].puntos, 51, 47, (4 << 4) | (15 & 0x0F));
    print_int(MainSystem.jugadores[1].puntos, 58, 47, (1 << 4) | (15 & 0x0F));
}

void imprimirTareasSanas() {
    int i;
    for(i = 0; i < 15; i++) {
        if(MainSystem.Htask[i].vivo) {
            switch (MainSystem.Htask[i].viruseada) {
                case H:
                    print("H", MainSystem.Htask[i].posMapa.x, MainSystem.Htask[i].posMapa.y, (2 << 4) | (15 & 0x0F));
                    break;
                case A:
                    print("H", MainSystem.Htask[i].posMapa.x, MainSystem.Htask[i].posMapa.y, (4 << 4) | (15 & 0x0F));
                    break;
                case B:
                    print("H", MainSystem.Htask[i].posMapa.x, MainSystem.Htask[i].posMapa.y, (1 << 4) | (15 & 0x0F));
                   break;
           }
        }
    }
}

void imprimirTareasJugador(tipoTarea j) {
	
    char* ch;
    unsigned int k;
    int color;
    if (j == A) {
        ch = "A";
        k = 0;
        color = 4;
    } else {
        ch = "B";
        k = 1;
        color = 1;
    }
    
    int i;
    for(i = 0; i < 5; i++) {
        if(MainSystem.jugadores[k].task[i].vivo) {
        	
            print(ch, MainSystem.jugadores[k].task[i].posMapa.x, MainSystem.jugadores[k].task[i].posMapa.y, (color << 4) | (15 & 0x0F));
        }
    }
}



void imprimirError(int gs, int fs, int es, int ds, int esp, int ebp, int edi, int esi, int edx, int ecx, int ebx, int eax, int errorCode, int eip, int cs, int eflags, int espTss,  int ss) {   

#define printear(r, x, y) print(r, x, y, (7 << 4) | (0 & 0x0F));
#define printear_hex(r, x, y) print_hex( r, 8, x, y, (7 << 4) | (0 & 0x0F));

    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;

    int y;
    int x;
    for (y = 7; y < 43; y++) {
        for (x = 24; x < 55; x++) tablaDebug[y - 8][x - 24] = p[y][x];
    }

    y = 7;
    x = 24;
    while (y < 43) {
        if (y == 7 || y == 42 || x == 24 || x == 54) print(" ", x, y    , 0);
        else {
            if (y == 8){
                if (MainSystem.jugadorActual == A) {
                    print(" ", x, y, (4 << 4));
                    print("virus A", 25, 8, (4 << 4) | (15 & 0x0F));
                    
                    
                } else {
                    print(" ", x, y, (1 << 4));
                    print("virus B", 25, 8, (1 << 4) | (15 & 0x0F));
                }
            } else {
                print(" ", x, y, (7 << 4));
            }
        }
        if (x == 54) {
            y++;
            x = 24;
        } else x++;
    }
    printRegisters(gs, fs, es, ds, esp, ebp, edi, esi, edx, ecx, ebx, eax, errorCode, eip, cs, eflags, espTss, ss);
}




void printRegisters(int gs, int fs, int es, int ds, int esp, int ebp, int edi, int esi, int edx, int ecx, int ebx, int eax, int errorCode, int eip, int cs, int eflags, int espTss, int ss){	

    unsigned int* Cesp = (unsigned int*) esp;
    print("eax", 26, 10, (7 << 4) | (0 & 0x0F));
	print_hex(eax, 8, 30, 10, (7 << 4) | (15 & 0x0F));

    print("ebx", 26, 12, (7 << 4) | (0 & 0x0F));
	print_hex(ebx, 8, 30, 12, (7 << 4) | (15 & 0x0F));

	print("ecx", 26, 14, (7 << 4) | (0 & 0x0F));
	print_hex(ecx, 8, 30, 14, (7 << 4) | (15 & 0x0F));

    print("edx", 26, 16, (7 << 4) | (0 & 0x0F));
	print_hex(edx, 8, 30, 16, (7 << 4) | (15 & 0x0F));

    print("esi", 26, 18, (7 << 4) | (0 & 0x0F));
	print_hex(esi, 8, 30, 18, (7 << 4) | (15 & 0x0F));

    print("edi", 26, 20, (7 << 4) | (0 & 0x0f));
	print_hex(edi, 8, 30, 20, (7 << 4) | (15 & 0x0F));

    print("ebp", 26, 22, (7 << 4) | (0 & 0x0f));
	print_hex(ebp, 8, 30, 22, (7 << 4) | (15 & 0x0F));

    print("esp", 26, 24, (7 << 4) | (0 & 0x0f));
	print_hex(esp, 8, 30, 24, (7 << 4) | (15 & 0x0F));
	
    print("eip", 26, 26, (7 << 4) | (0 & 0x0f));
	print_hex(eip, 8, 30, 26, (7 << 4) | (15 & 0x0F));

    print("cs", 27, 28, (7 << 4) | (0 & 0x0f));
	print_hex(cs, 4, 30, 28, (7 << 4) | (15 & 0x0F));
	
	print("ds", 27, 30, (7 << 4) | (0 & 0x0f));
	print_hex(ds, 4, 30, 30, (7 << 4) | (15 & 0x0F));

	print("es", 27, 32, (7 << 4) | (0 & 0x0f));
	print_hex(es, 4, 30, 32, (7 << 4) | (15 & 0x0F));

	print("fs", 27, 34, (7 << 4) | (0 & 0x0f));
	print_hex(fs, 4, 30, 34, (7 << 4) | (15 & 0x0F));

	print("gs", 27, 36, (7 << 4) | (0 & 0x0f));
	print_hex(gs, 4, 30, 36, (7 << 4) | (15 & 0x0F));
	
	print("ss", 27, 38, (7 << 4) | (0 & 0x0f));
	print_hex(ss, 4, 30, 38, (7 << 4) | (15 & 0x0F));
	
	print("eflags", 27, 40, (7 << 4) | (0 & 0x0f));
	print_hex(eflags, 8, 33, 40, (7 << 4) | (15 & 0x0F));

	print("cr0", 40, 10, (7 << 4) | (0 & 0x0F));
	print_hex(rcr0(), 8, 44, 10, (7 << 4) | (15 & 0x0F));

	print("cr2", 40, 12, (7 << 4) | (0 & 0x0F));
	print_hex(rcr2(), 8, 44, 12, (7 << 4) | (15 & 0x0F));

	print("cr3", 40, 14, (7 << 4) | (0 & 0x0F));
	print_hex(rcr3() , 8, 44, 14, (7 << 4) | (15 & 0x0F));

	print("cr4", 40, 16, (7 << 4) | (0 & 0x0F));
	print_hex(rcr4(), 8, 44, 16, (7 << 4) | (15 & 0x0F));

	print("stack", 40, 27, (7 << 4) | (0 & 0x0f));

	int i;
	 for (i = 0; i < 4 && (esp+i)<ebp ; i++){
	 	print_hex((*(Cesp + i)), 8, 40, (30+i), (7 << 4) | (15 & 0x0F));
	 }

}




void tirameEsteNumero(unsigned int n){
	    print_int(n, n%80, n%40, (4 << 4) | (15 & 0x0F));
	     int i;
	     while(1){
	     	print_int(n, i, i, (4 << 4) | (15 & 0x0F));
	     	i++;
	    }
	   // breakpoint();
}