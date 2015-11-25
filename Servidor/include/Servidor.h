#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "List.h"
#include "Partida.h"
#include "EstructuraHilo.h"

class Servidor
{
    private:
    //Atributos
        List<Partida*> partidas;
        int idServidor;
        int descriptorEspera;

    public:
    //Constructor
        Servidor();

    //Metodos de la clase
        void correr();
        int procesarHeader(List<uint8_t> bytes);
        uint8_t empaquetarByte(int tipo);
        void atenderCliente(EstructuraHilo* punteroPartida);
};

#endif // SERVIDOR_H
