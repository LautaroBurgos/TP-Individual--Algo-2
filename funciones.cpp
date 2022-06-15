#include "funciones.h"
#include <fstream>


void crearTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS]){
	for(int filaActual=0;filaActual<MAX_FILAS;filaActual++){
		for(int columnaActual=0;columnaActual<MAX_COLUMNAS;columnaActual++){
			tablero[filaActual][columnaActual].estado=VACIO;
			tablero[filaActual][columnaActual].fila=filaActual;
			tablero[filaActual][columnaActual].columna=columnaActual;
			tablero[filaActual][columnaActual].estaActivo=true;
		}
	}
}

void solicitarCoordenada(int &fila,int &columna,int numeroSoldado){
	std::cout<<"Introduzca la  coordenada fila del soldado Nº"<<numeroSoldado+1<<std::endl;
	std::cin>>fila;
	std::cout<<"Introduzca la coordenada columna del soldado Nº"<<numeroSoldado+1<<std::endl;
	std::cin>>columna;
}

bool validarCoordenada(int fila,int columna,Soldado soldados[MAX_SOLDADOS],
		int soldadoActual){
	bool es_valida=true;
	if(fila>=MAX_FILAS || columna>=MAX_COLUMNAS){
		es_valida=false;
	}
	else{
		for(int i=0;i<soldadoActual;i++){
			if(fila==soldados[i].fila && columna==soldados[i].columna){
				es_valida=false;
			}
		}
	}
	return es_valida;
}

void introducirSoldados(Soldado soldados[MAX_SOLDADOS],int &tope,char numeroJugador){

	int fila=VALOR_INICIAL;
	int columna=VALOR_INICIAL;

	std::cout<<"POSICIONAMIENTO DE LOS 3 SOLDADOS-Jugador Nº"<<numeroJugador<<std::endl;
	for(int numeroSoldado=0;numeroSoldado<MAX_SOLDADOS;numeroSoldado++){
		solicitarCoordenada(fila,columna,numeroSoldado);

		while(validarCoordenada(fila,columna,soldados,numeroSoldado)==false){
			std::cout<<"Coordenada invalida"<<std::endl;
			solicitarCoordenada(fila,columna,numeroSoldado);
		}
		soldados[numeroSoldado].fila=fila;
		soldados[numeroSoldado].columna=columna;
		soldados[numeroSoldado].numeroJugador=numeroJugador;
		tope++;
	}
}

void imprimirNumerosColumnas(){
	std::cout<<"/";
	for(int i=0;i<MAX_FILAS;i++){
		std::cout<<i;
	}
	std::cout<<std::endl;
}

void imprimirTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS]){
	imprimirNumerosColumnas();

	for(int filaActual=0;filaActual<MAX_FILAS;filaActual++){
		std::cout<<filaActual; //Linea que en cada fila del tablero imprime su numero para identificarla
		for(int columnaActual=0;columnaActual<MAX_COLUMNAS;columnaActual++){

			std::cout<<tablero[filaActual][columnaActual].estado;
		}
		std::cout<<std::endl;
	}

}

void guardarArchivoTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS]){
	std::ofstream archivo("tablero.txt");

	archivo<<"/";
		for(int i=0;i<MAX_FILAS;i++){
			archivo<<i;
		}
		archivo<<std::endl;

	for(int filaActual=0;filaActual<MAX_FILAS;filaActual++){
		archivo<<filaActual;
		for(int columnaActual=0;columnaActual<MAX_COLUMNAS;columnaActual++){

			archivo<<tablero[filaActual][columnaActual].estado;
		}
		archivo<<std::endl;
	}
	archivo.close();
}

void actualizarTablero(Casillero tablero[MAX_FILAS][MAX_COLUMNAS],
		Soldado soldadosJugador1[MAX_SOLDADOS],int tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int tope2){

		for(int i=0;i<tope1;i++){
			tablero[soldadosJugador1[i].fila][soldadosJugador1[i].columna].estado=SOLDADO_JUGADOR_1;
		}
		for(int j=0;j<tope2;j++){
			tablero[soldadosJugador2[j].fila][soldadosJugador2[j].columna].estado=SOLDADO_JUGADOR_2;
		}
		imprimirTablero(tablero);
		guardarArchivoTablero(tablero);

}

