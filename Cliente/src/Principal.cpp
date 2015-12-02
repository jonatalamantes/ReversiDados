#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Constantes.h"
#include "FuncionesPantalla.h"
#include "PantallaConfiguracion.h"
#include "PantallaInicio.h"
#include "PantallaJuego.h"
#include "Principal.h"

using namespace std;

///Constructor
Principal::Principal()
{
    Principal::pi = NULL;
    Principal::pc = NULL;
    Principal::pj = NULL;
    Principal::cl = NULL;
}

/**
 * Punto de partida del juego a comenzar a jugar
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void Principal::jugar()
{
    SDL_Surface* Pantalla;
    FuncionesPantalla* f = new FuncionesPantalla();

    //Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        //cout << "Unable to init SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    if (TTF_Init() != 0)
    {
    	//cout<< "Error letras " << TTF_GetError() << endl;
    	SDL_Quit();
    	exit(1);
    }

    //Creamos la pantalla
    Pantalla = SDL_SetVideoMode(TAM_CUADRO*9+TAM_LINEA, TAM_CUADRO*12+TAM_LINEA, 32, SDL_SWSURFACE);

    if (Pantalla == NULL)
    {
       //cout << "Unable to set 720x540 video: " << SDL_GetError() << endl;
       exit(1);
    }

    if (SDL_MUSTLOCK(Pantalla))
    {
        SDL_LockSurface(Pantalla);
    }

    pi = new PantallaInicio(Pantalla, f);
    pc = new PantallaConfiguracion(Pantalla, f);
    pj = new PantallaJuego(Pantalla, f);

    int op;

    //Establecemos el titulo
    SDL_WM_SetCaption("Reversi", NULL);

    do
    {
        op = pi->imprimirPantalla();

        if (op == 1)
        {
            pj->inicializar();
            pj->setNombreJugador1(pc->getNombreJugador());
            pj->setNombreJugador2("Computadora");
            pj->gestionarEventos();
        }
        else if (op == 2)
        {
            pj->jugarRed(pc);
        }
        else if (op == 3)
        {
            pc->imprimirPantalla();
        }
    }
    while (op != 4);

    delete pi;
    delete pj;
    delete pc;
    delete f;

	TTF_Quit();
    SDL_Quit();
}