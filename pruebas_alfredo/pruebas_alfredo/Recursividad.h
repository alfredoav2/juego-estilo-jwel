#pragma once
#include "pruebas_alfredo.h"
#include <iostream>
#include <string>
class Recursividad
{
private:
	int xyCell[8][8];
public:
	void Asignar(int cellContenido[64]);
	int ChecarPorDestrucciones(int x, int y);
};

