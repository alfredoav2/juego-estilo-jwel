#include "Recursividad.h"
/**
*@brief toma el el array gameBoardrandom de la clase principal, le asigna los valores de ese array
*@brief a una matriz y llama a la funcion ChecarPorDestruccion 
*@param cellContenido es el array gameBoardrandom que contiene el contenido de las casillas
*@return regresa el array con los colores nuevos
*/
int* Recursividad::Asignar(int cellContenido[64], int x, int y) {
	int n = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			xyCell[i][j] = cellContenido[n];
			nuevosColores[n] = cellContenido[n];
			n++;
		}
	}
	colorADestruir = xyCell[x][y];
	xOriginal = x;
	yOriginal = y;
	ChecarPorDestrucciones(x,y);
	return nuevosColores;
}
/**
*@brief checa si hay casillas con el mismo contenido pegadas con recursividad
*@param x, y son los valores que se usan en la matriz xyCell para checar su contenido
*/
void Recursividad::ChecarPorDestrucciones(int x, int y) {
	//FuncionamietoPowerUp1(x, y);
	//acia abajo
	if ((x < 7 && xyCell[x + 1][y] != bro) && xyCell[x + 1][y] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoAbajo++;
		ChecarPorDestruccionesAbajo(x + 1, y);
	}
	else if (x < 7) {
		grupoAbajo++;
		estadoCell[x + 1][y] = "revisado";
	}
	//acia arriba
	if ((x > 0 && xyCell[x - 1][y] != bro) && xyCell[x - 1][y] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoArriba++;
		ChecarPorDestruccionesArriba(x - 1, y);
	}
	else if (x > 0) {
		grupoArriba++;
		estadoCell[x - 1][y] = "revisado";
	}
	//acia la derecha
	if ((y < 7 && xyCell[x][y + 1] != bro) && xyCell[x][y + 1] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoDerecha++;
		ChecarPorDestruccionesDerecha(x, y + 1);
	}
	else if (y < 7) {
		grupoDerecha++;
		estadoCell[x][y + 1] = "revisado";
	}
	//acia la izquierda
	if ((y > 0 && xyCell[x][y - 1] != bro) && xyCell[x][y - 1] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoIzquierda++;
		ChecarPorDestruccionesIzquierda(x, y - 1);
	}
	else if (y > 0) {
		grupoIzquierda++;
		estadoCell[x][y - 1] = "revisado";
	}
	//aqui 
	if (x != xOriginal && y != yOriginal) {
		ChecarPorDestrucciones(xOriginal, yOriginal);
	}
	xyCell[x][y] = bro;
	Destruir();
}
/**
*@brief hace toda una linea hacia arriba igual a 0 antes de comparar los demas lados 
*@brie y aumenta en 10 a los puntos cada que encuentra un bro
*@param x, y es la pocicion de la celda
*/
void Recursividad::ChecarPorDestruccionesArriba(int x, int y) {
	if ((x > 0 && xyCell[x - 1][y] != bro) && xyCell[x - 1][y] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoArriba++;
		ChecarPorDestruccionesArriba(x - 1, y);
	}
	else if (x < 7) {
		ChecarPorDestrucciones(x, y);
	}
}
/**
*@brief hace toda una linea hacia abajo igual a 0 antes de comparar los demas lados
*@brie y aumenta en 10 a los puntos cada que encuentra un bro
*@param x, y es la pocicion de la celda
*/
void Recursividad::ChecarPorDestruccionesAbajo(int x, int y) {
	if ((x < 7 && xyCell[x + 1][y] != bro) && xyCell[x + 1][y] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoAbajo++;
		ChecarPorDestruccionesAbajo(x + 1, y);
	}
	else if (x > 0) {
		ChecarPorDestrucciones(x, y);
	}
}
/**
*@brief hace toda una linea hacia la derecha igual a 0 antes de comparar los demas lados
*@brie y aumenta en 10 a los puntos cada que encuentra un bro
*@param x, y es la pocicion de la celda
*/
void Recursividad::ChecarPorDestruccionesDerecha(int x, int y) {
	if ((y < 7 && xyCell[x][y + 1] != bro) && xyCell[x][y + 1] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoDerecha++;
		ChecarPorDestruccionesDerecha(x, y + 1);
	}
	else if (y > 0){
		ChecarPorDestrucciones(x, y);
	}
}
/**
*@brief hace toda una linea hacia la izquierda igual a 0 antes de comparar los demas lados
*@brie y aumenta en 10 a los puntos cada que encuentra un bro
*@param x, y es la pocicion de la celda
*/
void Recursividad::ChecarPorDestruccionesIzquierda(int x, int y) {
	if ((y > 0 && xyCell[x][y - 1] != bro) && xyCell[x][y - 1] == colorADestruir) {
		xyCell[x][y] = bro;
		estadoCell[x][y] = "revisado";
		puntos += 2;
		grupoIzquierda++;
		ChecarPorDestruccionesIzquierda(x, y - 1);
	}
	else if (y < 7) {
		ChecarPorDestrucciones(x, y);
	}
}
/**
*@brief es una funcion que regresa un valor dependiendo del valor de una variable random
*@param es una variable random
*@retur regresa un int 
*/
int Recursividad::Asignarcolor(int random) {
	if (random == 0) {
		return 2;
	}
	if (random == 1) {
		return 1;
	}
	if (random == 2) {
		return 3;
	}
	if (random == 3) {
		return 4;
	}
	if (random == 4) {
		return 5;
	}
	if (random == 5) {
		return 6;
	}
	if (random == 6) {
		return 7;
	}
	if (random == 7) {
		return 8;
	}
	if (random == 8) {
		return 9;
	}
}
/*
*/
//int Recursividad::FuncionamietoPowerUp1(int x, int y) {
//	int random;
//	if (xyCell[x + 1][y] == 4 && xyCell[x + 2][y] == colorADestruir) {
//		random = rand() % 9;
//		nuevosColores[xyCell[x + 1][y]] = Asignarcolor(random);
//		for (int i = 0; i < 64; i++) {
//			random = rand() % 9;
//			if (nuevosColores[i] == colorADestruir) {
//				nuevosColores[i] = Asignarcolor(random);
//			}
//		}
//	}
//	if (x > 0 && xyCell[x - 1][y] == 4 && xyCell[x - 2][y] == colorADestruir) {
//		random = rand() % 9;
//		nuevosColores[xyCell[x + 1][y]] = Asignarcolor(random);
//		for (int i = 0; i < 64; i++) {
//			random = rand() % 9;
//			if (nuevosColores[i] == colorADestruir) {
//				nuevosColores[i] = Asignarcolor(random);
//			}
//		}
//	}
//	if (xyCell[x][y + 1] == 4 && xyCell[x][y + 2] == colorADestruir) {
//		random = rand() % 9;
//		nuevosColores[xyCell[x + 1][y]] = Asignarcolor(random);
//		for (int i = 0; i < 64; i++) {
//			random = rand() % 9;
//			if (nuevosColores[i] == colorADestruir) {
//				nuevosColores[i] = Asignarcolor(random);
//			}
//		}
//	}
//	if (y > 0 && xyCell[x][y - 1] == 4 && xyCell[x][y - 2] == colorADestruir) {
//		random = rand() % 9;
//		nuevosColores[xyCell[x + 1][y]] = Asignarcolor(random);
//		for (int i = 0; i < 64; i++) {
//			random = rand() % 9;
//			if (nuevosColores[i] == colorADestruir) {
//				nuevosColores[i] = Asignarcolor(random);
//			}
//		}
//	}
//	return 0;
//}
//int Recursividad::FuncionamietoPowerUp1(int x, int y) {
//	int random;
//	if ( xyCell[x + 1][y] == 4 && xyCell[x + 2][y] == colorADestruir) {
//		random = rand() % 9;
//		for (int i = 0; i < 64; i++) {
//			random = rand() % 9;
//			nuevosColores[i] = Asignarcolor(random);
//		}
//	}
//	if (x > 0 && xyCell[x - 1][y] == 4 && xyCell[x - 2][y] == colorADestruir) {
//		random = rand() % 9;
//		for (int i = 0; i < 64; i++) {
//			for (int i = 0; i < 64; i++) {
//				random = rand() % 9;
//				nuevosColores[i] = Asignarcolor(random);
//			}
//		}
//	}
//	if ( xyCell[x][y + 1] == 4 && xyCell[x][y + 2] == colorADestruir) {
//		random = rand() % 9;
//		for (int i = 0; i < 64; i++) {
//			random = rand() % 9;
//			nuevosColores[i] = Asignarcolor(random);
//		}
//	}
//	if (y > 0 && xyCell[x][y - 1] == 4 && xyCell[x][y - 2] == colorADestruir) {
//		random = rand() % 9;
//		for (int i = 0; i < 64; i++) {
//			random = rand() % 9;
//			nuevosColores[i] = Asignarcolor(random);
//		}
//	}
//	return 0;
//}
/**
*@brief cambia los colores de las casillas si hay mas de 3 en una fila 
*/
void Recursividad::Destruir() {
	int n = 0;
	int random;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			random = rand() % 9;
			if (grupoArriba > 2 && xyCell[i][j] == bro) {
				nuevosColores[n] = Asignarcolor(random);
			}
			if (grupoAbajo > 2 && xyCell[i][j] == bro) {
				nuevosColores[n] = Asignarcolor(random);
			}
			if (grupoDerecha > 2 && xyCell[i][j] == bro) {
				nuevosColores[n] = Asignarcolor(random);
			}
			if (grupoIzquierda > 2 && xyCell[i][j] == bro) {
				nuevosColores[n] = Asignarcolor(random);
			}
			n++;
		}
	}
}
/**
*@brief regresa los puntos al main
*@return regresa los puntos del jugador
*/
int Recursividad::Puntos() {
	if (puntos > 0) {
		return puntos;
	}
}