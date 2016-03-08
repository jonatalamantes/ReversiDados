#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <SDL2/SDL_image.h>

#include "Fuente.h"
#include "FuncionesPantalla.h"
#include "Constantes.h"

using namespace std;

///Constructor
FuncionesPantalla::FuncionesPantalla(SDL_Window* win)
{
    FuncionesPantalla::window = win;

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

///Getters
string FuncionesPantalla::getPath()
{
    return FuncionesPantalla::path;
}

/**
 * Carga una textura a partir de un archivo de imagen
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  file    Nombre del archivo a abrir
 * @param  ren     Renderizador
 * @return         Textura resultante o NULL
 */
SDL_Texture* FuncionesPantalla::cargarTextura(string file, SDL_Renderer *ren)
{
    string url = (path + file);
	SDL_Texture *texture = IMG_LoadTexture(ren, url.c_str());

	if (texture == NULL)
	{
		cout << "No File: " << url << endl;
	}

	return texture;
}

/**
 * Copia una Textura en la memoria de un Renderizador
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  tex Textura a poner en el Renderizador
 * @param  ren Renderizador Objetivo
 * @param  x   Posicion X del objetivo
 * @param  y   Posicion Y del objetivo
 * @param  w   Tamaño del largo de la textura
 * @param  h   Tamaño del alto de la textura
 */
void FuncionesPantalla::renderizarTextura(SDL_Texture *tex, SDL_Renderer *ren,
                                          int x, int y, int w, int h)
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = FuncionesPantalla::calcularProporcion(x, 'w');
	dst.y = FuncionesPantalla::calcularProporcion(y, 'h');
	dst.w = FuncionesPantalla::calcularProporcion(w, 'w');
	dst.h = FuncionesPantalla::calcularProporcion(h, 'h');
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
 * Copia una Textura en la memoria de un Renderizador
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  tex Textura a poner en el Renderizador
 * @param  ren Renderizador Objetivo
 * @param  x   Posicion X del objetivo
 * @param  y   Posicion Y del objetivo
 */
void FuncionesPantalla::renderizarTextura(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderizarTextura(tex, ren, x, y, w, h);
}

/**
 * Crea una Textura de un texto en específico
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  message  Texto a Renderizar
 * @param  fontFile Nombre del archivo de la fuente
 * @param  color    Color que se usará
 * @param  fontSize Tamaño de la fuente
 * @param  renderer Renderizador
 * @return          Textura creada o NULL
 */
SDL_Texture* FuncionesPantalla::renderizarTexto(string message, string fontFile, SDL_Color color,
                                                int fontSize, SDL_Renderer *renderer)
{
    if (message != "")
    {
        //Creamos una fuente temporal
        Fuente aux;
        aux.setNombre(fontFile);
        aux.setTam(fontSize);

        //Buscamos si ya esta capturada
        int pos = FuncionesPantalla::fuentes.searchInList(aux);

        if (pos == -1)
        {
            //La insertamos de no estar en la lista
            string nFuente = FuncionesPantalla::path + "fonts/" + fontFile + ".png";
            aux.setPuntero(TTF_OpenFont(nFuente.c_str(), fontSize));

            if (aux.getPuntero() == NULL)
            {
                cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
            }

            FuncionesPantalla::fuentes.append(aux);
            pos = FuncionesPantalla::fuentes.getSize() -1;
        }

        TTF_Font *font = FuncionesPantalla::fuentes[pos].getPuntero();

        if (font == NULL)
        {
            cout << "Error al abrir TTF_OpenFont" << endl;
            return NULL;
        }

        //We need to first render to a surface as that's what TTF_RenderText
        //returns, then load that surface into a texture
        SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);

        if (surf == NULL)
        {
            TTF_CloseFont(font);
            cout << "Error al abrir TTF_RenderText";
            return NULL;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

        if (texture == NULL)
        {
            cout << "Error al abrir CreateTexture: " << SDL_GetError() << endl;
        }

        //Clean up the surface and font
        SDL_FreeSurface(surf);

        return texture;
    }
    else
    {
        return NULL;
    }
}

/**
 * Carga la imagen de una ficha segun el estado
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param Pantalla Apuntador con la direccion de la pantalla en SDL
 * @param fila     Fila donde poner la ficha (0-7)
 * @param columna  Columna donde poner la ficha (0-7)
 * @param tipo     'B' para Blanco o 'N' para negro
 * @param estado   Estado de la ficha
 */
void FuncionesPantalla::cargarFicha(SDL_Renderer* ren, int fila, int columna,
                                    char tipo, string estado)
{
    SDL_Texture* ficha = NULL;

    if (tipo == 'N' || tipo == 'n')
    {
        string fichaString = "img/negra";
        fichaString.append(estado);
        fichaString.append(".png");

        ficha = FuncionesPantalla::cargarTextura(fichaString, ren);
    }
    else if (tipo == 'B' || tipo == 'b')
    {
        string fichaString = "img/blanca";
        fichaString.append(estado);
        fichaString.append(".png");

        ficha = FuncionesPantalla::cargarTextura(fichaString, ren);
    }
    else if (tipo == 'G' || tipo == 'g')
    {
        string fichaString = "img/gris.png";
        ficha = FuncionesPantalla::cargarTextura(fichaString, ren);
    }

    if (ficha != NULL)
    {
        SDL_Rect rectangulo;
        rectangulo.x = (TAM_CUADRO*(fila)) + TAM_LINEA + 2;
        rectangulo.y = (TAM_CUADRO*(2 + columna)) + TAM_LINEA + 3;

        FuncionesPantalla::renderizarTextura(ficha, ren, rectangulo.x, rectangulo.y);
        SDL_DestroyTexture(ficha);
    }
}

/**
 * Calcula la proporcion de un objeto en relación del tamaño de la pantalla
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param antes   Numero a transformar en la proporcion
 * @param pos     'H' o 'h' es para horizontal, sino es en vertical
 * @return        Numero con la proporción resultante
 */
float FuncionesPantalla::calcularProporcion(float antes, char posicion)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    float nativeW = TAM_CUADRO*9+TAM_LINEA;
    float nativeH = TAM_CUADRO*12+TAM_LINEA;
    float res = 0;

    if (posicion == 'H' || posicion == 'h')
    {
        res = antes * (100*h/nativeH) / 100;
    }
    else
    {
        res = antes * (100*w/nativeW) / 100;
    }

    return res;
}
