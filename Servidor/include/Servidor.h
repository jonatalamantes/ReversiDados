#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "List.h"
#include "Partida.h"
#include "EstructuraHilo.h"

/**
* Clase con las funciones principales del servidor
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class Servidor
{
    private:
    ///Atributos
        List<Partida*> partidas;
        int idServidor;

    public:
    ///Constructor
        Servidor();

    ///Metodos de la clase
        
        /**
         * Subrutina para poner al servidor  a correr 
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void correr();

        /**
         * Devuelve el tipo de paquete que recibio el servidor
         * 
         * @param  bytes    Paquete recogido por el servidor
         * @return          Tipo de paquete segun el protocolo RV
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        int procesarHeader(List<uint8_t> bytes);

        /**
         * Devuelve las banderas para un tipo en el protocolo de RV
         * 
         * @param  tipo   Tipo de paquete a recobrar las banderas
         * @return        Un byte con las banderas segun el protocolo RV
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        uint8_t empaquetarByte(int tipo);

        /**
         * subrutina que se encarga de manipular a un nuevo cliente en el servidor
         * 
         * @param punteroPartida  Apuntador a EstructuraHilo con los datos de la partida
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         */
        void atenderCliente(EstructuraHilo* punteroPartida);
};

#endif // SERVIDOR_H
