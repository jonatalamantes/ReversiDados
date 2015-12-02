#include "Fuente.h"

///Constructor
Fuente::Fuente()
{
    Fuente::puntero = NULL;
    Fuente::tam = 0;
    Fuente::nombre = "";
}

Fuente::Fuente(TTF_Font* p, string n, int t)
{
    Fuente::puntero = p;
    Fuente::tam = t;
    Fuente::nombre = n;
}

///Destructor
Fuente::~Fuente()
{
    Fuente::puntero = NULL;
}

///Getters
TTF_Font* Fuente::getPuntero()
{
    return Fuente::puntero;
}

string Fuente::getNombre()
{
    return Fuente::nombre;
}

int Fuente::getTam()
{
    return Fuente::tam;
}

///Setters
void Fuente::setPuntero(TTF_Font* f)
{
    Fuente::puntero = f;
}

void Fuente::setNombre(string n)
{
    Fuente::nombre = n;
}

void Fuente::setTam(int t)
{
    Fuente::tam = t;
}

///Sobrecarga de operadores
bool Fuente::operator== (Fuente f)
{
    if (this->getNombre() == f.getNombre()  &&
        Fuente::getTam()    == f.getTam())
    {
        return true;
    }
    else
    {
        return false;
    }
}
