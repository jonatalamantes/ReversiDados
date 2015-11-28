#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdint.h>

using namespace std;

/**
* Estructura para guardar 128 bits
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
struct uint128_t
{
    uint8_t byte[16];
};

/**
* Clase encargada de crear un Tablero de Reversi
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class Tablero
{
	private:
	///Atributos
		short int fichas[8][8];
		unsigned short int dados[3];

	public:
	///Constructores
		Tablero();
		Tablero(short int fichas[8][8], unsigned short int dados[3]);
		Tablero(const Tablero& t);

	///Getter
		short int getFicha(short int x, short int y) const;
		unsigned short int getDado(short int p) const;

	///Setter
	    void setFicha(short int x, short int y, short int color);
	    void setDado(short int p, unsigned short int val);

    ///Funciones de la clase
    	
    	/**
    	 * Subturina que establece los datos del tablero en vacios
    	 *
    	 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
    	 */
		void inicializar();

		/**
		 * Devuelve la cantidad de fichas negras en el tablero
		 * 
		 * @return   La cantidad de fichas negras
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
	    short cantidadNegras();

	    /**
		 * Devuelve la cantidad de fichas blancas en el tablero
		 * 
		 * @return   La cantidad de fichas blancas
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
	    short cantidadBlancas();

	    /**
	     * Valida que exista un turno minimo para el jugador del color
	     * contemplando a los dados
	     * 
	     * @param  color   -1 si es blanco o 1 si es negro
	     * @return         Si puede mover la ficha
	     * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
	     */
	    bool turnoValido(short color);

	    /**
	     * Valida que exista un turno minimo para el jugador del color
	     * sin contemplar los dados
	     *
	     * @param  color   -1 si es blanco o 1 si es negro
	     * @return         Posicion del tablero probable a poner o -1
	     * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
	     */
	    short turnoGlobalValido(short color);
		
	    /**
	     * Valida un movimiento en una posicion en especifico
	     * 
	     * @param  x     Posicion X del tablero del 0-7
	     * @param  y     Posicion Y del tablero del 0-7
	     * @param  color -1 si es blanco o 1 si es negro
	     * @return       Si el turno es valido o no
	     * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
	     */
		bool validarMovimiento(int x,int y, int color);
		
		/**
		 * Tira los dados generando tres numeros psudo-aleatorios
		 * 
		 * @param forceColor  El primer dado termina con el color que se da menos uno
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		void tirarDados(int forceColor);

		/**
		 * Se ejecuta la accion de color una ficha en el tablero
		 * 
		 * @param x     Posicion X del tablero donde se inserta la ficha 0-7
		 * @param y     Posicion Y del tablero donde se inserta la ficha 0-7
		 * @param color -1 si es blanco o 1 si es negro
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		void colocarFicha(int x,int y, int color);

		/**
		 * Pone los tres dados con el valor de 0
		 *
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		void inicializarDados();

		/**
		 * Revisa si existe un numero en los dados ya puesto evitando repeticiones
		 * 
		 * @param  num  Numero a revisar
		 * @return      Si ya existe el numero en los dados
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		bool numInDados(short num);

		/**
		 * Imprime el tablero en una terminal de linux
		 *
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		void imprimirTablero();

		/**
		 * Empaca la ficha de una casilla de -1, 0, 1 a su version del Protocolo RV
		 * 
		 * @param  x  color a cambiar
		 * @return    2 si es negro, 1 si es blanco, 0 si no tiene color
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		uint8_t standardValor(short int x);

		/**
		 * Agarra un byte del protocolo RV y lo desempaca en su forma -1, 0, 1
		 * 
		 * @param  x  byte a desempacar
		 * @return    -1 si es negro, 1 si es blanco, 0 si no tiene color
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		short int tableroValor(uint8_t x);

		/**
		 * Transforma el tablero x su version de 128 bytes
		 * 
		 * @param  x Tablero a empaquetar
		 * @return   Conjunto de Bytes a enviar
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		uint128_t tableroToBytes(Tablero x);

		/**
		 * Transforma un 128 bits en un tablero
		 * 
		 * @param  x  Estructura de 128 bits a transformar
		 * @return    Tablero resultante
		 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
		 */
		Tablero bytesToTablero(uint128_t x);
};

#endif // TABLERO_H
