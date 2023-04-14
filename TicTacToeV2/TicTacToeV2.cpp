// Enunciado:
// Realizar un programa que juegue tic tac toe con el jugador.
// 
// Participantes:
// 1- John Luis Del Rosario Sánchez - ID 1106940
// 2- Ashly Marisell Paula Ynoa - ID 1108023
// 3- Elián Matos Díaz - ID 1106901
// 4- Juan Daniel Ubiera Méndez - ID 1107248
// 5- Kelvin Arístides García Espinal - ID 1107646
// 
// Fecha de entrega: 13/4/2023
// 
// Profesor: Casimiro Cordero

#include <iostream>
#include <string>
using namespace std;

char tablero[9], humano, ia;
int contJugadas = 0, tableroSize = sizeof(tablero) / sizeof(tablero[0]);

//evalua si se ha ganado el juego
bool Victory(char playedChar) {

	//caso filas y columnas
	if ((tablero[0] == playedChar && tablero[1] == playedChar && tablero[2] == playedChar) || //filas
		(tablero[3] == playedChar && tablero[4] == playedChar && tablero[5] == playedChar) ||
		(tablero[6] == playedChar && tablero[7] == playedChar && tablero[8] == playedChar) ||
		(tablero[0] == playedChar && tablero[3] == playedChar && tablero[6] == playedChar) || //columnas
		(tablero[1] == playedChar && tablero[4] == playedChar && tablero[7] == playedChar) ||
		(tablero[2] == playedChar && tablero[5] == playedChar && tablero[8] == playedChar)
		)
		return true;


	//caso para las diagonales
	if ((tablero[0] == playedChar && tablero[4] == playedChar && tablero[8] == playedChar) || //diagonal topizq bottder
		(tablero[2] == playedChar && tablero[4] == playedChar && tablero[6] == playedChar)	 //diagonal topder bottizq
		) {
		return true;
	}

	return false;
}

//evalua el puntaje que recibe el tablero actual
int evaluarTablero(int depth) {
	//si en este tablero gana la computadora, el puntaje es 10
	if (Victory(ia)) return 10-depth;
	//si gana el humano, es decir, el oponente, -10
	else if (Victory(humano)) return -10+depth;
	//si no gana ninguno, pues 0
	else return 0;
}

//evalua si el tablero esta lleno
bool tableroFinal() {
	for (int i = 0; i < tableroSize;i++) {
		if (tablero[i] == ' ') return false;
	}
	return true;
}

int Minimax(char tablero[9], int depth, bool isMax, int alfa, int beta) {
	int puntaje = evaluarTablero(depth);

	//solo se hace un return de puntaje cuando se gana o se pierde
	if (puntaje != 0)
		return puntaje;
	//si puntaje  no es ninguno de los valores anteriores, se devuelve 0 si es un empate
	if (tableroFinal())
		return 0;

	int mejorJugada = 0;

	//si se estan maximizando las oportunidades de ganar
	if (isMax) {
		//se inicializa con la peor jugada para la maquina
		mejorJugada = -1000;
		
		//se evalua cada jugada posible 
		for (int i = 0; i < tableroSize; i++) {
			if (tablero[i] == ' ') {
				//se hace la jugada
				tablero[i] = ia;
				//se obtiene la mejor jugada llamando recursivamente a la funcion minimax pero en este caso, minimizando
				mejorJugada = max(mejorJugada, Minimax(tablero, depth + 1, !isMax, alfa, beta));

				//se elimina la jugada del tablero
				tablero[i] = ' ';
				alfa = max(alfa, mejorJugada);

				//se dejan de evaluar los siguientes nodos si beta es menor o igual a alfa
				if (beta <= alfa)
					break; // poda alfa-beta
			}
		}
	}
	//si se estan minimizando las oportunidades de ganar
	else {
		mejorJugada = 1000;
		for (int j = 0; j < tableroSize; j++) {
			if (tablero[j] == ' ') {
				//se hace la jugada
				tablero[j] = humano;
				//se obtiene la mejor jugada llamando recursivamente a la funcion minimax pero en este caso, maximizando
				mejorJugada = min(mejorJugada, Minimax(tablero, depth + 1, !isMax, alfa, beta));

				//se elimina la jugada del tablero
				tablero[j] = ' ';
				beta = min(beta, mejorJugada);

				//se dejan de evaluar los siguientes nodos si beta es menor o igual a alfa
				if (beta <= alfa) {
					break; // poda alfa-beta
				}
			}
		}
	}
	//se devuelve la mejor jugada, valores posibles: 10,-10,0
	return mejorJugada;
}

