#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include <iostream>
#include "FuncionesPantalla.h"
#include "PantallaInicio.h"
#include "Constantes.h"

using namespace std;

///Constructor
PantallaInicio::PantallaInicio(SDL_Surface* vent, FuncionesPantalla* fe)
{
    PantallaInicio::opcionMenu = 1;
    PantallaInicio::ventana = vent;
    PantallaInicio::f = fe;
}

///Destructor
PantallaInicio::~PantallaInicio()
{
    PantallaInicio::ventana = NULL;
}

/**
 * Refresca el contenido de la ventana interna para mostrar
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaInicio::imprimirPantallaInterna()
{
    Uint32 color = SDL_MapRGB(PantallaInicio::ventana->format, 0,0,0); //negro

    //Rellenamos de negro el tablero
    SDL_FillRect(PantallaInicio::ventana, NULL, color);

    f->escribirPalabra(PantallaInicio::ventana, "Reversi", 5, 48, "Blazed", 43, 255, 0, 0);
    f->cargarImagen(PantallaInicio::ventana, "img/logo.bmp", TAM_CUADRO*6, TAM_CUADRO/2);

    f->escribirPalabra(ventana, "VS Computadora", 75, 170, "Arcarde", 30, 255, 255, 0);
    f->escribirPalabra(ventana, "VS Jugador 2", 110, 250, "Arcarde", 30, 255, 255, 0);
    f->escribirPalabra(ventana, "Opciones", 135, 330, "Arcarde", 30, 255, 255, 0);
    f->escribirPalabra(ventana, "Salir", 150, 400, "Arcarde", 30, 255, 255, 0);

    if (PantallaInicio::opcionMenu == 1)
    {
        f->cargarImagen(PantallaInicio::ventana, "img/fichaInicial.bmp", 10, 165);
    }
    else if (PantallaInicio::opcionMenu == 2)
    {
        f->cargarImagen(PantallaInicio::ventana, "img/fichaInicial.bmp", 10, 245);
    }
    else if (PantallaInicio::opcionMenu == 3)
    {
        f->cargarImagen(PantallaInicio::ventana, "img/fichaInicial.bmp", 10, 325);
    }
    else if (PantallaInicio::opcionMenu == 4)
    {
        f->cargarImagen(PantallaInicio::ventana, "img/fichaInicial.bmp", 10, 390);
    }

    SDL_UpdateRect(PantallaInicio::ventana, 0, 0, 0, 0);
}

/**
 * Funcion encargada de gestionar los eventos en la aplicacion
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
int PantallaInicio::imprimirPantalla()
{
    SDL_Event Evento1;
    bool Fin = false;

    while (!Fin)
    {
        PantallaInicio::imprimirPantallaInterna();

        SDL_WaitEvent(&Evento1);

        if (Evento1.type == SDL_MOUSEBUTTONDOWN)
        {
            int y = Evento1.motion.y;

            if (PantallaInicio::opcionMenu == 1 || (y > 170 && y < 220))
            {
                PantallaInicio::opcionMenu = 1;
                Fin = true;
            }
            else if (PantallaInicio::opcionMenu == 2 || (y > 250 && y < 300))
            {
                PantallaInicio::opcionMenu = 2;
                Fin = true;
            }
            else if (PantallaInicio::opcionMenu == 3 || (y > 320 && y < 370))
            {
                PantallaInicio::opcionMenu = 3;
                Fin = true;
            }
            else if (PantallaInicio::opcionMenu == 4 || (y > 370 && y < 450))
            {
                PantallaInicio::opcionMenu = 4;
                Fin = true;
            }
        }
        else if (Evento1.type == SDL_MOUSEMOTION)
        {
            int y = Evento1.motion.y;

            if (y > 170 && y < 220)
            {
                PantallaInicio::opcionMenu = 1;
            }
            else if (y > 250 && y < 300)
            {
                PantallaInicio::opcionMenu = 2;
            }
            else if (y > 320 && y < 370)
            {
                PantallaInicio::opcionMenu = 3;
            }
            else if (y > 390 && y < 430)
            {
                PantallaInicio::opcionMenu = 4;
            }
        }
        else if (Evento1.type == SDL_KEYDOWN)
        {
            if (Evento1.key.keysym.sym == 13) //Enter
            {
                Fin = true;
            }
            else if (Evento1.key.keysym.sym == 273) //Boton Arriba
            {
                if (PantallaInicio::opcionMenu == 2)
                {
                    PantallaInicio::opcionMenu = 1;
                }
                else if (PantallaInicio::opcionMenu == 3)
                {
                    PantallaInicio::opcionMenu = 2;
                }
                else if (PantallaInicio::opcionMenu == 4)
                {
                    PantallaInicio::opcionMenu = 3;
                }
            }
            else if (Evento1.key.keysym.sym == 274) //Boton Abajo
            {
                if (PantallaInicio::opcionMenu == 1)
                {
                    PantallaInicio::opcionMenu = 2;
                }
                else if (PantallaInicio::opcionMenu == 2)
                {
                    PantallaInicio::opcionMenu = 3;
                }
                else if (PantallaInicio::opcionMenu == 3)
                {
                    PantallaInicio::opcionMenu = 4;
                }
            }
        }
        else if (Evento1.type == SDL_QUIT)
        {
            PantallaInicio::opcionMenu = 4;
            Fin = true;
        }
    }

    return PantallaInicio::opcionMenu;
}
