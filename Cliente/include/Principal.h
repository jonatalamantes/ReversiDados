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

class Principal
{
    private:
        PantallaInicio* pi;
        PantallaConfiguracion* pc;
        PantallaJuego* pj;
        Cliente *cl;

    public:
        //Constructor
        Principal();

        //Metodo
        void jugar();
};

#endif // PRINCIPAL_H
