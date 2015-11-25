#include "Cliente.h"
#include "List.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>

using namespace std;

Cliente::Cliente()
{
    memset(&serv,0,sizeof(serv));
    memset(&clien,0,sizeof(clien));
    //memset(&qJ,0,sizeof(qJ));
    //memset(&m,0,sizeof(m));
    //memset(&pD,0,sizeof(pD));
    sin_size=sizeof(struct sockaddr);
    sock = 0;
}

bool Cliente::conectar(std::string host, std::string puerto)
{
    int errores;
    struct addrinfo hints,*res;

    memset(&hints,0,sizeof(hints));

    hints.ai_flags=AI_PASSIVE;
    hints.ai_family=AF_UNSPEC;
    hints.ai_socktype=SOCK_STREAM;

    errores=getaddrinfo(host.c_str(),puerto.c_str(),&hints,&res);
    if (errores<0)
    {
        perror("Error: getaddrinfo");
        return false;//Cambiar por un aviso grafico.
    }

    Cliente::sock=socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (Cliente::sock<0)
    {
        perror("Error: socket");
        return false;//Cambiar por un aviso grafico.
    }
    errores=connect(Cliente::sock, res->ai_addr, res->ai_addrlen);
    if (errores<0)
    {
        perror("Error: connect");
        return false;//Cambiar por un aviso grafico.
    }
    else
        return true;
}


void Cliente::armarPaqueteBuscar(std::string nombreJ)
{
    /*Variable para copiar los datos de la estructura*/
    uint16_t u16;
    uint8_t u8;

    /*Asignación de variables*/
    Cliente::qJ.RV=21078;//0101001001010110 Firma del protocolo
    Cliente::qJ.banderas=128;//1000 0000 Bandera Quiero Jugar
    Cliente::qJ.nombre=nombreJ;

    /*Copia de variables al paquete*/
    u16 = htons(Cliente::qJ.RV);
    memcpy(Cliente::paqueteJugar+0, &u16, 2);
    u8 = Cliente::qJ.banderas;
    memcpy(Cliente::paqueteJugar+2, &u8, 1);
    for(int i=0;i<16;i++)
    {
        u8 = Cliente::qJ.nombre[i];
        memcpy(Cliente::paqueteJugar+3+i, &u8, 1);
    }
}

bool Cliente::enviarBusquedaDeJuego()
{
    int errores;
    errores=send(Cliente::sock,paqueteJugar,sizeof(paqueteJugar),0);
    if(errores<0)
    {
        perror("Error: send");
        return false;
    }
    else
        return true;
}

void Cliente::armarPaqueteMovimiento(int x,int y)
{
    /*Variable para copiar los datos de la estructura*/
    uint16_t u16;

    /*Asignación de variables*/
    Cliente::m.RV=21078;//0101001zz001010110 Firma del protocolo
    Cliente::m.banderas=64;

    uint8_t x1 = x;
    uint8_t x2 = y;
    x1 = ((x1 << 4) & 0xF0);
    x2 = ((x2) & 0x0F);

    Cliente::m.xy= x1 | x2;

    /*Copia de variables al paquete*/
    u16 = htons(Cliente::m.RV);
    memcpy(Cliente::paqueteMovimiento+0, &u16, 2);
    memcpy(Cliente::paqueteMovimiento+2, &Cliente::m.banderas, 1);
    memcpy(Cliente::paqueteMovimiento+3, &Cliente::m.xy, 1);
}

bool Cliente::mandarMoviento()
{
    int errores;
    errores=send(Cliente::sock,Cliente::paqueteMovimiento,sizeof(Cliente::paqueteMovimiento),0);
    if(errores<0)
    {
        perror("Error: send");
        return false;
    }
    else
        return true;
}

void Cliente::armarPaquetePedirDado(int colorFicha)
{
    /*Variable para copiar los datos de la estructura*/
    uint16_t u16;
    uint8_t u8;

    /*Asignación de variables*/
    Cliente::pD.RV=21078;//0101001001010110 Firma del protocolo
    Cliente::pD.banderas=80;//0101 0000 Bandera Pedir Dado
    Cliente::pD.color=colorFicha;

    /*Copia de variables al paquete*/
    u16 = htons(Cliente::pD.RV);
    memcpy(Cliente::paqueteDado+0, &u16, 2);
    u8 = Cliente::pD.banderas;
    memcpy(Cliente::paqueteDado+2, &u8, 1);
    u8 = Cliente::pD.color;
    memcpy(Cliente::paqueteDado+3, &u8, 1);
}

bool Cliente::pedirDado()
{
    int errores;
    errores=send(Cliente::sock,Cliente::paqueteDado,sizeof(Cliente::paqueteDado),0);
    if(errores<0)
    {
        perror("Error: send");
        return false;
    }
    else
        return true;
}

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
    int resWrite = write(Cliente::sock, bufferPaquete, bytesEnviados.getSize());

    if (resWrite < 0)
    {
        //Error
    }

    //Liberamos el buffer
    delete [] bufferPaquete;
}

int Cliente::getSock()
{
    return Cliente::sock;
}