void solicitarDisparo(int &filaDisparo,int &columnaDisparo,char jugador){
	std::cout<<"Jugador Nº"<<jugador<<"  Elija coordenada a donde disparar\nFila:"<<std::endl;
	std::cin>>filaDisparo;
	std::cout<<"Columna:"<<std::endl;
	std::cin>>columnaDisparo;
}

int buscarSoldado(Soldado soldados[MAX_SOLDADOS],int tope,Casillero casillero){
	int posicion=NO_ENCONTRADO;
	for(int i=0;i<tope;i++){
		if((soldados[i].fila==casillero.fila) && (soldados[i].columna==casillero.columna)){
			posicion=i;
		}
	}
	return posicion;

}

void eliminarSoldado(Soldado soldados[MAX_SOLDADOS],int &tope,int posicion){
	for(int i=posicion;i<tope-1;i++){
		soldados[i]=soldados[i+1];
	}
	tope--;
}

void desactivarCasillero(Casillero &casillero){
	casillero.estaActivo=false;
	casillero.estado=INACTIVO;
}

void disparar(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
	Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,Casillero &casillero,char jugador){
	int posicion;
	if(jugador==SOLDADO_JUGADOR_1){
			posicion=(buscarSoldado(soldadosJugador2,tope2,casillero));

			if (posicion!=NO_ENCONTRADO){
				eliminarSoldado(soldadosJugador2,tope2,posicion);
			}
		}
		else{
			posicion=(buscarSoldado(soldadosJugador1,tope1,casillero));

			if (posicion!=NO_ENCONTRADO){
				eliminarSoldado(soldadosJugador1,tope1,posicion);
			}
		}
		desactivarCasillero(casillero);
}

char solicitarMovimiento(){
	char movimiento;
	std::cout<<"Ejecute un movimiento:"<<std::endl;
	std::cout<<"w= ARRIBA\ns=ABAJO\na=IZQUIERDA\nd=DERECHA"<<std::endl;
	std::cout<<"q=DIAGONAL ARRIBA IZQUIERDA\ne=DIAGONAL ARRIBA DERECHA"<<std::endl;
	std::cout<<"z=DIAGONAL ABAJO IZQUIERDA\nc=DIAGONAL ABAJO DERECHA"<<std::endl;
	std::cin>>movimiento;
	return movimiento;
}

void moverSoldado(Soldado &soldado,Casillero tablero[MAX_FILAS][MAX_COLUMNAS]){
	char movimiento=solicitarMovimiento();
	switch(movimiento){
				case ARRIBA:
					if((soldado.fila-1>0)&&(tablero[soldado.fila-1][soldado.columna].estaActivo)){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.fila-=1;
					}
					break;
				case ABAJO:
					if((soldado.fila+1<MAX_FILAS-1)&&
							(tablero[soldado.fila+1][soldado.columna].estaActivo)){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.fila+=1;
					}
					break;
				case IZQUIERDA:
					if((soldado.columna-1>0)&&
							(tablero[soldado.fila][soldado.columna-1].estaActivo)){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.columna-=1;
					}
					break;
				case DERECHA:
					if((soldado.columna+1<MAX_COLUMNAS-1)&&
							(tablero[soldado.fila][soldado.columna+1].estaActivo)){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.columna+=1;
					}
					break;
				case DIAGONAL_ARRIBA_DERECHA:
					if((soldado.fila-1>0)&&(soldado.columna+1<MAX_COLUMNAS-1)&&
							(tablero[soldado.fila-1][soldado.columna+1].estaActivo)){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.fila-=1;
						soldado.columna+=1;
					}
					break;
				case DIAGONAL_ARRIBA_IZQUIERDA:
					if((soldado.fila-1>0)&&(soldado.columna-1>0)&&
							(tablero[soldado.fila-1][soldado.columna+1].estaActivo)){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.fila-=1;
						soldado.columna+=1;
					}
					break;
				case DIAGONAL_ABAJO_DERECHA:
					if((soldado.fila+1<MAX_FILAS-1)&&(soldado.columna+1<MAX_COLUMNAS-1)&&
							tablero[soldado.fila+1][soldado.columna+1].estaActivo){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.fila+=1;
						soldado.columna+=1;
					}
					break;
				case DIAGONAL_ABAJO_IZQUIERDA:
					if(((soldado.fila)+1<MAX_FILAS-1)&&(soldado.columna-1>0)&&
							tablero[soldado.fila+1][soldado.columna-1].estaActivo){
						tablero[soldado.fila][soldado.columna].estado=VACIO;
						soldado.fila+=1;
						soldado.columna-=1;
					}
					break;
	}
}