//encuentra la mejor posicion llamando a minimax para cada posible jugada del turno actual
int EncontrarMejorPosicion() {
	int mejorPosicion = 0;
	int valorMax = -1000;

	for (int i = 0; i < tableroSize; i++) {
		if (tablero[i] == ' ') {
			tablero[i] = ia;
			//se obtiene el valor de la jugada con minimax
			int valorJugada = Minimax(tablero, 0, false, -1000, 1000);
			tablero[i] = ' ';
			if (valorJugada > valorMax) {
				valorMax = valorJugada; //se actualiza el valor de la mejor jugada encontrada
				mejorPosicion = i + 1; //se actualiza la posicion de dicha posicion encontrada
			}
		}

	}

	return mejorPosicion;
}

//genera una linea divisora para el tablero
void GenDiv(int n) {
	cout << '+';
	for (int i = 0; i < n; i++) {
		cout << "---";
		if (i < n - 1) cout << '+';
	}

	cout << '+' << endl;
}

//despliega el tablero
void Display() {
	int rowCount = 0, cantCeldas = tableroSize/sqrt(tableroSize);
	GenDiv(cantCeldas);

	cout << '|';

	for (int i = 0; i < tableroSize; i++) {
		cout << " " << tablero[i] << " |";

		if (i == 2 || i == 5 || i == 8) {
			cout << endl;

			GenDiv(cantCeldas);
			rowCount++;
			if (rowCount == 3) break;
			cout << '|';
		}
	}
}

//evalua si es una jugada valida y actualiza la posicion en el tablero
bool Jugada(char playedChar, int position) {
	if (tablero[position - 1] == ' ') {
		tablero[position - 1] = playedChar;
		contJugadas++;
		return true;
	}
	else return false;
}

//valida que la posicion ingresada sea de tipo numerico
bool ValidarNumero(string position)
{
	int i = 0;
	while ((position[i] != '\0') ) //'\0' es el character que marca el final del string
	{
		// compara cada caracter de la cadena para saber si es numerico
		if (isdigit(position[i]) == false) return false; 
		i++;
	}
	return true; //devuelve un str igual si no se encontraron letras
}

int main()
{
	//inicializa los valores del array en espacios vacios
	memset(tablero, ' ', sizeof(tablero));

	//caracteres correspondientes a los jugadores
	humano = 'O';
	ia = 'X';

	//variables
	string jugada,primerTurno;
	bool inicioHumano;

	cout << "Formato de insercion de jugadas:" << endl;
	cout << "+---+---+---+\n| 1 | 2 | 3 |\n+---+---+---+\n| 4 | 5 | 6 |\n+---+---+---+\n| 7 | 8 | 9 |\n+---+---+---+\n";

	//bucle para elegir el primer turno
	while (true) {
		cout << "A que jugador le correspondera el primer turno?\n(1)Humano\n(2)Computadora" << endl;
		cin >> primerTurno;

		if (!ValidarNumero(primerTurno)) {
			cout << "Formato invalido, intente de nuevo" << endl;
			continue;
		}
		else if (stoi(primerTurno) > 2 || stoi(primerTurno) < 1) { 
			cout << "Opcion fuera de rango, intente de nuevo" << endl;
			continue;
		}

		if (primerTurno == "1") inicioHumano = true;
		else inicioHumano = false;

		break;
	}

	//bucle para las jugadas
	while (true) {
		//si se llega a 9 jugadas y no hay victorias pues hay empate
		if (contJugadas == 9) {
			cout << "El juego es un embute! (empate)" << endl;
			break;
		}

		//condicion si el primer turno es del humano
		if (inicioHumano == true) {
			cout << "Inserte su jugada, humano: ";
			cin >> jugada;


			if (ValidarNumero(jugada)) {
				if (stoi(jugada) < 1 || stoi(jugada) > 9) {
					cout << "Jugada fuera de rango, intente de nuevo" << endl;
					continue;
				}

				if (!Jugada(humano, stoi(jugada))) {
					cout << "Jugada invalida, intente de nuevo\n";
					continue;
				}
			}
			else {
				cout << "Formato de jugada invalido, intente de nuevo" << endl;
				continue;
			}


			Display();

			if (Victory(humano)) {
				cout << "El humano ha ganado!" << endl;
				break;
			}
		}
		
		//seccion de la jugada de la computadora
		if (contJugadas < 9) {
			cout << "\nJugada Maquina: " << endl;
			int jugadaIA = EncontrarMejorPosicion();

			if (!Jugada(ia, jugadaIA)) {
				cout << "Jugada invalida, intente de nuevo\n";
				continue;
			}
			Display();

			if (Victory(ia)) {
				cout << "La maquina ha ganado!" << endl;
				break;
			}
		}

		inicioHumano = true;

	}
}