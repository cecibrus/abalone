/*
 ============================================================================
 Name        : GTKabalone.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in GTK+
 ============================================================================
 */
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "nuevoAbalone.h"

//Un vector de Strings, almacena ubicacion de imagenes
const gchar *imagenes[] =
		{"./IMG/blanconormal.png",
		"./IMG/negronormal.png",
		"./IMG/vacio.png",
		"./IMG/fueratablero.png",//fuera del tablero,
		"./IMG/invalido.png",
		"./IMG/blancoseleccionado.png",//borde de arriba,
		"./IMG/negroseleccionado.png",//borde de abajo
		};

int partidaIniciada; //bandera que determina si la partida inicio
int partidaTerminada; //bandera que determina si la partida termino
int resultado; //se guarda un numero distinto de acuerdo  a como termino la partida
int maxjugadas;
char **nombres;
int **partidas;
const gchar *entry_nombre;
const gchar *entry_rival;
const gchar *entry_directorio;
int clicks_jugada=0;
int cj=0;
int ban_config=0, ban_nombre=0, ban_rival=0;
int j_simple[14][15], j_doble[40][17], j_triple[40][19];
int c1, c2, c3, tj, ban, j, c, nj, h, a;
char x, y;

GtkImage *imagen[MAX_FILA][MAX_COLUMNA];
GtkWidget *label_turno;
GtkWidget *label_estado;
GtkWidget *label_advertencia;
GtkWidget *label_fichas;
GtkWidget *label_jugadores;
GObject *dialogAyuda;// identificador de la ventana de diálogo de ayuda al juego
GObject *dialogAcerca;// identificador de la ventana de diálogo de Acerca de ABALONE
GtkWidget *dialogConfig;//identificador de la ventana de configuracion del juego
GtkWidget *window;
GtkWidget *primeraventana;
GtkWidget *box_tablero;
GtkWidget *entrynombre;
GtkWidget *entryrival;
GtkWidget *entrydirectorio;
GtkWidget *negro;
GtkWidget *blanco;
GtkWidget *aleatoriocolor;
GtkWidget *humano;
GtkWidget *computadora;
GtkWidget *aleatorioinicia;
GtkWidget *spin_cant_jugadas;
GtkWidget *cpu_cpu;
GtkWidget *cpu_humano;
GtkWidget *aceptar;
GObject *menu_archivo_nuevo;
GtkWidget *b_configuracion;
GtkWidget *b_jugar;
GtkWidget *b_estadistica;
GtkWidget *b_instrucciones;

//declaraciones de funciones necesarias
void mostrarMensajeFin(int ficha_B, int ficha_N);
void actualizartablero();
void estadisticas();

/*
 * Funcion que cuenta la cantidad de lineas en un archivo. Sirve para contar la cantidad de jugadores
 * que estan guardados en las estadisticas.
 * Parametros:
 *  El puntero del archivo del cual queremos contar la cantidad de lineas
 * Retorno:
 *  Un int que indica la cantidad de lineas
 */
int cuentaLineas(FILE *f){
	int c,cont=0;
	while((c=getc(f))!=EOF){
		if(c=='\n'){
			cont++;
		}
	}
	return cont;
}


/*
 * Función que reserva espacio de memoria para una matriz de dos dimensiones
 * del tipo de datos cualquiera.
 * Parámetros:
 * 	f -> cantidad de fila
 * 	c -> cantidad de columnas
 * 	bytes -> cantidad de bytes del tipo de dato de la matriz
 * Retorno:
 * 	NULL si ocurrió un error. La dirección de la matriz si no ocurrió ningún error.
 */
void **creaMatriz2d (unsigned int f, unsigned int c, unsigned int bytes) {
	int i;
	void **ret = malloc (f * sizeof (void *));	// creamos vector de punteros
	if (ret == NULL)
		return NULL;	// indicamos error

	// reservamos espacio para las filas
	for (i = 0; i < f; i++){
		if ((ret[i] = malloc (c * bytes)) == NULL){
			// liberamos toda la memoria ya asignada
			while (i--){
				free (ret[i]);
			}
			free(ret);
			return NULL;	// indicamos error
		}
	}
	return ret;
}


/*
 * Funcion que inicializa el tablero de juego y las banderas de estado de la partida.
 * Tambien activa los botones de opciones para que el jugador elija sus preferencias.
 * No recibe parametros ni tiene retorno
 *
 */
void iniciajuego(){
	inicializartablero(tablero);

	partidaTerminada = 0;	// inicialmente partida no terminó
	partidaIniciada = 0;

	gtk_widget_set_sensitive (GTK_WIDGET(spin_cant_jugadas), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(blanco), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(negro), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(aleatoriocolor), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(humano), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(computadora), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(aleatorioinicia), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(cpu_cpu), TRUE);
	gtk_widget_set_sensitive (GTK_WIDGET(cpu_humano), TRUE);
}


/*
 * Funcion que inicia la partida y desactiva los botones de configuraciones.
 * No recibe parametros ni tiene retorno
 */
