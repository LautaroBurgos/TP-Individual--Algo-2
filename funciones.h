
#ifndef FUNCIONES_H_
#define FUNCIONES_H_
#include <iostream>


const char VACIO= '-';
const char INACTIVO= 'X';
const char ARRIBA= 'w';
const char ABAJO= 's';
const char IZQUIERDA= 'a';
const char DERECHA='d';
const char DIAGONAL_ARRIBA_DERECHA='e';
const char DIAGONAL_ARRIBA_IZQUIERDA='q';
const char DIAGONAL_ABAJO_DERECHA='c';
const char DIAGONAL_ABAJO_IZQUIERDA='z';
const char SOLDADO_JUGADOR_1='1';
const char SOLDADO_JUGADOR_2='2';
const int NO_ENCONTRADO=-1;
const int MAX_FILAS=10;
const int MAX_COLUMNAS=10;
const int MAX_SOLDADOS=3;
const int VALOR_INICIAL=0;

typedef struct Soldado{
	char numeroJugador;
	int fila;
	int columna;
};
typedef struct Casillero{
	char estado;
	bool estaActivo;
	int fila;
	int columna;
};

/*
 *	Procedimiento que se encarga de poner todos los casilleros en estado inicial VACIO
 *	PRE:Recibe una matriz de tipo Casillero.
 *	POST: Queda el tablero en estado listo para jugar.
 *
 */
void crearTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS]);
/*
 * Procedimiento que se encarga de solicitar coordenada fila y columna al usuario por
 * teclado para asignarsela a X soldado al comienzo del juego.En caso de no ser valores validos,
 * (fuera del tablero, o donde ya hay un soldado de ese jugador), solicita una nueva coordenada.
 * PRE:Recibe las varibles vacias de fila y columna y el numero de soldado.
 * POST:Las variables fila y columna quedan con un valor valido.
 *
 * */
void solicitarCoordenada(int &fila,int &columna,int numeroSoldado);
/*
 * Procedimiento que se encarga de validar la coordenada ingresada por el usuario.
 *
 * */
bool validarCoordenada(int fila,int columna,Soldado soldados[MAX_SOLDADOS],
		int soldadoActual);
/*
*	 Procedimiento que se encarga de introducir los 3 soldados de un jugador determinado
*	  al tablero, esto mediante la solicitud de datos por teclado.
*	  PRE:Recibe un vector vacio de soldados, y su tope o cant. de elementos,inicialmente en
*	  cero, y el caracter que representa el numero de jugador.
*	  POST:El vector queda con 3 soldados con posiciones que son validas del tablero.
*
*
*/
void introducirSoldados(Soldado soldados[MAX_SOLDADOS],int &tope,char numeroJugador);
/*
 * 	Procedimiento que enumera las columnas del tablero para que facilitar la lectura del mismo.
 *
 *
 * */
void imprimirNumerosColumnas();
/*
 *	 Procedimiento que se encarga de mostrar el tablero por pantalla
 */
void imprimirTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS]);
/*
 * 	Procedimiento que crea un archivo txt con el estado actual del tablero.
 *
 * */
void guardarArchivoTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS]);
/*
 * 	Procedimiento que se encarga de actualizar el tablero con los datos actuales de los soldados.
 *
 * */
void actualizarTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS],
		Soldado soldadosJugador1[MAX_SOLDADOS],int tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int tope2);
/*
 *
 * 	Procedimiento que se encarga de solicitar coordenadas al usuario para que
 * 	posteriormente se realize el disparo.
 * 	PRE:Recibe variables vacias de fila y columna donde se va a disparar, junto con el caracter
 * 	que representa el numero de jugador.
 * 	POST:Las variables quedan con una coordenada para disparar.
 *
 * */
void solicitarDisparo(int &filaDisparo,int &columnaDisparo,char jugador);
/*
 * 	Funcion que mediante un casillero pasasdo por parametro, busca en un vector de soldados ,
 * 	alguno que se encuentre en ese casillero, si este existe, devuelve su posicion en el
 * 	vector.Caso contrario devuelve -1.
 * 	PRE:Recibe un vector de soldados, su tope , y el casillero donde se quiere buscar.
 * 	POST: Se devuelve -1 si no encontro o , la posicion del soldado en el vector pasado por
 * 	parametro.
 *
 * */
