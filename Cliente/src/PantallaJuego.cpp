#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include "PantallaJuego.h"
#include "Constantes.h"
#include "stringConvert.h"
#include "Cliente.h"

using namespace std;

///Constructor
PantallaJuego::PantallaJuego(SDL_Surface* v, FuncionesPantalla* fp)
{
    srand(time(NULL));

    PantallaJuego::posibleX = -1;
    PantallaJuego::posibleY = -1;

    PantallaJuego::ventana = v;
    PantallaJuego::f = fp;

    if (rand() % 2 == 0)
    {
        PantallaJuego::turnoJugador = -1;
        PantallaJuego::colorJugador = -1;
    }
    else
    {
        PantallaJuego::turnoJugador = 1;
        PantallaJuego::colorJugador = 1;
    }
}

///Setters
void PantallaJuego::setNombreJugador1(string j)
{
    PantallaJuego::nombreJugador1 = j;
}

void PantallaJuego::setNombreJugador2(string j)
{
    PantallaJuego::nombreJugador2 = j;
}

/**
 * Inicializa la ventana y el tablero
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaJuego::inicializar()
{
    srand(time(NULL));

    PantallaJuego::posibleX = -1;
    PantallaJuego::posibleY = -1;

    if (rand() % 2 == 0)
    {
        PantallaJuego::colorJugador = 1;
        PantallaJuego::turnoJugador = 1;
    }
    else
    {
        PantallaJuego::colorJugador = -1;
        PantallaJuego::turnoJugador = -1;
    }

    //Fichas iniciales
    PantallaJuego::tablero.inicializar();

    PantallaJuego::tablero.setFicha(4, 3, 1);
    PantallaJuego::tablero.setFicha(4, 4, -1);
    PantallaJuego::tablero.setFicha(3, 3, -1);
    PantallaJuego::tablero.setFicha(3, 4, 1);
}

/**
 * Crea una animacion para los dados
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaJuego::animacionDado()
{
    SDL_Rect rectangulo;
    Uint32 color = SDL_MapRGB(PantallaJuego::ventana->format, 170,170,170); //blanco
    short tamCuadro = 270;

    short dado1 = PantallaJuego::tablero.getDado(0);
    short dado2 = PantallaJuego::tablero.getDado(1);
    short dado3 = PantallaJuego::tablero.getDado(2);

    //Inicializamos todo y dibujamos el tablero
    PantallaJuego::tablero.inicializarDados();
    dibujarTablero();

    //Dibujamos un cuadrado gris grande en medio de la pantalla
    rectangulo.x = ((TAM_CUADRO*9)/2)-(tamCuadro/2);
    rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
    rectangulo.w = tamCuadro;
    rectangulo.h = tamCuadro;

    SDL_FillRect(PantallaJuego::ventana, &rectangulo, color);

    //Dibujamos un cuadrado blanco mas pequeño que el anterior en medio de la pantalla
    color = SDL_MapRGB(PantallaJuego::ventana->format, 255,255,255); //blanco
    tamCuadro = 250;

    rectangulo.x = ((TAM_CUADRO*9)/2)-(tamCuadro/2);
    rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
    rectangulo.w = tamCuadro;
    rectangulo.h = tamCuadro;

    SDL_FillRect(PantallaJuego::ventana, &rectangulo, color);

    //Actualizamos el cuadro
    SDL_UpdateRect(PantallaJuego::ventana, 0, 0, 0, 0);

    //Establecemos las variables para el tiempo
    struct timeval tv;
    struct timezone tz;

    int gtres = gettimeofday(&tv, &tz), i = 0;

    double tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);
    double ptiempo = tiempo;
    bool terminar = false;

    stringConvert fx;

    while(!terminar)
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

            //Imprimimos un punto si han pasado 75 milisegundos
            if (tiempo - ptiempo > 75000)
            {
                //Cargamos la imagen en relacion del numero del 1-5
                string cad = "img/animacionDado";
                cad = cad + fx.intToStr((i % 5) + 1) + ".bmp";

                rectangulo.x = ((TAM_CUADRO*9)/2)+125-(tamCuadro/2);
                rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
                rectangulo.w = tamCuadro;
                rectangulo.h = tamCuadro;

                f->cargarImagen(PantallaJuego::ventana, cad.c_str(), rectangulo.x, rectangulo.y);

                rectangulo.x = ((TAM_CUADRO*9)/2)+62-(tamCuadro/2);
                rectangulo.y = ((TAM_CUADRO*12)/2)+125-(tamCuadro/2);
                rectangulo.w = tamCuadro;
                rectangulo.h = tamCuadro;

                f->cargarImagen(PantallaJuego::ventana, cad.c_str(), rectangulo.x, rectangulo.y);

                rectangulo.x = ((TAM_CUADRO*9)/2)-(tamCuadro/2);
                rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
                rectangulo.w = tamCuadro;
                rectangulo.h = tamCuadro;

                f->cargarImagen(PantallaJuego::ventana, cad.c_str(), rectangulo.x, rectangulo.y);

                SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);

                ptiempo = tiempo;
                i++;
            }
        }

        if (i == 21)
        {
            terminar = true;
        }
    }

    //Cargamos el dado y ponemos el numero
    rectangulo.x = ((TAM_CUADRO*9)/2)+125-(tamCuadro/2);
    rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
    rectangulo.w = tamCuadro;
    rectangulo.h = tamCuadro;

    f->escribirPalabra(PantallaJuego::ventana, fx.intToStr(dado2).c_str(),
                      rectangulo.x+56, rectangulo.y+45, "KeepCalm", 32, 224, 7, 43); //Rojo

    rectangulo.x = ((TAM_CUADRO*9)/2)+62-(tamCuadro/2);
    rectangulo.y = ((TAM_CUADRO*12)/2)+125-(tamCuadro/2);
    rectangulo.w = tamCuadro;
    rectangulo.h = tamCuadro;

    f->escribirPalabra(PantallaJuego::ventana, fx.intToStr(dado3).c_str(),
                      rectangulo.x+56, rectangulo.y+45, "KeepCalm", 32, 224, 7, 43); //Rojo

    rectangulo.x = ((TAM_CUADRO*9)/2)-(tamCuadro/2);
    rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
    rectangulo.w = tamCuadro;
    rectangulo.h = tamCuadro;

    f->escribirPalabra(PantallaJuego::ventana, fx.intToStr(dado1).c_str(),
                      rectangulo.x+56, rectangulo.y+45, "KeepCalm", 32, 224, 7, 43); //Rojo

    SDL_UpdateRect(PantallaJuego::ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);

    //Pausamos y agregamos el dado al tablero
    sleep(1);
    PantallaJuego::tablero.setDado(0, dado1);
    PantallaJuego::tablero.setDado(1, dado2);
    PantallaJuego::tablero.setDado(2, dado3);
}

void PantallaJuego::ponerAnimacion(Tablero antiguo, short color, short lastX, short lastY)
{
    int cnn = PantallaJuego::tablero.cantidadNegras();
    int cbn = PantallaJuego::tablero.cantidadBlancas();

    //Buscamos condiciones de fin de juego
    if ( (cnn + cbn == 64) || (cnn == 0) || (cbn == 0) )
    {
        Fin = true;
        dibujarTablero();
        sleep(1);

        if (cnn > cbn)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    tablero.setFicha(i,j, 1);
                }
            }
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    tablero.setFicha(i,j, -1);
                }
            }
        }

        dibujarTablero();
    }
    else
    {
        //Recogemos el tablero
        Tablero nuevo = PantallaJuego::tablero;

        //Cargamos el tablero antiguo para cargar la animacion junto con el ultimo movimiento
        PantallaJuego::tablero = antiguo;
        PantallaJuego::tablero.setFicha(lastX -1, lastY-1,color);

        //Dibujamos
        dibujarTablero();
        sleep(1);

        //Establecemos el nuevo tablero
        PantallaJuego::tablero = nuevo;
        dibujarTablero();

        //Encontramos el color del ultimo movimiento
        char fichaC;

        if (color == -1)
        {
            fichaC = 'N';
        }
        else
        {
            fichaC = 'B';
        }

        //Cargamos la ficha temporal
        f->cargarFicha(PantallaJuego::ventana, posibleX, posibleY, 'G', "0");

        //Por cada ficha del tablero diferencte cargamos la animacion
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (!(i+1 == lastX && j+1 == lastY))
                {
                    if (PantallaJuego::tablero.getFicha(i,j) != antiguo.getFicha(i,j))
                    {
                        f->cargarFicha(PantallaJuego::ventana, i+1, j+1, fichaC, "1");
                    }
                }
            }
        }

        //Actualizamos el tablero
        SDL_UpdateRect(PantallaJuego::ventana, 0, 0, 0, 0);

        sleep(1);
    }
}

/**
 * Dibuja la ventana del tablero
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaJuego::dibujarTablero()
{
    int iniX, iniY, maxX, maxY;
    SDL_Rect rectangulo;
    stringConvert strc;

    Uint32 color = SDL_MapRGB(PantallaJuego::ventana->format, 0,0,0); //negro

    //Rellenamos de negro el tablero
    SDL_FillRect(PantallaJuego::ventana, NULL, color);

    //Dibuja la parte cafe del tablero
    iniX = 0;
    iniY = 2;
    maxX = 9;
    maxY = 11;
    color = SDL_MapRGB(PantallaJuego::ventana->format, 71, 29, 11); //cafe tablero

    for (int i = iniX; i < maxX; i++)
    {
        for (int j = iniY; j < maxY; j++)
        {
            rectangulo.x = TAM_CUADRO*i;
            rectangulo.y = TAM_CUADRO*j;
            rectangulo.w = (TAM_CUADRO*maxX)-(TAM_CUADRO*i);
            rectangulo.h = (TAM_CUADRO*maxY)-(TAM_CUADRO*j);

            SDL_FillRect(PantallaJuego::ventana, &rectangulo, color);
        }
    }

    //Dibuja la parte verde del tablero
    iniX = 1;
    iniY = 3;
    maxX = 9;
    maxY = 11;
    color = SDL_MapRGB(PantallaJuego::ventana->format, 6, 112, 1); //verde tablero

    for (int i = iniX; i < maxX; i++)
    {
        for (int j = iniY; j < maxY; j++)
        {
            rectangulo.x = TAM_CUADRO*i;
            rectangulo.y = TAM_CUADRO*j;
            rectangulo.w = (TAM_CUADRO*maxX)-(TAM_CUADRO*i);
            rectangulo.h = (TAM_CUADRO*maxY)-(TAM_CUADRO*j);

            SDL_FillRect(PantallaJuego::ventana, &rectangulo, color);
        }
    }

    //Dibuja las lineas del tablero
    color = SDL_MapRGB(PantallaJuego::ventana->format, 200, 200, 200); //gris

    for (int i = 0; i < TAM_CUADRO*9; i+=TAM_CUADRO)
    {
        rectangulo.x = i;
        rectangulo.y = TAM_CUADRO*2;
        rectangulo.w = TAM_LINEA;
        rectangulo.h = (TAM_CUADRO*12)-(TAM_CUADRO*3);

        SDL_FillRect(PantallaJuego::ventana, &rectangulo, color);
    }

    rectangulo.x = TAM_CUADRO*9;
    SDL_FillRect(PantallaJuego::ventana, &rectangulo, color);

    for (int i = TAM_CUADRO*2; i < TAM_CUADRO*12; i+=TAM_CUADRO)
    {
        rectangulo.x = 0;
        rectangulo.y = i;
        rectangulo.w = (TAM_CUADRO*9)+TAM_LINEA;
        rectangulo.h = TAM_LINEA;

        SDL_FillRect(PantallaJuego::ventana, &rectangulo, color);
    }

    //Dibuja los números en el tablero
    f->escribirPalabra(ventana, "1", 10+TAM_CUADRO*1, 7+TAM_CUADRO*2, "NinjaNaruto", 28);
    f->escribirPalabra(ventana, "2", 10+TAM_CUADRO*2, 7+TAM_CUADRO*2, "NinjaNaruto", 28);
    f->escribirPalabra(ventana, "3", 10+TAM_CUADRO*3, 7+TAM_CUADRO*2, "NinjaNaruto", 28);
    f->escribirPalabra(ventana, "4", 10+TAM_CUADRO*4, 7+TAM_CUADRO*2, "NinjaNaruto", 28);
    f->escribirPalabra(ventana, "5", 10+TAM_CUADRO*5, 7+TAM_CUADRO*2, "NinjaNaruto", 28);
    f->escribirPalabra(ventana, "6", 10+TAM_CUADRO*6, 7+TAM_CUADRO*2, "NinjaNaruto", 28);
    f->escribirPalabra(ventana, "7", 10+TAM_CUADRO*7, 7+TAM_CUADRO*2, "NinjaNaruto", 28);
    f->escribirPalabra(ventana, "8", 10+TAM_CUADRO*8, 7+TAM_CUADRO*2, "NinjaNaruto", 28);

    f->escribirPalabra(PantallaJuego::ventana, "1", 10, 7+TAM_CUADRO*3, "NinjaNaruto", 28);
    f->escribirPalabra(PantallaJuego::ventana, "2", 10, 7+TAM_CUADRO*4, "NinjaNaruto", 28);
    f->escribirPalabra(PantallaJuego::ventana, "3", 10, 7+TAM_CUADRO*5, "NinjaNaruto", 28);
    f->escribirPalabra(PantallaJuego::ventana, "4", 10, 7+TAM_CUADRO*6, "NinjaNaruto", 28);
    f->escribirPalabra(PantallaJuego::ventana, "5", 10, 7+TAM_CUADRO*7, "NinjaNaruto", 28);
    f->escribirPalabra(PantallaJuego::ventana, "6", 10, 7+TAM_CUADRO*8, "NinjaNaruto", 28);
    f->escribirPalabra(PantallaJuego::ventana, "7", 10, 7+TAM_CUADRO*9, "NinjaNaruto", 28);
    f->escribirPalabra(PantallaJuego::ventana, "8", 10, 7+TAM_CUADRO*10, "NinjaNaruto", 28);

    //Escribe nombre Jugadores
    if (PantallaJuego::turnoJugador == PantallaJuego::colorJugador)
    {
        f->cargarImagen(PantallaJuego::ventana, "img/btnJugadorA.bmp", 5, 3);
        f->cargarImagen(PantallaJuego::ventana, "img/btnJugadorB.bmp", 5, TAM_CUADRO+3);
    }
    else
    {
        f->cargarImagen(PantallaJuego::ventana, "img/btnJugadorB.bmp", 5, 3);
        f->cargarImagen(PantallaJuego::ventana, "img/btnJugadorA.bmp", 5, TAM_CUADRO+3);
    }

    f->escribirPalabra(ventana, "Jugador A: " + nombreJugador1, 25, 0, "HelveticaStandar", 16);
    f->escribirPalabra(ventana, "Jugador B: "+nombreJugador2,25,TAM_CUADRO, "HelveticaStandar", 16);

    //Cargamos los tres octagonos
    short dado;

    for (int i = 0; i < 3; i++)
    {
        dado = PantallaJuego::tablero.getDado(i);

        if (dado == 0)
        {
            f->cargarImagen(ventana, "img/octagonoVacio.bmp", TAM_CUADRO*(6+i)-10, TAM_CUADRO/2);
        }
        else
        {
            f->cargarImagen(ventana, "img/octagonoLleno.bmp", TAM_CUADRO*(6+i)-10, TAM_CUADRO/2);
            f->escribirPalabra(PantallaJuego::ventana, strc.intToStr(dado), TAM_CUADRO*(6+i)+4,
                               TAM_CUADRO/2+13, "KeepCalm", 15);
        }
    }

    //Boton de abajo
    if (Fin)
    {
        f->cargarImagen(PantallaJuego::ventana, "img/btnOn.bmp", TAM_CUADRO*6+10, TAM_CUADRO*11+10);
        f->escribirPalabra(PantallaJuego::ventana, "c e r r a r", TAM_CUADRO*6+27,
                           TAM_CUADRO*11+15, "CrownTitle", 22);
    }
    else
    {
        if (dadosSet == false || turnoJugador != colorJugador)
        {
            f->cargarImagen(ventana, "img/btnOn.bmp", TAM_CUADRO*6+10, TAM_CUADRO*11+10);
            f->escribirPalabra(ventana, "tirar dados", TAM_CUADRO*6+19, TAM_CUADRO*11+15,
                               "CrownTitle", 22);
        }
        else
        {
            f->cargarImagen(ventana, "img/btnOff.bmp", TAM_CUADRO*6+10, TAM_CUADRO*11+10);
        }
    }

    //Estado del juego
    int cnn = PantallaJuego::tablero.cantidadBlancas();
    int cbn = PantallaJuego::tablero.cantidadNegras();

    string estadoJuego = "Blancas: " + strc.intToStr(cbn) + " | Negras: " + strc.intToStr(cnn);

    if (cnn + cbn == 64 || tablas)
    {
        if (cnn == cbn)
        {
            estadoJuego = "Empate";
            dibujarReversiChan(9);
        }
        else if (cbn > cnn)
        {
            estadoJuego = "Gana Blancas";
        }
        else
        {
            estadoJuego = "Gana Negras";
        }
    }
    else if (cnn == 0)
    {
        estadoJuego = "Gana Blancas";
    }
    else if (cbn == 0)
    {
        estadoJuego = "Gana Negras";
    }

    if (noTurno)
    {
        noTurno = false;
        estadoJuego = "No tiene movimiento";
    }

    f->escribirPalabra(ventana, estadoJuego, 15, TAM_CUADRO*11+15, "KeepCalm", 15, 255, 255, 0);

    //Cargamos las fichas del tablero
    short int colorFicha;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            colorFicha = PantallaJuego::tablero.getFicha(i,j);

            if (colorFicha < 0)
            {
                f->cargarFicha(PantallaJuego::ventana, i+1, j+1, 'N', "0");
            }
            else if (colorFicha > 0)
            {
                f->cargarFicha(PantallaJuego::ventana, i+1, j+1, 'B', "0");
            }
        }
    }

    //Revisamos que exista un movimiento posible, de ser así lo ponemos con una ficha gris
    if (posibleX != -1 && posibleY != -1)
    {
        f->cargarFicha(PantallaJuego::ventana, posibleX, posibleY, 'G', "0");
    }

    //Actualizamos la superficie del tablero
    SDL_UpdateRect(PantallaJuego::ventana, 0, 0, 0, 0);

    if (cnn + cbn == 64 || tablas)
    {
        if (cnn == cbn)
        {
            dibujarReversiChan(9);
        }
        else if (cbn > cnn)
        {
            if (colorJugador != -1)
            {
                dibujarReversiChan(7);
            }
            else
            {
                dibujarReversiChan(8);
            }
        }
        else
        {
            if (colorJugador != -1)
            {
                dibujarReversiChan(8);
            }
            else
            {
                dibujarReversiChan(7);
            }
        }
    }
    else if (cnn == 0)
    {
        if (colorJugador != -1)
        {
            dibujarReversiChan(7);
        }
        else
        {
            dibujarReversiChan(8);
        }
    }
    else if (cbn == 0)
    {
        if (colorJugador != -1)
        {
            dibujarReversiChan(8);
        }
        else
        {
            dibujarReversiChan(7);
        }
    }
}

/**
 * Dibuja a Reversi-chan segun el estado (ver imagenes)
 *
 * @param estado [description]
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaJuego::dibujarReversiChan(int estado)
{
    //Marco de la miniventana
    SDL_Rect rectangulo;
    uint32_t color = SDL_MapRGB(ventana->format, 255, 255, 255); //Blanco

    rectangulo.x = 90;
    rectangulo.y = 110;
    rectangulo.w = 170;
    rectangulo.h = 255;

    SDL_FillRect(ventana, &rectangulo, color);

    SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);

    //Color interno de la miniventana
    color = SDL_MapRGB(ventana->format, 255, 150, 0); //Naranja

    rectangulo.x = 100;
    rectangulo.y = 120;
    rectangulo.w = 150;
    rectangulo.h = 235;

    SDL_FillRect(ventana, &rectangulo, color);
    SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);

    SDL_FillRect(ventana, &rectangulo, color);

    if (estado == 1)
    {
        f->cargarImagen(ventana, "img/ReversiChan1.png", rectangulo.x, rectangulo.y);
        f->escribirPalabra(ventana, "Buscando", rectangulo.x + 25, rectangulo.y + 190, "Arcarde",
                           18, 255,255,255);
        f->escribirPalabra(ventana, "Contrincante", rectangulo.x + 5, rectangulo.y + 210, "Arcarde",
                           18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 2)
    {
        f->cargarImagen(ventana, "img/ReversiChan2.png", rectangulo.x + 15, rectangulo.y);
        f->escribirPalabra(ventana, "Buscando", rectangulo.x + 25, rectangulo.y + 190, "Arcarde",
                           18, 255,255,255);
        f->escribirPalabra(ventana, "Contrincante", rectangulo.x + 5, rectangulo.y + 210, "Arcarde",
                           18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 3)
    {
        f->cargarImagen(ventana, "img/ReversiChan3.png", rectangulo.x, rectangulo.y);
        f->escribirPalabra(ventana, "Buscando", rectangulo.x + 25, rectangulo.y + 190, "Arcarde",
                           18, 255,255,255);
        f->escribirPalabra(ventana, "Contrincante", rectangulo.x + 5, rectangulo.y + 210, "Arcarde",
                           18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 4)
    {
        //Imprimimos la imagen necesaria
        f->cargarImagen(ventana, "img/ReversiChan4.png", rectangulo.x+10, rectangulo.y);
        f->escribirPalabra(ventana, "Oponente", rectangulo.x + 35, rectangulo.y + 190, "Arcarde",
                           16, 0,0,0);
        f->escribirPalabra(ventana, "No Encontrado", rectangulo.x + 5, rectangulo.y + 210,
                           "Arcarde", 16, 0,0,0);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 5)
    {
        f->cargarImagen(ventana, "img/ReversiChan5.png", rectangulo.x + 10, rectangulo.y);
        f->escribirPalabra(ventana, "Su Color", rectangulo.x + 35, rectangulo.y + 190, "Arcarde",
                           18, 255,255,255);
        f->escribirPalabra(ventana, "Negro", rectangulo.x + 45, rectangulo.y + 210, "Arcarde",
                           18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 6)
    {
        f->cargarImagen(ventana, "img/ReversiChan6.png", rectangulo.x + 10, rectangulo.y);
        f->escribirPalabra(ventana, "Su Color", rectangulo.x + 35, rectangulo.y + 190,
                          "Arcarde", 18, 255,255,255);
        f->escribirPalabra(ventana, "Blanco", rectangulo.x + 40, rectangulo.y + 210,
                          "Arcarde", 18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 7)
    {
        f->cargarImagen(ventana, "img/ReversiChan7.png", rectangulo.x + 10, rectangulo.y);
        f->escribirPalabra(ventana, "Ganador", rectangulo.x + 35, rectangulo.y + 210,
                           "Arcarde", 18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 8)
    {
        f->cargarImagen(ventana, "img/ReversiChan8.png", rectangulo.x + 10, rectangulo.y);
        f->escribirPalabra(ventana, "Perdedor", rectangulo.x + 30, rectangulo.y + 210,
                           "Arcarde", 18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
    else if (estado == 9)
    {
        f->cargarImagen(ventana, "img/ReversiChan4.png", rectangulo.x + 10, rectangulo.y);
        f->escribirPalabra(ventana, "Empate", rectangulo.x + 40, rectangulo.y + 210,
                          "Arcarde", 18, 255,255,255);

        SDL_UpdateRect(ventana, rectangulo.x, rectangulo.y, rectangulo.w, rectangulo.h);
    }
}

/**
 * @param pc    Puntero hacia el objeto encargado de manejar los enventos en pantalla
 *
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
void PantallaJuego::jugarRed(PantallaConfiguracion* pc)
{
    Cliente *cl = new Cliente();

    if (pc->getHost() == "" || pc->getPuerto() == "0")
    {
        pc->imprimirPantalla();
    }

    inicializar();

    if (cl->conectar(pc->getHost(),pc->getPuerto()))
    {
        //Mandamos el paquete de Jugar
        cl->armarPaqueteBuscar(pc->getNombreJugador());
        cl->enviarBusquedaDeJuego();

        //Creamos la estructura del Poll
        struct pollfd revisar;
        revisar.fd = cl->getSock();
        revisar.events = POLLIN;

        //Establecemos las variables para el tiempo
        struct timeval tv;
        struct timezone tz;

        int gtres = gettimeofday(&tv, &tz), n, res;

        double tiempo = ((double)tv.tv_sec * 1000000 + (double)tv.tv_usec);
        double ptiempo = tiempo;

        int contador = 0;
        bool animar = true, iniciaJuego = false;

        //Iteramos hasta que se termine el tiempo o nos reciba el servidor
        while (animar)
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

                //Imprimimos un punto si han pasado 400 milisegundos
                if (tiempo - ptiempo > 500000)
                {
                    if (animar)
                    {
                        //Imprimimos la imagen necesaria
                        if (contador % 4 == 0)
                        {
                            dibujarReversiChan(1);
                        }
                        else if (contador % 4 == 1 || contador % 4 == 3)
                        {
                            dibujarReversiChan(2);
                        }
                        else
                        {
                            dibujarReversiChan(3);
                        }

                        ptiempo = tiempo;
                        contador++;

                        //15 Segundos de confirmacion
                        if (contador == 30)
                        {
                            animar = false;
                        }
                    }
                }
            }

            //Llamamos a poll para revisar si tenemos un evento en 50 milisegundos
            n = poll(&revisar, 1, 50);

            if (n < 0)
            {
                //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
            }
            else if (n > 0)
            {
                if ((revisar.revents & POLLERR) == POLLERR)
                {
                    //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
                }
                else if ((revisar.revents & POLLHUP) == POLLHUP)
                {
                    //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
                }
                else if ((revisar.revents & POLLIN) == POLLIN)
                {
                    //Leemos los datos del socket
                    char buffer[256];
                    memset(buffer, 0, 256);

                    res = read(cl->getSock(), buffer, 255);

                    if (res < 0)
                    {
                        if (errno != EAGAIN && errno != EWOULDBLOCK)
                        {
                            //cerr<< "Error al llamar a read: \"" <<  strerror(errno) << "\"" << endl;
                        }
                        else
                        {
                            //cerr<< "Tendra que internarlo más tarde" << endl;
                        }
                    }
                    else if (res == 0)
                    {
                        //cout << endl << "Cerrando la conexion" << endl;
                        animar = false;
                        iniciaJuego = false;
                    }
                    else
                    {
                        if(cl->recibirPaquete(buffer)==1)
                        {
                            uint8_t colorF=buffer[3];
                            string nombreVersus;
                            for(int i=4;i<20;i++)
                            {
                                nombreVersus.push_back(buffer[i]);
                            }

                            //string  nombreVersus=string(nombreversus);
                            if(colorF == 0)
                            {
                                //Color del jugador blancas, inicia blancas
                                PantallaJuego::colorJugador=-1;
                                PantallaJuego::turnoJugador=-1;
                                PantallaJuego::setNombreJugador1(pc->getNombreJugador());
                                PantallaJuego::setNombreJugador2(nombreVersus);
                            }
                            else if(colorF == 1)
                            {
                                //Color del jugador blancas, inicia negras
                                PantallaJuego::colorJugador=-1;
                                PantallaJuego::turnoJugador=1;
                                PantallaJuego::setNombreJugador1(pc->getNombreJugador());
                                PantallaJuego::setNombreJugador2(nombreVersus);
                            }
                            else if(colorF == 16)
                            {
                                //Color del jugador negas, inicia blancas
                                PantallaJuego::colorJugador=1;
                                PantallaJuego::turnoJugador=-1;
                                PantallaJuego::setNombreJugador1(pc->getNombreJugador());
                                PantallaJuego::setNombreJugador2(nombreVersus);
                            }
                            else if(colorF == 17)
                            {
                                //Color del jugador negras, inicia negras
                                PantallaJuego::colorJugador=1;
                                PantallaJuego::turnoJugador=1;
                                PantallaJuego::setNombreJugador1(pc->getNombreJugador());
                                PantallaJuego::setNombreJugador2(nombreVersus);
                            }
                        }
                        animar = false;
                        iniciaJuego = true;
                    }
                }
            }
        }

        //Conexion Establecida
        if (iniciaJuego)
        {
            gestionarEventosRed(cl);
        }
        else
        {
            //Cerramos la conexion
            close(cl->getSock());

            dibujarReversiChan(4);
            sleep(3);
        }
    }
    else
    {
        pc->setPuerto("0");
    }
}

/**
 * @param clrev    Puntero hacia el objeto con los datos del cliente
 *
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
void PantallaJuego::gestionarEventosRed(Cliente *clrev)
{
    SDL_Event Evento;

    Cliente *cl = clrev;
    bool endgame = false;
    tablas = false;
    dadosSet = false;
    Fin = false;
    int n,res;

    //Poll para jugar
    struct pollfd revisar;
    revisar.fd = cl->getSock();
    revisar.events = POLLIN | POLLRDNORM;

    dibujarTablero();

    if (colorJugador != 1)
    {
        dibujarReversiChan(5);
        sleep(3);
    }
    else
    {
        dibujarReversiChan(6);
        sleep(3);
    }

    do
    {
        n = poll(&revisar, 1, 30);

        if (n < 0)
        {
            //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
        }
        else if (n > 0)
        {
            if ((revisar.revents & POLLERR) == POLLERR)
            {
                    //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
            }
            else if ((revisar.revents & POLLHUP) == POLLHUP)
            {
                //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
            }
            else if ((revisar.revents & POLLIN) == POLLIN ||
                     (revisar.revents & POLLRDNORM) == POLLRDNORM)
            {
                //Leemos los datos del socket
                char buffer[256];
                memset(buffer, 0, 256);

                res = read(cl->getSock(), buffer, 255);

                if (res < 0)
                {
                    if (errno != EAGAIN && errno != EWOULDBLOCK)
                    {
                        //cerr<< "Error al llamar a read: \"" <<  strerror(errno) << "\"" << endl;
                    }
                    else
                    {
                        //cerr<< "Tendra que internarlo más tarde" << endl;
                    }
                }
                else if (res == 0)
                {
                    endgame = true;
                }
                else
                {
                    if(cl->recibirPaquete(buffer)==3)//Dados
                    {
                        uint8_t dadoRecividoUno=buffer[3];
                        tablero.setDado(0,dadoRecividoUno);
                        uint8_t dadoRecividoDos=buffer[4];
                        tablero.setDado(1,dadoRecividoDos);
                        uint8_t dadoRecividoTres=buffer[5];
                        tablero.setDado(2,dadoRecividoTres);

                        PantallaJuego::animacionDado();

                        //Revision de si hay mas dados por tirar
                        if (PantallaJuego::tablero.getDado(2) != 0)
                        {
                            dadosSet = true;
                        }
                        else
                        {
                            PantallaJuego::turnoJugador = (-1) * PantallaJuego::colorJugador;
                        }
                    }
                    else if(cl->recibirPaquete(buffer)==5)//Movimiento Invalido
                    {
                        //cout << "Invalido" << endl;
                        //cout.flush();
                    }
                    else if(cl->recibirPaquete(buffer)==6)//Movimiento Valido
                    {
                        uint128_t tableroRecibido;
                        uint8_t color=buffer[3];

                        for (int j = 0; j < 16; j++)
                        {
                            tableroRecibido.byte[j]=buffer[j+4];
                        }

                        Tablero antes = tablero;
                        tablero = tablero.bytesToTablero(tableroRecibido);

                        noTurno = true;
                        PantallaJuego::tablero.inicializarDados();

                        int px, py;
                        tablero.buscarMovimiento(antes, tablero, colorJugador, &px, &py);

                        posibleX = -1;
                        posibleY = -1;

                        ponerAnimacion(antes, PantallaJuego::colorJugador, px+1, py+1);

                        if (color != 0)
                        {
                            PantallaJuego::turnoJugador = -1;
                        }
                        else
                        {
                            PantallaJuego::turnoJugador = 1;
                        }

                        dadosSet = false;
                    }
                    else if(cl->recibirPaquete(buffer)==7) //Fin
                    {
                        Fin=true;
                        uint8_t razonFin=buffer[3];

                        if((razonFin & 0x0)==razonFin)//Empate
                        {
                            tablas=true;
                        }
                        else if((razonFin & 0x1)==razonFin)//Gana Blancas
                        {
                            for (int i = 0; i < 8; i++)
                            {
                                for (int j = 0; j < 8; j++)
                                {
                                    tablero.setFicha(i,j, -1);
                                }
                            }

                            tablas=false;
                            Fin=true;
                        }
                        else if((razonFin & 0x2)==razonFin)//Gana Negras
                        {
                            for (int i = 0; i < 8; i++)
                            {
                                for (int j = 0; j < 8; j++)
                                {
                                    tablero.setFicha(i,j, 1);
                                }
                            }

                            tablas=false;
                            Fin=true;
                        }
                        else if((razonFin & 0x3)==razonFin)//Desconexion Blancas
                        {
                            for (int i = 0; i < 8; i++)
                            {
                                for (int j = 0; j < 8; j++)
                                {
                                    tablero.setFicha(i,j, 1);
                                }
                            }

                            tablas=false;
                            Fin=true;
                        }
                        else if((razonFin & 0x4)==razonFin)//Desconexion Negras
                        {
                            for (int i = 0; i < 8; i++)
                            {
                                for (int j = 0; j < 8; j++)
                                {
                                    tablero.setFicha(i,j, -1);
                                }
                            }

                            tablas=false;
                            Fin=true;
                        }

                        dibujarTablero();
                        sleep(3);
                    }
                }
            }
        }

        if (Fin) //Si hay fin de juego
        {
            //Cambiamos al turno del jugador
            PantallaJuego::turnoJugador = PantallaJuego::colorJugador;

            SDL_PollEvent(&Evento);

            //Indicamos que tiene que dar click en el boton de abajo o salir
            if (Evento.type == SDL_MOUSEBUTTONDOWN)
            {
                int y = Evento.button.y;
                int x = Evento.button.x;

                if (x > TAM_CUADRO*6+10 && y > TAM_CUADRO*11+10 &&
                    x < TAM_CUADRO*6+110 && y < TAM_CUADRO*11+43)
                {
                    endgame = true;
                }
            }
            else if (Evento.type == SDL_QUIT)
            {
                endgame = true;
            }
        }
        else //Hay juego activo
        {
            PantallaJuego::dibujarTablero();
            SDL_PollEvent(&Evento);

            if (PantallaJuego::turnoJugador == PantallaJuego::colorJugador)
            {
                if (Evento.type == SDL_MOUSEMOTION)
                {
                    if (dadosSet) //No hay para poner dados
                    {
                        int y = Evento.button.y;
                        int x = Evento.button.x;

                        int tabY = ((y/TAM_CUADRO) - 2);
                        int tabX = ((x/TAM_CUADRO) - 0);

                        //Revisamos si la posicion donde esta es un movimiento valido
                        if (tabX > 0 and tabY <= 8 and tabY > 0 and tabY <= 8)
                        {
                            if ((posibleX != tabX || posibleY != tabY) &&
                               (tablero.numInDados(tabX) || tablero.numInDados(tabY)) )
                            {
                                if (tablero.validarMovimiento(tabX-1,  tabY-1, colorJugador))
                                {
                                    posibleX = tabX;
                                    posibleY = tabY;
                                }
                                else
                                {
                                    posibleX = -1;
                                    posibleY = -1;
                                }
                            }
                        }
                        else
                        {
                            posibleX = -1;
                            posibleY = -1;
                        }
                    }
                }
                else if (Evento.type == SDL_MOUSEBUTTONDOWN)
                {
                    int y = Evento.button.y;
                    int x = Evento.button.x;

                    if (!dadosSet) //Tirar Dado
                    {
                        if (x > TAM_CUADRO*6+10 && y > TAM_CUADRO*11+10 &&
                            x < TAM_CUADRO*6+110 && y < TAM_CUADRO*11+43)
                        {
                            cl->armarPaquetePedirDado(PantallaJuego::colorJugador);

                            if(!cl->pedirDado())
                            {
                                exit(1);
                            }
                        }
                    }
                    else //Hace Movimiento
                    {
                        if (turnoJugador == colorJugador) //Turno Jugador Blancas
                        {
                            int tabY = ((y/TAM_CUADRO) - 2);
                            int tabX = ((x/TAM_CUADRO) - 0);

                            //Validacion de movimiento en el tablero
                            if (tabX > 0 and tabY <= 8 and tabY > 0 and tabY <= 8)
                            {
                                if (tablero.numInDados(tabX) || tablero.numInDados(tabY))
                                {
                                    if (tablero.validarMovimiento(tabX-1,  tabY-1, colorJugador))
                                    {
                                        posibleX = -1;
                                        posibleY = -1;
                                        cl->armarPaqueteMovimiento(tabX-1,  tabY-1);
                                        cl->mandarMoviento();

                                        PantallaJuego::tablero.inicializarDados();
                                        dadosSet = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (Evento.type == SDL_QUIT) //Salir
            {
                cl->enviarPaqueteFin(PantallaJuego::colorJugador);
            }
        }

    }while(!endgame);

    close(cl->getSock());
}

/**
 * Genera una jugabilidad normal contra la computadora
 *
 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
 */
