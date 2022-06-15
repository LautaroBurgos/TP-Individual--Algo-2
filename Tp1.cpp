#include "funciones.h"
using namespace std;

int main(){
	Casillero tablero[MAX_FILAS][MAX_COLUMNAS];
	Soldado soldadosJugador1[MAX_SOLDADOS];
	int tope1=0;
	Soldado soldadosJugador2[MAX_SOLDADOS];
	int tope2=0;
	bool juegoTerminado=false;

	inicializarJuego(soldadosJugador1,tope1,soldadosJugador2,tope2,tablero);
	actualizarTablero(tablero,soldadosJugador1,tope1,soldadosJugador2,tope2);

	while(!juegoTerminado){
		ejecutarTurnos(soldadosJugador1,tope1,soldadosJugador2,tope2,tablero);
		actualizarTablero(tablero,soldadosJugador1,tope1,soldadosJugador2,tope2);
		if(tope1==0 || tope2==0){
			juegoTerminado=true;
		}
	}
		cout<<"JUEGO TERMINADO ,";
		if(tope1==0&&tope2!=0){
			cout<<" EL JUGADOR 2 ES EL GANADOR!"<<endl;
		}
		else if(tope1!=0 &&tope2==0){
			cout<<" EL JUGADOR 1 ES ES EL GANADOR!"<<endl;
		}
		else{
			cout<<"SE HA PRODUCIDO UN EMPATE!"<<endl;
		}
	return 0;
}