void iniciarPartida(){
	partidaIniciada = 1;
	//una vez que la partida inicia ya no se pueden editar las configuraciones
	gtk_widget_set_sensitive (GTK_WIDGET(spin_cant_jugadas), FALSE);
	if(maxjugadas==0){
		maxjugadas=1000;
	}
	gtk_widget_set_sensitive (GTK_WIDGET(blanco), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(negro), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(aleatoriocolor), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(humano), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(computadora), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(aleatorioinicia), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(aleatoriocolor), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(cpu_cpu), FALSE);
	gtk_widget_set_sensitive (GTK_WIDGET(cpu_humano), FALSE);
}


/*
 * Funcion que guarda las coordenadas de los lugares en los que se hacen clicks, como máximo 3, para realizar las jugadas.
 * Parametros:
 *  caja de eventos, evento
 * Retorno:
 *  Ninguno, pero modifica la variable global de jugadas.
 */
void tablero_cb(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	guint i,l;
	i = (GUINT_FROM_LE(event->y) / 30); //las imagenes tienen son 30x30pixeles
	l = (GUINT_FROM_LE(event->x) / 30);

	iniciarPartida();

	jugadas[clicks_jugada][0]=i;
	jugadas[clicks_jugada][1]=l;
	clicks_jugada++;//hay un máximo de 4 clicks; 3 posiciones de origen y 1 de destino

	gchar *temp1= g_strdup_printf("Posicion invalida");

		if(colorhumano==1){
			if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='N'){
					gtk_image_clear(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]);
					gtk_image_set_from_file(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])],imagenes[6]);
					if(clicks_jugada==4){
						if(tablero[(jugadas[clicks_jugada-2][0])][(jugadas[clicks_jugada-2][1])]=='B'){
							tipodejugada=3; //es jugada triple empujando
							c1=c2=c3=0;
							x='B';
							y='N';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							tj=tipodejugada;
							mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
							x='N';
							y='B';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							h = huida(tablero, j_simple, j_doble, j_triple, x, y);
							if(h == 0){
								a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
							}
							if(h == 0 && a == 0){ // no atacó ni escapó
								mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
							}
							actualizartablero();
							cj++;
							gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
						}
					}else if(clicks_jugada==3){
						if(tablero[(jugadas[clicks_jugada-2][0])][(jugadas[clicks_jugada-2][1])]=='B'){
							tipodejugada=2; //es jugada doble empujando
							c1=c2=c3=0;
							x='B';
							y='N';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							tj=tipodejugada;
							mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
							x='N';
							y='B';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							h = huida(tablero, j_simple, j_doble, j_triple, x, y);
							if(h == 0){
								a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
							}
							if(h == 0 && a == 0){ // no atacó ni escapó
								mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
							}
							actualizartablero();
							cj++;
							gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
						}
						clicks_jugada=4;
					}
				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='B'){
					gtk_image_clear(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]);
					gtk_image_set_from_file(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])],imagenes[5]);
					if(clicks_jugada==4){
						gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					}
				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='O'){
					if(clicks_jugada==1||clicks_jugada==5){
						gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					}else if(clicks_jugada==2){
						tipodejugada=1; //es jugada simple
						c1=c2=c3=0;
						x='B';
						y='N';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						tj=tipodejugada;
						mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
						x='N';
						y='B';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						h = huida(tablero, j_simple, j_doble, j_triple, x, y);
						if(h == 0){
							a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
						}
						if(h == 0 && a == 0){ // no atacó ni escapó
							mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
						}
						actualizartablero();
						cj++;
						gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
					}else if(clicks_jugada==3){
						tipodejugada=2; //es jugada doble
						c1=c2=c3=0;
						x='B';
						y='N';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						tj=tipodejugada;
						mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
						x='N';
						y='B';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						h = huida(tablero, j_simple, j_doble, j_triple, x, y);
						if(h == 0){
							a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
						}
						if(h == 0 && a == 0){ // no atacó ni escapó
							mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
						}
						actualizartablero();
						cj++;
						gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
					}else if(clicks_jugada==4){
						tipodejugada=3; //es jugada triple
						c1=c2=c3=0;
						x='B';
						y='N';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						tj=tipodejugada;
						mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
						x='N';
						y='B';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						h = huida(tablero, j_simple, j_doble, j_triple, x, y);
						if(h == 0){
							a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
						}
						if(h == 0 && a == 0){ // no atacó ni escapó
							mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
						}
						actualizartablero();
						cj++;
						gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
					}
					clicks_jugada=4;

				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='$'){
					gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					clicks_jugada=0;
				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='*'){
					gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					clicks_jugada=0;
			}
		}else{
			if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='B'){
					gtk_image_clear(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]);
					gtk_image_set_from_file(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])],imagenes[5]);
					if(clicks_jugada==4){
						if(tablero[(jugadas[clicks_jugada-2][0])][(jugadas[clicks_jugada-2][1])]=='N'){
							tipodejugada=3; //es jugada triple empujando
							x='N';
							y='B';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							tj=tipodejugada;
							mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
							x='B';
							y='N';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							h = huida(tablero, j_simple, j_doble, j_triple, x, y);
							if(h == 0){
								a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
							}
							if(h == 0 && a == 0){ // no atacó ni escapó
								mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
							}
							actualizartablero();
							cj++;
							gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
						}
						clicks_jugada=0;
						//gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					}else if(clicks_jugada==3){
						if(tablero[(jugadas[clicks_jugada-2][0])][(jugadas[clicks_jugada-2][1])]=='N'){
							tipodejugada=2; //es jugada doble empujando
							c1=c2=c3=0;
							x='N';
							y='B';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							tj=tipodejugada;
							mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
							x='B';
							y='N';
							jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
							h = huida(tablero, j_simple, j_doble, j_triple, x, y);
							if(h == 0){
								a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
							}
							if(h == 0 && a == 0){ // no atacó ni escapó
								mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
							}
							actualizartablero();
							cj++;
							gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
						}
					}
				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='N'){
					gtk_image_clear(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]);
					gtk_image_set_from_file(imagen[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])],imagenes[6]);
					if(clicks_jugada==4){
						gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					}
				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='O'){
					if(clicks_jugada==1||clicks_jugada==5){
						gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					}else if(clicks_jugada==2){
						tipodejugada=1; //es jugada simple
						c1=c2=c3=0;
						x='N';
						y='B';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						tj=tipodejugada;
						mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
						x='B';
						y='N';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						h = huida(tablero, j_simple, j_doble, j_triple, x, y);
						if(h == 0){
							a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
						}
						if(h == 0 && a == 0){ // no atacó ni escapó
							mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
						}
						actualizartablero();
						cj++;
						gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
					}else if(clicks_jugada==3){
						tipodejugada=2; //es jugada doble
						c1=c2=c3=0;
						x='N';
						y='B';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						tj=tipodejugada;
						mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
						x='B';
						y='N';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						h = huida(tablero, j_simple, j_doble, j_triple, x, y);
						if(h == 0){
							a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
						}
						if(h == 0 && a == 0){ // no atacó ni escapó
							mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
						}
						actualizartablero();
						cj++;
						gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
					}else if(clicks_jugada==4){
						tipodejugada=3; //es jugada triple
						c1=c2=c3=0;
						x='N';
						y='B';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						tj=tipodejugada;
						mov_jugador(tablero, j_simple, j_doble, j_triple, tj, x, y);
						x='B';
						y='N';
						jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
						h = huida(tablero, j_simple, j_doble, j_triple, x, y);
						if(h == 0){
							a = ataque(tablero, j_simple, j_doble, j_triple, x, y);
						}
						if(h == 0 && a == 0){ // no atacó ni escapó
							mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
						}
						actualizartablero();
						cj++;
						gtk_label_set_text(GTK_LABEL(label_advertencia), " ");
					}
					clicks_jugada=4;
				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='$'){
					gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					clicks_jugada=0;
				}else if(tablero[(jugadas[clicks_jugada-1][0])][(jugadas[clicks_jugada-1][1])]=='*'){
					gtk_label_set_text(GTK_LABEL(label_advertencia), temp1);
					clicks_jugada=0;
			}
		}
	//}

	cantidad_fichas(tablero);
	gchar *temp2= g_strdup_printf("Fichas blancas: %d	Fichas negras: %d",ficha_B,ficha_N);
	gtk_label_set_text(GTK_LABEL(label_fichas), temp2);
	gchar *temp3= g_strdup_printf("%s VS %s",entry_nombre,entry_rival);
	if(entry_nombre!=NULL && entry_rival!=NULL){
		gtk_label_set_text(GTK_LABEL(label_jugadores), temp3);
	}

	if(cj==maxjugadas || ficha_B<8 || ficha_N<8){
			finJuego();
	}

	int fil,col;
	for(fil=0;fil<4;fil++){
		for(col=0;col<2;col++){
			printf("%d ", jugadas[fil][col]);
		}
	}printf("\n");

	if(clicks_jugada>=4){
		for(fil=0;fil<4;fil++){
			for(col=0;col<2;col++){
				jugadas[fil][col]=0;
			}
		}
		clicks_jugada=0;
	}

	printf("clicks %d \n", clicks_jugada);
	printf("tipo de jugada %d \n", clicks_jugada);
	g_free(temp1);
	g_free(temp2);
	g_free(temp3);
}


