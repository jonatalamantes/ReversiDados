#include <iostream>
#include <sstream>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iomanip>
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

#include "Servidor.h"
#include "EstructuraHilo.h"

using namespace std;

///Constructor
Servidor::Servidor()
{
    idServidor = 0;
}

/**
 * Devuelve el tipo de paquete que recibio el servidor
 * 
 * @param  bytes    Paquete recogido por el servidor
 * @return          Tipo de paquete segun el protocolo RV
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
int Servidor::procesarHeader(List<uint8_t> bytesRecibidos)
{
    if (bytesRecibidos[0] != 'R')
    {
        return -1;
    }

    if (bytesRecibidos[1] != 'V')
    {
        return -1;
    }

    uint8_t byte = bytesRecibidos[2];

    if ((byte & 0x80) == byte)
    {
        return 2;
    }
    else if ((byte & 0x20) == byte)
    {
        return 9;
    }
    else if ((byte & 0x40) == byte)
    {
        return 4;
    }
    else if ((byte & 0x50) == byte)
    {
        return 8;
    }
    else
    {
        return -1;
    }
}

/**
 * Devuelve las banderas para un tipo en el protocolo de RV
 * 
 * @param  tipo   Tipo de paquete a recobrar las banderas
 * @return        Un byte con las banderas segun el protocolo RV
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
uint8_t Servidor::empaquetarByte(int tipo)
{
    uint8_t byte = 0;

    if (tipo == 1)
    {
        byte = byte | 0x80;
    }
    else if (tipo == 3)
    {
        byte = byte | 0x10;
    }
    else if (tipo == 5)
    {
        byte = byte | 0x48;
    }
    else if (tipo == 6)
    {
        byte = byte | 0x40;
    }
    else if (tipo == 7)
    {
        byte = byte | 0x20;
    }

    return byte;
}

/**
 * subrutina que se encarga de manipular a un nuevo cliente en el servidor
 * 
 * @param punteroPartida  Apuntador a EstructuraHilo con los datos de la partida
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void Servidor::atenderCliente(EstructuraHilo* punteroPartida)
{
    char buffer[255];
    memset(buffer, 0, sizeof(buffer));
    bool fin = false;

    //Leemos el mensaje
    int res = read(punteroPartida->getDescriptorSocket(), buffer, 255);

    cout << "[" << res << ", " << punteroPartida->getPartida() << "]" << endl;
    cout.flush();

    if (res < 0)
    {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            cerr<< "Error al llamar a write: \"" <<  strerror(errno) << "\"" << endl;
        }
        else
        {
            cerr<< "Tendra que internarlo más tarde" << endl;
        }
    }
    else if (res == 0)
    {
        //Cerraron la conexion.
        fin = true;

        List<uint8_t> bytesEnviados;

        //Cabecera
        bytesEnviados.append('R');
        bytesEnviados.append('V');
        bytesEnviados.append(Servidor::empaquetarByte(7));

        //Razon de final de juego
        if (punteroPartida->getDescriptorSocket() == punteroPartida->getPartida()->getDescriptorJ1())
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
        }

        //Enviamos el paquete
        int resWrite = write(punteroPartida->getPartida()->getDescriptorJ1(), 
                             bufferPaquete, bytesEnviados.getSize());

        if (resWrite < 0)
        {
            //Error
        }

        resWrite = write(punteroPartida->getPartida()->getDescriptorJ2(), 
                         bufferPaquete, bytesEnviados.getSize());

        if (resWrite < 0)
        {
            //Error
        }

        //Liberamos el buffer
        delete [] bufferPaquete;

        //Señal de final de juego compartida
        punteroPartida->getPartida()->setTurnoJugador(7);
    }
    else
    {
        //Creamos la lista de los bytes recibidor
        List<uint8_t> bytesRecibidos;

        for (int i = 0; i < res; i++)
        {
            bytesRecibidos.append(buffer[i]);
        }

        //Leemos el paquete
        int tipo = Servidor::procesarHeader(bytesRecibidos);
        unsigned pos = 0;

        //Eliminamos los bytes del inicio y banderas
        try
        {
            bytesRecibidos.deleteForPosition(pos);
            bytesRecibidos.deleteForPosition(pos);
            bytesRecibidos.deleteForPosition(pos);
        }
        catch(ListException x)
        {
            cout << "El mensaje debe ser mayor a 3";
            fin = true;
        }

        cout << "< " << punteroPartida->getDescriptorSocket() << " >";
        cout << "< " << tipo << " >" << endl;

        if (tipo == 2) //Quiero Jugar
        {
            //Buscamos que soy, si J1 o J2
            if (punteroPartida->getPartida()->getNombreJ1() == "") //Soy J1
            {
                //Sacamos el nombre del jugador
                char nombreJ1[bytesRecibidos.getSize()];

                for (unsigned i = 0; i < bytesRecibidos.getSize(); i++)
                {
                    nombreJ1[i] = bytesRecibidos[i];
                }

                punteroPartida->getPartida()->setNombreJ1(nombreJ1);
                punteroPartida->getPartida()->setDescriptorJ1(punteroPartida->getDescriptorSocket());
                punteroPartida->getPartida()->setIniciada(true);
            }
            else //Soy J2
            {
                //Sacamos el nombre del jugador
                char nombreJ2[bytesRecibidos.getSize()];

                for (unsigned i = 0; i < bytesRecibidos.getSize(); i++)
                {
                    nombreJ2[i] = bytesRecibidos[i];
                }

                uint8_t inicia = 1;

                if (inicia == 0)
                {
                    punteroPartida->getPartida()->setTurnoJugador(-1);
                }
                else
                {
                    punteroPartida->getPartida()->setTurnoJugador(1);
                }

                punteroPartida->getPartida()->setNombreJ2(nombreJ2);
                punteroPartida->getPartida()->setDescriptorJ2(punteroPartida->getDescriptorSocket());

                //Paquete 1
                //Generamos el paquete de regreso
                char* bufferPaquete;

                //Generamos el paquete de regreso.
                List<uint8_t> bytesSaliente1;

                //Cabecera
                bytesSaliente1.append('R');
                bytesSaliente1.append('V');
                bytesSaliente1.append(Servidor::empaquetarByte(1));

                if (punteroPartida->getPartida()->getTurnoJugador() == -1)
                {
                    bytesSaliente1.append(0);
                }
                else
                {
                    bytesSaliente1.append(1);
                }

                //Nombre de oponente
                string nombre = punteroPartida->getPartida()->getNombreJ2();
                for (unsigned i = 0; i < nombre.size();  i++)
                {
                    bytesSaliente1.append(nombre[i]);
                }

                //Generamos el buffer del paquete;
                bufferPaquete = new char[bytesSaliente1.getSize()];

                for (unsigned i = 0; i < bytesSaliente1.getSize(); i++)
                {
                    bufferPaquete[i] = bytesSaliente1[i];
                }

                //Enviamos el paquete
                int r = write(punteroPartida->getPartida()->getDescriptorJ1(), 
                              bufferPaquete, bytesSaliente1.getSize());

                if (r < 0)
                {
                    //Error
                }

                //Liberamos el buffer
                delete [] bufferPaquete;

                //Inicializamos el tablero
                punteroPartida->getPartida()->getTablero()->inicializar();

                //Fichas iniciales
                punteroPartida->getPartida()->getTablero()->setFicha(4, 3, 1);
                punteroPartida->getPartida()->getTablero()->setFicha(4, 4, -1);
                punteroPartida->getPartida()->getTablero()->setFicha(3, 3, -1);
                punteroPartida->getPartida()->getTablero()->setFicha(3, 4, 1);

                //Paquete 2
                //Generamos el paquete de regreso
                bytesSaliente1.nullify();
                //Cabecera
                bytesSaliente1.append('R');
                bytesSaliente1.append('V');
                bytesSaliente1.append(Servidor::empaquetarByte(1));

                if (punteroPartida->getPartida()->getTurnoJugador() == -1)
                {
                    bytesSaliente1.append(16);
                }
                else
                {
                    bytesSaliente1.append(17);
                }

                //Nombre de oponente
                nombre = punteroPartida->getPartida()->getNombreJ1();
                for (unsigned i = 0; i < nombre.size();  i++)
                {
                    bytesSaliente1.append(nombre[i]);
                }

                //Generamos el buffer del paquete;
                bufferPaquete = new char[bytesSaliente1.getSize()];

                for (unsigned i = 0; i < bytesSaliente1.getSize(); i++)
                {
                    bufferPaquete[i] = bytesSaliente1[i];
                }

                //Enviamos el paquete
                r = write(punteroPartida->getPartida()->getDescriptorJ2(), 
                          bufferPaquete, bytesSaliente1.getSize());

                if (r < 0)
                {
                    //Error
                }

                //Liberamos el buffer
                delete [] bufferPaquete;

                //Inicializamos el tablero
                punteroPartida->getPartida()->setActive(true);
            }
        }
        else if (tipo == 8) //Pedir Dado
        {
            List<uint8_t> bytesEnviados;
            char* bufferPaquete;
            int jugador = 0; //0 sin jugador, 1 blancas, -1 negras;

            //Identificamos al jugador
            if (punteroPartida->getPartida()->getDescriptorJ1() == punteroPartida->getDescriptorSocket())
            {
                jugador = -1;
            }
            else
            {
                jugador = 1;
            }

            //Revisamos que se valido
            if (punteroPartida->getPartida()->getTurnoJugador() == jugador)
            {
                //Cabecera
                bytesEnviados.append('R');
                bytesEnviados.append('V');
                bytesEnviados.append(Servidor::empaquetarByte(3));

                int globalN = punteroPartida->getPartida()->getTablero()->turnoGlobalValido(jugador);

                //Generamos los dados si existe movimiento
                if (globalN != -1)
                {
                    //Revisamos que se pueda poner en alguna posicion
                    punteroPartida->getPartida()->getTablero()->tirarDados(globalN);
                }

                //Asignamos los dado
                bytesEnviados.append(punteroPartida->getPartida()->getTablero()->getDado(0));
                bytesEnviados.append(punteroPartida->getPartida()->getTablero()->getDado(1));
                bytesEnviados.append(punteroPartida->getPartida()->getTablero()->getDado(2));

                //Generamos el buffer del paquete;
                bufferPaquete = new char[bytesEnviados.getSize()];

                for (unsigned i = 0; i < bytesEnviados.getSize(); i++)
                {
                    bufferPaquete[i] = bytesEnviados[i];
                }

                //Enviamos el paquete
                int r = write(punteroPartida->getPartida()->getDescriptorJ1(), 
                              bufferPaquete, bytesEnviados.getSize());

                if (r < 0)
                {
                    //Error
                }

                r = write(punteroPartida->getPartida()->getDescriptorJ2(), 
                          bufferPaquete, bytesEnviados.getSize());

                if (r < 0)
                {
                    //Error
                }

                //Liberamos el buffer
                delete [] bufferPaquete;
            }
            else //Movimiento Invalido
            {
                bytesEnviados.append('R');
                bytesEnviados.append('V');
                bytesEnviados.append(Servidor::empaquetarByte(5));

                //Generamos el buffer del paquete;
                bufferPaquete = new char[bytesEnviados.getSize()];

                for (unsigned i = 0; i < bytesEnviados.getSize(); i++)
                {
                    bufferPaquete[i] = bytesEnviados[i];
                }

                //Enviamos el paquete
                int r = write(punteroPartida->getDescriptorSocket(), 
                              bufferPaquete, bytesEnviados.getSize());

                if (r < 0)
                {
                    //Error
                }

                //Liberamos el buffer
                delete [] bufferPaquete;
            }
        }
        else if (tipo == 4) //Movimiento
        {
            List<uint8_t> bytesEnviados;
            char* bufferPaquete;
            int jugador = 0; //0 sin jugador, 1 blancas, -1 negras;

            //Identificamos al jugador
            if (punteroPartida->getPartida()->getDescriptorJ1() == punteroPartida->getDescriptorSocket())
            {
                jugador = -1;
            }
            else
            {
                jugador = 1;
            }

            //Cabecera del paquete
            bytesEnviados.append('R');
            bytesEnviados.append('V');

            //Revisamos que se valido
            if (punteroPartida->getPartida()->getTurnoJugador() == jugador)
            {
                //Leemos el movimiento que intenta hacer
                uint8_t x = (bytesRecibidos[0] & 0xF0) >> 4;
                uint8_t y = (bytesRecibidos[0] & 0x0F);

                //Generamos los dados
                Tablero* t = punteroPartida->getPartida()->getTablero();

                if (t->validarMovimiento(x,y,jugador)) //Movimiento Valido
                {
                    t->colocarFicha(x,y,jugador);

                    //Fin de Juego
                    if (t->cantidadNegras() + t->cantidadBlancas() == 64 || 
                        t->cantidadBlancas() == 0 || t->cantidadNegras() == 0)
                    {
                        bytesEnviados.append(Servidor::empaquetarByte(7));

                        if (t->cantidadBlancas() == 0)
                        {
                            bytesEnviados.append(2);
                        }
                        else if (t->cantidadNegras() == 0)
                        {
                            bytesEnviados.append(1);
                        }
                        else
                        {
                            if (t->cantidadBlancas() > t->cantidadNegras())
                            {
                                bytesEnviados.append(1);
                            }
                            else if (t->cantidadNegras() > t->cantidadBlancas())
                            {
                                bytesEnviados.append(2);
                            }
                            else
                            {
                                bytesEnviados.append(0);
                            }
                        }

                        //Señal de final de juego compartida
                        punteroPartida->getPartida()->setTurnoJugador(7);

                        fin = true;
                    }
                    else //Movimiento Valido sin fin de juego
                    {
                        //Inicializamos los dados
                        t->inicializarDados();

                        short turno = punteroPartida->getPartida()->getTurnoJugador();

                        if (t->turnoGlobalValido(turno*(-1)) != -1) //Oponente tiene turno
                        {
                            //Empacamos cambio dem ovimiento
                            bytesEnviados.append(Servidor::empaquetarByte(6));

                            //Empacamos el color del siguiente turno
                            if (turno*(-1) == -1) //cambio a negras
                            {
                                bytesEnviados.append(1);
                            }
                            else
                            {
                                bytesEnviados.append(0);
                            }

                            punteroPartida->getPartida()->setTurnoJugador(turno*(-1));

                            //Empacamos el tablero
                            uint128_t tableroByte = t->tableroToBytes(*t);

                            for (int i = 0; i < 16; i++)
                            {
                                bytesEnviados.append(tableroByte.byte[i]);
                            }
                        }
                        else if (t->turnoGlobalValido(turno) != -1) //Oponente no tiene turno
                        {
                            //Empacamos cambio dem ovimiento
                            bytesEnviados.append(Servidor::empaquetarByte(6));

                            //Empacamos el color del siguiente turno
                            if (turno == -1) //cambio a negras
                            {
                                bytesEnviados.append(1);
                            }
                            else
                            {
                                bytesEnviados.append(0);
                            }

                            //Empacamos el tablero
                            uint128_t tableroByte = t->tableroToBytes(*t);

                            for (int i = 0; i < 16; i++)
                            {
                                bytesEnviados.append(tableroByte.byte[i]);
                            }
                        }
                        else //No hay turno (tablas)
                        {
                            bytesEnviados.append(Servidor::empaquetarByte(7));

                            //Señal de final de juego compartida
                            punteroPartida->getPartida()->setTurnoJugador(7);

                            fin = true;
                        }
                    }

                    //Generamos el buffer del paquete;
                    bufferPaquete = new char[bytesEnviados.getSize()];

                    for (unsigned i = 0; i < bytesEnviados.getSize(); i++)
                    {
                        bufferPaquete[i] = bytesEnviados[i];
                        //cout << (int)bufferPaquete[i] << endl;
                    }

                    //Enviamos el paquete
                    int r = write(punteroPartida->getPartida()->getDescriptorJ1(), 
                                  bufferPaquete, bytesEnviados.getSize());

                    if (r < 0)
                    {
                        //Error
                    }

                    r = write(punteroPartida->getPartida()->getDescriptorJ2(), 
                              bufferPaquete, bytesEnviados.getSize());

                    if (r < 0)
                    {
                        //Error
                    }

                    //Liberamos el buffer
                    delete [] bufferPaquete;
                }
                else //Movimiento Invalido
                {
                    bytesEnviados.append(Servidor::empaquetarByte(5));

                    //Generamos el buffer del paquete;
                    bufferPaquete = new char[bytesEnviados.getSize()];

                    for (unsigned i = 0; i < bytesEnviados.getSize(); i++)
                    {
                        bufferPaquete[i] = bytesEnviados[i];
                    }

                    //Enviamos el paquete
                    int r = write(punteroPartida->getDescriptorSocket(), 
                                  bufferPaquete, bytesEnviados.getSize());

                    if (r < 0)
                    {
                        //Error
                    }

                    //Liberamos el buffer
                    delete [] bufferPaquete;
                }
            }
            else //Movimiento Invalido
            {
                bytesEnviados.append(Servidor::empaquetarByte(5));

                //Generamos el buffer del paquete;
                bufferPaquete = new char[bytesEnviados.getSize()];

                for (unsigned i = 0; i < bytesEnviados.getSize(); i++)
                {
                    bufferPaquete[i] = bytesEnviados[i];
                }

                //Enviamos el paquete
                int r = write(punteroPartida->getDescriptorSocket(), 
                              bufferPaquete, bytesEnviados.getSize());

                if (r < 0)
                {
                    //Error
                }

                //Liberamos el buffer
                delete [] bufferPaquete;
            }
        }
        else if (tipo == 9) //Fin de Juego
        {
            //Pido Fin de Juego
            fin = true;

            List<uint8_t> bytesEnviados;

            //Cabecera
            bytesEnviados.append('R');
            bytesEnviados.append('V');
            bytesEnviados.append(Servidor::empaquetarByte(7));

            //Razon de final de juego
            if (punteroPartida->getDescriptorSocket() == punteroPartida->getPartida()->getDescriptorJ1())
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
            }

            //Enviamos el paquete
            int resWrite = write(punteroPartida->getPartida()->getDescriptorJ1(), 
                                 bufferPaquete, bytesEnviados.getSize());

            if (resWrite < 0)
            {
                //Error
            }

            resWrite = write(punteroPartida->getPartida()->getDescriptorJ2(), 
                             bufferPaquete, bytesEnviados.getSize());

            if (resWrite < 0)
            {
                //Error
            }

            //Liberamos el buffer
            delete [] bufferPaquete;

            //Señal de final de juego compartida
            punteroPartida->getPartida()->setTurnoJugador(7);
        }

    }

    if (fin || punteroPartida->getPartida() == NULL || 
        punteroPartida->getPartida()->getTurnoJugador() == 7)
    {
        if (punteroPartida->getPartida() != NULL)
        {
            punteroPartida->getPartida()->setFinalizada(true);
        }
    }
}

/**
 * Subrutina para poner al servidor  a correr 
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void Servidor::correr()
{
    //Creamos las variables
    int res, puerto = 7777;

    //Creamos la estructura del servidor
    struct sockaddr_storage servidor;
    struct sockaddr_storage cliente;
    struct sockaddr_in6 *addr_in6;
    socklen_t tam_sock = sizeof(cliente);

    //Creamos el socket
    idServidor = socket(AF_INET6, SOCK_STREAM, 0);

    if (idServidor < 0)
    {
        cerr<< "Error al llamar a socket: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    srand(time(NULL));

    //Rellenamos los datos con valor 0
    memset(&servidor, 0, sizeof(servidor));
    memset(&cliente, 0, sizeof(cliente));

    //Completamos los datos del servidor
    addr_in6    = (struct sockaddr_in6*)&servidor;
    addr_in6->sin6_family    = AF_INET6;
    addr_in6->sin6_port      = htons(puerto);
    addr_in6->sin6_addr      = in6addr_any;

    //Asociamos con bind a la direcion a escuchar
    res = bind(idServidor, (struct sockaddr*)&servidor, sizeof(servidor));

    if (res < 0)
    {
        cerr<< "Error al llamar a bind: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    //ponemos a escuchar al socket
    res = listen(idServidor, 10);

    if (res < 0)
    {
        cerr<< "Error al llamar a listen: \"" <<  strerror(errno) << "\"" << endl;
        exit(-1);
    }

    //Creamos la estructura del Poll
    int ultimaCantidad = 1;
    struct pollfd* descritoresSocket = new pollfd[ultimaCantidad];
    descritoresSocket[0].fd = idServidor;
    descritoresSocket[0].events = POLLIN | POLLRDNORM;

    int n;
    int gtres;
    string msj = "Hola desde un servidor TCP/IP";

    struct timeval tv;
    struct timezone tz;

    gtres = gettimeofday(&tv, &tz);

    double tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);
    double ptiempo = tiempo;

    Partida *w;

    while (true)
    {
        //Obtenemos la hora actual con los milisegundos
        gtres = gettimeofday(&tv, &tz);

        if (gtres < 0)
        {
            //cerr<< "Error al llamar a gettimeofday: \"" <<  strerror(errno) << "\"" << endl;
        }
        else
        {
            //Transformamos a un número doble la hora
            tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);

            for (unsigned i = 0; i < partidas.getSize(); i++)
            {
                if ((partidas[i]->getIniciada() && not partidas[i]->getActive() &&
                     tiempo - partidas[i]->getTiempoCreado() >  15000000)
                    || partidas[i]->getFinalizada())
                {
                    //Eliminamos a los descriptores de Poll
                    if (partidas[i]->getDescriptorJ1() != 0)
                    {
                        //Cerramos los descriptores
                        close(partidas[i]->getDescriptorJ1());

                        //Creamos una estructura provicional con el tamaño del nuevo poll
                        struct pollfd *provicional = new pollfd[ultimaCantidad-1];

                        //Buscamos el descriptor en la estructura de poll y no lo insertamos
                        bool encontrado = false;
                        for (int j = 0; j < ultimaCantidad; j++)
                        {
                            if (encontrado)
                            {
                                provicional[j-1] = descritoresSocket[j];
                            }
                            else
                            {
                                if (descritoresSocket[j].fd == partidas[i]->getDescriptorJ1())
                                {
                                    encontrado = true;
                                }
                                else
                                {
                                    provicional[j] = descritoresSocket[j];
                                }
                            }
                        }

                        if (encontrado)
                        {
                            delete [] descritoresSocket;
                            descritoresSocket = provicional;
                            ultimaCantidad--;
                        }
                    }

                    //Recuperamos el descriptor del jugador 2
                    if (partidas[i]->getDescriptorJ2() != 0)
                    {
                        //Cerramos el descriptor
                        close(partidas[i]->getDescriptorJ2());

                        //Creamos una estructura provicional con el tamaño del nuevo poll
                        struct pollfd *provicional = new pollfd[ultimaCantidad-1];

                        //Buscamos el descriptor en la estructura de poll y no lo insertamos
                        bool encontrado = false;
                        for (int j = 0; j < ultimaCantidad; j++)
                        {
                            if (encontrado)
                            {
                                provicional[j-1] = descritoresSocket[j];
                            }
                            else
                            {
                                if (descritoresSocket[j].fd == partidas[i]->getDescriptorJ2())
                                {
                                    encontrado = true;
                                }
                                else
                                {
                                    provicional[j] = descritoresSocket[j];
                                }
                            }
                        }

                        if (encontrado)
                        {
                            delete [] descritoresSocket;
                            descritoresSocket = provicional;
                            ultimaCantidad--;
                        }
                    }

                    //Eliminamos la partida
                    delete partidas[i];
                    partidas.deleteForPosition(i);
                }
            }

            //Imprimimos un punto si han pasado 500 milisegundos
            if (tiempo - ptiempo > 500000)
            {
                cout << '.';
                cout.flush();
                ptiempo = tiempo;
            }
        }

        n = poll(descritoresSocket, ultimaCantidad, 75);

        if (n < 0)
        {
            //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
        }
        else if (n > 0)
        {
            for (int i = 0; i < ultimaCantidad; i++)
            {
                if ((descritoresSocket[i].revents & POLLERR) == POLLERR)
                {
                    //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
                }
                else if ((descritoresSocket[i].revents & POLLHUP) == POLLHUP)
                {
                    //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
                }
                else if ((descritoresSocket[i].revents & POLLIN) == POLLIN || 
                         (descritoresSocket[i].revents & POLLRDNORM) == POLLRDNORM)
                {
                    //Evento en el servidor principal
                    if (descritoresSocket[i].fd == idServidor)
                    {
                        //Aceptamos un nuevo cliente
                        int idCliente = accept(idServidor, (struct sockaddr *)&cliente, &tam_sock);

                        if (idCliente > 0)
                        {
                            //Buscamos el Cliente que nos esta tratando de escribir
                            EstructuraHilo* estructura = new EstructuraHilo();

                            int partida = -1;
                            for (unsigned j = 0; j < partidas.getSize(); j++)
                            {
                                if (partidas[j]->getDescriptorJ2() == 0)
                                {
                                    partida = j;
                                    break;
                                }
                            }

                            //No hay partida activa para unirse
                            if (partida == -1)
                            {
                                //Creamos una partida
                                w = new Partida();
                                w->setIniciada(true);
                                w->setTiempoCreado(tiempo);
                                partidas.append(w);

                                partida = partidas.getSize() - 1;
                            }

                            //Agregamos el cliente a Poll
                            struct pollfd provicional[ultimaCantidad];

                            //copiamos los descriptores al arreglo provicional
                            for (int j = 0; j < ultimaCantidad; j++)
                            {
                                provicional[j] = descritoresSocket[j];
                            }

                            //Aumentamos el tamaño del arreglo
                            ultimaCantidad++;
                            delete [] descritoresSocket;
                            descritoresSocket = new pollfd[ultimaCantidad];

                            //Copiamos los descriptores que teniamos
                            for (int k = 0; k < ultimaCantidad-1; k++)
                            {
                                descritoresSocket[k] = provicional[k];
                            }

                            //Agregamos el nuevo descriptor
                            descritoresSocket[ultimaCantidad-1].fd = idCliente;
                            descritoresSocket[ultimaCantidad-1].events = POLLIN | POLLRDNORM;

                            //Setteamos la estructura
                            estructura->setPartida(partidas[partida]);
                            estructura->setDescriptorSocket(idCliente);

                            atenderCliente(estructura);
                            delete estructura;
                        }
                    }
                    else //Evento en un cliente
                    {
                        //Buscamos el Cliente que nos esta tratando de escribir
                        EstructuraHilo *estructura = new EstructuraHilo();

                        //buscar el descriptore las partidas
                        int partida = -1;
                        for (unsigned j = 0; j < partidas.getSize(); j++)
                        {
                            if (partidas[j]->getDescriptorJ1() == descritoresSocket[i].fd ||
                                partidas[j]->getDescriptorJ2() == descritoresSocket[i].fd )
                            {
                                partida = j;
                                break;
                            }
                        }

                        if (partida != -1)
                        {
                            estructura->setPartida(partidas[partida]);
                            estructura->setDescriptorSocket(descritoresSocket[i].fd);

                            atenderCliente(estructura);
                        }

                        delete estructura;
                    }
                }
            }
        }
    }

    //Cerramos el servidor
    close(idServidor);
}

