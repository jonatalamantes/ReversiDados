#ifndef FUENTE_H
#define FUENTE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

/**
 * Clase encargada de gestionar las fuentes en el sistema
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
class Fuente
{
    private:
    ///Atributos
        TTF_Font* puntero;
        string nombre;
        int tam;

    public:
    ///Constructores
        Fuente();
        Fuente(TTF_Font* p, string n, int t);

        //Destructor
        ~Fuente();

    ///Getters
        TTF_Font* getPuntero();
        string getNombre();
        int getTam();

    ///Setters
        void setPuntero(TTF_Font* f);
        void setNombre(string n);
        void setTam(int t);

    ///Sobrecarga de operadores
        bool operator== (Fuente);
};

#endif // FUENTE_H
