#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <SDL2/SDL_net.h>
#include "Tablero.h"

struct quieroJugar
{
    uint16_t RV;
    uint8_t banderas;
    std::string nombre;
};

struct moviento
{
    uint16_t RV;
    uint8_t banderas;
    uint8_t xy;
};

struct pidoDado
{
    uint16_t RV;
    uint8_t banderas;
    uint8_t color;
};

class Cliente
{
    private:
        quieroJugar qJ;
        moviento m;
        pidoDado pD;
        char paqueteJugar[19];
        char paqueteMovimiento[4];
        char paqueteDado[6];
        TCPsocket clien;

    public:
        Cliente();
        bool conectar(std::string host,std::string puerto);
        bool enviarBusquedaDeJuego();
        bool mandarMoviento();
        bool pedirDado();
        void recibirMoviento();
        int recibirPaquete(char buffer[255]);
        void analizarMensaje();
        void armarPaqueteBuscar(std::string nombre);
        void armarPaqueteMovimiento(int x,int y);
        void armarPaquetePedirDado(int colorFicha);
        void recibirPaquete();
        void enviarPaqueteFin(int color);

        TCPsocket* getCliente();
};

#endif // CLIENTE_H
