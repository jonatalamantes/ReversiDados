#ifndef PANTALLAJUEGO_H
#define PANTALLAJUEGO_H

#include <SDL.h>
#include "PantallaConfiguracion.h"
#include "FuncionesPantalla.h"
#include "Tablero.h"
#include "Cliente.h"

/**
* Clase con los del manejo de la pantalla del Cliente
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
* @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
**/
class PantallaJuego
{
    private:
    ///Atributos
        SDL_Renderer* renderizador;
        SDL_Window* window;
        FuncionesPantalla* f;
        Tablero tablero;
        short posibleX;
        short posibleY;
        short turnoJugador;
        short colorJugador;
        bool dadosSet;
        bool Fin;
        bool tablas;
        bool noTurno;
        string nombreJugador1;
        string nombreJugador2;

    public:
    ///Constructor
        PantallaJuego(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* f);

    ///Setters
        void setNombreJugador1(string j);
        void setNombreJugador2(string j);

    ///Método de la clase

        /**
         * Inicializa la ventana y el tablero
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void inicializar();

        /**
         * Dibuja la ventana del tablero
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void dibujarTablero();

        /**
         * Crea una animacion para los dados
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void animacionDado();

        /**
         * Método para iniciar la partida en red
         *
         * @param p Apuntador de la pantalla para su manejo
		 * @author Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
         */
        void jugarRed(PantallaConfiguracion* p);

        /**
         * Genera una animacion entre el tablero antiguo y el actual de las fichas cambiadas

         * @param antiguo  Tablero antiguo antes del movimiento
         * @param color    Color que cambiara
         * @param lastX    Ultima posicion X donde estaba la ficha del movimiento
         * @param lastY    Ultima posicion Y donde estaba la ficha del movimiento
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void ponerAnimacion(Tablero antiguo, short color, short lastX, short lastY);

        /**
         * Dibuja a Reversi-chan segun el estado (ver imagenes)
         *
         * @param estado  Imagen de Reversi-chan a cargar
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void dibujarReversiChan(int estado);

        /**
         * Genera una jugabilidad normal contra la computadora
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void gestionarEventos();

        /**
         * Genera una partida en Red entre dos jugadores usando el protocolo RV
         *
         * @param clienteRcv   Apuntador del Cliente con el socket asociado
		 * @author Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
         */
        void gestionarEventosRed(Cliente* clienteRcv);
};

#endif // PANTALLAJUEGO_H
