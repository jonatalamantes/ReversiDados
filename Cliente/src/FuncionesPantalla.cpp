#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <SDL/SDL_image.h>

#include "Fuente.h"
#include "FuncionesPantalla.h"
#include "Constantes.h"

using namespace std;

///Constructor
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

///Getters
string FuncionesPantalla::getPath()
{
    return FuncionesPantalla::path;
}

///Funciones útiles para SDL

/**
 * Escriba una palabra en la pantalla de SDL
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param Pantalla     Apuntador para la pantalla de SDL
 * @param palabra      Palabra que se desea poner en la pantalla
 * @param x            Posicion X de la pantalla
 * @param y            Posicion Y de la pantalla
 * @param nombreFuente Nombre de la fuente en la carpeta "fonts" sin el .ttf
 * @param tamFuente    Tamaño de la fuente a poner en pantalla
 * @param r            Escala RGB tomando la 'R' para el color
 * @param g            Escala RGB tomando la 'G' para el color
 * @param b            Escala RGB tomando la 'B' para el color
 */
void FuncionesPantalla::escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                                        string nombreFuente, int tamFuente, Uint8 r, Uint8 g,
                                        Uint8 b, int *w, int *h)
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

        //Creamos una rectangulo
        SDL_Rect rectangulo;
        SDL_Surface* palabraRender;
        SDL_Color color = {r, g, b};

        //Generamos una superficie para la pantalla
        palabraRender = TTF_RenderUTF8_Blended(FuncionesPantalla::fuentes[pos].getPuntero(),
                                               palabra.c_str(), color);

        //Guardamos los datos de la fuente generada
        rectangulo.x = x;
        rectangulo.y = y;
        rectangulo.w = palabraRender->w;
        rectangulo.h = palabraRender->h;

        *w = palabraRender->w;
        *h = palabraRender->h;

        //insertamos la palabra generada en la pantalla
        SDL_BlitSurface(palabraRender, NULL, Pantalla, &rectangulo);
        SDL_FreeSurface(palabraRender);
    }
}

/**
 * Escriba una palabra en la pantalla de SDL
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param Pantalla     Apuntador para la pantalla de SDL
 * @param palabra      Palabra que se desea poner en la pantalla
 * @param x            Posicion X de la pantalla
 * @param y            Posicion Y de la pantalla
 * @param nombreFuente Nombre de la fuente en la carpeta "fonts" sin el .ttf
 * @param tamFuente    Tamaño de la fuente a poner en pantalla
 */
void FuncionesPantalla::escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                                        string nombreFuente, int tamFuente)
{
    int a,b;
    FuncionesPantalla::escribirPalabra(Pantalla, palabra, x, y, nombreFuente,
                                       tamFuente, 255, 255, 255, &a, &b);
}

/**
 * Escriba una palabra en la pantalla de SDL
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param Pantalla     Apuntador para la pantalla de SDL
 * @param palabra      Palabra que se desea poner en la pantalla
 * @param x            Posicion X de la pantalla
 * @param y            Posicion Y de la pantalla
 * @param nombreFuente Nombre de la fuente en la carpeta "fonts" sin el .ttf
 * @param tamFuente    Tamaño de la fuente a poner en pantalla
 * @param r            Escala RGB tomando la 'R' para el color
 * @param g            Escala RGB tomando la 'G' para el color
 * @param b            Escala RGB tomando la 'B' para el color
 * @param w            Apuntador donde se guardará la longitud de la palabra en la pantalla
 * @param h            Apuntador donde se guardará la altitud de la palabra en la pantalla
 */
void FuncionesPantalla::escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                                        string nombreFuente, int tamFuente, Uint8 r, Uint8 g,
                                        Uint8 b)
{
    int a,c;
    FuncionesPantalla::escribirPalabra(Pantalla, palabra, x, y, nombreFuente, tamFuente, r, g, b,
                                       &a, &c);
}

/**
 * Inserte una imagen en la pantalla
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  Pantalla Apuntador con la direccion de la pantalla en SDL
 * @param  nombre   Nombre de la imagen a cargar
 * @param  X        Posicion X en la pantalla a insertar la imagen
 * @param  Y        Posicion Y en la pantalla a insertar la imagen
 * @return          Si fue posible cargar la imagen
 */
bool FuncionesPantalla::cargarImagen(SDL_Surface* Pantalla, string nombre, int X, int Y)
{
    int a,b;

    return cargarImagen(Pantalla, nombre, X, Y, &a, &b);
}

/**
 * Inserte una imagen en la pantalla
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param  Pantalla Apuntador con la direccion de la pantalla en SDL
 * @param  nombre   Nombre de la imagen a cargar
 * @param  X        Posicion X en la pantalla a insertar la imagen
 * @param  Y        Posicion Y en la pantalla a insertar la imagen
 * @param  tamX     Apuntador donde se guardara la longitud de la imagen
 * @param  tamY     Apuntador donde se guardara la altutud de la imagen
 * @return          Si fue posible cargar la imagen
 */
bool FuncionesPantalla::cargarImagen(SDL_Surface* Pantalla, string nombre, int X, int Y,
                                     int* tamX, int* tamY)
{
    //Buscamos la ruta del archivo
    string x = FuncionesPantalla::path + nombre;

    const char* buffer = x.c_str();

    //Cargamos la imagen
    SDL_Surface *image;
    image = IMG_Load(buffer);

    if (image != NULL)
    {
        //Dibujamos la imagen en la pantalla
        SDL_Rect rcDest = {(Sint16)X, (Sint16)Y, 0, 0};
        SDL_BlitSurface (image, NULL, Pantalla, &rcDest);

        *tamX = image->w;
        *tamY = image->h;

        SDL_FreeSurface(image);

        return true;
    }

    return false;
}

/**
 * Dibuje un circulo en la pantalla
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 * @param Pantalla Apuntador con la direccion de la pantalla en SDL
 * @param radio    Radio en pixeles que tendra el circulo
 * @param x        Posicion X en donde se comenzará a evaluar e lcirculo
 * @param y        Posicion Y donde se comenzará a evaluar el circulo
 * @param r            Escala RGB tomando la 'R' para el color
 * @param g            Escala RGB tomando la 'G' para el color
 * @param b            Escala RGB tomando la 'B' para el color
 */
void FuncionesPantalla::dibujarCirculo(SDL_Surface* Pantalla, int radio, int x, int y,
                                       int r, int g, int b)
{
    //Copiamos el radio
    int tam = radio;

    //Creamos un cuadrado con el tamaño de un pixel
    SDL_Rect rect;
    rect.w = 1;
    rect.h = 1;

    //Creamos el color
    Uint32 color = SDL_MapRGB(Pantalla->format, r, g, b);

    //Recorremos un cuadrado en relacion del radio
    for (int i = tam/2; i < tam; i++) //y
    {
        for (int j = 0; j < tam; j++) //x
        {
            //Evaluamos la funcion matemtica x² + y² = r²
            int uper = sqrt( (((tam/2)*(tam/2)) - ((j- (tam/2))*(j-(tam/2))) )) + (tam/2);

            //Si nos encontramos dentro de la funcion dibujamos en ambos lados
            if (i <= uper)
            {
                //Dibujamos el circulo en ambos lados
                rect.x = j + x;
                rect.y = i + y;

                SDL_FillRect(Pantalla, &rect, color);

                rect.x = j + x;
                rect.y = (tam-i) + y;

                SDL_FillRect(Pantalla, &rect, color);
            }
        }
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
void FuncionesPantalla::cargarFicha(SDL_Surface* Pantalla, int fila, int columna,
                                    char tipo, string estado)
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
