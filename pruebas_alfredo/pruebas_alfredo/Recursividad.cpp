#include "Recursividad.h"
/**
*@brief toma el el array gameBoardrandom de la clase principal, le asigna los valores de ese array
*@brief a una matriz y llama a la funcion ChecarPorDestruccion 
*@param cellContenido es el array gameBoardrandom que contiene el contenido de las casillas
*/
void Recursividad::Asignar(int cellContenido[64]) {
	int n = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			xyCell[j][i] = cellContenido[n];
			n++;
		}
	}
	ChecarPorDestrucciones(2,2);
}
/**
*@brief checa si hay casillas con el mismo contenido pegadas con recursividad
*@param x, y son los valores que se usan en la matriz xyCell para checar su contenido
*/
int Recursividad::ChecarPorDestrucciones(int x, int y) {
	int bro = 0;
	if ((xyCell[x + 1][y] != bro && x < 7) && xyCell[x][y] == xyCell[x + 1][y]) {
		xyCell[x][y] = bro;
		ChecarPorDestrucciones(x + 1, y);
	}
	if ((xyCell[x - 1][y] != bro && x > 0) && xyCell[x][y] == xyCell[x - 1][y]) {
		xyCell[x][y] = bro;
		ChecarPorDestrucciones(x - 1, y);
	}
	if ((xyCell[x][y + 1] != bro && y < 7) && xyCell[x][y] == xyCell[x][y + 1]) {
		xyCell[x][y] = bro;
		ChecarPorDestrucciones(x, y + 1);
	}
	if ((xyCell[x][y - 1] != bro && y > 0) && xyCell[x][y] == xyCell[x][y - 1]) {
		xyCell[x][y] = bro;
		ChecarPorDestrucciones(x, y - 1);
	}
	/*if ((xyCell[x - 1][y] != bro && x > 0) && xyCell[x][y] == xyCell[x - 1][y]) {
		xyCell[x][y] = bro;
		ChecarPorDestrucciones(x - 1, y);
	}
	if ((xyCell[x][y + 1] != bro && y < 7) && xyCell[x][y] == xyCell[x][y + 1]) {
		xyCell[x][y] = bro;
		ChecarPorDestrucciones(x, y + 1);
	}
	if ((xyCell[x][y - 1] != bro && y > 0) && xyCell[x][y] == xyCell[x][y - 1]) {
		xyCell[x][y] = bro;
		ChecarPorDestrucciones(x, y - 1);
	}*/
	return 0;
}