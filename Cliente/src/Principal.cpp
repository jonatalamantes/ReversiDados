#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
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
        //The window we'll be rendering to
    SDL_Window* window = NULL;
    FuncionesPantalla* f = NULL;

    //The surface contained by the window
    if (SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }


    if (TTF_Init() != 0)
    {
        printf( "SDL could not initialize! SDL_TTF: %s\n", SDL_GetError() );
        SDL_Quit();
        exit(1);
    }

    if(SDLNet_Init() != 0)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    //Create window
    window = SDL_CreateWindow("Reversi",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               TAM_CUADRO*9+TAM_LINEA,
                               TAM_CUADRO*12+TAM_LINEA,
                               SDL_WINDOW_RESIZABLE);

    if(window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        exit(1);
    }

    f = new FuncionesPantalla(window);

    SDL_Surface* icono = IMG_Load((f->getPath() + "img/icono.png").c_str());
    SDL_SetWindowIcon(window, icono);

    SDL_Renderer *ren = SDL_CreateRenderer(window, -1,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (ren == NULL)
    {
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }

    pi = new PantallaInicio(window, ren, f);
    pc = new PantallaConfiguracion(window, ren, f);
    pj = new PantallaJuego(window, ren, f);

    int op;

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
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