/* Funcion carga tablero, que recorre el tablero donde se realizan las jugadas y guarda las imagenes correspondientes de
 * acuerdo al contenido de este.
 * Parametros:
 *  ->Tablero de 9x17
 * Retorno:
 *  Ninguno, pero modifica una variable global.
 */
GtkWidget *cargatablero(){
	int fila;
	int columna;
	GtkWidget *eventbox;
	GtkWidget *tablerogtk;

	eventbox = gtk_event_box_new();
	tablerogtk = gtk_grid_new();

	if(partidaIniciada==0){
		for(fila=0;fila<MAX_FILA;fila++){
			for(columna=0;columna<MAX_COLUMNA;columna++){
				if(tablero[fila][columna]=='B'){ //tablero de c normal
					imagen[fila][columna] = gtk_image_new_from_file(imagenes[0]);
					gtk_grid_attach(GTK_GRID(tablerogtk), GTK_WIDGET(imagen[fila][columna]), columna, fila, 1, 1);
				}else if(tablero[fila][columna]=='O'){
					imagen[fila][columna] = gtk_image_new_from_file(imagenes[2]);
					gtk_grid_attach(GTK_GRID(tablerogtk), GTK_WIDGET(imagen[fila][columna]), columna, fila, 1, 1);
				}else if(tablero[fila][columna]=='N'){
					imagen[fila][columna] = gtk_image_new_from_file(imagenes[1]);
					gtk_grid_attach(GTK_GRID(tablerogtk), GTK_WIDGET(imagen[fila][columna]), columna, fila, 1, 1);
				}else if(tablero[fila][columna]=='*'){
					imagen[fila][columna] = gtk_image_new_from_file(imagenes[3]);
					gtk_grid_attach(GTK_GRID(tablerogtk), GTK_WIDGET(imagen[fila][columna]), columna, fila, 1, 1);
				}else if(tablero[fila][columna]=='$'){
					imagen[fila][columna] = gtk_image_new_from_file(imagenes[4]);
					gtk_grid_attach(GTK_GRID(tablerogtk), GTK_WIDGET(imagen[fila][columna]), columna, fila, 1, 1);
				}
			}
		}
		gtk_container_add(GTK_CONTAINER(eventbox), tablerogtk);
		g_signal_connect(eventbox, "button-press-event", G_CALLBACK(tablero_cb), tablerogtk);
	}else{
		for(fila=0;fila<MAX_FILA;fila++){
			for(columna=0;columna<MAX_COLUMNA;columna++){
				if(tablero[fila][columna]=='B'){ //tablero de c normal que viene de un include
					gtk_image_clear(imagen[fila][columna]);
					gtk_image_set_from_file(imagen[fila][columna],imagenes[0]);
				}else if(tablero[fila][columna]=='O'){
					gtk_image_clear(imagen[fila][columna]);
					gtk_image_set_from_file(imagen[fila][columna],imagenes[2]);
				}else if(tablero[fila][columna]=='N'){
					gtk_image_clear(imagen[fila][columna]);
					gtk_image_set_from_file(imagen[fila][columna],imagenes[1]);
				}else if(tablero[fila][columna]=='*'){
					gtk_image_clear(imagen[fila][columna]);
					gtk_image_set_from_file(imagen[fila][columna],imagenes[3]);
				}else if(tablero[fila][columna]=='$'){
					imagen[fila][columna] = gtk_image_new_from_file(imagenes[4]);
					gtk_grid_attach(GTK_GRID(tablerogtk), GTK_WIDGET(imagen[fila][columna]), columna, fila, 1, 1);
				}
			}
		}
	}
	return eventbox;
}

