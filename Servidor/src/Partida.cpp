#include "Partida.h"

///Constructor
Partida::Partida()
{
    nombreJ1 = "";
    nombreJ2 = "";
    descriptorJ1 = 0;
    descriptorJ2 = 0;
    turnoJugador = 1;
    iniciada = false;
    active = false;
    finalizada = false;
    tablero = new Tablero();
}

Partida::~Partida()
{
    delete tablero;
}

///Getters
Tablero* Partida::getTablero()
{
    return Partida::tablero;
}

string Partida::getNombreJ1()
{
    return Partida::nombreJ1;
}

string Partida::getNombreJ2()
{
    return Partida::nombreJ2;
}

short Partida::getTurnoJugador()
{
    return Partida::turnoJugador;
}

int Partida::getDescriptorJ1()
{
    return Partida::descriptorJ1;
}

int Partida::getDescriptorJ2()
{
    return Partida::descriptorJ2;
}

bool Partida::getActive()
{
    return Partida::active;
}

double Partida::getTiempoCreado()
{
    return Partida::tiempoCreado;
}

bool Partida::getIniciada()
{
    return Partida::iniciada;
}

bool Partida::getFinalizada()
{
    return Partida::finalizada;
}

///Setters
void Partida::setTablero(Tablero* x)
{
    Partida::tablero = x;
}

void Partida::setNombreJ1(string x)
{
    Partida::nombreJ1 = x;
}

void Partida::setNombreJ2(string x)
{
    Partida::nombreJ2 = x;
}

void Partida::setTurnoJugador(short x)
{
    Partida::turnoJugador = x;
}

void Partida::setDescriptorJ1(int x)
{
    Partida::descriptorJ1 = x;
}

void Partida::setDescriptorJ2(int x)
{
    Partida::descriptorJ2 = x;
}

void Partida::setActive(bool x)
{
    Partida::active = x;
}

void Partida::setIniciada(bool x)
{
    Partida::iniciada = x;
}

void Partida::setTiempoCreado(double x)
{
    Partida::tiempoCreado = x;
}

void Partida::setFinalizada(bool x)
{
    Partida::finalizada = x;
}
