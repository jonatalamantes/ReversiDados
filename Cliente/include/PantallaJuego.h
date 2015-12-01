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
        SDL_Surface* ventana;
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
        //Constructor
        PantallaJuego(SDL_Surface* v, FuncionesPantalla* f);

        void setNombreJugador1(string j);
        void setNombreJugador2(string j);

        //Método de la clase
        void inicializar();
        void dibujarTablero();
        void animacionDado();
        void jugarRed(PantallaConfiguracion* p);
        void ponerAnimacion(Tablero antiguo, short color, short lastX, short lastY);
        void dibujarReversiChan(int estado);
        void gestionarEventos();
        void gestionarEventosRed(Cliente* clienteRcv);
};

#endif // PANTALLAJUEGO_H