/*
 * Funcion que actualiza el tablero de acuerdo a las jugadas realizadas.
 * No tiene parametros ni retorno
 */
void actualizartablero(){
	int fila,columna;
	for(fila=0;fila<MAX_FILA;fila++){
				for(columna=0;columna<MAX_COLUMNA;columna++){
					if(tablero[fila][columna]=='B'){ //tablero de c normal que viene de un include
						gtk_image_clear(imagen[fila][columna]);
						gtk_image_set_from_file(imagen[fila][columna],imagenes[0]);
					}else if(tablero[fila][columna]=='O'){
						gtk_image_clear(imagen[fila][columna]);
						gtk_image_set_from_file(imagen[fila][columna],imagenes[2]);
					}else if(tablero[fila][columna]=='N'){
						gtk_image_clear(imagen[fila][columna]);
						gtk_image_set_from_file(imagen[fila][columna],imagenes[1]);
					}else if(tablero[fila][columna]=='*'){
						gtk_image_clear(imagen[fila][columna]);
						gtk_image_set_from_file(imagen[fila][columna],imagenes[3]);
					}
				}
			}
}

/*
 * Funcion que maneja el juego en red
 */
/*
 *
 */
void juego_red(){
	FILE *local;
	FILE *rival;
	FILE *historial;

	gchar *directorio_rival=NULL;
	gchar *directorio_local=NULL;

	strcpy(directorio_rival, entry_directorio);
	strcpy(directorio_local, entry_directorio);
	strcat(directorio_rival,entry_rival);
	strcat(directorio_local, entry_nombre);

	inicializartablero(tablero);

	partidaTerminada = 0;	// inicialmente partida no terminó
	partidaIniciada = 0;

	if(quieninicia==1){ //inicia el rival
		rival=fopen(directorio_rival,"r");

		actualizartablero();
		fclose(rival);
	}else{ //inicia local
		local=fopen(directorio_local,"w");
		historial=fopen("historial", "a");

		actualizartablero();
		fclose(local);
		fclose(historial);
	}

	free(directorio_rival);
	free(directorio_local);
}