int buscarSoldado(Soldado soldados[MAX_SOLDADOS],int tope,Casillero casillero);
/*
 * 	Procedimiento que se encarga de eliminar un soldado del vector de soldados y reducir el tope
 * 	en 1.
 * 	PRE:Recibe el vector de soldados, su tope y la posicion en el vector, del soldado que se quiere
 * 	eliminar.
 * 	POST:El soldado queda eliminado del vector y su tope se reduce en 1.
 *
 *
 * */
void eliminarSoldado(Soldado soldados[MAX_SOLDADOS],int &tope,int posicion);
/*
 * 	Procedimiento que desactiva el casillero pasado por parametro, cambiando su campo estado
 * 	y su campo estaActivo.
 *
 * */
void desactivarCasillero(Casillero &casillero);
/*
 * 	Procedimiento que se encarga de realizar un disparo de un jugador,en caso de darle a un
 * 	soldado enemigo, este es eliminado y el casillero en el que estaba queda desactivado. O
 * 	en caso de no darle a nada, solo se desactiva el casillero.
 * 	PRE:Recibe ambos vectores de soldados con sus respectivos topes,el casillero a donde se
 * 	dispara,y el caracter que representa al jugador .
 * 	POST:El casillero queda inutilizado, y en caso de haber un soldado queda eliminado.
 *
 * */
void disparar(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
	Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,Casillero &casillero,char jugador);
/*
 * 	Procedimiento que se encarga de mostrarle un menu  de movimientos al usuario para que este
 * 	elija y posteriormente lo devuelve.
 *
 * */
char solicitarMovimiento();
/*
 * 	Procedimiento que se encarga de mover un soldado, un casillero , en la direccion que escoja
 * 	el usuario. Los movimientos posibles son:
 * 	-ARRIBA, ABAJO, IZQUIERDA,DERECHA.
 * 	DIAGONALES: DIAGONAL ARRIBA DERECHA, DIAGONAL ARRIBA IZQUIERDA, DIAGONAL ABAJO IZQUIERDA,
 * 	DIAGONAL ABAJO DERECHA
 * */
void moverSoldado(Soldado &soldado,Casillero tablero[MAX_FILAS][MAX_COLUMNAS]);
/*
 * 	Funcion que muestra por pantalla los soldados que tiene un jugador en el tablero para
 * 	que posteriormente elija el que va a moverse.
 * */
int seleccionarSoldadoMover(Soldado soldadosJugador[MAX_SOLDADOS],int tope,char jugador);
/*
 *	Procedimiento que ejecuta un turno del jugador que se le pase por parametro, un turno consiste
 *	en un disparo y en un movimiento de uno de los 3 soldados.
 * */
void turnoJugador(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
	Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,Casillero tablero[MAX_FILAS][MAX_COLUMNAS],
	char jugador);
/*
 * 	Procedimiento que deja el juego en estado inicial listo para ser jugado, con los datos de los
 * 	3 soldados de cada jugador y el tablero listo para jugar.
 *
 * */
void inicializarJuego(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,
		Casillero tablero[MAX_FILAS][MAX_COLUMNAS]);
/*
 * 	Funcion que compara los 2 vectores de soldados y devuelve la posicion,del vector del jugador
 * 	1 donde se encuentra el soldado que comparte posicion con un soldado del jugador 2. O devuelve
 * 	-1 en caso de no encontrar coincidencias.
 *
 * */
int soldadosIguales(Soldado soldadosJugador1[MAX_SOLDADOS],int tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int tope2);
/*
 * 	Funcion que elimina 2 soldados que esten en la misma posicion y desactiva el casillero en el
 * 	que se encontraban.
 *
 * */
void eliminarAmbosSoldados(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,int posicion1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,Casillero &casillero);
/*
 * 	Procedimiento que ejecuta ambos turnos correctamente, y revisa luego de cada turno si hay
 * 	2 soldados(1 de cada jugador) en el mismo casillero, en caso de que esto pase, elimina ambos
 * 	soldados, segun las reglas del juego y desactiva el casillero.
 *
 * */
void ejecutarTurnos(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,
		Casillero tablero[MAX_FILAS][MAX_COLUMNAS]);



#endif /* FUNCIONES_H_ */
