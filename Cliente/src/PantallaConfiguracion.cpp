#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cctype>
#include "FuncionesPantalla.h"
#include "PantallaConfiguracion.h"
#include "Constantes.h"

///Constructores
PantallaConfiguracion::PantallaConfiguracion(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* f)
{
    PantallaConfiguracion::window = win;
    PantallaConfiguracion::renderizador = ren;
    PantallaConfiguracion::hostJugador = "";
    PantallaConfiguracion::nombreJugador = "J1";
    PantallaConfiguracion::puerto = "0";
    PantallaConfiguracion::opcionMenu = 1;
    PantallaConfiguracion::f = f;
}

PantallaConfiguracion::PantallaConfiguracion(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* f, string nj,
                                             string hj, string p)
{
    PantallaConfiguracion::window = win;
    PantallaConfiguracion::renderizador = ren;
    PantallaConfiguracion::hostJugador = hj;
    PantallaConfiguracion::nombreJugador = nj;
    PantallaConfiguracion::puerto = p;
    PantallaConfiguracion::opcionMenu = 1;
    PantallaConfiguracion::f = f;
}

PantallaConfiguracion::~PantallaConfiguracion()
{
    PantallaConfiguracion::window = NULL;
    PantallaConfiguracion::renderizador = NULL;
    PantallaConfiguracion::f = NULL;
}

///Getters
string PantallaConfiguracion::getNombreJugador()
{
    return PantallaConfiguracion::nombreJugador;
}

string PantallaConfiguracion::getHost()
{
    return PantallaConfiguracion::hostJugador;
}

string PantallaConfiguracion::getPuerto()
{
    return PantallaConfiguracion::puerto;
}

///Setters
void PantallaConfiguracion::setNombreJugador(string x)
{
    PantallaConfiguracion::nombreJugador = x;
}

void PantallaConfiguracion::setHost(string x)
{
    PantallaConfiguracion::hostJugador = x;
}

void PantallaConfiguracion::setPuerto(string x)
{
    PantallaConfiguracion::puerto = x;
}

///Métodos de la clase

