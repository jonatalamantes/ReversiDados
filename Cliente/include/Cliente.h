#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <csignal>
#include <sys/poll.h>

#include "Tablero.h"

/**
 * Estructura que encapsula los datos del paquete quiero jugar
 *
 * @author Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
struct quieroJugar
{
    uint16_t RV;
    uint8_t banderas;
    std::string nombre;
};

/**
 * Estructura que encapsula los datos del paquete de los movimientos por jugador
 *
 * @author Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
struct moviento
{
    uint16_t RV;
    uint8_t banderas;
    uint8_t xy;
};

/**
 * Estructura que encapsula los datos del paquete para pedir los dados
 *
 * @author Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
struct pidoDado
{
    uint16_t RV;
    uint8_t banderas;
    uint8_t color;
};

/**
 * Clase con los datos de un cliente del juego
 *
 * @author Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
class Cliente
{
    private:
    ///Atributos
        quieroJugar qJ;
        moviento m;
        pidoDado pD;
        char paqueteJugar[19];
        char paqueteMovimiento[4];
        char paqueteDado[6];
        int sock;
        struct sockaddr_in serv;
        struct sockaddr_in clien;
        socklen_t sin_size;
    public:
    ///Constructor
        Cliente();
    ///Metodos
        void recibirMoviento();
        void analizarMensaje();
        void armarPaqueteBuscar(std::string nombre);
        void armarPaqueteMovimiento(int x,int y);
        void armarPaquetePedirDado(int colorFicha);
        void recibirPaquete();
        void enviarPaqueteFin(int color);
        bool conectar(std::string host,std::string puerto);
        bool enviarBusquedaDeJuego();
        bool mandarMoviento();
        bool pedirDado();
        int recibirPaquete(char buffer[255]);
        int getSock();
};

#endif // CLIENTE_H
