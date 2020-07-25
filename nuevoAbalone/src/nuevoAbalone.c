/*
 ============================================================================
 Name        : nuevoAbalone.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nuevoAbalone.h"

//int ficha_B, ficha_N;
//char tablero[11][19];
/*
int main(void) {
	int j_simple[14][15], j_doble[40][17], j_triple[40][19];
	int c1, c2, c3, tj, ban, j, c, cj, nj, i;
	char x, y;
	ban=0;
	nj=1;
	c1=c2=c3=0;
	inicializartablero(tablero);
	imprimirtablero(tablero);
	j=iniciarjuego();
	c=colorfichas();
	cj=cantjug();
	do{
		if(j==2){ //inicia el humano
			if(c==1){ //el jugador usará fichas blancas
				x='B';
				y='N';
				jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
				tj=tipo_jugada();
				mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
				x='N';
				y='B';
				jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
				mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
				imprimirtablero(tablero);
			}
			else{ //el jugador usará fichas negras
				x='N';
				y='B';
				jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
				tj=tipo_jugada();
				mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
				x='B';
				y='N';
				jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
				mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
				imprimirtablero(tablero);
			}
		}
		else{ //inicia la computadora
				if(quieninicia==1 && ban_comp_inicia==0){
			if(c==1){ //la computadora usará fichas negras
				x='N';
				y='B';
				jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
				mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
				actualizartablero();
				ban_comp_inicia=1;
			}
			else{ //la computadora usará fichas blancas
				x='B';
				y='N';
				jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
				mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
				actualizartablero();
				ban_comp_inicia=1;
			}
		}
		}
		cantidad_fichas(tablero);
		if( ficha_B<8 || ficha_N<8 || (nj==cj) ){ //verifica que no se hayan sacado más de 6 fichas o se hayan cumplido la cantidad de jugadas
			ban=1;
		}
		nj++;
	}while(ban==0);
	printf("\nGAME OVER");
	if( ficha_B > ficha_N){
		printf("\nWhite Power");
	}
	else if( ficha_N > ficha_B){
		printf("\nNigga Power");
	}
	else{
		printf("\nTIE");
	}

	return 0;
}*/

/*
 * Funcion inicializartablero que carga las fichas de ambos colores al tablero de juego.
 * Parametros:
 *  Recibe la matriz que se utiliza para representar el tablero
 * Retorno:
 *  Ninguno
 */
void inicializartablero(char tablero[11][19]){
	int i,j;
	for(i=0;i<11;i++){
		for(j=0;j<19;j++){
			tablero[i][j]='*';

		}
	}
	for(j=5;j<8;j=j+2){
		tablero[1][j]='B';
	}
	for(j=4;j<9;j=j+2){
		tablero[2][j]='B';
	}
	for(j=5;j<8;j=j+2){
		tablero[3][j]='B';//los tres primeros 'for' cargan las fichas blancas de la esquina suṕerior izquierda
	}
	for(j=5;j<8;j=j+2){
		tablero[7][j]='N';
	}
	for(j=4;j<9;j=j+2){
		tablero[8][j]='N';
	}
	for(j=5;j<8;j=j+2){
		tablero[9][j]='N';//fichas negras de esquina inferior izquierda
	}

	for(j=11;j<14;j=j+2){
		tablero[1][j]='N';
	}
	for(j=10;j<15;j=j+2){
		tablero[2][j]='N';
	}
	for(j=11;j<15;j=j+2){
		tablero[3][j]='N';//fichas negras esquina superior derecha
	}
	for(j=11;j<14;j=j+2){
		tablero[7][j]='B';
	}
	for(j=10;j<15;j=j+2){
		tablero[8][j]='B';
	}
	for(j=11;j<14;j=j+2){
		tablero[9][j]='B';//fichas blancas esquina inferior izquierda
	}
	tablero[1][9]=tablero[3][3]=tablero[3][9]=tablero[3][15]=tablero[7][3]=tablero[7][9]=tablero[7][15]=tablero[9][9]='O'; //espacios vacios
	for(j=2; j<17; j=j+2){ //se cargan los espacios vacios
		tablero[4][j]='O';
		tablero[6][j]='O';
	}
	for(j=1; j<18; j=j+2){ //se cargan los espacios vacios
		tablero[5][j]='O';
	}
	for(j=6; j<13; j=j+2){ //se cargan los espacios inválidos
		tablero[1][j]='$';
		tablero[9][j]='$';
	}
	for(j=5; j<14; j=j+2){ //se cargan los espacios inválidos
		tablero[2][j]='$';
		tablero[8][j]='$';
	}
	for(j=4; j<15; j=j+2){ //se cargan los espacios inválidos
		tablero[3][j]='$';
		tablero[7][j]='$';
	}
	for(j=3; j<16; j=j+2){ //se cargan los espacios inválidos
		tablero[4][j]='$';
		tablero[6][j]='$';
	}
	for(j=2; j<17; j=j+2){ //se cargan los espacios inválidos
		tablero[5][j]='$';
	}
}

/*
 * Funcion imprimirtablero que imprime el tablero en la forma correcta
 * Parametros:
 *  Matriz del tablero
 * Retorno:
 *  Ninguno
 */
void imprimirtablero(char tablero[11][19]){
	int i,j;
	for(i=1;i<10;i++){
		int a;
		a=74-i;
		printf("\n %c ", a); //para imprimir los indices desde I hasta A
		for(j=0;j<19;j++){
			if( (tablero[i][j]=='*') || (tablero[i][j]=='$') ){
				printf(" "); //los elementos de la matriz no son lugares validos del tablero y no se imprimen
			}
			else{
				printf("%c", tablero[i][j]);
			}
			//printf("%c", tablero[i][j]);
		}
	}
}

/*
 * Funcion que calcula la cantidad de fichas de cada color presentes en el tablero
 * Parametros:
 * Tablero
 * Retorno:
 * Ninguno. Pero modifica variables globales
 */
void cantidad_fichas(char tablero[11][19]){
	int i, j;
	ficha_B=0;
	ficha_N=0;
	for(i=0; i<11; i++){
		for(j=0; j<19; j++){
			if(tablero[i][j]=='B') ficha_B+=1;
			if(tablero[i][j]=='N') ficha_N+=1;
		}
	}
	printf("\nFichas de B: %d", ficha_B);
	printf("\nFichas de N: %d", ficha_N);
}

/*
 *Funcion jugadaposible que calcula las jugadas posibles de todas las fichas de cada color y
 *y las almacena en matrices
 *Parametros:
 * Matriz del tablero de juego, matrices para almacenar jugadas posibles, las columnas
 * en las que se encuentran las fichas y los char x e y que contienen el color de ficha utilizada.
 *Retorno:
 * Ninguno
 */
