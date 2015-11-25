#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cctype>
#include "FuncionesPantalla.h"
#include "PantallaConfiguracion.h"
#include "Constantes.h"

PantallaConfiguracion::PantallaConfiguracion(SDL_Surface* vent, FuncionesPantalla* f)
{
    PantallaConfiguracion::ventana = vent;
    PantallaConfiguracion::hostJugador = "";
    PantallaConfiguracion::nombreJugador = "J1";
    PantallaConfiguracion::puerto = "0";
    PantallaConfiguracion::opcionMenu = 1;
    PantallaConfiguracion::f = f;
}

PantallaConfiguracion::PantallaConfiguracion(SDL_Surface * vent, FuncionesPantalla* f, string nj, string hj, string p)
{
    PantallaConfiguracion::ventana = vent;
    PantallaConfiguracion::hostJugador = hj;
    PantallaConfiguracion::nombreJugador = nj;
    PantallaConfiguracion::puerto = p;
    PantallaConfiguracion::opcionMenu = 1;
}

//Destructor
PantallaConfiguracion::~PantallaConfiguracion()
{
    PantallaConfiguracion::ventana = NULL;
}

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

//Métodos de la clase
void PantallaConfiguracion::imprimirPantallaInterna()
{
    SDL_Rect areai;
    SDL_Rect areae;
    Uint32 color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 0,0,0); //negro
    Uint32 colorIn = SDL_MapRGB(PantallaConfiguracion::ventana->format, 200,200,200); //gris
    Uint32 colorAc = SDL_MapRGB(PantallaConfiguracion::ventana->format, 250,200,0); //amarillo fuerte

    //Rellenamos de negro el tablero
    SDL_FillRect(PantallaConfiguracion::ventana, NULL, color);

    f->escribirPalabra(PantallaConfiguracion::ventana, "Reversi", 15, 48, "Blazed", 60, 255, 0, 0);
    //Insertamos las etiquetas de las configuraciones
    f->escribirPalabra(PantallaConfiguracion::ventana, "Nombre Jugador", 90, 170, "Arcarde", 20, 255, 255, 0);
    f->escribirPalabra(PantallaConfiguracion::ventana, "Host o IP a conectar", 70, 250, "Arcarde", 20, 255, 255, 0);
    f->escribirPalabra(PantallaConfiguracion::ventana, "Puerto a conectar", 80, 330, "Arcarde", 20, 255, 255, 0);

    //Area del cuadro de texto NJ
    areae.x = 20;
    areae.y = 195;
    areae.w = 325;
    areae.h = 40;

    color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 0, 0, 0); //Negro
    areai.x = 25;
    areai.y = 200;
    areai.w = 315;
    areai.h = 30;

    if (PantallaConfiguracion::opcionMenu == 1)
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorAc);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
        f->escribirPalabra(PantallaConfiguracion::ventana, PantallaConfiguracion::nombreJugador + "_", 30, 200, "Digital", 25, 169, 255, 118); //Verde Claro
    }
    else
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorIn);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
        f->escribirPalabra(PantallaConfiguracion::ventana, PantallaConfiguracion::nombreJugador, 30, 200, "Digital", 25, 169, 255, 118); //Verde Claro
    }

    //Area del cuadro de texto HC
    color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 200, 200, 200); //Gris
    areae.x = 20;
    areae.y = 275;
    areae.w = 325;
    areae.h = 40;

    color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 0, 0, 0); //Negro
    areai.x = 25;
    areai.y = 280;
    areai.w = 315;
    areai.h = 30;

    if (PantallaConfiguracion::opcionMenu == 2)
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorAc);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
        f->escribirPalabra(PantallaConfiguracion::ventana, PantallaConfiguracion::hostJugador + "_", 30, 280, "Digital", 25, 169, 255, 118); //Verde Claro
    }
    else
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorIn);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
        f->escribirPalabra(PantallaConfiguracion::ventana, PantallaConfiguracion::hostJugador, 30, 280, "Digital", 25, 169, 255, 118); //Verde Claro
    }

    //Area del cuadro de texto Puerto
    color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 200, 200, 200); //Gris
    areae.x = 20;
    areae.y = 355;
    areae.w = 325;
    areae.h = 40;

    color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 0, 0, 0); //Negro
    areai.x = 25;
    areai.y = 360;
    areai.w = 315;
    areai.h = 30;

    if (PantallaConfiguracion::opcionMenu == 3)
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorAc);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
        f->escribirPalabra(PantallaConfiguracion::ventana, PantallaConfiguracion::puerto + "_", 30, 360, "Digital", 30, 169, 255, 118); //Verde Claro
    }
    else
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorIn);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
        f->escribirPalabra(PantallaConfiguracion::ventana, PantallaConfiguracion::puerto, 30, 360, "Digital", 30, 169, 255, 118); //Verde Claro
    }

    //Area del Boton de Salir
    color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 200, 200, 200); //Gris
    areae.x = 100;
    areae.y = 420;
    areae.w = 170;
    areae.h = 40;

    color = SDL_MapRGB(PantallaConfiguracion::ventana->format, 4, 74, 116); //Azul
    areai.x = 105;
    areai.y = 425;
    areai.w = 160;
    areai.h = 30;

    if (PantallaConfiguracion::opcionMenu == 4)
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorAc);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
    }
    else
    {
        SDL_FillRect(PantallaConfiguracion::ventana, &areae, colorIn);
        SDL_FillRect(PantallaConfiguracion::ventana, &areai, color);
    }

    f->escribirPalabra(PantallaConfiguracion::ventana, "Guardar", areai.x + 35, areai.y + 2, "Arcarde", 20, 255, 255, 255);

    //Actualizamos la pantalla
    SDL_UpdateRect(PantallaConfiguracion::ventana, 0, 0, 0, 0);
}

