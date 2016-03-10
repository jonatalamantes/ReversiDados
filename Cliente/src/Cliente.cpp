#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdlib>

#include "Cliente.h"
#include "List.h"
#include "stringConvert.h"

using namespace std;

///Constructor
Cliente::Cliente()
{
    memset(&clien,0,sizeof(clien));
}

/**
 * Devuelve el resultado de la conexión, ya sea si esta fue exitosa o no
 *
 * @param   host    Recibe una cadeba con el nombre o IP del host donde se hospeda el servidor
 * @param   puerto  Recibe una cadeba con el número de puerto donde se hospeda el servidor
 * @return          Si se logro la conexión
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
bool Cliente::conectar(std::string host, std::string puerto)
{
    int errores;
    IPaddress ip;
    stringConvert ss;

    errores = SDLNet_ResolveHost(&ip, host.c_str(), ss.strToInt(puerto));

    if (errores != 0)
    {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        return false;
    }

    clien = SDLNet_TCP_Open(&ip);

    if(clien == NULL)
    {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
        return false;
    }

    return true;
}

/**
 * Arma el paquete a ser enviado para buscar una partida
 *
 * @param   nombreJ Cadena de caracteres con el nombre del jugador
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
void Cliente::armarPaqueteBuscar(std::string nombreJ)
{
    /*Variable para copiar los datos de la estructura*/
    uint16_t u16;
    uint8_t u8;

    /*Asignación de variables*/
    Cliente::qJ.RV=22098;//0101011001010010 Firma del protocolo
    Cliente::qJ.banderas=128;//1000 0000 Bandera Quiero Jugar
    Cliente::qJ.nombre=nombreJ;

    /*Copia de variables al paquete*/
    u16 = Cliente::qJ.RV;
    memcpy(Cliente::paqueteJugar+0, &u16, 2);
    u8 = Cliente::qJ.banderas;
    memcpy(Cliente::paqueteJugar+2, &u8, 1);
    for(int i=0;i<16;i++)
    {
        u8 = Cliente::qJ.nombre[i];
        memcpy(Cliente::paqueteJugar+3+i, &u8, 1);
    }
}

/**
 * Devuelve el resultado del envío del paquete de busqueda de un juego
 *
 * @return          Si se ha enviado el paquete correctamente
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
bool Cliente::enviarBusquedaDeJuego()
{
    int errores;

    errores = SDLNet_TCP_Send(Cliente::clien, paqueteJugar, sizeof(paqueteJugar));

    if(errores<0)
    {
        perror("Error: send");
        return false;
    }
    else
        return true;
}

/**
 * Arma el paquete a ser enviado por cada movimiento del jugador
 *
 * @param   x   Coordenada x del movimiento que fue realizado por el jugador
 * @param   y   Coordenada y del movimiento que fue realizado por el jugador
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
void Cliente::armarPaqueteMovimiento(int x,int y)
{
    /*Variable para copiar los datos de la estructura*/
    uint16_t u16;

    /*Asignación de variables*/
    Cliente::m.RV=22098;//0101011001010010 Firma del protocolo
    Cliente::m.banderas=64;

    uint8_t x1 = x;
    uint8_t x2 = y;
    x1 = ((x1 << 4) & 0xF0);
    x2 = ((x2) & 0x0F);

    Cliente::m.xy= x1 | x2;

    /*Copia de variables al paquete*/
    u16 = Cliente::m.RV;
    memcpy(Cliente::paqueteMovimiento+0, &u16, 2);
    memcpy(Cliente::paqueteMovimiento+2, &Cliente::m.banderas, 1);
    memcpy(Cliente::paqueteMovimiento+3, &Cliente::m.xy, 1);
}

