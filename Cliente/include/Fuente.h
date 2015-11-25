#ifndef FUENTE_H
#define FUENTE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

class Fuente
{
    private:
        TTF_Font* puntero;
        string nombre;
        int tam;

    public:
        //Constructor
        Fuente();
        Fuente(TTF_Font* p, string n, int t);

        //Destructor
        ~Fuente();

        //Getters
        TTF_Font* getPuntero();
        string getNombre();
        int getTam();

        //Setters
        void setPuntero(TTF_Font* f);
        void setNombre(string n);
        void setTam(int t);

        //Sobrecarga de operadores
        bool operator== (Fuente);
};

#endif // FUENTE_H
