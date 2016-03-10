#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "FuncionesPantalla.h"
#include "PantallaInicio.h"
#include "Constantes.h"

using namespace std;

///Constructor
PantallaInicio::PantallaInicio(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* fe)
{
    PantallaInicio::opcionMenu = 1;
    PantallaInicio::window = win;
    PantallaInicio::renderizador = ren;
    PantallaInicio::f = fe;
}

///Destructor
PantallaInicio::~PantallaInicio()
{
    PantallaInicio::window = NULL;
    PantallaInicio::renderizador = NULL;
    PantallaInicio::f = NULL;
}

/**
 * Refresca el contenido de la ventana interna para mostrar
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaInicio::imprimirPantallaInterna()
{
    int iW, iH;
    SDL_Color color;
    SDL_Texture* tex;
    SDL_GetWindowSize(window, &iW, &iH);
    SDL_Rect r;

    //Rellenamos de negro el tablero
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //negro
    r.x = 0;
    r.y = 0;
    r.h = iH;
    r.w = iW;

    SDL_RenderFillRect(renderizador, &r);

    //Cargamos las palabras
    color.r = 255;
    color.g = 0;
    color.b = 0;
    tex = f->renderizarTexto("Reversi", "Blazed", color, 43, renderizador);
    f->renderizarTextura(tex, renderizador, 5, 48);
    SDL_DestroyTexture(tex);

    tex = f->cargarTextura("img/logo.png", renderizador);
    f->renderizarTextura(tex, renderizador, TAM_CUADRO*6, TAM_CUADRO/2);
    SDL_DestroyTexture(tex);

    color.r = 255;
    color.g = 255;
    color.b = 0;
    tex = f->renderizarTexto("VS Computadora", "Arcarde", color, 30, renderizador);
    f->renderizarTextura(tex, renderizador, 75, 165);
    SDL_DestroyTexture(tex);

    tex = f->renderizarTexto("VS Jugador 2", "Arcarde", color, 30, renderizador);
    f->renderizarTextura(tex, renderizador, 110, 245);
    SDL_DestroyTexture(tex);

    tex = f->renderizarTexto("Opciones", "Arcarde", color, 30, renderizador);
    f->renderizarTextura(tex, renderizador, 135, 325);
    SDL_DestroyTexture(tex);

    tex = f->renderizarTexto("Salir", "Arcarde", color, 30, renderizador);
    f->renderizarTextura(tex, renderizador, 150, 405);
    SDL_DestroyTexture(tex);

    if (PantallaInicio::opcionMenu == 1)
    {
        tex = f->cargarTextura("img/fichaInicial.png", renderizador);
        f->renderizarTextura(tex, renderizador, 10, 160);
        SDL_DestroyTexture(tex);
    }
    else if (PantallaInicio::opcionMenu == 2)
    {
        tex = f->cargarTextura("img/fichaInicial.png", renderizador);
        f->renderizarTextura(tex, renderizador, 10, 240);
        SDL_DestroyTexture(tex);
    }
    else if (PantallaInicio::opcionMenu == 3)
    {
        tex = f->cargarTextura("img/fichaInicial.png", renderizador);
        f->renderizarTextura(tex, renderizador, 10, 320);
        SDL_DestroyTexture(tex);
    }
    else if (PantallaInicio::opcionMenu == 4)
    {
        tex = f->cargarTextura("img/fichaInicial.png", renderizador);
        f->renderizarTextura(tex, renderizador, 10, 400);
        SDL_DestroyTexture(tex);
    }

    SDL_RenderPresent(renderizador);
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

        if (not SDL_PollEvent(&Evento1))
        {
            continue;
        }

        if (Evento1.type == SDL_MOUSEBUTTONDOWN)
        {
            int y = Evento1.motion.y;

            if (PantallaInicio::opcionMenu == 1 ||
                ( y > f->calcularProporcion(170, 'h') && y < f->calcularProporcion(220, 'h')) )
            {
                PantallaInicio::opcionMenu = 1;
                Fin = true;
            }
            else if (PantallaInicio::opcionMenu == 2 ||
                    ( y > f->calcularProporcion(250, 'h') && y < f->calcularProporcion(300, 'h')) )
            {
                PantallaInicio::opcionMenu = 2;
                Fin = true;
            }
            else if (PantallaInicio::opcionMenu == 3 ||
                    ( y > f->calcularProporcion(320, 'h') && y < f->calcularProporcion(370, 'h')) )
            {
                PantallaInicio::opcionMenu = 3;
                Fin = true;
            }
            else if (PantallaInicio::opcionMenu == 4 ||
                    ( y > f->calcularProporcion(370, 'h') && y < f->calcularProporcion(450, 'h')) )
            {
                PantallaInicio::opcionMenu = 4;
                Fin = true;
            }
        }
        else if (Evento1.type == SDL_MOUSEMOTION)
        {
            int y = Evento1.motion.y;

            if ( y > f->calcularProporcion(170, 'h') && y < f->calcularProporcion(220, 'h') )
            {
                PantallaInicio::opcionMenu = 1;
            }
            else if ( y > f->calcularProporcion(250, 'h') && y < f->calcularProporcion(300, 'h') )
            {
                PantallaInicio::opcionMenu = 2;
            }
            else if ( y > f->calcularProporcion(320, 'h') && y < f->calcularProporcion(370, 'h') )
            {
                PantallaInicio::opcionMenu = 3;
            }
            else if ( y > f->calcularProporcion(390, 'h') && y < f->calcularProporcion(493, 'h') )
            {
                PantallaInicio::opcionMenu = 4;
            }
        }
        else if (Evento1.type == SDL_KEYDOWN)
        {
            if (Evento1.key.keysym.sym == SDLK_RETURN ||
                Evento1.key.keysym.sym == SDLK_KP_ENTER) //Enter
            {
                Fin = true;
            }
            else if (Evento1.key.keysym.sym == SDLK_AC_BACK)
            {
                PantallaInicio::opcionMenu = 4;
                Fin = true;
            }
            else if (Evento1.key.keysym.sym == SDLK_UP) //Boton Arriba
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
            else if (Evento1.key.keysym.sym == SDLK_DOWN) //Boton Abajo
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
