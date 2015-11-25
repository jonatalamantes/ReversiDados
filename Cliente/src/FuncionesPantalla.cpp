#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Constantes.h"
#include "FuncionesPantalla.h"

using namespace std;

//Constructor
FuncionesPantalla::FuncionesPantalla()
{
    ifstream archivo("pathFile.dat");

    if (archivo)
    {
        FuncionesPantalla::path = "";
    }
    else
    {
        FuncionesPantalla::path = "../../";
    }

    archivo.close();
}

//Funciones útiles para SDL
void FuncionesPantalla::escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                                        string nombreFuente, int tamFuente, Uint8 r, Uint8 g, Uint8 b)
{
    if (palabra != "")
    {
        //Creamos una fuente temporal
        Fuente aux;
        aux.setNombre(nombreFuente);
        aux.setTam(tamFuente);

        //Buscamos si ya esta capturada
        int pos = FuncionesPantalla::fuentes.searchInList(aux);

        if (pos == -1)
        {
            //La insertamos de no estar en la lista
            string nFuente = FuncionesPantalla::path + "fonts/" + nombreFuente + ".ttf";
            aux.setPuntero(TTF_OpenFont(nFuente.c_str(), tamFuente));

            if (aux.getPuntero() == NULL)
            {
                cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
            }

            FuncionesPantalla::fuentes.append(aux);
            pos = FuncionesPantalla::fuentes.getSize() -1;
        }

        SDL_Rect rectangulo;
        SDL_Surface* palabraRender;
        SDL_Color color = {r, g, b};

        palabraRender = TTF_RenderUTF8_Blended(FuncionesPantalla::fuentes[pos].getPuntero(), palabra.c_str(), color);

        rectangulo.x = x;
        rectangulo.y = y;
        rectangulo.w = palabraRender->w;
        rectangulo.h = palabraRender->h;

        SDL_BlitSurface(palabraRender, NULL, Pantalla, &rectangulo);
        SDL_FreeSurface(palabraRender);
    }
}

void FuncionesPantalla::escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                                        string nombreFuente, int tamFuente)
{
    FuncionesPantalla::escribirPalabra(Pantalla, palabra, x, y, nombreFuente, tamFuente, 255, 255, 255);
}

void FuncionesPantalla::cargarFicha(SDL_Surface* Pantalla, int fila, int columna, char tipo, string estado)
{
    SDL_Surface* ficha;
    SDL_Rect rectangulo;

    if (tipo == 'N' || tipo == 'n')
    {
        string fichaString = FuncionesPantalla::path + "img/negra";
        fichaString.append(estado);
        fichaString.append(".bmp");

        ficha = SDL_LoadBMP(fichaString.c_str());
    }
    else if (tipo == 'B' || tipo == 'b')
    {
        string fichaString = FuncionesPantalla::path + "img/blanca";
        fichaString.append(estado);
        fichaString.append(".bmp");

        ficha = SDL_LoadBMP(fichaString.c_str());
    }
    else if (tipo == 'G' || tipo == 'g')
    {
        string fichaString = FuncionesPantalla::path + "img/gris.bmp";
        ficha = SDL_LoadBMP(fichaString.c_str());
    }
    else
    {
        string fichaString = FuncionesPantalla::path + "img/trasparente.bmp";
        ficha = SDL_LoadBMP(fichaString.c_str());
    }

    rectangulo.x = (TAM_CUADRO*(fila)) + TAM_LINEA + 2;
    rectangulo.y = (TAM_CUADRO*(2 + columna)) + TAM_LINEA + 3;

    SDL_BlitSurface(ficha, NULL, Pantalla, &rectangulo);

    SDL_FreeSurface(ficha);
}

bool FuncionesPantalla::cargarImagen(SDL_Surface* Pantalla, string nombre, int X, int Y)
{
    string x = FuncionesPantalla::path + nombre;

    const char* buffer = x.c_str();

    SDL_Surface *image;
    image = IMG_Load(buffer);

    if (image != NULL)
    {
        // Draws the image on the screen:
        SDL_Rect rcDest = {(Sint16)X, (Sint16)Y, 0, 0};
        SDL_BlitSurface (image, NULL, Pantalla, &rcDest);

        SDL_FreeSurface(image);

        return true;
    }

    return false;
}