/*
 * Función que verifica la existencia de un archivo
 * Parámetro:
 * 	f -> nombre y path del archivo
 * Retorno:
 * 	0 -> si el archivo no existe
 * 	1 -> si el archivo existe
 */
int existeArchivo(gchar *f) {
	FILE *a;
	if ((a = fopen(f, "r")) == NULL ) {
		return 0;
	} else {
		fclose(a);
		return 1;
	}
}

/*
 * Función de callback para el item Ayuda del menú Ayuda
 * Parámetros:
 * 	Los estandar de un callback
 * Retorno:
 *  Ninguno
 */
static void mostrar_ayuda(GtkWidget *widget, gpointer data) {
	gtk_dialog_run(GTK_DIALOG(dialogAyuda) );// mostramos la ventana de diálogo
	gtk_widget_hide(GTK_WIDGET(dialogAyuda) );	// escondemos la ventana
}

/*
 * Función de callback para el item Acerca de del menú Ayuda
 * Parámetros:
 * 	Los estandar de un callback
 * Retorno:
 *  Ninguno
 */
static void mostrar_acerca(GtkWidget *widget, gpointer data) {
	gtk_dialog_run(GTK_DIALOG(dialogAcerca) );// mostramos la ventana de diálogo
	gtk_widget_hide(GTK_WIDGET(dialogAcerca) );	// escondemos la ventana
}

/*
 * Función de callback para el item Preferencias de del menú Juego
 * Parámetros:
 * 	Los estandar de un callback
 * Retorno:
 *  Ninguno
 */
static void mostrar_configuracion(GtkWidget *widget, gpointer data) {
	gtk_dialog_run(GTK_DIALOG(dialogConfig) );// mostramos la ventana de diálogo
	gtk_widget_hide(GTK_WIDGET(dialogConfig) );	// escondemos la ventana
}

/*
 * Funcion de callback para la opción jugar de la ventana de bienvenida
 * Parametros:
 *  Estandar de un callback
 * Retorno:
 *  Ninguno
 */
static void mostrar_juego(GtkWidget *widget, gpointer data) {
	iniciajuego();
	if(quieninicia==1){
		if(colorhumano==1){ //la computadora usará fichas negras
			x='N';
			y='B';
			jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
			mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
			//actualizartablero();
			//ban_comp_inicia=1;
		}
		else{ //la computadora usará fichas blancas
			x='B';
			y='N';
			jugadaposible(tablero, j_simple, j_doble, j_triple, c1, c2, c3, x, y);
			mov_comp(tablero, j_simple, j_doble, j_triple, x, y);
			//actualizartablero();
			//ban_comp_inicia=1;
		}
	}

	if(ban_config!=1){ //si eljugador no elige preferencias se les pone unas predeterminadas
		tipodejuego=1;// es cpu vs humano

		colorhumano=1; //juega con las fichas blancas
		gtk_label_set_text(GTK_LABEL(label_estado), "El jugador utiliza las fichas blancas");

		quieninicia=2;//inicia el jugador
		gtk_label_set_text(GTK_LABEL(label_turno), "Inicia el jugador");
	}
	gtk_box_pack_start(GTK_BOX(box_tablero), cargatablero(), TRUE, FALSE, 61);
	gtk_widget_show_all((GtkWidget *)window);// mostramos la ventana de juego
	gtk_widget_hide(primeraventana);	// escondemos la ventana
}

/*
 * Si el juego termina muestra una ventana de mensaje, pone en verdadero la bandera de fin
 * de partida y guarda el resultado en una variable
 * Parámetros:
 * 	La cantidad de fichas de cada color
 * Retorno:
 *  Ninguno
 */
void mostrarMensajeFin(int ficha_B, int ficha_N) {
	GtkWidget *dialog;

	// indicamos que la partida terminó
	partidaTerminada = 1;

	//if (modoJuego == HUMANO_VS_HUMANO){
	if( ficha_B > ficha_N){
		if(colorhumano==2){
			dialog = gtk_message_dialog_new(GTK_WINDOW (window),
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
			GTK_BUTTONS_CLOSE, "¡Usted perdió! La computadora le ha ganado");
			resultado=2;
		}else{
			dialog = gtk_message_dialog_new(GTK_WINDOW (window),
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
			GTK_BUTTONS_CLOSE, "¡USTED HA GANADO LA PARTIDA!");
			resultado=1;
		}
	}
	else if( ficha_N > ficha_B){
		if(colorhumano==1){
			dialog = gtk_message_dialog_new(GTK_WINDOW (window),
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
			GTK_BUTTONS_CLOSE, "¡Usted perdió! La computadora le ha ganado");
			resultado=2;
		}else{
			dialog = gtk_message_dialog_new(GTK_WINDOW (window),
			GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
			GTK_BUTTONS_CLOSE, "¡USTED HA GANADO LA PARTIDA!");
			resultado=1;
		}
	}
	else{
		dialog = gtk_message_dialog_new(GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
		GTK_BUTTONS_CLOSE, "Es un empate!");
		resultado=2;
	}

	// Close dialog on user response
	gtk_label_set_text(GTK_LABEL(label_estado), "¡LA PARTIDA TERMINÓ!");
	gtk_dialog_run(GTK_DIALOG(dialog));

	gtk_widget_destroy(GTK_WIDGET(dialog) );	// Eliminamos ventana de diálogo
}

