#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"
#include <semaphore.h>

class Partida
{
    private:
        string jugador1;
        string jugador2;
        int descriptorJ1;
        int descriptorJ2;
        Tablero* tablero;
        string nombreJ1;
        string nombreJ2;
        short turnoJugador; //-1 Blancas, 1 negras, 7 si es final de juego
        bool active;
        bool iniciada;
        bool finalizada;
        double tiempoCreado;

    public:
    //Constructor
        Partida();

    //Getters
        string getJugador1();
        string getJugador2();
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

    //Setters
        void setJugador1(string x);
        void setJugador2(string x);
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
