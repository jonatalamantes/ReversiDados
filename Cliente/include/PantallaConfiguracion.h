#ifndef PANTALLACONFIGURACION_H
#define PANTALLACONFIGURACION_H

#include <SDL.h>
#include <string>
#include "FuncionesPantalla.h"

using namespace std;

class PantallaConfiguracion
{
    private:
        SDL_Surface* ventana;
        string nombreJugador;
        string hostJugador;
        string puerto;
        int opcionMenu;
        FuncionesPantalla* f;

        //Funcion de la pantallaInicio
        void imprimirPantallaInterna();

    public:
        //Constructor
        PantallaConfiguracion(SDL_Surface * vent, FuncionesPantalla* f);
        PantallaConfiguracion(SDL_Surface * vent, FuncionesPantalla* f, string nj, string hj, string p);

        //Destructor
        ~PantallaConfiguracion();

        //Funcion de la pantallaInicio
        string getNombreJugador();
        string getHost();
        string getPuerto();

        void setNombreJugador(string x);
        void setHost(string x);
        void setPuerto(string x);

        void imprimirPantalla();
};

#endif // PANTALLACONFIGURACION_H
