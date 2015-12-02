#ifndef FUNCIONESPANTALLA_H
#define FUNCIONESPANTALLA_H

#include <SDL.h>
#include <string>
#include "List.h"
#include "Fuente.h"

using namespace std;

/**
* Clase Encargada de realizar funciones en la pantalla facilmente
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class FuncionesPantalla
{
    private:
    ///Atributos
        List<Fuente> fuentes;
        string path;

    public:
    ///Constructor
        FuncionesPantalla();

    ///Getters
        string getPath();

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
        void escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                            string nombreFuente, int tamFuente, Uint8 r, Uint8 g, Uint8 b);

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
        void escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                             string nombreFuente, int tamFuente);

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
        void escribirPalabra(SDL_Surface* Pantalla, string palabra, int x, int y,
                             string nombreFuente, int tamFuente, Uint8 r, Uint8 g, Uint8 b,
                             int *w, int *h);
        /**
         * Inserte una imagen en la pantalla
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  Pantalla Apuntador con la direccion de la pantalla en SDL
         * @param  nombre   Nombre de la imagen a cargar
         * @param  X        Posicion X en la pantalla a insertar la imagen
         * @param  Y        Posicion Y en la pantalla a insertar la imagen
         * @return          Si fue posible cargar la imagen
         */
        bool cargarImagen(SDL_Surface* Pantalla, string nombre, int X, int Y);

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
        bool cargarImagen(SDL_Surface* Pantalla, string nombre, int X, int Y, int* tamX, int* tamY);

        /**
         * Dibuje un circulo en la pantalla
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param Pantalla Apuntador con la direccion de la pantalla en SDL
         * @param radio    Radio en pixeles que tendra el circulo
         * @param x        Posicion X en donde se comenzará a evaluar e lcirculo
         * @param y        Posicion Y donde se comenzará a evaluar el circulo
         * @param r        Escala RGB tomando la 'R' para el color
         * @param g        Escala RGB tomando la 'G' para el color
         * @param b        Escala RGB tomando la 'B' para el color
         */
        void dibujarCirculo(SDL_Surface* Pantalla, int radio, int x, int y, int r, int g, int b);

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
        void cargarFicha(SDL_Surface* Pantalla, int fila, int columna, char tipo, string estado);
};

#endif // FUNCIONESPANTALLA_H
