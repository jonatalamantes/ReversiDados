#ifndef ESTRUCTURAHILO_H
#define ESTRUCTURAHILO_H

#include "Partida.h"

/**
* Clase para el almacenamiento de una partida en red
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class EstructuraHilo
{
    private:
        ///Atributos
        Partida* partida;
        int descriptorSocket;

    public:
        ///Constructor
            EstructuraHilo();
            ~EstructuraHilo();

        ///Getters
            Partida* getPartida();
            int getDescriptorSocket();

        ///Setters
            void setPartida(Partida* x);
            void setDescriptorSocket(int x);
};

#endif // ESTRUCTURAHILO_H