void jugadaposible(char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], int c1, int c2, int c3, char x, char y){
	int i, j, a, b, cj;
	for(i=0; i<14; i++){
		for(j=0; j<15; j++){
			j_simple[i][j]=-1;
		}
	}
	a=0;
	b=0; //a controla las filas y b las columnas
	for(i=0; i<11; i++){ //for principal. Prototipo de jugada posible para la ficha B, luego adaptar para N
		for(j=0; j<19; j++){
			if(tablero[i][j]== x){ //para la jugada simple
				j_simple[a][b]=i;
				b=b+1;
				j_simple[a][b]=j;
				b=b+1;
				cj=0;
				if(tablero[i][j+2]=='O'){ //espacio libre a la DERECHA
					j_simple[a][b]=i;
					b=b+1;
					j_simple[a][b]=j+2;
					b=b+1;
					cj=cj+1;
				}
				if(tablero[i][j-2]=='O'){ //espacio libre a la ZIQUIERDA
					j_simple[a][b]=i;
					b=b+1;
					j_simple[a][b]=j-2;
					b=b+1;
					cj=cj+1;
				}
				if(tablero[i-1][j-1]=='O'){ //espacio libre DIAGONAL IZQUIERDA SUPERIOR
					j_simple[a][b]=i-1;
					b=b+1;
					j_simple[a][b]=j-1;
					b=b+1;
					cj=cj+1;
				}
				if(tablero[i-1][j+1]=='O'){ //espacio libre DIAGONAL DERECHA SUPERIOR
					j_simple[a][b]=i-1;
					b=b+1;
					j_simple[a][b]=j+1;
					b=b+1;
					cj=cj+1;
				}
				if(tablero[i+1][j+1]=='O'){ //espacio libre DIAGONAL DERECHA INFERIOR
					j_simple[a][b]=i+1;
					b=b+1;
					j_simple[a][b]=j+1;
					b=b+1;
					cj=cj+1;
				}
				if(tablero[i+1][j-1]=='O'){ //espacio libre DIAGONAL IZQUIERDA INFERIOR
					j_simple[a][b]=i+1;
					b=b+1;
					j_simple[a][b]=j-1;
					b=b+1;
					cj=cj+1;
				}
				a=a+1;
				b=0;
			}
		}
	}

	/*    printf("\nJugadas simples posibles para la ficha B:");
    for(i=0; i<14; i++){
            printf("\n");
            for(j=0; j<15; j++){
                printf("%d ", j_simple[i][j]);
            }
        }*/


	//FICHAS DOBLES
	for(i=0; i<40; i++){
		for(j=0; j<16; j++){
			j_doble[i][j]=-1;
		}
	}
	a=0;
	b=0; //a controla las filas y b las columnas
	for(i=0; i<11; i++){ //for principal. Prototipo de jugada posible para la ficha B, luego adaptar para N
		for(j=0; j<17; j++){
			if(tablero[i][j]== x){ //IF PRINCIPAL DE FICHA
				if(tablero[i][j+2]== x){//para la jugada doble horizontal;
					j_doble[a][b]=i;
					b=b+1;
					j_doble[a][b]=j;
					b=b+1;
					j_doble[a][b]=i;
					b=b+1;
					j_doble[a][b]=j+2;
					b=b+1;
					if(tablero[i-1][j-1]=='O' && tablero[i-1][j+1]=='O'){ //CASO 1
						j_doble[a][b]=i-1;
						b=b+1;
						j_doble[a][b]=j-1;
						b=b+1;
					}
					if(tablero[i-1][j+1]=='O' && tablero[i-1][j+3]=='O'){ //CASO 2
						j_doble[a][b]=i-1;
						b=b+1;
						j_doble[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i][j+4]=='O'){ //CASO 3 (FICHA CONTRARIA)
						j_doble[a][b]=i;
						b=b+1;
						j_doble[a][b]=j+4;
						b=b+1;
					}
					else if(tablero[i][j+4]== y && (tablero[i][j+6]=='O' || tablero[i][j+5]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_doble[a][b]=i; //guarda la posicion a la que se movera la ficha de la izquierda, que toma el lugar de la ficha aliada de su derecha
						b=b+1;
						j_doble[a][b]=j+4;
						b=b+1;
					}
					if(tablero[i+1][j+3]=='O' && tablero[i+1][j+1]=='O'){ //CASO 4
						j_doble[a][b]=i+1;
						b=b+1;
						j_doble[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i+1][j-1]=='O' && tablero[i+1][j+1]=='O'){ //CASO 5
						j_doble[a][b]=i+1;
						b=b+1;
						j_doble[a][b]=j-1;
						b=b+1;
					}
					if(tablero[i][j-2]=='O'){ //CASO 6 FICHA CONTRARIA
						j_doble[a][b]=i;
						b=b+1;
						j_doble[a][b]=j-2;
						b=b+1;
					}
					else if(tablero[i][j-2]== y && (tablero[i][j-4]=='O' || tablero[i][j-3]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_doble[a][b]=i; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_doble[a][b]=j-2;
						b=b+1;
					}
					a=a+1;
					b=0;

				}

				if(tablero[i+1][j-1]== x){ //para la jugada doble diagonal izquierda inferior
					j_doble[a][b]=i;
					b=b+1;
					j_doble[a][b]=j;
					b=b+1;
					j_doble[a][b]=i+1;
					b=b+1;
					j_doble[a][b]=j-1;
					b=b+1;
					if(tablero[i-1][j+1]=='O'){ //CASO 1 FICHA CONTRARIA
						j_doble[a][b]=i-1;
						b=b+1;
						j_doble[a][b]=j+1;
						b=b+1;
					}
					else if(tablero[i-1][j+1]== y && (tablero[i-2][j+2]=='O' || tablero[i-2][j+2]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_doble[a][b]=i-1; //guarda la posicion a la que se movera la ficha de la izquierda, que toma el lugar de la ficha aliada de su derecha
						b=b+1;
						j_doble[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i][j+2]=='O' && tablero[i+1][j+1]=='O'){ //CASO 2
						j_doble[a][b]=i;
						b=b+1;
						j_doble[a][b]=j+2;
						b=b+1;
					}
					if(tablero[i+1][j+1]=='O' && tablero[i+2][j]=='O'){ //CASO 3
						j_doble[a][b]=i+1;
						b=b+1;
						j_doble[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i+2][j-2]=='O'){ //CASO 4 FICHA CONTRARIA
						j_doble[a][b]=i+2;
						b=b+1;
						j_doble[a][b]=j-2;
						b=b+1;
					}
					else if(tablero[i+2][j-2]== y && (tablero[i+3][j-3]=='O' || tablero[i+3][j-3]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_doble[a][b]=i+2; //guarda la posicion a la que se movera la ficha de arriba, que toma el lugar de la ficha aliada de su diagonal inferior
						b=b+1;
						j_doble[a][b]=j-2;
						b=b+1;
					}
					if(tablero[i][j-2]=='O' && tablero[i+1][j-3]=='O'){ //CASO 5
						j_doble[a][b]=i;
						b=b+1;
						j_doble[a][b]=j-2;
						b=b+1;
					}
					if(tablero[i-1][j-1]=='O' && tablero[i][j-2]=='O'){ //CASO 6
						j_doble[a][b]=i-1;
						b=b+1;
						j_doble[a][b]=j-1;
						b=b+1;
					}
					a=a+1;
					b=0;
				}

				if(tablero[i+1][j+1]== x){ //DIAGONAL INFERIOR DERECHA
					j_doble[a][b]=i;
					b=b+1;
					j_doble[a][b]=j;
					b=b+1;
					j_doble[a][b]=i+1;
					b=b+1;
					j_doble[a][b]=j+1;
					b=b+1;
					if(tablero[i-1][j-1]=='O'){ //CASO 1 FICHA CONTRARIA
						j_doble[a][b]=i-1;
						b=b+1;
						j_doble[a][b]=j-1;
						b=b+1;
					}
					else if(tablero[i-1][j-1]== y && (tablero[i-2][j-2]=='O' || tablero[i-2][j-2]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_doble[a][b]=i-1;
						b=b+1;
						j_doble[a][b]=j-1;
						b=b+1;
					}
					if(tablero[i-1][j+1]=='O' && tablero[i][j+2]=='O'){ //CASO 2
						j_doble[a][b]=i-1;
						b=b+1;
						j_doble[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i][j+2]=='O' && tablero[i+1][j+3]=='O'){ //CASO 3
						j_doble[a][b]=i;
						b=b+1;
						j_doble[a][b]=j+2;
						b=b+1;
					}
					if(tablero[i+2][j+2]=='O'){ //CASO 4 FICHA CONTRARIA
						j_doble[a][b]=i+2;
						b=b+1;
						j_doble[a][b]=j+2;
						b=b+1;
					}
					else if(tablero[i+2][j+2]== y && (tablero[i+3][j+3]=='O' || tablero[i+3][j+3]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_doble[a][b]=i+2;
						b=b+1;
						j_doble[a][b]=j+2;
						b=b+1;
					}
					if(tablero[i+1][j-1]=='O' && tablero[i+2][j]=='O'){ //CASO 5
						j_doble[a][b]=i+1;
						b=b+1;
						j_doble[a][b]=j-1;
						b=b+1;
					}
					if(tablero[i][j-2]=='O' && tablero[i+1][j-1]=='O'){ //CASO 6
						j_doble[a][b]=i;
						b=b+1;
						j_doble[a][b]=j-2;
						b=b+1;
					}
					a=a+1;
					b=0;
				}
			}

		}
	}
	  /*  printf("\n Jugadas dobles posibles:");
        for(i=0; i<40; i++){
            printf("\n");
            for(j=0; j<16; j++){
                printf(" %d", j_doble[i][j]);
            }
        } */

	//FICHAS TRIPLES
	for(i=0; i<40; i++){
		for(j=0; j<19; j++){
			j_triple[i][j]=-1;
		}
	}
	a=0;
	b=0; //a controla las filas y b las columnas
	for(i=0; i<11; i++){ //for principal. Prototipo de jugada posible para la ficha B, luego adaptar para N
		for(j=0; j<19; j++){
			if(tablero[i][j]== x){ //IF PRINCIPAL DE FICHA
				if(tablero[i][j+2]== x && tablero[i][j+4]== x){//para la jugada triple horizontal;
					j_triple[a][b]=i;
					b=b+1;
					j_triple[a][b]=j;
					b=b+1;
					j_triple[a][b]=i;
					b=b+1;
					j_triple[a][b]=j+2;
					b=b+1;
					j_triple[a][b]=i;
					b=b+1;
					j_triple[a][b]=j+4;
					b=b+1;
					if(tablero[i][j-2]=='O'){ //CASO 1 FICHA CONTRARIA
						j_triple[a][b]=i;
						b=b+1;
						j_triple[a][b]=j-2;
						b=b+1;
					}
					//para una ficha contraria
					else if(tablero[i][j-2]== y && (tablero[i][j-4]=='O' || tablero[i][j-3]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j-2;
						b=b+1;
					}
					//para dos fichas contrarias
					else if( (tablero[i][j-2]== y && tablero[i][j-4]== y ) && (tablero[i][j-6]=='O' || tablero[i][j-5]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j-2;
						b=b+1;
					}
					if(tablero[i-1][j-1]=='O' && tablero[i-1][j+1]=='O' && tablero[i-1][j+3]=='O'){ //CASO 2
						j_triple[a][b]=i-1;
						b=b+1;
						j_triple[a][b]=j-1;
						b=b+1;
					}
					if(tablero[i-1][j+1]=='O' && tablero[i-1][j+3]=='O' && tablero[i-1][j+5]=='O'){ //CASO 3
						j_triple[a][b]=i-1;
						b=b+1;
						j_triple[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i][j+6]=='O'){ //CASO 4 FICHA CONTRARIA
						j_triple[a][b]=i;
						b=b+1;
						j_triple[a][b]=j+6;
						b=b+1;
					}
					//para una ficha contraria
					else if(tablero[i][j+6]== y && (tablero[i][j+8]=='O' || tablero[i][j+7]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j+6;
						b=b+1;
					}
					//para dos fichas contrarias
					else if( (tablero[i][j+6]== y && tablero[i][j+8]== y ) && (tablero[i][j+10]=='O' || tablero[i][j+9]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j+6;
						b=b+1;
					}
					if(tablero[i+1][j+1]=='O' && tablero[i+1][j+3]=='O' && tablero[i+1][j+5]=='O'){ //CASO 5
						j_triple[a][b]=i+1;
						b=b+1;
						j_triple[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i+1][j-1]=='O' && tablero[i+1][j+1]=='O' && tablero[i+1][j+3]=='O'){ //CASO 6
						j_triple[a][b]=i+1;
						b=b+1;
						j_triple[a][b]=j-1;
						b=b+1;
					}
					a=a+1;
					b=0;
				}

				if(tablero[i+1][j+1]== x && tablero[i+2][j+2]== x){ //para la jugada triple diagonal izquierda superior
					j_triple[a][b]=i;
					b=b+1;
					j_triple[a][b]=j;
					b=b+1;
					j_triple[a][b]=i+1;
					b=b+1;
					j_triple[a][b]=j+1;
					b=b+1;
					j_triple[a][b]=i+2;
					b=b+1;
					j_triple[a][b]=j+2;
					b=b+1;
					if(tablero[i-1][j-1]=='O'){ //CASO 1 FICHA CONTRARIA
						j_triple[a][b]=i-1;
						b=b+1;
						j_triple[a][b]=j-1;
						b=b+1;
					}
					//para una ficha contraria
					else if(tablero[i-1][j-1]== y && (tablero[i-2][j-2]=='O' || tablero[i-2][j-2]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i-1; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j-1;
						b=b+1;
					}
					//para dos fichas contrarias
					else if( (tablero[i-1][j-1]== y && tablero[i-2][j-2]== y ) && (tablero[i-3][j-3]=='O' || tablero[i-3][j-3]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i-1; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j-1;
						b=b+1;
					}
					if(tablero[i-1][j+1]=='O' && tablero[i][j+2]=='O' && tablero[i+1][j+3]=='O'){ //CASO 2
						j_triple[a][b]=i-1;
						b=b+1;
						j_triple[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i][j+2]=='O' && tablero[i+1][j+3]=='O' && tablero[i+2][j+4]=='O'){ //CASO 3
						j_triple[a][b]=i;
						b=b+1;
						j_triple[a][b]=j+2;
						b=b+1;
					}
					if(tablero[i+3][j+3]=='O'){ //CASO 4 FICHA CONTRARIA
						j_triple[a][b]=i+3;
						b=b+1;
						j_triple[a][b]=j+3;
						b=b+1;
					}
					else if(tablero[i+3][j+3]== y && (tablero[i+4][j+4]=='O' || tablero[i+4][j+4]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i+3; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j+3;
						b=b+1;
					}
					//para dos fichas contrarias
					else if( (tablero[i+3][j+3]== y && tablero[i+4][j+4]== y ) && (tablero[i+5][j+5]=='O' || tablero[i+5][j+5]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i+3; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j+3;
						b=b+1;
					}
					if(tablero[i+1][j-1]=='O' && tablero[i+2][j]=='O' && tablero[i+3][j+1]=='O'){ //CASO 5
						j_triple[a][b]=i+1;
						b=b+1;
						j_triple[a][b]=j-1;
						b=b+1;
					}
					if(tablero[i][j-2]=='O' && tablero[i+1][j-1]=='O' && tablero[i+2][j]=='O'){ //CASO 6
						j_triple[a][b]=i;
						b=b+1;
						j_triple[a][b]=j-2;
						b=b+1;
					}
					a=a+1;
					b=0;
				}

				if(tablero[i+1][j-1]== x && tablero[i+2][j-2]== x){ //para la jugada triple diagonal izquierda inferior
					j_triple[a][b]=i;
					b=b+1;
					j_triple[a][b]=j;
					b=b+1;
					j_triple[a][b]=i+1;
					b=b+1;
					j_triple[a][b]=j-1;
					b=b+1;
					j_triple[a][b]=i+2;
					b=b+1;
					j_triple[a][b]=j-2;
					b=b+1;
					if(tablero[i-1][j+1]=='O'){ //CASO 1 FICHA CONTRARIA
						j_triple[a][b]=i-1;
						b=b+1;
						j_triple[a][b]=j+1;
						b=b+1;
					}
					else if(tablero[i-1][j+1]== y && (tablero[i-2][j+2]=='O' || tablero[i-2][j+2]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i-1; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j+1;
						b=b+1;
					}
					//para dos fichas contrarias
					else if( (tablero[i-1][j+1]== y && tablero[i-2][j+2]== y ) && (tablero[i-3][j+3]=='O' || tablero[i-3][j+3]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i-1; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i][j+2]=='O' && tablero[i+1][j+1]=='O' && tablero[i+2][j]=='O'){ //CASO 2
						j_triple[a][b]=i;
						b=b+1;
						j_triple[a][b]=j+2;
						b=b+1;
					}
					if(tablero[i+1][j+1]=='O' && tablero[i+2][j]=='O' && tablero[i+3][j-1]=='O'){ //CASO 3
						j_triple[a][b]=i+1;
						b=b+1;
						j_triple[a][b]=j+1;
						b=b+1;
					}
					if(tablero[i+3][j-3]=='O'){ //CASO 4 FICHA CONTRARIA
						j_triple[a][b]=i+3;
						b=b+1;
						j_triple[a][b]=j-3;
						b=b+1;
					}
					else if(tablero[i+3][j-3]== y && (tablero[i+4][j-4]=='O' || tablero[i+4][j-4]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i+3; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j-3;
						b=b+1;
					}
					//para dos fichas contrarias
					else if( (tablero[i+3][j-3]== y && tablero[i+4][j-4]== y ) && (tablero[i+5][j-5]=='O' || tablero[i+5][j-5]=='*')){ //si hay un espacio o final del tablero luego de la ficha contraria
						j_triple[a][b]=i+3; //guarda la posicion a la que se movera la ficha de la izquierda, que es el lugar de la ficha enemiga
						b=b+1;
						j_triple[a][b]=j-3;
						b=b+1;
					}
					if(tablero[i][j-2]=='O' && tablero[i+1][j-3]=='O' && tablero[i+2][j-4]=='O'){ //CASO 5
						j_triple[a][b]=i;
						b=b+1;
						j_triple[a][b]=j-2;
						b=b+1;
					}
					if(tablero[i-1][j-1]=='O' && tablero[i][j-2]=='O' && tablero[i+1][j-3]=='O'){ //CASO 6
						j_triple[a][b]=i-1;
						b=b+1;
						j_triple[a][b]=j-1;
						b=b+1;
					}
					a=a+1;
					b=0;
				}
			}

		}
	}
	/*    printf("\n Jugadas triples posibles: \n");
        for(i=0; i<40; i++){
            printf("\n");
                    for(j=0; j<19; j++){
                        printf(" %d", j_triple[i][j]);
                    }
                }*/
}

/*
 * Funcion que realiza el movimiento deseado por el jugador
 * Parametros:
 * j_simple: Se guardan las fichas y coordenadas posibles para una ficha especifica
 * j_doble: Se guardan las fichas y coordenadas posibles para dos fichas especificas
 * j_triple: Se guardan las fichas y coordenadas posibles para tres fichas especificas
 * tj: recibe el tipo de jugada diferenciada que se hará
 * x: contiene el valor de la(s) ficha(s) aliada(s) respecto a la cual se calcularan las jugadas posibles
 * y: contiene el valor de la(s) ficha(s) enemigas(s) respecto a la cual se calcularan las jugadas posibles
 */
void mov_jugador(char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], int tj, char x, char y){
	int i, j, a, b, f, c, fd, cd, ban, con;
	a=0;
	if(tj==1){ //JUGADA SIMPLE
		ban=1; //condicion de validez
		do{ //para validar la ficha
			printf("\nUsuario ingrese las coordenadas de la ficha que desea mover\n");
			//scanf("%d,%d", &f, &c);
			f=jugadas[0][0];
			c=jugadas[0][1];
			for(i=0; i<14; i++){
				if( j_simple[i][0] == f  &&  j_simple[i][1] == c){
					ban=1;
					a=i; //se guarda la fila de la ficha seleccionada
					break;
				}
				if(a==13){ //no encontró las coordenadas en la matriz
					ban=0;
				}
			}
			if( j_simple[a][2] == -1){
				ban=0;
			}
		}
		while(ban==0);
		ban=0;
		do{
			printf("\nUsuario ingrese las coordenadas de destino\n");
			//scanf("%d,%d", &fd, &cd);
			fd=jugadas[1][0];
			cd=jugadas[1][1];
			for(b=2; b<14; b=b+2){
				if( j_simple[a][b] == fd && j_simple[a][b+1] == cd){
					ban=1;
				}
			}
		}
		while(ban==0);
		tablero[fd][cd]= x;
		tablero[f][c]='O';
	}
	//DOBLE
	int f1, c1, f2, c2, f3, c3, aux1, aux2, x1, y1, df, dc; //los auxiliares son para ordenar
	if(tj==2){ //JUGADA DOBLE
		ban=1; //condicion de validez
		do{ //para validar la ficha
			printf("\nUsuario ingrese las coordenadas de las fichas que desea mover\n");
			//scanf("%d,%d", &f1, &c1);
			//scanf("%d,%d", &f2, &c2);
			f1=jugadas[0][0];
			c1=jugadas[0][1];
			f2=jugadas[1][0];
			c2=jugadas[1][1];
			//para ordenar las fichas de acuerdo a como estan guardadas en la matriz
			if(f1>f2){
				aux1=f1;
				f1=f2;
				f2=aux1;
				aux2=c1;
				c1=c2;
				c2=aux2;
			}
			else if(f1==f2){
				if(c1>c2){
					aux2=c1;
					c1=c2;
					c2=aux2;
				}

			}
			printf("(%d,%d) (%d,%d)", f1,c1,f2,c2);
			con=0;
			for(i=0; i<40; i++){
				if( j_doble[i][0] == f1  &&  j_doble[i][1] == c1 && j_doble[i][2] == f2  &&  j_doble[i][3] == c2 ){
					a=i; //se guarda la fila de la ficha seleccionada
					ban=1;
					break;
				}
				con=con+1;
				if(con==40){
					ban=0;
				}
			}
			if( j_doble[a][4] == -1){
				ban=0;
			}
		}
		while(ban==0);
		ban=0;
		do{
			printf("\nUsuario ingrese las coordenadas de destino\n");
			//scanf("%d,%d", &fd, &cd);
			fd=jugadas[2][0];
			cd=jugadas[2][1];
			for(b=4; b<16; b=b+2){
				if( j_doble[a][b] == fd && j_doble[a][b+1] == cd){
					ban=1;
				}
			}
		}
		while(ban==0);

		x1= fd - j_doble[a][0]; //se guarda la diferencia de coordenadas entre destino y posicion actual de la primera ficha
		y1= cd- j_doble[a][1];
		df= fd - j_doble[a][0];
		dc= cd- j_doble[a][1];
		if( tablero[fd][cd]== y ){ //EMPUJAR FICHA CONTRARIA
			if(y1==4){ //PRIMER CASO
				df=0;
				dc=2;
				if( tablero[fd][cd+1]== '*'){ //final del tablero
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{ //espacio vacio
					tablero[fd+df][cd+dc]= y;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==2 && y1==2){ //SEGUNDO CASO
				df=1;
				dc=1;
				if( tablero[fd+1][cd+1]== '*'){
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==2 && y1==-2 ){ //TERCER CASO
				df=1;
				dc=-1;
				if( tablero[fd+1][cd-1]== '*'){
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else{ //PARA CASOS NORMALES
				if( (tablero[fd+x1][cd+y1]== '*') || (tablero[fd][cd-1] == '*') ){ //si es final del tablero
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else{
					tablero[fd+x1][cd+y1]= y;
					tablero[fd][cd]= 'O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
			}
		}

		else{        //MOVIMIENTO EN ESPACIO VACIO
			if(y1==4){ //PRIMER CASO ESPECIAL
				df=0; //diferencia fila
				dc=2; //diferencia columna
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==2 && y1==2){ //SEGUNDO CASO ESPECIAL
				df=1;
				dc=1;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==2 && y1==-2 ){ //TERCER CASO ESPECIAL
				df=1;
				dc=-1;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else{
				tablero[f1+x1][c1+y1]= x;
				tablero[f1][c1]='O';
				tablero[f2+x1][c2+y1]= x;
				tablero[f2][c2]='O';
			}
		}
	}

	//JUGADA TRIPLE
	if(tj==3){
		con=0;
		int aux1, aux2; // para guardar la primera, segunda y tercera fila
		int vec[6];
		ban=1; //condicion de validez
		do{ //para validar la ficha
			printf("\nUsuario ingrese las coordenadas de las fichas que desea mover\n");
			//scanf("%d,%d", &f1, &c1);
			//scanf("%d,%d", &f2, &c2);
			//scanf("%d,%d", &f3, &c3);
			f1=jugadas[0][0];
			c1=jugadas[0][1];
			f2=jugadas[1][0];
			c2=jugadas[1][1];
			f3=jugadas[2][0];
			c3=jugadas[2][1];
			vec[0]=f1;
			vec[1]=c1;
			vec[2]=f2;
			vec[3]=c2;
			vec[4]=f3;
			vec[5]=c3;
			if(f1!=f2 ){
				printf("\nEntra if diferente");
				for(i=0; i<6; i=i+2){
					for(j=0; j<6; j=j+2){
						if( vec[i] < vec[j] ){
							aux1=vec[i];
							vec[i]=vec[j];
							vec[j]=aux1;
							aux2=vec[i+1];
							vec[i+1]=vec[j+1];
							vec[j+1]=aux2;
						}
					}
				}
				f1=vec[0];
				c1=vec[1];
				f2=vec[2];
				c2=vec[3];
				f3=vec[4];
				c3=vec[5];
			}
			if(f1==f2 && f1==f3){
				for(i=1; i<6; i=i+2){
					for(j=1; j<6; j=j+2){
						if( vec[i] < vec[j] ){
							aux1=vec[i];
							vec[i]=vec[j];
							vec[j]=aux1;
							aux2=vec[i-1];
							vec[i-1]=vec[j-1];
							vec[j-1]=aux2;
						}
					}
				}
				f1=vec[0];
				c1=vec[1];
				f2=vec[2];
				c2=vec[3];
				f3=vec[4];
				c3=vec[5];
			}
			printf("(%d,%d) (%d,%d) (%d,%d)", f1,c1,f2,c2,f3,c3);
			for(i=0; i<40; i++){
				if( j_triple[i][0] == f1  &&  j_triple[i][1] == c1 && j_triple[i][2] == f2  &&  j_triple[i][3] == c2 && j_triple[i][4] == f3  &&  j_triple[i][5] == c3 ){
					a=i; //se guarda la fila de la ficha seleccionada
					ban=1;
					break;
				}
				con=con+1;
				if(con==40){
					ban=0;
				}
			}
			if( j_triple[a][6] == -1){
				ban=0;
			}
		}
		while(ban==0);
		ban=0;
		do{
			printf("\nUsuario ingrese las coordenadas de destino\n");
			//scanf("%d,%d", &fd, &cd);
			fd=jugadas[3][0];
			cd=jugadas[3][1];
			for(b=6; b<18; b=b+2){
				if( j_triple[a][b] == fd && j_triple[a][b+1] == cd){
					ban=1;
				}
			}
		}
		while(ban==0);

		x1= fd - j_triple[a][0]; //se guarda la diferencia de coordenadas entre destino y posicion actual de la primera ficha
		y1= cd- j_triple[a][1];
		df= fd- j_triple[a][0];
		dc= cd- j_triple[a][1];

			if( y1==6 && tablero[fd][cd]== y && tablero[fd][cd+2]== y ){ //PRIMER CASO EMPUJAR DOS FICHA CONTRARIAS A LA DERECHA
				df=0;
				dc=2;
				if( tablero[fd][cd+3]== '*'){ //final del tablero
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{ //espacio vacio
					tablero[fd+df][(cd+2)+dc]= y; //para mover la segunda ficha
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}

			else if( x1==3 && y1==3 && tablero[fd][cd]== y && tablero[fd+1][cd+1]== y ){ //SEGUNDO CASO MOVER 2 FICHAS DIAG ABAJO DERECHA
				df=1;
				dc=1;
				if( tablero[fd+2][cd+2]== '*'){
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+2][cd+2]= y; //para mover la segunda ficha
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}

			else if( x1==3 && y1==-3 && tablero[fd][cd]== y && tablero[fd+1][cd-1]== y ){ //TERCER CASO MOVER 2 FICHAS DIAG ABAJO IZQ
				df=1;
				dc=-1;
				if( tablero[fd+2][cd-2]== '*'){
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+2][cd-2]= y; //para mover la segunda ficha
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}

			else if ( tablero[fd][cd]== y && tablero[fd+x1][cd+y1]== y ) { //si no es ninguno de los 3 casos especiales
				if(tablero[fd+df][(cd-1)+dc]== '*'){ //si es final del tablero en horizontal
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
				else if(tablero[(fd-1)+df][(cd-1)+dc]== '*'){
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
				else if(tablero[(fd-1)+df][(cd+1)+dc]== '*'){
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
				else{ //no es final de tablero
					tablero[fd+(2*x1)][cd+(2*y1)]= y;
					tablero[fd+x1][cd+y1]= y;
					tablero[fd][cd]= 'O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
			}

		else if( tablero[fd][cd]== y ){ //EMPUJAR UNA FICHA CONTRARIA
			if(y1==6){ //PRIMER CASO
				df=0;
				dc=2;
				if( tablero[fd][cd+1]== '*'){ //final del tablero
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{ //espacio vacio
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==3 && y1==3){ //SEGUNDO CASO
				df=1;
				dc=1;
				if( tablero[fd+1][cd+1]== '*'){ //final tablero
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==3 && y1==-3 ){ //TERCER CASO
				df=1;
				dc=-1;
				if( tablero[fd+1][cd-1]== '*'){ //final tablero
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}

			else{ //si no es ninguno de los 3 casos especiales
				if(tablero[fd+df][cd+dc]== '*'){ //si es final del tablero en horizontal
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
				else if(tablero[fd+df][cd+dc]== '*'){
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
				else if(tablero[fd+df][cd+dc]== '*'){
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
				else{ //no es final de tablero
					tablero[fd+x1][cd+y1]= y;
					tablero[fd][cd]= 'O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
				}
			}
		}

		else{     //PARA MOVER LAS 3 FICHAS A UN ESPACIO VACIO
			if(y1==6){ //PRIMER CASO ESPECIAL (poner el else final aquí
				df=0; //diferencia fila
				dc=2; //diferencia columna
				tablero[f3+df][c3+dc]= x;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==3 && y1==3){ //SEGUNDO CASO ESPECIAL
				df=1;
				dc=1;
				tablero[f3+df][c3+dc]= x;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==3 && y1==-3 ){ //TERCER CASO ESPECIAL
				df=1;
				dc=-1;
				tablero[f3+df][c3+dc]= x;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else{ //PARA MOVER 3 FICHAS A UN ESPACIO VACIO
				tablero[f1+x1][c1+y1]= x;
				tablero[f1][c1]='O';
				tablero[f2+x1][c2+y1]= x;
				tablero[f2][c2]='O';
				tablero[f3+x1][c3+y1]= x;
				tablero[f3][c3]='O';
			}
		}
	}
}

/*
 * Funcion con la cual se determina el tipo de jugada que se hará
 * Parametros:
 * Ninguno
 * Retorno:
 * a: variable en la cual se guarda el tipo de jugada. (1) Si es simple, (2) Si es doble, (3) Si es triple
 */
int tipo_jugada(void){
	int a,c, ban;
	do{
		printf("\nUsuario elija el tipo de jugada:\n1.JUGADA SIMPLE\n2.JUGADA DOBLE\n3.JUGADA TRIPLE\n");
		scanf("\n%d", &a);
		ban=1;
		if(a<0 || a>3){
			printf("\nOpcion invalida, vuelva a ingresar la opcion.");
			while((c = getchar()) != '\n'){}
			ban=0;
		}
	}while(ban==0);
	return a;
}

/*
 *Funcion que realiza el movimiento de la computadora
 *Parametros:
 *j_simple : la matriz que contiene las jugadas válidas para una ficha
 *j_doble : la matriz que contiene las jugadas válidas para dos fichas
 *j_triple: la matriz que contiene las jugadas válidas para tres fichas
 *x: contiene el valor de la(s) ficha(s) aliada(s) respecto a la cual se harán los movimientos
 *y: contiene el valor de la(s) ficha(s) enemiga(s) respecto a la cual se harán los movimientos
 *Retorno:
 *Un entero que es cero si la función es correcta
 */
int mov_comp(char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], char x, char y){
	int a, b, fd, cd, band1, band2, tj, df, dc;
	tj= rand()%3; //se sortea el tipo de jugada que hará la computadora
	if(tj==0){ //ALEATORIO SIMPLE
		int f, c; //para guardar las coordenadas de la ficha que se moverá
		do{
			band1=1;
			a= rand()%14;
			if(j_simple[a][0] == -1 || j_simple[a][2] == -1){ //si no hay ninguna ficha o la ficha no tiene jugada posible
				band1=0;
			}
		}while(band1 == 0);

		do{
			band2=0;
			b= rand()%12+2; //un numero entre 2 y 13
			if( j_simple[a][b] != -1){
				band2=1;
				if(b%2 != 0){
					b=b-1; //para que  cambie de lugar a la fila porque apuntaba a una columna
				}
			}
		}while(band2 == 0);
		fd=j_simple[a][b]; //fd es la fila destino
		cd=j_simple[a][b+1]; //cd es la columna destino
		f=j_simple[a][0];
		c=j_simple[a][1];
		tablero[fd][cd]= x;
		tablero[f][c]='O';
	}

	if(tj==1){ //ALEATORIO DOBLE
		int f1, c1, f2, c2, x1, y1; //para guardar las coordenadas de las fichas que se moverán
		do{
			band1=1;
			a= rand()%40;
			if(j_doble[a][0] == -1 || j_doble[a][4] == -1){ //si no hay ninguna ficha o la ficha no tiene jugada posible
				band1=0;
			}
		}while(band1 == 0);

		do{
			band2=0;
			b= rand()%12+4; //numero entre 4 y 15
			if( j_doble[a][b] != -1){
				band2=1;
				if(b%2 != 0){
					b=b-1; //para que  cambie de lugar a la fila porque apuntaba a una columna
				}
			}
		}while(band2 == 0);

		fd=j_doble[a][b]; //fd es la fila destino
		cd=j_doble[a][b+1]; //cd es la columna destino
		f1=j_doble[a][0];
		c1=j_doble[a][1];
		f2=j_doble[a][2];
		c2=j_doble[a][3];
		x1= fd - j_doble[a][0]; //se guarda la diferencia de coordenadas entre destino y posicion actual de la primera ficha
		y1= cd- j_doble[a][1];
		if( tablero[fd][cd]==y ){ //EMPUJAR FICHA CONTRARIA
			if(y1==4){ //PRIMER CASO
				df=0;
				dc=2;
				if( tablero[fd][cd+1]== '*'){ //final del tablero
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{ //espacio vacio
					tablero[fd+df][cd+dc]= y;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==2 && y1==2){ //SEGUNDO CASO
				df=1;
				dc=1;
				if( tablero[fd+1][cd+1]== '*'){
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==2 && y1==-2 ){ //TERCER CASO
				df=1;
				dc=-1;
				if( tablero[fd+1][cd-1]== '*'){
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else{ //PARA CASOS NORMALES
				if( (tablero[fd+x1][cd+y1]== '*') || (tablero[fd][cd-1] == '*') ){ //si es final del tablero
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else{
					tablero[fd+x1][cd+y1]= y;
					tablero[fd][cd]= 'O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
			}
		}

		else{        //MOVIMIENTO EN ESPACIO VACIO
			if(y1==4){ //PRIMER CASO ESPECIAL
				df=0; //diferencia fila
				dc=2; //diferencia columna
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==2 && y1==2){ //SEGUNDO CASO ESPECIAL
				df=1;
				dc=1;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==2 && y1==-2 ){ //TERCER CASO ESPECIAL
				df=1;
				dc=-1;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else{
				tablero[f1+x1][c1+y1]= x;
				tablero[f1][c1]='O';
				tablero[f2+x1][c2+y1]= x;
				tablero[f2][c2]='O';
			}
		}
	}

	if(tj==2){ //ALEATORIO TRIPLE
		int f1, c1, f2, c2, f3, c3, x1, y1; //para guardar las coordenadas de las fichas que se moverán
		do{
			band1=1;
			a= rand()%40;
			if(j_triple[a][0] == -1 || j_triple[a][6] == -1){ //si no hay ninguna ficha o la ficha no tiene jugada posible
				band1=0;
			}
		}while(band1 == 0);

		do{
			band2=0;
			b= rand()%12+6; //numero entre 6 y 18
			if( j_triple[a][b] != -1){
				band2=1;
				if(b%2 != 0){
					b=b-1; //para que  cambie de lugar a la fila porque apuntaba a una columna
				}
			}
		}while(band2 == 0);

		fd=j_triple[a][b]; //fd es la fila destino
		cd=j_triple[a][b+1]; //cd es la columna destino
		f1=j_triple[a][0];
		c1=j_triple[a][1];
		f2=j_triple[a][2];
		c2=j_triple[a][3];
		f3=j_triple[a][4];
		c3=j_triple[a][5];
		x1= fd - j_triple[a][0]; //se guarda la diferencia de coordenadas entre destino y posicion actual de la primera ficha
		y1= cd- j_triple[a][1];
		if( tablero[fd][cd]== y && tablero[fd][cd+2]== y ){ //EMPUJAR DOS FICHA CONTRARIAS
			if(y1==6){ //PRIMER CASO
				df=0;
				dc=2;
				if( tablero[fd][cd+3]== '*'){ //final del tablero
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{ //espacio vacio
					tablero[fd+df][(cd+2)+dc]= y; //para mover la segunda ficha
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==3 && y1==3){ //SEGUNDO CASO
				df=1;
				dc=1;
				if( tablero[fd+2][cd+2]== '*'){
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+2][cd+2]= y; //para mover la segunda ficha
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==3 && y1==-3 ){ //TERCER CASO
				df=1;
				dc=-1;
				if( tablero[fd+2][cd-2]== '*'){
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+2][cd-2]= y; //para mover la segunda ficha
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}

			else{ //si no es ninguno de los 3 casos especiales
				if(tablero[fd+df][(cd-1)+dc]== '*'){ //si es final del tablero en horizontal
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else if(tablero[(fd-1)+df][(cd-1)+dc]== '*'){
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else if(tablero[(fd-1)+df][(cd+1)+dc]== '*'){
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else{ //no es final de tablero
					tablero[fd+(2*x1)][cd+(2*y1)]= y;
					tablero[fd+x1][cd+y1]= y;
					tablero[fd][cd]= 'O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
			}

		}
		else if( tablero[fd][cd]== y ){ //EMPUJAR UNA FICHA CONTRARIA
			if(y1==6){ //PRIMER CASO
				df=0;
				dc=2;
				if( tablero[fd][cd+1]== '*'){ //final del tablero
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{ //espacio vacio
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==3 && y1==3){ //SEGUNDO CASO
				df=1;
				dc=1;
				if( tablero[fd+1][cd+1]== '*'){
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}
			else if( x1==3 && y1==-3 ){ //TERCER CASO
				df=1;
				dc=-1;
				if( tablero[fd+1][cd-1]== '*'){
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
				else{
					tablero[fd+df][cd+dc]= y;
					tablero[f3+df][c3+dc]= x;
					tablero[f2+df][c2+dc]= x;
					tablero[f1+df][c1+dc]= x;
					tablero[f1][c1]='O';
				}
			}

			else{ //si no es ninguno de los 3 casos especiales
				if(tablero[fd+df][cd+dc]== '*'){ //si es final del tablero en horizontal
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else if(tablero[fd+df][cd+dc]== '*'){
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else if(tablero[fd+df][cd+dc]== '*'){
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
				else{ //no es final de tablero
					tablero[fd+x1][cd+y1]= y;
					tablero[fd][cd]= 'O';
					tablero[f3+x1][c3+y1]= x;
					tablero[f3][c3]='O';
					tablero[f1+x1][c1+y1]= x;
					tablero[f1][c1]='O';
					tablero[f2+x1][c2+y1]= x;
					tablero[f2][c2]='O';
				}
			}
		}

		else{     //PARA MOVER LAS 3 FICHAS A UN ESPACIO VACIO
			if(y1==6){ //PRIMER CASO ESPECIAL (poner el else final aquí
				df=0; //diferencia fila
				dc=2; //diferencia columna
				tablero[f3+df][c3+dc]= x;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==3 && y1==3){ //SEGUNDO CASO ESPECIAL
				df=1;
				dc=1;
				tablero[f3+df][c3+dc]= x;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else if( x1==3 && y1==-3 ){ //TERCER CASO ESPECIAL
				df=1;
				dc=-1;
				tablero[f3+df][c3+dc]= x;
				tablero[f2+df][c2+dc]= x;
				tablero[f1+df][c1+dc]= x;
				tablero[f1][c1]='O';
			}
			else{ //PARA MOVER 3 FICHAS A UN ESPACIO VACIO
				tablero[f1+x1][c1+y1]= x;
				tablero[f1][c1]='O';
				tablero[f2+x1][c2+y1]= x;
				tablero[f2][c2]='O';
				tablero[f3+x1][c3+y1]= x;
				tablero[f3][c3]='O';
			}
		}
	}
	return 0;
}

int huida (char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], char x, char y){
	int i, j, f1, c1, f2, c2, a, fd, cd, df, dc, band_h;
	band_h = 0;
	for(i=0; i<11; i++){
		for(j=0; j<19; j++){
			//CASO 1
			if( tablero[i][j] == x && tablero[i][j+1] == '*' && tablero[i][j-2] == y && tablero[i][j-4] == y){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				for(a=0; a<14; a++){ //busca la ficha en la matriz de jugadas
					if( (j_simple[a][0] == f1 && j_simple[a][1] == c1) && ( j_simple[a][2] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_simple[a][2];
						cd = j_simple[a][3];
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}
			if( tablero[i][j] == x && tablero[i][j-2] == x && tablero[i][j+1] == '*' && tablero[i][j-4] == y && tablero[i][j-6] == y && tablero[i][j-8] == y){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				f2 = i;
				c2 = j;
				f1 = i;
				c1 = j-2;
				for(a=0; a<40; a++){
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2 ) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_doble[a][4];
						cd = j_doble[a][5];
						df = fd - f1;
						dc = cd - c1;
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						tablero[f2+df][c2+dc] = x;
						tablero[f2][c2] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}

			//CASO 2
			if( tablero[i][j] == x && tablero[i][j-1] == '*' && tablero[i][j+2] == y && tablero[i][j+4] == y){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				for(a=0; a<14; a++){ //busca la ficha en la matriz de jugadas
					if( (j_simple[a][0] == f1 && j_simple[a][1] == c1) && ( j_simple[a][2] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_simple[a][2];
						cd = j_simple[a][3];
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}
			if( tablero[i][j] == x && tablero[i][j+2] == x && tablero[i][j-1] == '*' && tablero[i][j+4] == y && tablero[i][j+6] == y && tablero[i][j+8] == y){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				f2 = i;
				c2 = j+2;
				for(a=0; a<40; a++){
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2 ) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_doble[a][4];
						cd = j_doble[a][5];
						df = fd - f1;
						dc = cd - c1;
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						tablero[f2+df][c2+dc] = x;
						tablero[f2][c2] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}

			//CASO 3
			if( tablero[i][j] == x && tablero[i+1][j+1] == '*' && tablero[i-1][j-1] == y && tablero[i-2][j-2] == y){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				for(a=0; a<14; a++){ //busca la ficha en la matriz de jugadas
					if( (j_simple[a][0] == f1 && j_simple[a][1] == c1) && ( j_simple[a][2] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_simple[a][2];
						cd = j_simple[a][3];
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}
			if( tablero[i][j] == x && tablero[i+1][j+1] == x && tablero[i+2][j+2] == '*' && tablero[i-1][j-1] == y && tablero[i-2][j-2] == y && tablero[i-3][j-3] == y){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				f2 = i+1;
				c2 = j+1;
				for(a=0; a<40; a++){
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2 ) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_doble[a][4];
						cd = j_doble[a][5];
						df = fd - f1;
						dc = cd - c1;
						tablero[f2+df][c2+dc] = x;
						tablero[f2][c2] = 'O';
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}

			//CASO 4
			if( tablero[i][j] == x && tablero[i-1][j-1] == '*' && tablero[i+1][j+1] == y && tablero[i+2][j+2] == y){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				for(a=0; a<14; a++){ //busca la ficha en la matriz de jugadas
					if( (j_simple[a][0] == f1 && j_simple[a][1] == c1) && ( j_simple[a][2] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_simple[a][2];
						cd = j_simple[a][3];
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}
			if( tablero[i][j] == x && tablero[i+1][j+1] == x && tablero[i-1][j-1] == '*' && tablero[i+2][j+2] == y && tablero[i+3][j+3] == y && tablero[i+4][j+4] == y){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				f2 = i+1;
				c2 = j+1;
				for(a=0; a<40; a++){
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2 ) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_doble[a][4];
						cd = j_doble[a][5];
						df = fd - f1;
						dc = cd - c1;
						tablero[f2+df][c2+dc] = x;
						tablero[f2][c2] = 'O';
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}

			//CASO 5
			if( tablero[i][j] == x && tablero[i+1][j-1] == '*' && tablero[i-1][j+1] == y && tablero[i-2][j+2] == y){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				for(a=0; a<14; a++){ //busca la ficha en la matriz de jugadas
					if( (j_simple[a][0] == f1 && j_simple[a][1] == c1) && ( j_simple[a][2] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_simple[a][2];
						cd = j_simple[a][3];
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}
			if( tablero[i][j] == x && tablero[i+1][j-1] == x && tablero[i+2][j-2] == '*' && tablero[i-1][j+1] == y && tablero[i-2][j+2] == y && tablero[i-3][j+3] == y){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				f2 = i+1;
				c2 = j-1;
				for(a=0; a<40; a++){
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2 ) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_doble[a][4];
						cd = j_doble[a][5];
						df = fd - f1;
						dc = cd - c1;
						tablero[f2+df][c2+dc] = x;
						tablero[f2][c2] = 'O';
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}

			//CASO 6
			if( tablero[i][j] == x && tablero[i-1][j+1] == '*' && tablero[i+1][j-1] == y && tablero[i+2][j-2] == y){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				for(a=0; a<14; a++){ //busca la ficha en la matriz de jugadas
					if( (j_simple[a][0] == f1 && j_simple[a][1] == c1) && ( j_simple[a][2] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_simple[a][2];
						cd = j_simple[a][3];
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}
			if( tablero[i][j] == x && tablero[i+1][j-1] == x && tablero[i-1][j+1] == '*' && tablero[i+2][j-2] == y && tablero[i+3][j-3] == y && tablero[i+4][j-4] == y){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				f1 = i;
				c1 = j;
				f2 = i+1;
				c2 = j-1;
				for(a=0; a<40; a++){
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2 ) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						fd = j_doble[a][4];
						cd = j_doble[a][5];
						df = fd - f1;
						dc = cd - c1;
						tablero[f2+df][c2+dc] = x;
						tablero[f2][c2] = 'O';
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_h = 1; // realizó la jugada de escape
						printf("\nHUIDA\n");
						break;
					}
				}
			}


		}
	}

	return band_h;

}

int ataque (char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], char x, char y){
	int i, j, f1, c1, f2, c2, f3, c3, a, fd, cd, band_a;
	band_a = 0;
	for(i=0; i<11; i++){
		for(j=0; j<19; j++){
			//CASO 1
			if( tablero[i][j] == y && tablero[i][j+1] == '*' && tablero[i][j-2] == x && tablero[i][j-4] == x ){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i;
				c1 = j-4;
				f2 = i;
				c2 = j-2;
				for(a=0; a<40; a++){ //busca la ficha en la matriz de jugadas
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_a = 1; // realizó la jugada de ataque
						printf("\nATAQUE");
						break;
					}
				}
			}
			if( tablero[i][j] == y && tablero[i][j+3] == '*' && tablero[i][j+2] == y && tablero[i][j-2] == x && tablero[i][j-4] == x && tablero[i][j-6] == x ){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i;
				c1 = j-6;
				f2 = i;
				c2 = j-4;
				f3 = i;
				c3 = j-2;
				for(a=0; a<40; a++){
					if( (j_triple[a][0] == f1 && j_triple[a][1] == c1 && j_triple[a][2] == f2 && j_triple[a][3] == c2 && j_triple[a][4] == f3 && j_triple[a][5] == c3) && ( j_triple[a][6] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_a = 1; // realizó la jugada de escape
						printf("\nATAQUE\n");
						break;
					}
				}
			}

			//CASO 2
			if( tablero[i][j] == y && tablero[i][j-1] == '*' && tablero[i][j+2] == x && tablero[i][j+4] == x ){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i;
				c1 = j+2;
				f2 = i;
				c2 = j+4;
				for(a=0; a<40; a++){ //busca la ficha en la matriz de jugadas
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f2][c2] = 'O';
						band_a = 1; // realizó la jugada de ataque
						printf("\nATAQUE");
						break;
					}
				}
			}
			if( tablero[i][j] == y && tablero[i][j-1] == '*' && tablero[i][j+2] == y && tablero[i][j+4] == x && tablero[i][j+6] == x && tablero[i][j+8] == x ){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i;
				c1 = j+4;
				f2 = i;
				c2 = j+6;
				f3 = i;
				c3 = j+8;
				for(a=0; a<40; a++){
					if( (j_triple[a][0] == f1 && j_triple[a][1] == c1 && j_triple[a][2] == f2 && j_triple[a][3] == c2 && j_triple[a][4] == f3 && j_triple[a][5] == c3) && ( j_triple[a][6] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f3][c3] = 'O';
						band_a = 1; // realizó la jugada de escape
						printf("\nATAQUE\n");
						break;
					}
				}
			}

			//CASO 3
			if( tablero[i][j] == y && tablero[i+1][j+1] == '*' && tablero[i-1][j-1] == x && tablero[i-2][j-2] == x ){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i-2;
				c1 = j-2;
				f2 = i-1;
				c2 = j-1;
				for(a=0; a<40; a++){ //busca la ficha en la matriz de jugadas
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_a = 1; // realizó la jugada de ataque
						printf("\nATAQUE");
						break;
					}
				}
			}
			if( tablero[i][j] == y && tablero[i+2][j+2] == '*' && tablero[i+1][j+1] == y && tablero[i-1][j-1] == x && tablero[i-2][j-2] == x && tablero[i-3][j-3] == x ){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i-3;
				c1 = j-3;
				f2 = i-2;
				c2 = j-2;
				f3 = i-1;
				c3 = j-1;
				for(a=0; a<40; a++){
					if( (j_triple[a][0] == f1 && j_triple[a][1] == c1 && j_triple[a][2] == f2 && j_triple[a][3] == c2 && j_triple[a][4] == f3 && j_triple[a][5] == c3) && ( j_triple[a][6] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_a = 1; // realizó la jugada de escape
						printf("\nATAQUE\n");
						break;
					}
				}
			}

			//CASO 4
			if( tablero[i][j] == y && tablero[i-1][j-1] == '*' && tablero[i+1][j+1] == x && tablero[i+2][j+2] == x ){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i+1;
				c1 = j+1;
				f2 = i+2;
				c2 = j+2;
				for(a=0; a<40; a++){ //busca la ficha en la matriz de jugadas
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f2][c2] = 'O';
						band_a = 1; // realizó la jugada de ataque
						printf("\nATAQUE");
						break;
					}
				}
			}
			if( tablero[i][j] == y && tablero[i-1][j-1] == '*' && tablero[i+1][j+1] == y && tablero[i+2][j+2] == x && tablero[i+3][j+3] == x && tablero[i+4][j+4] == x ){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i+2;
				c1 = j+2;
				f2 = i+3;
				c2 = j+3;
				f3 = i+4;
				c3 = j+4;
				for(a=0; a<40; a++){
					if( (j_triple[a][0] == f1 && j_triple[a][1] == c1 && j_triple[a][2] == f2 && j_triple[a][3] == c2 && j_triple[a][4] == f3 && j_triple[a][5] == c3) && ( j_triple[a][6] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f3][c3] = 'O';
						band_a = 1; // realizó la jugada de escape
						printf("\nATAQUE\n");
						break;
					}
				}
			}

			//CASO 5
			if( tablero[i][j] == y && tablero[i+1][j-1] == '*' && tablero[i-1][j+1] == x && tablero[i-2][j+2] == x ){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i-2;
				c1 = j+2;
				f2 = i-1;
				c2 = j+1;
				for(a=0; a<40; a++){ //busca la ficha en la matriz de jugadas
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_a = 1; // realizó la jugada de ataque
						printf("\nATAQUE");
						break;
					}
				}
			}
			if( tablero[i][j] == y && tablero[i+2][j-2] == '*' && tablero[i+1][j-1] == y && tablero[i-1][j+1] == x && tablero[i-2][j+2] == x && tablero[i-3][j+3] == x ){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i-3;
				c1 = j+3;
				f2 = i-2;
				c2 = j+2;
				f3 = i-1;
				c3 = j+1;
				for(a=0; a<40; a++){
					if( (j_triple[a][0] == f1 && j_triple[a][1] == c1 && j_triple[a][2] == f2 && j_triple[a][3] == c2 && j_triple[a][4] == f3 && j_triple[a][5] == c3) && ( j_triple[a][6] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f1][c1] = 'O';
						band_a = 1; // realizó la jugada de escape
						printf("\nATAQUE\n");
						break;
					}
				}
			}

			//CASO 6
			if( tablero[i][j] == y && tablero[i-1][j+1] == '*' && tablero[i+1][j-1] == x && tablero[i+2][j-2] == x ){ //final del tablero a la derecha con 2 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i+1;
				c1 = j-1;
				f2 = i+2;
				c2 = j-2;
				for(a=0; a<40; a++){ //busca la ficha en la matriz de jugadas
					if( (j_doble[a][0] == f1 && j_doble[a][1] == c1 && j_doble[a][2] == f2 && j_doble[a][3] == c2) && ( j_doble[a][4] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f2][c2] = 'O';
						band_a = 1; // realizó la jugada de ataque
						printf("\nATAQUE");
						break;
					}
				}
			}
			if( tablero[i][j] == y && tablero[i-1][j+1] == '*' && tablero[i+1][j-1] == y && tablero[i+2][j-2] == x && tablero[i+3][j-3] == x && tablero[i+4][j-4] == x ){ //final del tablero a la derecha con 3 fichas enemigas amenazando a la izquierda
				fd = i;
				cd = j;
				f1 = i+2;
				c1 = j-2;
				f2 = i+3;
				c2 = j-3;
				f3 = i+4;
				c3 = j-4;
				for(a=0; a<40; a++){
					if( (j_triple[a][0] == f1 && j_triple[a][1] == c1 && j_triple[a][2] == f2 && j_triple[a][3] == c2 && j_triple[a][4] == f3 && j_triple[a][5] == c3) && ( j_triple[a][6] != -1 ) ){ //encontro la ficha acorralada y es capaz de hacer un movimiento
						tablero[fd][cd] = x;
						tablero[f3][c3] = 'O';
						band_a = 1; // realizó la jugada de escape
						printf("\nATAQUE\n");
						break;
					}
				}
			}

		}
	}

	return band_a;

}
