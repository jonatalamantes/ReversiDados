#ifndef FUNCIONESPANTALLA_H
#define FUNCIONESPANTALLA_H

#include <SDL.h>
#include <string>
#include "List.h"
#include "Fuente.h"

using namespace std;

class FuncionesPantalla
{
    private:
        //Fuentes que tiene las funcioens de pantalla
        List<Fuente> fuentes;
        string path;

    public:
        //Constructor
        FuncionesPantalla();

        //Funciones útiles para SDL
        void escribirPalabra(SDL_Surface* Pantalla,
                            string palabra,
                            int x,
                            int y,
                            string nombreFuente,
                            int tamFuente,
                            Uint8 r, Uint8 g, Uint8 b);

        void escribirPalabra(SDL_Surface* Pantalla,
                            string palabra,
                            int x,
                            int y,
                            string nombreFuente,
                            int tamFuente);

        bool cargarImagen(SDL_Surface* Pantalla, string nombre, int X, int Y);

        void cargarFicha(SDL_Surface* Pantalla, int fila, int columna, char tipo, string estado);
};

#endif // FUNCIONESPANTALLA_H
