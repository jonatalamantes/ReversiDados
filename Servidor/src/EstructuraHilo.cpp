#include "EstructuraHilo.h"

///Constructor
EstructuraHilo::EstructuraHilo()
{
    partida = NULL;
    descriptorSocket = 0;
}

EstructuraHilo::~EstructuraHilo()
{
    partida = NULL;
}

///Getters
Partida* EstructuraHilo::getPartida()
{
    return EstructuraHilo::partida;
}

int EstructuraHilo::getDescriptorSocket()
{
    return EstructuraHilo::descriptorSocket;
}

///Setters
void EstructuraHilo::setPartida(Partida* x)
{
    EstructuraHilo::partida = x;
}

void EstructuraHilo::setDescriptorSocket(int x)
{
    EstructuraHilo::descriptorSocket = x;
}
