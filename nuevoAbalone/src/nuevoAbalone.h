/*
 * abalone.h
 *
 *  Created on: 15 nov. 2018
 *      Author: lp1-2018
 */

#ifndef ABALONE_H_
#define ABALONE_H_

#define MAX_FILA 11
#define MAX_COLUMNA 19
#define MAX_LON_NOM 15 //maxima longitud que puede tener el nombre que ingresa el usuario

int ficha_B, ficha_N;
char tablero[11][19];

int quieninicia;
int colorhumano;
int tipodejuego;
int jugadas[4][2];
int tipodejugada;

void inicializartablero(char tablero[11][19]);
void imprimirtablero(char tablero[11][19]);
int iniciarjuego(void);
int colorfichas(void);
int cantjug(void);
void cantidad_fichas(char tablero[11][19]);
void jugadaposible(char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], int c1, int c2, int c3, char x, char y);
void mov_jugador(char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], int tj, char x, char y);
int mov_comp(char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], char x, char y);
int tipo_jugada(void);
int huida (char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], char x, char y);
int ataque (char tablero[11][19], int j_simple[14][15], int j_doble[40][17], int j_triple[40][19], char x, char y);

#endif /* ABALONE_H_ */
