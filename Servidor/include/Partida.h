#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"

/**
* Clase con los datos de una partida en linea
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class Partida
{
    private:
    ///Atributos
        int descriptorJ1;
        int descriptorJ2;
        Tablero* tablero;
        string nombreJ1;
        string nombreJ2;
        bool active;
        bool iniciada;
        bool finalizada;
        double tiempoCreado;
        short turnoJugador; //-1 Blancas, 1 Negras, 7 si es final de juego

    public:
    ///Constructor
        Partida();
        ~Partida();

    ///Getters
        Tablero* getTablero();
        string getNombreJ1();
        string getNombreJ2();
        short getTurnoJugador();
        int getDescriptorJ1();
        int getDescriptorJ2();
        bool getActive();
        bool getIniciada();
        bool getFinalizada();
        double getTiempoCreado();

    ///Setters
        void setTablero(Tablero* x);
        void setNombreJ1(string x);
        void setNombreJ2(string x);
        void setTurnoJugador(short x);
        void setDescriptorJ1(int x);
        void setDescriptorJ2(int x);
        void setActive(bool x);
        void setIniciada(bool x);
        void setTiempoCreado(double x);
        void setFinalizada(bool x);
};

#endif // PARTIDA_H
