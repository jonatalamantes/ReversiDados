#ifndef PANTALLAINICIO_H
#define PANTALLAINICIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "FuncionesPantalla.h"

/**
* Clase Encargada de generar una ventana en SDL para el inicio del juego
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class PantallaInicio
{
    private:
    ///Atributos
        SDL_Renderer* renderizador;
        SDL_Window* window;
        FuncionesPantalla* f;
        int opcionMenu;

    //Funcion de la pantallaInicio

        /**
         * Refresca el contenido de la ventana interna para mostrar
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void imprimirPantallaInterna();

    public:
    ///Constructor
        PantallaInicio(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* f);
        ~PantallaInicio();

    ///Funcion de la pantalla

        /**
         * Funcion encargada de gestionar los eventos en la aplicacion
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        int imprimirPantalla();
};

#endif
