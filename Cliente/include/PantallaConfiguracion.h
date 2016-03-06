#ifndef PANTALLACONFIGURACION_H
#define PANTALLACONFIGURACION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "FuncionesPantalla.h"

using namespace std;

/**
* Clase Encargada de generar una ventana en SDL para la configuracion
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class PantallaConfiguracion
{
    private:
    ///Atributos
        SDL_Renderer* renderizador;
        SDL_Window* window;
        string nombreJugador;
        string hostJugador;
        string puerto;
        int opcionMenu;
        FuncionesPantalla* f;

    //Funcion de la pantalla

        /**
         * Refresca el contenido de la ventana interna para mostrar
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void imprimirPantallaInterna();

    public:
    ///Constructores
        PantallaConfiguracion(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* f);
        PantallaConfiguracion(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* f, string nj,
                              string hj, string p);

        //Destructor
        ~PantallaConfiguracion();

    ///Getters
        string getNombreJugador();
        string getHost();
        string getPuerto();

    ///Setters
        void setNombreJugador(string x);
        void setHost(string x);
        void setPuerto(string x);

    ///Funcion de la pantalla

        /**
         * Funcion encargada de gestionar los eventos en la aplicacion
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void imprimirPantalla();
};

#endif // PANTALLACONFIGURACION_H
