#pragma once
#include "pruebas_alfredo.h"
#include <windows.h>
#include "RevisarTodo.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <vector>

class Recursividad
{
private:
	int xyCell[8][8];
	std::string estadoCell[8][8];
	int xOriginal = 0;
	int yOriginal = 0;
	int colorADestruir;
	int bro = 0;
	int grupoArriba = 0;
	int grupoAbajo = 0;
	int grupoDerecha = 0;
	int grupoIzquierda = 0;
public:
	int* Asignar(int cellContenido[64], int x, int y);
	void ChecarPorDestrucciones(int x, int y);
	void ChecarPorDestruccionesArriba(int x, int y);
	void ChecarPorDestruccionesAbajo(int x, int y);
	void ChecarPorDestruccionesDerecha(int x, int y);
	void ChecarPorDestruccionesIzquierda(int x, int y);
	void Destruir();
	void FuncionamietoPowerUp1(int x, int y);
	void FuncionamietoPowerUp2(int x, int y);
	int Asignarcolor(int random);
	int* nuevosColores = new int[64];
	int GetPuntos();
public:
	int puntos = 0;
};