void finJuego(){
	partidaTerminada=1;
	estadisticas();
	mostrarMensajeFin(ficha_B, ficha_N);
}


void estadisticas(){
	FILE *estadisticas;
	GtkWidget *dialog;
	char *nombre=NULL;
	int ban_guardado; //indica si ya se actualizo la estadistica
	int filasnombre; //cantidad de jugadores
	int retss; //guarda el retorno de sscanf
	int i; //contadores
	int pg,pp,pe; //auxiliares para leer cantidad de partidas ganadas, perdidas y empatadas
	char *buf = NULL;
	int c;
	size_t tamBuf = 0;

	ban_guardado=0;

	 if(partidaIniciada==0){ //como el juego no se inicio aun, se cargan las estadisticas del archivo
		 if((estadisticas=fopen("estadistica", "r"))==NULL){
			 printf("Hubo un error al intentar recuperar las estadisticas");
			 return;
		 }else{
			filasnombre=cuentaLineas(estadisticas)-1;
			if  ((nombres = (char **)creaMatriz2d(filasnombre, MAX_LON_NOM, sizeof(char))) == NULL){
				printf ("No hay memoria suficiente\n");
			}
			if  ((partidas = (int **)creaMatriz2d(filasnombre, 3, sizeof(int))) == NULL){
				printf ("No hay memoria suficiente\n");
			}
			//while((c=getc(estadisticas))!='\n'); //se salta la primera linea que contiene solo titulos
			for(i=0; i<filasnombre;i++){
				getline(&buf, &tamBuf, estadisticas);
				 retss=sscanf(buf, "%s\t%d\t%d\t%d", nombre, &pg, &pp, &pe);
				 if(retss==4){
					 nombres[i]=nombre;
					 partidas[i][0]=pg; //se guardan las partidas ganadas
					 partidas[i][1]=pp; //se guardas las partidas perdidas
					 partidas[i][2]=pe; //se guardan las partidas empatadas
				 }
			}
		 }
	 }
	 if(partidaTerminada==1){ //el juego ya inicio y termino, por lo que se debe actualizar la estadistica
		 while(ban_nombre!=1){ //el jugador no introdujo su nombre
		 dialog = gtk_message_dialog_new(GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO,
		GTK_BUTTONS_CLOSE, "Debe introducir su nombre para las estadisticas");
		 gtk_dialog_run(GTK_DIALOG(dialog));
		 gtk_widget_destroy(GTK_WIDGET(dialog) );	// Eliminamos ventana de diálogo
		 //mostrar_configuracion(); NO FUNCIONA
		 }
		 for(i=0; i<filasnombre; i++){
			 if(nombres[i]==entry_nombre){
				 partidas[i][resultado-1]++;
				 ban_guardado=1;
			 }
		 }
		 if(ban_guardado==0){ //no se encontro el nombre, por lo que no se pudo actualizar la estadistica
			 nombres=realloc(nombres, (filasnombre+1)*sizeof(char));
			 nombres[filasnombre] = malloc (MAX_LON_NOM * sizeof(char));
			 nombres[filasnombre]=entrynombre;
			 partidas=realloc(partidas, (filasnombre+1)*sizeof(int));
			 partidas[filasnombre]=malloc(3 * sizeof(int));
			 partidas[i][resultado-1]++;
			 ban_guardado=1;
		 }
	 }

	 fclose(estadisticas);
}


/*
 * funcion de callback para el boton aceptar de la ventana de preferencias de juego
 * Parametros:
 *  Estandar de un callback
 * Retorno:
 *  Ninguno
 */