int seleccionarSoldadoMover(Soldado soldadosJugador[MAX_SOLDADOS],int tope,char jugador){
	int posicion;
	std::cout<<"Jugador Nº"<<jugador<<"   Seleccione soldado a mover:"<<std::endl;
	for(int i=0;i<tope;i++){
		std::cout<<"Soldado:"<<i<<"  Fila:"<<soldadosJugador[i].fila;
		std::cout<<"   Columna:"<<soldadosJugador[i].columna<<std::endl;
	}
	std::cin>>posicion;
	return posicion;
}

void turnoJugador(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
	Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,Casillero tablero[MAX_FILAS][MAX_COLUMNAS],
	char jugador){
	int filaDisparo,columnaDisparo;
	solicitarDisparo(filaDisparo,columnaDisparo,jugador);

	disparar(soldadosJugador1,tope1,soldadosJugador2,tope2,tablero[filaDisparo][columnaDisparo],
			jugador);

	if(jugador==SOLDADO_JUGADOR_1){
		moverSoldado(soldadosJugador1[seleccionarSoldadoMover(soldadosJugador1,tope1,jugador)],
				tablero);
	}
	else{
		moverSoldado(soldadosJugador2[seleccionarSoldadoMover(soldadosJugador2,tope2,jugador)],
				tablero);

	}

}

void inicializarJuego(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,
		Casillero tablero[MAX_FILAS][MAX_COLUMNAS]){
	introducirSoldados(soldadosJugador1,tope1,SOLDADO_JUGADOR_1);
	introducirSoldados(soldadosJugador2,tope2,SOLDADO_JUGADOR_2);
	crearTablero(tablero);
}

int soldadosIguales(Soldado soldadosJugador1[MAX_SOLDADOS],int tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int tope2){
	int posicion_repetida=NO_ENCONTRADO;
	for(int i=0;i<tope1;i++){
		for(int j=0;j<tope2;j++){
			if(((soldadosJugador1[i].fila)==(soldadosJugador2[j].fila))&&
					((soldadosJugador2[i].columna)==(soldadosJugador2[j].columna))){
				posicion_repetida=i;
			}
		}
	}
	return posicion_repetida;
}

void eliminarAmbosSoldados(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,int posicion1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,Casillero &casillero){
	int posicion2=buscarSoldado(soldadosJugador2,tope2,casillero);

	eliminarSoldado(soldadosJugador1,tope1,posicion1);
	eliminarSoldado(soldadosJugador2,tope2,posicion2);
	desactivarCasillero(casillero);
}

void ejecutarTurnos(Soldado soldadosJugador1[MAX_SOLDADOS],int &tope1,
		Soldado soldadosJugador2[MAX_SOLDADOS],int &tope2,
		Casillero tablero[MAX_FILAS][MAX_COLUMNAS]){
	int posicion1;

	turnoJugador(soldadosJugador1,tope1,soldadosJugador2,tope2,tablero,
			SOLDADO_JUGADOR_1);
	posicion1=soldadosIguales(soldadosJugador1,tope1,soldadosJugador2,tope2);

	if(posicion1!=NO_ENCONTRADO){
		eliminarAmbosSoldados(soldadosJugador1,tope1,posicion1,soldadosJugador2,tope2,
				tablero[soldadosJugador1[posicion1].fila][soldadosJugador1[posicion1].columna]);
	}

	actualizarTablero(tablero,soldadosJugador1,tope1,soldadosJugador2,tope2);

	turnoJugador(soldadosJugador1,tope1,soldadosJugador2,tope2,tablero,
			SOLDADO_JUGADOR_2);
	posicion1=soldadosIguales(soldadosJugador1,tope1,soldadosJugador2,tope2);

	if(posicion1!=NO_ENCONTRADO){
		eliminarAmbosSoldados(soldadosJugador1,tope1,posicion1,soldadosJugador2,tope2,
				tablero[soldadosJugador1[posicion1].fila][soldadosJugador1[posicion1].columna]);
	}
}