/**
 * Devuelve el resultado del envío del paquete que contiene el movimiento realizado por el jugador
 *
 * @return          Si se ha enviado el paquete correctamente
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
bool Cliente::mandarMoviento()
{
    int errores;

    errores = SDLNet_TCP_Send(Cliente::clien, paqueteMovimiento, sizeof(paqueteMovimiento));

    if(errores<0)
    {
        perror("Error: send");
        return false;
    }
    else
        return true;
}

/**
 * Arma el paquete a ser enviado por cada peticíón un dado por parte del jugador
 *
 * @param   colorFicha  Color de la ficha correspondiente al jugador que realiza la petición
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
void Cliente::armarPaquetePedirDado(int colorFicha)
{
    /*Variable para copiar los datos de la estructura*/
    uint16_t u16;
    uint8_t u8;

    /*Asignación de variables*/
    Cliente::pD.RV=22098;//0101011001010010 Firma del protocolo
    Cliente::pD.banderas=80;//0101 0000 Bandera Pedir Dado
    Cliente::pD.color=colorFicha;

    /*Copia de variables al paquete*/
    u16 = Cliente::pD.RV;
    memcpy(Cliente::paqueteDado+0, &u16, 2);
    u8 = Cliente::pD.banderas;
    memcpy(Cliente::paqueteDado+2, &u8, 1);
    u8 = Cliente::pD.color;
    memcpy(Cliente::paqueteDado+3, &u8, 1);
}

/**
 * Devuelve el resultado del envío del paquete de solicitud de dado
 *
 * @return          Si se ha enviado el paquete correctamente
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
bool Cliente::pedirDado()
{
    int errores;

    errores = SDLNet_TCP_Send(Cliente::clien, paqueteDado, sizeof(paqueteDado));

    if(errores<0)
    {
        perror("Error: send");
        return false;
    }
    else
        return true;
}

/**
 * Devuelve el tipo de paquete que ha sido recibido
 *
 * @param   buffer  Mensaje que ha sido recibido para su análisis
 * @return          Tipo de mensaje recibido
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
int Cliente::recibirPaquete(char buffer[255])
{
    if(buffer[0]!='R')
    {
        return -1;
    }
    if(buffer[1]!='V')
    {
        return -1;
    }

    uint8_t banderas = buffer[2];

    if ((banderas & 0x80) == banderas)//Comenzar Partida
    {
        return 1;
    }
    else if ((banderas & 0x10) == banderas)//Dar Dados
    {
        return 3;
    }
    else if ((banderas & 0x40) == banderas)//Movimiento Invalido
    {
        return 6;
    }
    else if ((banderas & 0x48) == banderas)//Movimiento Valido
    {
        return 5;
    }
    else if ((banderas & 0x20) == banderas)//Fin Partida
    {
        return 7;
    }
    else
    {
        return -1;
    }
}

/**
 * Envia el paquete que indica el final de la partida
 *
 * @param   color   El color de ficha del jugador que envia el paquete
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
void Cliente::enviarPaqueteFin(int color)
{
    List<uint8_t> bytesEnviados;
    uint8_t byte = 0;

    //Cabecera
    bytesEnviados.append('R');
    bytesEnviados.append('V');
    bytesEnviados.append(byte | 0x20);

    //Razon de final de juego
    if (color < 0)
    {
        bytesEnviados.append(3);
    }
    else
    {
        bytesEnviados.append(4);
    }

    //Generamos el buffer del paquete;
    char *bufferPaquete;
    bufferPaquete = new char[bytesEnviados.getSize()];

    for (unsigned i = 0; i < bytesEnviados.getSize(); i++)
    {
        bufferPaquete[i] = bytesEnviados[i];
        //cout << (int)bytesEnviados[i] << endl;
    }

    //Enviamos el paquete
    int resWrite = SDLNet_TCP_Send(Cliente::clien, bufferPaquete, bytesEnviados.getSize());

    if (resWrite < 0)
    {
        //Error
    }

    //Liberamos el buffer
    delete [] bufferPaquete;
}

/// Getter
TCPsocket* Cliente::getCliente()
{
    return &clien;
}