static void guardar_settings(GtkButton *button, gpointer data){//conectar al boton de aceptar que esta en la ventana de dialogo

	srand(time(NULL));

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cpu_cpu))){
		tipodejuego=1;
	}else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cpu_humano))){
		tipodejuego=2;
	}


	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(blanco))){
		colorhumano=1;
		gtk_label_set_text(GTK_LABEL(label_estado), "El jugador utiliza las fichas blancas");
	}else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(negro))){
		colorhumano=2;
		gtk_label_set_text(GTK_LABEL(label_estado), "El jugador utiliza las fichas negras");
	}else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aleatoriocolor))){
		int t;
		t=rand()%2;
		if(t==0){
			colorhumano=1;
			gtk_label_set_text(GTK_LABEL(label_estado), "El jugador utiliza las fichas blancas");
		}else{
			colorhumano=2;
			gtk_label_set_text(GTK_LABEL(label_estado), "El jugador utiliza las fichas negras");
		}
	}


	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(computadora))){
		quieninicia=1;
		gtk_label_set_text(GTK_LABEL(label_turno), "Inicio la computadora");
	}else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(humano))){
		quieninicia=2;
		gtk_label_set_text(GTK_LABEL(label_turno), "Inicia el jugador");
	}else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(aleatorioinicia))){
		int t;
		t=rand()%2;
		if(t==0){
			quieninicia=1;
			gtk_label_set_text(GTK_LABEL(label_turno), "Inicio la computadora");
		}
		else{
			quieninicia=2;
			gtk_label_set_text(GTK_LABEL(label_turno), "Inicia el jugador");

		}
	}

	maxjugadas = gtk_spin_button_get_value_as_int ((GtkSpinButton*)spin_cant_jugadas);
	entry_nombre = gtk_entry_get_text (GTK_ENTRY (entrynombre));
	entry_rival = gtk_entry_get_text (GTK_ENTRY (entryrival));
	entry_directorio = gtk_entry_get_text (GTK_ENTRY (entrydirectorio));

	if(entry_nombre[0]!='\0'){
		ban_nombre=1;
	}
	if(entry_rival[0]!='\0'){
		ban_rival=1;
	}

	gtk_widget_hide(dialogConfig);

	if(tipodejuego==1){
		juego_red();
	}
}

/*
 * Función asociada con el menú juego->salir
 * Parámetros:
 * 	Los estandar de un callback
 * Retorno:
 *  Ninguno
 */
static void confirmaSalir(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog;

	if(partidaIniciada && partidaTerminada) {
			gtk_main_quit();
	}else if (partidaIniciada){
		dialog = gtk_message_dialog_new(GTK_WINDOW(window),
				GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,
				GTK_BUTTONS_OK_CANCEL, "El juego no ha terminado\n¿Esta seguro de que desea salir?");

		if (gtk_dialog_run(GTK_DIALOG(dialog) ) == GTK_RESPONSE_OK){// mostramos la ventana de diálogo
			gtk_main_quit();
		}

		gtk_widget_destroy(GTK_WIDGET(dialog) );	// destruimos la ventana

	} else {
		gtk_main_quit();
	}
}

/*
 * Función asociada con el evento de apretar el botón X de la ventana
 */