void PantallaConfiguracion::imprimirPantalla()
{
    SDL_Event Evento;
    bool Fin = false, shift = false;

    while (!Fin)
    {
        PantallaConfiguracion::imprimirPantallaInterna();

        SDL_WaitEvent(&Evento);

        if (Evento.type == SDL_MOUSEBUTTONDOWN)
        {
            int y = Evento.button.y;

            if (y > 180 && y < 260)
            {
                PantallaConfiguracion::opcionMenu = 1;
            }
            else if (y > 260 && y < 340)
            {
                PantallaConfiguracion::opcionMenu = 2;
            }
            else if (y > 340 && y < 405)
            {
                PantallaConfiguracion::opcionMenu = 3;
            }
            else if (y > 405)
            {
                PantallaConfiguracion::opcionMenu = 4;
                Fin = true;
            }
        }
        else if (Evento.type == SDL_KEYDOWN)
        {
            if (Evento.key.keysym.sym == SDLK_RSHIFT || Evento.key.keysym.sym == SDLK_LSHIFT)
            {
                shift = true;
            }
            else if (Evento.key.keysym.sym == 13) //Enter
            {
                if (PantallaConfiguracion::opcionMenu == 4)
                {
                    Fin = true;
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
            else
            {
                int c = Evento.key.keysym.sym;

                if (PantallaConfiguracion::opcionMenu == 1)
                {
                    string palabra = PantallaConfiguracion::nombreJugador;

                    if (c == 8) //backspace
                    {
                        if (palabra.size() != 0)
                        {
                            palabra = palabra.substr(0, palabra.size()-1);
                        }
                    }
                    else if (isdigit(c) || isupper(c) || islower(c))
                    {
                        if (shift)
                        {
                            palabra.push_back(toupper(c));
                        }
                        else
                        {
                            palabra.push_back(c);
                        }
                    }

                    palabra = palabra.substr(0, MAX_CHAR_TEXTBOX);

                    PantallaConfiguracion::nombreJugador = palabra;
                }
                else if (PantallaConfiguracion::opcionMenu == 2)
                {
                    string palabra = PantallaConfiguracion::hostJugador;

                    if (c == 8) //backspace
                    {
                        if (palabra.size() != 0)
                        {
                            palabra = palabra.substr(0, palabra.size()-1);
                        }
                    }
                    else if (isdigit(c) || islower(c) || isupper(c) || c == '.')
                    {
                        if (shift)
                        {
                            palabra.push_back(toupper(c));
                        }
                        else
                        {
                            palabra.push_back(c);
                        }
                    }
                    else if (c >= 256 && c <= 265)
                    {
                        palabra.push_back('0' + (c-256));
                    }
                    else if (c == 266)
                    {
                        palabra.push_back('.');
                    }


                    palabra = palabra.substr(0, MAX_CHAR_TEXTBOX);

                    PantallaConfiguracion::hostJugador = palabra;
                }
                else if (PantallaConfiguracion::opcionMenu == 3)
                {
                    string palabra = PantallaConfiguracion::puerto;

                    if (c == 8) //backspace
                    {
                        if (palabra.size() != 0)
                        {
                            palabra = palabra.substr(0, palabra.size()-1);
                        }
                    }
                    else if (isdigit(c))
                    {
                        palabra.push_back(c);
                    }
                    else if (c >= 256 && c <= 265)
                    {
                        palabra.push_back('0' + (c-256));
                    }

                    palabra = palabra.substr(0, MAX_CHAR_TEXTBOX);

                    PantallaConfiguracion::puerto = palabra;
                }
            }
        }
        else if (Evento.type == SDL_KEYUP)
        {
            if (Evento.key.keysym.sym == SDLK_RSHIFT || Evento.key.keysym.sym == SDLK_LSHIFT)
            {
                shift = false;
            }
        }
        else if (Evento.type == SDL_QUIT)
        {
            Fin = true;
        }
    }
}

