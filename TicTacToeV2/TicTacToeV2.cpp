// TicTacToeV2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <limits>
#include <algorithm>
using namespace std;

char humano, ia;
int contJugadas = 0, tableroSize;


bool Victory(char tablero[], char playedChar) {
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

int evaluarTablero(char tablero[]) {
	if (Victory(tablero, ia)) return 10;
	else if (Victory(tablero, humano)) return -10;
	else return 0;
}

bool tableroFinal(char tablero[]) {
	for (int i = 0; i < sizeof(tablero) / tablero[0];i++) {
		if (tablero[i] == ' ') return false;
	}
	return true;
}

int Minimax(char tablero[], int depth, bool isMax) {
	int puntaje = evaluarTablero(tablero);

	if (puntaje == 10 || puntaje == -10) return puntaje;
	if (tableroFinal(tablero)) return 0;

	int mejorJugada;

	if (isMax) {
		mejorJugada = numeric_limits<int>::min();
		for (int i = 0; i < tableroSize; i++) {
			if (tablero[i] == ' ') {
				tablero[i] = ia;
				mejorJugada = max(mejorJugada, Minimax(tablero, depth + 1, !isMax));
				tablero[i] = ' ';
			}
		}
	}
	else {
		mejorJugada = numeric_limits<int>::min();
		for (int j = 0; j < tableroSize; j++) {
			if (tablero[j] == ' ') {
				tablero[j] = humano;
				mejorJugada = min(mejorJugada, Minimax(tablero, depth + 1, !isMax));
				tablero[j] = ' ';
			}
		}
	}

	return mejorJugada;
}


int EncontrarMejorPosicion(char tablero[]) {
	int mejorPosicion = 0;
	int valorMax = numeric_limits<int>::min();

	for (int i = 0; i < tableroSize; i++) {
		tablero[i] = ia;
		int valorJugada = Minimax(tablero, 0, false);
		tablero[i] = ' ';
		if (valorJugada > valorMax) {
			valorMax = valorJugada;
			mejorPosicion = i + 1;
		}
	}

	return mejorPosicion;

}


void GenDiv(int n) {
	cout << '+';
	for (int i = 0; i < n; i++) {
		cout << "---";
		if (i < n - 1) cout << '+';
	}

	cout << '+' << endl;
}

void Display(char tablero[]) {
	int size = sizeof(tablero) / sizeof(tablero[0]);
	size = size / sqrt(size);
	int rowCount = 0;
	GenDiv(size);

	cout << '|';

	for (int i = 0; i < size * size; i++) {
		cout << " " << tablero[i] << " |";

		if (i == 2 || i == 5 || i == 8) {
			cout << endl;

			GenDiv(size);
			rowCount++;
			if (rowCount == 3) break;
			cout << '|';
		}
	}
}

bool Jugada(char playedChar, int position, char tablero[]) {
	if (tablero[position - 1] == ' ') {
		tablero[position - 1] = playedChar;
		contJugadas++;
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	char tablero[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };

	tableroSize = sizeof(tablero) / sizeof(tablero[0]);

	humano = 'O';
	ia = 'X';
	string jugada;

	cout << "Formato de insercion de jugadas:" << endl;
	cout << "+---+---+---+\n| 1 | 2 | 3 |\n+---+---+---+\n| 4 | 5 | 6 |\n+---+---+---+\n| 7 | 8 | 9 |\n+---+---+---+\n";

	while (true) {
		if (contJugadas == 9) {
			cout << "El juego es un empate!" << endl;
			break;
		}

		cout << "Inserte su jugada, humano: ";
		cin >> jugada;

		if (!Jugada(humano, stoi(jugada), tablero)) {
			cout << "Jugada invalida, intente de nuevo\n";
			continue;
		}
		if (Victory(tablero,stoi(jugada))) break;
		Display(tablero);


		int jugadaIA = EncontrarMejorPosicion(tablero);

		if (!Jugada(ia, jugadaIA, tablero)) {
			cout << "Jugada invalida, intente de nuevo\n";
			continue;
		}
		if (Victory(tablero,jugadaIA)) break;

		Display(tablero);

	}
}