static gboolean confirmaSalirX(GtkWidget *widget, GdkEvent  *event, gpointer data) {
	GtkWidget *dialog;
	if(partidaIniciada && partidaTerminada) {
		return FALSE;
	}else if (partidaIniciada){
		dialog = gtk_message_dialog_new(GTK_WINDOW(window),
				GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,
				GTK_BUTTONS_OK_CANCEL, "El juego no ha terminado\n¿Esta seguro de que desea salir?");

		if (gtk_dialog_run(GTK_DIALOG(dialog) ) == GTK_RESPONSE_OK){// mostramos la ventana de diálogo
			gtk_widget_destroy(GTK_WIDGET(dialog) );	// escondemos la ventana
			return FALSE;
		}

		gtk_widget_destroy(GTK_WIDGET(dialog) );	// escondemos la ventana
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Reinicializa el juego. Es un callback del ítem Nuevo del menú archivo
 * Parámetros:
 * 	Los estandar de un callback
 * Retorno:
 *  Ninguno
 */
void reiniciarPartida(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog;

	if (partidaIniciada && !partidaTerminada){
		// si no se salvó o la partida no ha sido iniciada
		dialog = gtk_message_dialog_new(GTK_WINDOW(window),
				GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,
				GTK_BUTTONS_OK_CANCEL, "El juego no ha terminado\n¿Seguro que desea iniciar uno nuevo?");

		if (gtk_dialog_run(GTK_DIALOG(dialog) ) == GTK_RESPONSE_OK){// mostramos la ventana de diálogo
			iniciajuego();
			actualizartablero();
			cj=0;
		}
		gtk_widget_destroy(GTK_WIDGET(dialog) );	// destruimos la ventana
	} else {
		iniciajuego();	// inicializa el juego
		actualizartablero();
		cj=0;
	}
}


int main (int argc, char *argv[]){
	GObject *menu_mostrar_ayuda;	// identificador del objeto menu item ayuda
	GObject *menu_mostrar_acerca;	// identificador del objeto menu item acerca
	GObject *menu_mostrar_configuracion; // identificador del objeto menu item configuracion
	GObject *menu_archivo_salir;	// identificador del objeto menu item salir
	//Para el GtkBuilder
	guint ret;
	GtkBuilder *builder;
	GError *error = NULL;

	GtkAdjustment *adjustment;

	gtk_init (&argc, &argv);

	builder = gtk_builder_new();

	//Se carga el builder
	ret = gtk_builder_add_from_file(builder, "tablero.glade", &error);
	if (ret == 0) {
		g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
		return 1;
	}

	g_free(error);

	//Ventana principal
	window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana"));
	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);	// cuando la ventana es destruida se sale del programa
	g_signal_connect (window, "delete_event", G_CALLBACK (confirmaSalirX), NULL);	// el evento de cerrar la ventana principal es capturado
	primeraventana=GTK_WIDGET(gtk_builder_get_object(builder, "primera_ventana"));
	g_signal_connect(primeraventana, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	//Ventanas de dialogo dentro del juego
	dialogAyuda = gtk_builder_get_object(builder, "ayuda_abalone");// leemos la ventana de diálogo de ayuda para el juego
	dialogAcerca = gtk_builder_get_object(builder, "acerca_abalone");// leemos la ventana de diálogo de ayuda para el juego
	dialogConfig = GTK_WIDGET(gtk_builder_get_object(builder, "config_abalone"));// leemos la ventana de diálogo de configuracion del juego

	//Box donde estara el Tablero
	box_tablero = GTK_WIDGET(gtk_builder_get_object(builder, "box_tablero"));

	//Entrada de texto para introducir los nombres
	entrynombre = GTK_WIDGET(gtk_builder_get_object(builder, "entrynombre"));
	entryrival = GTK_WIDGET(gtk_builder_get_object(builder, "entryrival"));
	entrydirectorio = GTK_WIDGET(gtk_builder_get_object(builder, "entrydirectorio"));

	//Labels
	label_turno = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno"));
	label_estado = GTK_WIDGET(gtk_builder_get_object(builder, "label_estado"));
	label_advertencia = GTK_WIDGET(gtk_builder_get_object(builder, "label_advertencia"));
	label_fichas = GTK_WIDGET(gtk_builder_get_object(builder, "label_fichas"));
	label_jugadores = GTK_WIDGET(gtk_builder_get_object(builder, "label_jugadores"));

	//Radiobuttons
	negro = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_negro"));
    blanco = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_blanco"));
	aleatoriocolor = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_aleatorio_color")); // revisar para separar o convertir en checkbutton
	humano = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_humano"));
	computadora = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_computadora"));
	aleatorioinicia = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_aleatorio_inicia"));
	cpu_cpu = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_cpu_cpu"));
	cpu_humano = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton_humano_cpu"));

	//spinbutton
	spin_cant_jugadas = GTK_WIDGET(gtk_builder_get_object(builder, "spinbutton_cant_jugadas"));
	adjustment = gtk_adjustment_new (0, 0, 100, 1, 0, 0);
	gtk_spin_button_configure ((GtkSpinButton  *)spin_cant_jugadas,adjustment, 1, 0);
	gtk_widget_set_hexpand (spin_cant_jugadas, TRUE);

	//boton de aceptar configuraciones
	aceptar= GTK_WIDGET(gtk_builder_get_object(builder, "button_aceptar"));
	g_signal_connect (aceptar, "clicked", G_CALLBACK (guardar_settings), aceptar);

	//botones de la primera ventana
	b_configuracion = GTK_WIDGET(gtk_builder_get_object(builder, "button_config"));
	g_signal_connect (b_configuracion, "clicked", G_CALLBACK (mostrar_configuracion), b_configuracion);

	b_jugar = GTK_WIDGET(gtk_builder_get_object(builder, "button_jugar"));
	g_signal_connect (b_jugar, "clicked", G_CALLBACK (mostrar_juego), NULL);

	//b_estadistica = GTK_WIDGET(gtk_builder_get_object(builder, "button_estadisticas"));
	//g_signal_connect (b_estadistica, "clicked", G_CALLBACK (guardar_settings), b_estadistica);

	b_instrucciones = GTK_WIDGET(gtk_builder_get_object(builder, "button_instrucciones"));
	g_signal_connect (b_instrucciones, "clicked", G_CALLBACK (mostrar_ayuda), b_instrucciones);

	gtk_entry_set_max_length (GTK_ENTRY (entrynombre), MAX_LON_NOM);
	gtk_entry_set_max_length (GTK_ENTRY (entryrival), MAX_LON_NOM);

	menu_archivo_salir = gtk_builder_get_object(builder, "menu_archivo_salir");
	g_signal_connect(menu_archivo_salir, "activate", G_CALLBACK (confirmaSalir), NULL);

	menu_archivo_nuevo = gtk_builder_get_object(builder, "menu_archivo_nuevo");
	g_signal_connect(menu_archivo_nuevo, "activate", G_CALLBACK (reiniciarPartida), NULL);

	menu_mostrar_ayuda = gtk_builder_get_object(builder, "menu_ayuda_ayuda");
	g_signal_connect(menu_mostrar_ayuda, "activate", G_CALLBACK (mostrar_ayuda), NULL);

	menu_mostrar_acerca = gtk_builder_get_object(builder, "menu_ayuda_acerca");
	g_signal_connect(menu_mostrar_acerca, "activate", G_CALLBACK (mostrar_acerca), NULL);

	menu_mostrar_configuracion = gtk_builder_get_object(builder, "menu_juego_configuracion");
	g_signal_connect(menu_mostrar_configuracion, "activate", G_CALLBACK (mostrar_configuracion), NULL);

	estadisticas();

	gtk_widget_show_all((GtkWidget *) primeraventana);

	gtk_main ();

	return 0;
}
