#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdint.h>

using namespace std;

struct uint128_t
{
    uint8_t byte[16];
};

class Tablero
{
	private:
	short int fichas[8][8];
	unsigned short int dados[3];

	public:
	//Constructores
	Tablero();
	Tablero(short int fichas[8][8], unsigned short int dados[3]);
	Tablero(const Tablero& t);

	//Getter
	short int getFicha(short int x, short int y) const;
	unsigned short int getDado(short int p) const;

	//Setter
    void setFicha(short int x, short int y, short int color);
    void setDado(short int p, unsigned short int val);

    //Funciones de la clase
	void inicializar();
    short cantidadNegras();
    short cantidadBlancas();
    bool turnoValido(short color); //Mínimo un movimiento
    short turnoGlobalValido(short color); //Mínimo un movimiento Global
	bool validarMovimiento(int x,int y, int color);
	void computerMove(short, short *x, short *y);
	void tirarDados(int forceColor);
	void colocarFicha(int x,int y, int color);
	void inicializarDados();
	bool numInDados(short num);
	void imprimirTablero();

	uint8_t standardValor(short int x);
	short int tableroValor(uint8_t x);
	uint128_t tableroToBytes(Tablero x);
	Tablero bytesToTablero(uint128_t x);
};

#endif // TABLERO_H
