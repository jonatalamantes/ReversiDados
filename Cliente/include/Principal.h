#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "Constantes.h"
#include "FuncionesPantalla.h"
#include "PantallaConfiguracion.h"
#include "PantallaInicio.h"
#include "PantallaJuego.h"
#include "Cliente.h"

/**
* Clase Encargada de generar el inicio de la aplicacion e inicializacion
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class Principal
{
    private:
    ///Atributos
        PantallaInicio* pi;
        PantallaConfiguracion* pc;
        PantallaJuego* pj;
        Cliente *cl;

    public:
    ///Constructor
        Principal();

    ///Metodo

        /**
         * Punto de partida del juego a comenzar a jugar
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void jugar();
};

#endif // PRINCIPAL_H