void PantallaJuego::gestionarEventos()
{
    SDL_Event Evento;
    srand(time(NULL));

    bool endgame = false;
    bool turnoRevisado = false;
    tablas = false;
    dadosSet = false;
    Fin = false;

    dibujarTablero();

    if (colorJugador != 1)
    {
        dibujarReversiChan(5);
        sleep(3);
    }
    else
    {
        dibujarReversiChan(6);
        sleep(3);
    }

    while (!endgame)
    {
        //Dibujamos el tablero
        PantallaJuego::dibujarTablero();

        if (Fin) //Si hay fin de juego
        {
            sleep(3);
            endgame = true;
        }
        else //Hay juego activo
        {
            int cnn = PantallaJuego::tablero.cantidadNegras();
            int cbn = PantallaJuego::tablero.cantidadBlancas();

            //Buscamos condiciones de fin de juego
            if ( (cnn + cbn == 64) || (cnn == 0) || (cbn == 0) )
            {
                Fin = true;
                dadosSet = true;
                continue;
            }

            if (dadosSet)
            {
                //Validamos movimiento de dados
                if (!PantallaJuego::tablero.turnoValido(PantallaJuego::turnoJugador))
                {
                    noTurno = true;
                    PantallaJuego::tablero.inicializarDados();
                    dibujarTablero();
                    sleep(2);

                    PantallaJuego::turnoJugador = (-1) * PantallaJuego::turnoJugador;
                    dadosSet = false;

                    continue;
                }
                else //No puede mover
                {
                    noTurno = false;
                }
            }

            //Revisamos de quien es el turno
            if (PantallaJuego::turnoJugador != PantallaJuego::colorJugador && turnoRevisado) //Turno Computadora
            {
                if (!dadosSet) //Tirar Dado
                {
                    int num = PantallaJuego::tablero.turnoGlobalValido(turnoJugador);

                    PantallaJuego::tablero.tirarDados(num);
                    PantallaJuego::animacionDado();

                    //Revisamos si aun se pueden tirar mas dados
                    if (PantallaJuego::tablero.getDado(2) != 0)
                    {
                        dadosSet = true;
                    }
                    else
                    {
                        PantallaJuego::turnoJugador = PantallaJuego::colorJugador;
                    }
                }
                else //Realizar Movimiento
                {
                    //Insertamos la ficha que deseamos
                    Tablero t;
                    short x = -1, y = -1;

                    //La computadora realiza un movimiento
                    t = PantallaJuego::tablero;
                    PantallaJuego::tablero.computerMove(PantallaJuego::colorJugador * (-1), &x, &y);

                    //Validamos el movimiento
                    if (x != -1 && y != -1)
                    {
                        if (PantallaJuego::tablero.validarMovimiento(x, y, colorJugador * (-1)))
                        {
                            sleep(1);

                            //Cargamos el movimiento de la computadora
                            PantallaJuego::tablero.colocarFicha(x, y, colorJugador * (-1));
                            PantallaJuego::ponerAnimacion(t, colorJugador * (-1), x+1, y+1);
                            PantallaJuego::turnoJugador = PantallaJuego::colorJugador;

                            PantallaJuego::tablero.inicializarDados();
                            dadosSet = false;
                            turnoRevisado = false;
                        }

                    }
                }
            }
            else if (turnoRevisado)//Turno del usuario
            {
                SDL_WaitEvent(&Evento);

                if (Evento.type == SDL_MOUSEMOTION)
                {
                    if (dadosSet) //No hay para poner dados
                    {
                        int y = Evento.button.y;
                        int x = Evento.button.x;

                        int tabY = ((y/TAM_CUADRO) - 2);
                        int tabX = ((x/TAM_CUADRO) - 0);

                        //Revisamos si la posicion donde esta es un movimiento valido
                        if (tabX > 0 and tabY <= 8 and tabY > 0 and tabY <= 8)
                        {
                            if ((posibleX != tabX || posibleY != tabY) &&
                               (tablero.numInDados(tabX) || tablero.numInDados(tabY)) )
                            {
                                if (tablero.validarMovimiento(tabX-1,  tabY-1, colorJugador))
                                {
                                    posibleX = tabX;
                                    posibleY = tabY;
                                }
                                else
                                {
                                    posibleX = -1;
                                    posibleY = -1;
                                }
                            }
                        }
                        else
                        {
                            posibleX = -1;
                            posibleY = -1;
                        }
                    }
                }
                else if (Evento.type == SDL_MOUSEBUTTONDOWN)
                {
                    int y = Evento.button.y;
                    int x = Evento.button.x;

                    if (!dadosSet) //Tirar Dado
                    {
                        if (x > TAM_CUADRO*6+10 && y > TAM_CUADRO*11+10 &&
                            x < TAM_CUADRO*6+110 && y < TAM_CUADRO*11+43)
                        {
                            int num = PantallaJuego::tablero.turnoGlobalValido(turnoJugador);

                            PantallaJuego::tablero.tirarDados(num);
                            PantallaJuego::animacionDado();

                            //Revision de si hay mas dados por tirar
                            if (PantallaJuego::tablero.getDado(2) != 0)
                            {
                                dadosSet = true;
                            }
                            else
                            {
                                PantallaJuego::turnoJugador = (-1) * PantallaJuego::colorJugador;
                            }
                        }
                    }
                    else //Hace Movimiento
                    {
                        if (PantallaJuego::turnoJugador == colorJugador) //Turno Jugador
                        {
                            int tabY = ((y/TAM_CUADRO) - 2);
                            int tabX = ((x/TAM_CUADRO) - 0);

                            //Validacion de movimiento en el tablero
                            if (tabX > 0 and tabY <= 8 and tabY > 0 and tabY <= 8)
                            {
                                if (tablero.numInDados(tabX) || tablero.numInDados(tabY))
                                {
                                    if (tablero.validarMovimiento(tabX-1,  tabY-1, colorJugador))
                                    {
                                        posibleX = -1;
                                        posibleY = -1;

                                        //Insertamos la ficha que deseamos
                                        Tablero t;
                                        t = PantallaJuego::tablero;
                                        tablero.colocarFicha(tabX-1, tabY-1, colorJugador);

                                        ponerAnimacion(t, PantallaJuego::colorJugador, tabX, tabY);
                                        PantallaJuego::turnoJugador = (-1) * colorJugador;

                                        PantallaJuego::tablero.inicializarDados();
                                        dadosSet = false;
                                        turnoRevisado = false;
                                    }
                                }
                            }
                        }
                    }
                }
                else if (Evento.type == SDL_QUIT) //Salir
                {
                    for (int i = 0; i < 8; i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            tablero.setFicha(i,j, colorJugador*(-1));
                        }
                    }

                    dibujarTablero();
                    sleep(3);

                    endgame = true;
                }
            }
            else //Validamos que se turno valido o haya tablas
            {
                //Turno Valido sin importar los dados
                if (PantallaJuego::tablero.turnoGlobalValido(PantallaJuego::turnoJugador) == -1)
                {
                    noTurno = true;

                    if (tablas)
                    {
                        Fin = true;
                    }
                    else
                    {
                        tablas = true;
                        PantallaJuego::turnoJugador = (-1) * PantallaJuego::turnoJugador;
                    }

                    continue;
                }
                else
                {
                    tablas = false;
                }

                turnoRevisado = true;
            }
        }
    }
}

