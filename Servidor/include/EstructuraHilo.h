#ifndef ESTRUCTURAHILO_H
#define ESTRUCTURAHILO_H

#include "Partida.h"

class EstructuraHilo
{
    private:
        Partida* partida;
        int descriptorSocket;

    public:
        //Constructor
            EstructuraHilo();
            ~EstructuraHilo();

        //Getters
            Partida* getPartida();
            int getDescriptorSocket();

        //Setters
            void setPartida(Partida* x);
            void setDescriptorSocket(int x);
};

#endif // ESTRUCTURAHILO_H
