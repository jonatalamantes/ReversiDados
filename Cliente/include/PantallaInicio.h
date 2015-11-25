#ifndef PANTALLAINICIO_H
#define PANTALLAINICIO_H

#include <SDL.h>
#include "FuncionesPantalla.h"

class PantallaInicio
{
    private:
        SDL_Surface* ventana;
        FuncionesPantalla* f;
        int opcionMenu;

        //Funcion de la pantallaInicio
        void imprimirPantallaInterna();

    public:
        //Constructor
        PantallaInicio(SDL_Surface * vent, FuncionesPantalla* f);

        //Destructor
        ~PantallaInicio();

        //Funcion de la pantallaInicio
        int imprimirPantalla();
};

#endif
