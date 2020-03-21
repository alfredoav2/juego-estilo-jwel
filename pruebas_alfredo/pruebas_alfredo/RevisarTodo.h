#pragma once
#include<iostream>
#include "string.h"
template<class Revision>
class RevisarTodo{
private:
	int xyCell[8][8];
	int random;
	std::string cambioDeCell[8][8];
public:
	RevisarTodo(Revision casillas[]);
	int AsignarColor(Revision numeroAlAzar);
	void Checar();
	Revision* Reemplazar();
	int coloresCambiados[64];
};
/**
*@brief llena una matriz con la informacion de los colores de las casillas
*@param casillas[] es un array que tiene toda la informacion de las casillas
*@param tamano es el tamaño del array casillas
*/
template <class Revision>
RevisarTodo<Revision>::RevisarTodo(Revision casillas[]) {
	int n = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			xyCell[i][j] = casillas[n];
			n++;
		}
	}
	Checar();
}
/**
*@brief aqui se crea el valor que determina que imagen se usa en la casilla
*@param numeroALAzar es un numero random del 0 al 110
*@return regresa un numero entero que se usara para determinar que imagen va en cada casilla al actualizarse
*/
template <class Revision>
int RevisarTodo<Revision>::AsignarColor(Revision numeroAlAzar) {
	if (numeroAlAzar >= 5 && numeroAlAzar < 11) {
		return 10;
	}
	if (numeroAlAzar < 5) {
		return 12;
	}
	else if (numeroAlAzar >= 11) {
		int random2 = rand() % 9;
		if (random2 == 0) {
			return 1;
		}
		if (random2 == 1) {
			return 2;
		}
		if (random2 == 2) {
			return 3;
		}
		if (random2 == 3) {
			return 4;
		}
		if (random2 == 4) {
			return 5;
		}
		if (random2 == 5) {
			return 6;
		}
		if (random2 == 6) {
			return 7;
		}
		if (random2 == 7) {
			return 8;
		}
		if (random2 == 8) {
			return 9;
		}
	}
}
/**
*@brief checa toa la pantalla por grupos de 3 o mas para saver si se destrullen
*/
template<class Revision>
void RevisarTodo<Revision>::Checar() {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			//acia abajo
			if (x < 6 && xyCell[x + 1][y] == xyCell[x][y] && xyCell[x + 2][y] == xyCell[x][y]){
				cambioDeCell[x][y] = "cambiara";
				cambioDeCell[x+1][y] = "cambiara";
				cambioDeCell[x+2][y] = "cambiara";
			}
			//acia la derecha
			if (y < 6 && xyCell[x][y + 1] == xyCell[x][y] && xyCell[x][y + 2] == xyCell[x][y]) {
				cambioDeCell[x][y] = "cambiara";
				cambioDeCell[x][y + 1] = "cambiara";
				cambioDeCell[x][y + 2] = "cambiara";
			}
		}
	}
	Reemplazar();
}
/**
*@brief reemplaza las imagenes de las casillas si tienen una "etiqueta" de cambiar
*@return regresa un array de tamaño 64 con todas las nuevas imagenes de las casillas
*/
template <class Revision>
Revision* RevisarTodo<Revision>::Reemplazar() {
	int n = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			random = rand() % 110;
			if (cambioDeCell[x][y] == "cambiara") {
				xyCell[x][y] = AsignarColor(random);
			}
			coloresCambiados[n] = xyCell[x][y];
			n++;
		}
	}
	return(coloresCambiados);
}