/**
 * Refresca el contenido de la ventana interna para mostrar
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaConfiguracion::imprimirPantallaInterna()
{
    int iW, iH;
    SDL_Color color;
    SDL_Texture* tex;
    SDL_GetWindowSize(window, &iW, &iH);
    SDL_Rect areai;
    SDL_Rect areae;
    SDL_Rect r;

    //Rellenamos de negro el tablero
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //negro
    r.x = 0;
    r.y = 0;
    r.h = iH;
    r.w = iW;

    SDL_RenderFillRect(renderizador, &r);

    //Escribimos la palabra de Reversi
    color.r = 255;
    color.g = 0;
    color.b = 0;
    tex = f->renderizarTexto("Reversi", "Blazed", color, 60, renderizador);
    f->renderizarTextura(tex, renderizador, 15, 48);
    SDL_DestroyTexture(tex);

    //Insertamos las etiquetas de las configuraciones
    color.r = 255;
    color.g = 255;
    color.b = 0;

    tex = f->renderizarTexto("Nombre Jugador", "Arcarde", color, 20, renderizador);
    f->renderizarTextura(tex, renderizador, 90, 170);
    SDL_DestroyTexture(tex);

    tex = f->renderizarTexto("Host o IP a conectar", "Arcarde", color, 20, renderizador);
    f->renderizarTextura(tex, renderizador, 70, 250);
    SDL_DestroyTexture(tex);

    tex = f->renderizarTexto("Puerto a conectar", "Arcarde", color, 20, renderizador);
    f->renderizarTextura(tex, renderizador, 80, 330);
    SDL_DestroyTexture(tex);

    //Area del cuadro de texto NJ
    areae.x = f->calcularProporcion(20, 'w');
    areae.y = f->calcularProporcion(195, 'h');
    areae.w = f->calcularProporcion(325, 'w');
    areae.h = f->calcularProporcion(40, 'h');

    areai.x = f->calcularProporcion(25, 'w');
    areai.y = f->calcularProporcion(200, 'h');
    areai.w = f->calcularProporcion(315, 'w');
    areai.h = f->calcularProporcion(30, 'h');

    if (PantallaConfiguracion::opcionMenu == 1)
    {
        SDL_SetRenderDrawColor(renderizador, 250, 200, 0, 255); //Amarillo
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //Negro
        SDL_RenderFillRect(renderizador, &areai);

        color.r = 169;
        color.g = 255;
        color.b = 118;
        tex = f->renderizarTexto(nombreJugador + "_", "Digital", color, 25, renderizador);
        f->renderizarTextura(tex, renderizador, 30, 200);
        SDL_DestroyTexture(tex);
    }
    else
    {
        SDL_SetRenderDrawColor(renderizador, 200, 200, 200, 255); //Gris
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //Negro
        SDL_RenderFillRect(renderizador, &areai);

        color.r = 169;
        color.g = 255;
        color.b = 118;
        tex = f->renderizarTexto(nombreJugador, "Digital", color, 25, renderizador);
        f->renderizarTextura(tex, renderizador, 30, 200);
        SDL_DestroyTexture(tex);
    }

    //Area del cuadro de texto HC
    areae.x = f->calcularProporcion(20, 'w');
    areae.y = f->calcularProporcion(275, 'h');
    areae.w = f->calcularProporcion(325, 'w');
    areae.h = f->calcularProporcion(40, 'h');

    areai.x = f->calcularProporcion(25, 'w');
    areai.y = f->calcularProporcion(280, 'h');
    areai.w = f->calcularProporcion(315, 'w');
    areai.h = f->calcularProporcion(30, 'h');

    if (PantallaConfiguracion::opcionMenu == 2)
    {
        SDL_SetRenderDrawColor(renderizador, 250, 200, 0, 255); //Amarillo
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //Negro
        SDL_RenderFillRect(renderizador, &areai);

        color.r = 169;
        color.g = 255;
        color.b = 118;
        tex = f->renderizarTexto(hostJugador + "_", "Digital", color, 25, renderizador);
        f->renderizarTextura(tex, renderizador, 30, 280);
        SDL_DestroyTexture(tex);
    }
    else
    {
        SDL_SetRenderDrawColor(renderizador, 200, 200, 200, 255); //Gris
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //Negro
        SDL_RenderFillRect(renderizador, &areai);

        color.r = 169;
        color.g = 255;
        color.b = 118;
        tex = f->renderizarTexto(hostJugador, "Digital", color, 25, renderizador);
        f->renderizarTextura(tex, renderizador, 30, 280);
        SDL_DestroyTexture(tex);
    }

    //Area del cuadro de texto Puerto
    areae.x = f->calcularProporcion(20, 'w');
    areae.y = f->calcularProporcion(355, 'h');
    areae.w = f->calcularProporcion(325, 'w');
    areae.h = f->calcularProporcion(40, 'h');

    areai.x = f->calcularProporcion(25, 'w');
    areai.y = f->calcularProporcion(360, 'h');
    areai.w = f->calcularProporcion(315, 'w');
    areai.h = f->calcularProporcion(30, 'h');

    if (PantallaConfiguracion::opcionMenu == 3)
    {
        SDL_SetRenderDrawColor(renderizador, 250, 200, 0, 255); //Amarillo
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //Negro
        SDL_RenderFillRect(renderizador, &areai);

        color.r = 169;
        color.g = 255;
        color.b = 118;
        tex = f->renderizarTexto(puerto + "_", "Digital", color, 30, renderizador);
        f->renderizarTextura(tex, renderizador, 30, 360);
        SDL_DestroyTexture(tex);
    }
    else
    {
        SDL_SetRenderDrawColor(renderizador, 200, 200, 200, 255); //Gris
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //Negro
        SDL_RenderFillRect(renderizador, &areai);

        color.r = 169;
        color.g = 255;
        color.b = 118;
        tex = f->renderizarTexto(puerto, "Digital", color, 30, renderizador);
        f->renderizarTextura(tex, renderizador, 30, 360);
        SDL_DestroyTexture(tex);
    }

    //Area del Boton de Salir
    areae.x = f->calcularProporcion(100, 'w');
    areae.y = f->calcularProporcion(420, 'h');
    areae.w = f->calcularProporcion(170, 'w');
    areae.h = f->calcularProporcion(40, 'h');

    areai.x = f->calcularProporcion(105, 'w');
    areai.y = f->calcularProporcion(425, 'h');
    areai.w = f->calcularProporcion(160, 'w');
    areai.h = f->calcularProporcion(30, 'h');

    if (PantallaConfiguracion::opcionMenu == 4)
    {
        SDL_SetRenderDrawColor(renderizador, 250, 200, 0, 255); //Amarillo
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 4, 74, 116, 255); //Azul
        SDL_RenderFillRect(renderizador, &areai);
    }
    else
    {
        SDL_SetRenderDrawColor(renderizador, 200, 200, 200, 255); //Amarillo
        SDL_RenderFillRect(renderizador, &areae);

        SDL_SetRenderDrawColor(renderizador, 4, 74, 116, 255); //Azul
        SDL_RenderFillRect(renderizador, &areai);
    }

    color.r = 255;
    color.g = 255;
    color.b = 255;
    tex = f->renderizarTexto("Guardar", "Arcarde", color, 20, renderizador);
    f->renderizarTextura(tex, renderizador, 140, 427);
    SDL_DestroyTexture(tex);

    //Actualizamos la pantalla
    SDL_RenderPresent(renderizador);
}

/**
 * Funcion encargada de gestionar los eventos en la aplicacion
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaConfiguracion::imprimirPantalla()
{
    SDL_Event Evento;
    bool Fin = false;

    SDL_StartTextInput();

    while (!Fin)
    {
        PantallaConfiguracion::imprimirPantallaInterna();

        if (not SDL_PollEvent(&Evento))
        {
            continue;
        }

        if (Evento.type == SDL_MOUSEBUTTONDOWN)
        {
            int y = Evento.button.y;

            if (y > f->calcularProporcion(180, 'h') && y < f->calcularProporcion(260, 'h'))
            {
                SDL_StartTextInput();
                PantallaConfiguracion::opcionMenu = 1;
            }
            else if (y > f->calcularProporcion(260, 'h') && y < f->calcularProporcion(340, 'h'))
            {
                SDL_StartTextInput();
                PantallaConfiguracion::opcionMenu = 2;
            }
            else if (y > f->calcularProporcion(340, 'h') && y < f->calcularProporcion(405, 'h'))
            {
                SDL_StartTextInput();
                PantallaConfiguracion::opcionMenu = 3;
            }
            else if (y > f->calcularProporcion(405, 'h'))
            {
                PantallaConfiguracion::opcionMenu = 4;
                Fin = true;
            }
        }
        else if (Evento.type == SDL_KEYDOWN)
        {
            if (Evento.key.keysym.sym == SDLK_RETURN ||
                Evento.key.keysym.sym == SDLK_KP_ENTER) //Enter
            {
                if (PantallaConfiguracion::opcionMenu == 4)
                {
                    Fin = true;
                }
                else
                {
                    int opcion = PantallaConfiguracion::opcionMenu % 4;
                    opcion++;
                    PantallaConfiguracion::opcionMenu = opcion;
                }
            }
            else if (Evento.key.keysym.sym == SDLK_UP) //Boton Arriba
            {
                if (PantallaConfiguracion::opcionMenu == 2)
                {
                    PantallaConfiguracion::opcionMenu = 1;
                }
                else if (PantallaConfiguracion::opcionMenu == 3)
                {
                    PantallaConfiguracion::opcionMenu = 2;
                }
                else if (PantallaConfiguracion::opcionMenu == 4)
                {
                    PantallaConfiguracion::opcionMenu = 3;
                }
            }
            else if (Evento.key.keysym.sym == SDLK_TAB) //Tab
            {
                int opcion = PantallaConfiguracion::opcionMenu % 4;
                opcion++;
                PantallaConfiguracion::opcionMenu = opcion;
            }
            else if (Evento.key.keysym.sym == SDLK_DOWN) //Boton Abajo
            {
                if (PantallaConfiguracion::opcionMenu == 1)
                {
                    PantallaConfiguracion::opcionMenu = 2;
                }
                else if (PantallaConfiguracion::opcionMenu == 2)
                {
                    PantallaConfiguracion::opcionMenu = 3;
                }
                else if (PantallaConfiguracion::opcionMenu == 3)
                {
                    PantallaConfiguracion::opcionMenu = 4;
                }
            }
            else if (Evento.key.keysym.sym == SDLK_BACKSPACE) //Boton Abajo
            {
                if (PantallaConfiguracion::opcionMenu == 1)
                {
                    nombreJugador = nombreJugador.substr(0, nombreJugador.size()-1);
                }
                else if (PantallaConfiguracion::opcionMenu == 2)
                {
                    hostJugador = hostJugador.substr(0, hostJugador.size()-1);
                }
                else if (PantallaConfiguracion::opcionMenu == 3)
                {
                    puerto = puerto.substr(0, puerto.size()-1);
                }
            }
            else if (Evento.key.keysym.sym == SDLK_AC_BACK)
            {
                Fin = true;
            }
        }
        else if (Evento.type == SDL_TEXTINPUT)
        {
            string nuevaLetra = Evento.text.text;

            if (opcionMenu == 1)
            {
                if (nuevaLetra.size() < 2 && isalnum(nuevaLetra.at(0)) && nombreJugador.size() < 16)
                {
                    nombreJugador = nombreJugador + nuevaLetra;
                }
            }
            else if (opcionMenu == 2)
            {
                if (nuevaLetra.size() < 2 && hostJugador.size() < 25 &&
                    (isalnum(nuevaLetra[0]) || nuevaLetra[0] == '.'))
                {
                    hostJugador = hostJugador + nuevaLetra;
                }
            }
            else if (opcionMenu == 3)
            {
                if (nuevaLetra.size() < 2 && puerto.size() < 7 && isdigit(nuevaLetra[0]))
                {
                    puerto = puerto + nuevaLetra;
                }
            }
        }
        else if (Evento.type == SDL_QUIT)
        {
            Fin = true;
        }
    }

    SDL_StopTextInput();
}
