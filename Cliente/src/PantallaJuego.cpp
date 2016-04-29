#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include "PantallaJuego.h"
#include "Constantes.h"
#include "stringConvert.h"
#include "Cliente.h"

using namespace std;

///Constructor
PantallaJuego::PantallaJuego(SDL_Window* win, SDL_Renderer* ren, FuncionesPantalla* fp)
{
    srand(time(NULL));

    PantallaJuego::posibleX = -1;
    PantallaJuego::posibleY = -1;

    PantallaJuego::window = win;
    PantallaJuego::renderizador = ren;
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
    SDL_Color color;
    short tamCuadro = 270;

    short dado1 = PantallaJuego::tablero.getDado(0);
    short dado2 = PantallaJuego::tablero.getDado(1);
    short dado3 = PantallaJuego::tablero.getDado(2);

    //Inicializamos todo y dibujamos el tablero
    PantallaJuego::tablero.inicializarDados();
    dibujarTablero();

    //Dibujamos un cuadrado gris grande en medio de la pantalla
    rectangulo.x = f->calcularProporcion(((TAM_CUADRO*9)/2)-(tamCuadro/2), 'w');
    rectangulo.y = f->calcularProporcion(((TAM_CUADRO*12)/2)-(tamCuadro/2), 'h');
    rectangulo.w = f->calcularProporcion(tamCuadro, 'w');
    rectangulo.h = f->calcularProporcion(tamCuadro, 'h');

    SDL_Rect past2 = rectangulo;

    SDL_SetRenderDrawColor(renderizador, 170, 170, 170, 255); //Gris
    SDL_RenderFillRect(renderizador, &rectangulo);

    //Dibujamos un cuadrado blanco mas pequeño que el anterior en medio de la pantalla
    SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255); //Blanco
    tamCuadro = 250;

    rectangulo.x = f->calcularProporcion(((TAM_CUADRO*9)/2)-(tamCuadro/2), 'w');
    rectangulo.y = f->calcularProporcion(((TAM_CUADRO*12)/2)-(tamCuadro/2), 'h');
    rectangulo.w = f->calcularProporcion(tamCuadro, 'w');
    rectangulo.h = f->calcularProporcion(tamCuadro, 'h');

    SDL_RenderFillRect(renderizador, &rectangulo);
    SDL_Rect past = rectangulo;

    //Establecemos las variables para el tiempo
    double tiempo = SDL_GetTicks();
    double ptiempo = tiempo;
    bool terminar = false;
    int i = 0;

    stringConvert fx;
    SDL_Texture* tex;

    SDL_Event e;

    while(not terminar && not Fin)
    {
    	dibujarTablero();

        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        tablero.setFicha(i,j, colorJugador*(-1));
                    }
                }

                Fin = true;
                dibujarTablero();
                continue;
            }
        }

        //Transformamos a un número doble la hora
        tiempo = SDL_GetTicks();

        //Imprimimos un punto si han pasado 75 milisegundos
        if (tiempo - ptiempo > 75)
        {
            SDL_SetRenderDrawColor(renderizador, 170, 170, 170, 255); //Gris
            SDL_RenderFillRect(renderizador, &past2);

            SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255); //Gris
            SDL_RenderFillRect(renderizador, &past);

            //Cargamos la imagen en relacion del numero del 1-5
            string cad = "img/animacionDado";
            cad = cad + fx.intToStr((i % 5) + 1) + ".png";

            tex = f->cargarTextura(cad, renderizador);

            rectangulo.x = ((TAM_CUADRO*9)/2)+125-(tamCuadro/2);
            rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
            rectangulo.w = tamCuadro/2;
            rectangulo.h = tamCuadro/2;

            f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y,
                                 rectangulo.w, rectangulo.h);

            rectangulo.x = ((TAM_CUADRO*9)/2)+62-(tamCuadro/2);
            rectangulo.y = ((TAM_CUADRO*12)/2)+125-(tamCuadro/2);
            rectangulo.w = tamCuadro/2;
            rectangulo.h = tamCuadro/2;

            f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y,
                                 rectangulo.w, rectangulo.h);

            rectangulo.x = ((TAM_CUADRO*9)/2)-(tamCuadro/2);
            rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
            rectangulo.w = tamCuadro/2;
            rectangulo.h = tamCuadro/2;

            f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y,
                                 rectangulo.w, rectangulo.h);

            SDL_DestroyTexture(tex);
            SDL_RenderPresent(renderizador);

            ptiempo = tiempo;
            i++;
        }

        if (i == 21)
        {
            terminar = true;
        }
    }

    if (not Fin || terminar)
    {
    	dibujarTablero();
        SDL_SetRenderDrawColor(renderizador, 170, 170, 170, 255); //Gris
        SDL_RenderFillRect(renderizador, &past2);

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255); //Gris
        SDL_RenderFillRect(renderizador, &past);

        //Cargamos la imagen en relacion del numero del 1-5
        string cad = "img/animacionDado1.png";

        SDL_Texture* tex = f->cargarTextura(cad, renderizador);

        rectangulo.x = ((TAM_CUADRO*9)/2)+125-(tamCuadro/2);
        rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
        rectangulo.w = tamCuadro/2;
        rectangulo.h = tamCuadro/2;

        f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y,
                             rectangulo.w, rectangulo.h);

        rectangulo.x = ((TAM_CUADRO*9)/2)+62-(tamCuadro/2);
        rectangulo.y = ((TAM_CUADRO*12)/2)+125-(tamCuadro/2);
        rectangulo.w = tamCuadro/2;
        rectangulo.h = tamCuadro/2;

        f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y,
                             rectangulo.w, rectangulo.h);

        rectangulo.x = ((TAM_CUADRO*9)/2)-(tamCuadro/2);
        rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
        rectangulo.w = tamCuadro/2;
        rectangulo.h = tamCuadro/2;

        f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y,
                             rectangulo.w, rectangulo.h);

        SDL_DestroyTexture(tex);

        //Cargamos el dado y ponemos el numero
        rectangulo.x = ((TAM_CUADRO*9)/2)+125-(tamCuadro/2);
        rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
        rectangulo.w = tamCuadro;
        rectangulo.h = tamCuadro;

        color.r = 224;
        color.g = 7;
        color.b = 43;

        tex = f->renderizarTexto(fx.intToStr(dado2).c_str(), "KeepCalm", color, 32, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x+56, rectangulo.y+45);
        SDL_DestroyTexture(tex);

        rectangulo.x = ((TAM_CUADRO*9)/2)+62-(tamCuadro/2);
        rectangulo.y = ((TAM_CUADRO*12)/2)+125-(tamCuadro/2);
        rectangulo.w = tamCuadro;
        rectangulo.h = tamCuadro;

        tex = f->renderizarTexto(fx.intToStr(dado3).c_str(), "KeepCalm", color, 32, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x+56, rectangulo.y+45);
        SDL_DestroyTexture(tex);

        rectangulo.x = ((TAM_CUADRO*9)/2)-(tamCuadro/2);
        rectangulo.y = ((TAM_CUADRO*12)/2)-(tamCuadro/2);
        rectangulo.w = tamCuadro;
        rectangulo.h = tamCuadro;

        tex = f->renderizarTexto(fx.intToStr(dado1).c_str(), "KeepCalm", color, 32, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x+56, rectangulo.y+45);
        SDL_DestroyTexture(tex);

        SDL_RenderPresent(renderizador);

        //Pausamos y agregamos el dado al tablero
        SDL_Delay(1000);
        PantallaJuego::tablero.setDado(0, dado1);
        PantallaJuego::tablero.setDado(1, dado2);
        PantallaJuego::tablero.setDado(2, dado3);
    }
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
        SDL_RenderPresent(renderizador);
        SDL_Delay(1000);

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
        SDL_RenderPresent(renderizador);
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
        SDL_RenderPresent(renderizador);

        SDL_Delay(1000);

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
        f->cargarFicha(renderizador, posibleX, posibleY, 'G', "0");

        //Por cada ficha del tablero diferencte cargamos la animacion
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (!(i+1 == lastX && j+1 == lastY))
                {
                    if (PantallaJuego::tablero.getFicha(i,j) != antiguo.getFicha(i,j))
                    {
                        f->cargarFicha(renderizador, i+1, j+1, fichaC, "1");
                    }
                }
            }
        }

        //Actualizamos el tablero
        SDL_RenderPresent(renderizador);

        SDL_Delay(1000);
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
    stringConvert strc;
    int iW, iH;
    SDL_Color color;
    SDL_Texture* tex;
    SDL_GetWindowSize(window, &iW, &iH);
    SDL_Rect rectangulo;

    //Rellenamos de negro el tablero
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); //negro
    SDL_RenderClear(renderizador);

    //Dibuja la parte cafe del tablero
    iniX = 0;
    iniY = 2;
    maxX = 9;
    maxY = 11;

    SDL_SetRenderDrawColor(renderizador, 71, 29, 11, 255); //Cafe

    for (int i = iniX; i < maxX; i++)
    {
        for (int j = iniY; j < maxY; j++)
        {
            rectangulo.x = f->calcularProporcion(TAM_CUADRO*i, 'w');
            rectangulo.y = f->calcularProporcion(TAM_CUADRO*j, 'h');
            rectangulo.w = f->calcularProporcion((TAM_CUADRO*maxX)-(TAM_CUADRO*i), 'w');
            rectangulo.h = f->calcularProporcion((TAM_CUADRO*maxY)-(TAM_CUADRO*j), 'h');

            SDL_RenderFillRect(renderizador, &rectangulo);
        }
    }

    //Dibuja la parte verde del tablero
    iniX = 1;
    iniY = 3;
    maxX = 9;
    maxY = 11;
    SDL_SetRenderDrawColor(renderizador, 6, 112, 1, 255); //Cafe

    for (int i = iniX; i < maxX; i++)
    {
        for (int j = iniY; j < maxY; j++)
        {
            rectangulo.x = f->calcularProporcion(TAM_CUADRO*i, 'w');
            rectangulo.y = f->calcularProporcion(TAM_CUADRO*j, 'h');
            rectangulo.w = f->calcularProporcion((TAM_CUADRO*maxX)-(TAM_CUADRO*i), 'w');
            rectangulo.h = f->calcularProporcion((TAM_CUADRO*maxY)-(TAM_CUADRO*j), 'h');

            SDL_RenderFillRect(renderizador, &rectangulo);
        }
    }

    //Dibuja las lineas del tablero
    SDL_SetRenderDrawColor(renderizador, 200, 200, 200, 255); //Cafe

    for (int i = 0; i < TAM_CUADRO*9; i+=TAM_CUADRO)
    {
        rectangulo.x = f->calcularProporcion(i, 'w');
        rectangulo.y = f->calcularProporcion(TAM_CUADRO*2, 'h');
        rectangulo.w = f->calcularProporcion(TAM_LINEA, 'w');
        rectangulo.h = f->calcularProporcion((TAM_CUADRO*12)-(TAM_CUADRO*3), 'h');

        SDL_RenderFillRect(renderizador, &rectangulo);
    }

    rectangulo.x = f->calcularProporcion(TAM_CUADRO*9, 'w');
    SDL_RenderFillRect(renderizador, &rectangulo);

    for (int i = TAM_CUADRO*2; i < TAM_CUADRO*12; i+=TAM_CUADRO)
    {
        rectangulo.x = f->calcularProporcion(0, 'w');
        rectangulo.y = f->calcularProporcion(i, 'h');
        rectangulo.w = f->calcularProporcion((TAM_CUADRO*9)+TAM_LINEA, 'w');
        rectangulo.h = f->calcularProporcion(TAM_LINEA, 'h');

        SDL_RenderFillRect(renderizador, &rectangulo);
    }

    //Dibuja los números en el tablero
    color.r = 255;
    color.g = 255;
    color.b = 255;

    stringConvert s;
    for (int i = 1; i <= 8; i++)
    {
        tex = f->renderizarTexto(s.intToStr(i), "NinjaNaruto", color, 28, renderizador);
        f->renderizarTextura(tex, renderizador, 10+TAM_CUADRO*i, 7+TAM_CUADRO*2);
        f->renderizarTextura(tex, renderizador, 10, 7+TAM_CUADRO*(2+i));
        SDL_DestroyTexture(tex);
    }

    //Escribe nombre Jugadores
    if (PantallaJuego::turnoJugador == PantallaJuego::colorJugador)
    {
        tex = f->cargarTextura("img/btnJugadorA.png", renderizador);
        f->renderizarTextura(tex, renderizador, 5, 3);
        SDL_DestroyTexture(tex);

        tex = f->cargarTextura("img/btnJugadorB.png", renderizador);
        f->renderizarTextura(tex, renderizador, 5, TAM_CUADRO+3);
        SDL_DestroyTexture(tex);
    }
    else
    {
        tex = f->cargarTextura("img/btnJugadorB.png", renderizador);
        f->renderizarTextura(tex, renderizador, 5, 3);
        SDL_DestroyTexture(tex);

        tex = f->cargarTextura("img/btnJugadorA.png", renderizador);
        f->renderizarTextura(tex, renderizador, 5, TAM_CUADRO+3);
        SDL_DestroyTexture(tex);
    }

    tex = f->renderizarTexto("Jugador A: " + nombreJugador1, "HelveticaStandar",
                             color, 16, renderizador);
    f->renderizarTextura(tex, renderizador, 25, 0);
    SDL_DestroyTexture(tex);

    tex = f->renderizarTexto("Jugador B: " + nombreJugador2, "HelveticaStandar",
                             color, 16, renderizador);
    f->renderizarTextura(tex, renderizador, 25, TAM_CUADRO);
    SDL_DestroyTexture(tex);

    //Cargamos los tres octagonos
    short dado;

    for (int i = 0; i < 3; i++)
    {
        dado = PantallaJuego::tablero.getDado(i);

        if (dado == 0)
        {
            tex = f->cargarTextura("img/octagonoVacio.png", renderizador);
            f->renderizarTextura(tex, renderizador, TAM_CUADRO*(6+i)-10, TAM_CUADRO/2);
            SDL_DestroyTexture(tex);
        }
        else
        {
            tex = f->cargarTextura("img/octagonoLleno.png", renderizador);
            f->renderizarTextura(tex, renderizador, TAM_CUADRO*(6+i)-10, TAM_CUADRO/2);
            SDL_DestroyTexture(tex);

            tex = f->renderizarTexto(strc.intToStr(dado), "KeepCalm", color, 15, renderizador);
            f->renderizarTextura(tex, renderizador, TAM_CUADRO*(6+i)+4, TAM_CUADRO/2+13);
            SDL_DestroyTexture(tex);
        }
    }

    //Boton de abajo
    if (Fin)
    {
        tex = f->cargarTextura("img/btnOn.png", renderizador);
        f->renderizarTextura(tex, renderizador, TAM_CUADRO*6+10, TAM_CUADRO*11+10);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("c e r r a r", "CrownTitle", color, 22, renderizador);
        f->renderizarTextura(tex, renderizador, TAM_CUADRO*6+27, TAM_CUADRO*11+15);
        SDL_DestroyTexture(tex);
    }
    else
    {
        if (not dadosSet && (turnoJugador == colorJugador))
        {
            tex = f->cargarTextura("img/btnOn.png", renderizador);
            f->renderizarTextura(tex, renderizador, TAM_CUADRO*6+10, TAM_CUADRO*11+10);
            SDL_DestroyTexture(tex);

            tex = f->renderizarTexto("tirar dados", "CrownTitle", color, 22, renderizador);
            f->renderizarTextura(tex, renderizador, TAM_CUADRO*6+19, TAM_CUADRO*11+15);
            SDL_DestroyTexture(tex);
        }
        else
        {
            tex = f->cargarTextura("img/btnOff.png", renderizador);
            f->renderizarTextura(tex, renderizador, TAM_CUADRO*6+10, TAM_CUADRO*11+10);
            SDL_DestroyTexture(tex);
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

    color.r = 255;
    color.g = 255;
    color.b = 0;

    tex = f->renderizarTexto(estadoJuego, "KeepCalm", color, 15, renderizador);
    f->renderizarTextura(tex, renderizador, 15, TAM_CUADRO*11+15);
    SDL_DestroyTexture(tex);

    //Cargamos las fichas del tablero
    short int colorFicha;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            colorFicha = PantallaJuego::tablero.getFicha(i,j);

            if (colorFicha < 0)
            {
                f->cargarFicha(renderizador, i+1, j+1, 'N', "0");
            }
            else if (colorFicha > 0)
            {
                f->cargarFicha(renderizador, i+1, j+1, 'B', "0");
            }
        }
    }

    //Revisamos que exista un movimiento posible, de ser así lo ponemos con una ficha gris
    if (posibleX != -1 && posibleY != -1)
    {
        f->cargarFicha(renderizador, posibleX, posibleY, 'G', "0");
    }

    if (Fin)
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
    SDL_Color color;
    SDL_SetRenderDrawColor(renderizador, 50, 50, 50, 255); //Blanco

    rectangulo.x = f->calcularProporcion(90, 'w');
    rectangulo.y = f->calcularProporcion(110, 'h');
    rectangulo.w = f->calcularProporcion(170, 'w');
    rectangulo.h = f->calcularProporcion(255, 'h');

    SDL_RenderFillRect(renderizador, &rectangulo);

    //Color interno de la miniventana
    SDL_SetRenderDrawColor(renderizador, 255, 150, 0, 255); //Naranja

    rectangulo.x = f->calcularProporcion(100, 'w');
    rectangulo.y = f->calcularProporcion(120, 'h');
    rectangulo.w = f->calcularProporcion(150, 'w');
    rectangulo.h = f->calcularProporcion(235, 'h');

    SDL_RenderFillRect(renderizador, &rectangulo);
    SDL_Texture* tex;

    rectangulo.x = 100;
    rectangulo.y = 120;
    rectangulo.w = 150;
    rectangulo.h = 235;

    color.r = 255;
    color.g = 255;
    color.b = 255;

    if (estado == 1)
    {
        tex = f->cargarTextura("img/ReversiChan1.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Buscando", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 25, rectangulo.y + 190);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Contrincante", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 5, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 2)
    {
        tex = f->cargarTextura("img/ReversiChan2.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 15, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Buscando", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 25, rectangulo.y + 190);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Contrincante", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 5, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 3)
    {
        tex = f->cargarTextura("img/ReversiChan3.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Buscando", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 25, rectangulo.y + 190);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Contrincante", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 5, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 4)
    {
        tex = f->cargarTextura("img/ReversiChan4.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 10, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Oponente", "Arcarde", color, 16, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 35, rectangulo.y + 190);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("No Encontrado", "Arcarde", color, 16, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 5, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 5)
    {
        tex = f->cargarTextura("img/ReversiChan5.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 10, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Su Color", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 35, rectangulo.y + 190);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Negro", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 45, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 6)
    {
        tex = f->cargarTextura("img/ReversiChan6.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 10, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Su Color", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 35, rectangulo.y + 190);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Blanco", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 45, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 7)
    {
        tex = f->cargarTextura("img/ReversiChan7.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 10, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Ganador", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 35, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 8)
    {
        tex = f->cargarTextura("img/ReversiChan8.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 10, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Perdedor", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 35, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }
    else if (estado == 9)
    {
        tex = f->cargarTextura("img/ReversiChan4.png", renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 10, rectangulo.y);
        SDL_DestroyTexture(tex);

        tex = f->renderizarTexto("Empate", "Arcarde", color, 18, renderizador);
        f->renderizarTextura(tex, renderizador, rectangulo.x + 45, rectangulo.y + 210);
        SDL_DestroyTexture(tex);
    }

    //SDL_RenderPresent(renderizador);
}

/**
 * @param pc    Puntero hacia el objeto encargado de manejar los enventos en pantalla
 *
 * @author  Luis Fernando Gutiérrez <G.G.LuisFer@gmail.com>
 */
void PantallaJuego::jugarRed(PantallaConfiguracion* pc)
{
    Cliente *cl = new Cliente();
    bool iniciaJuego = false;

    if (pc->getHost() == "" || pc->getPuerto() == "0")
    {
        pc->imprimirPantalla();
    }

    inicializar();
    SDLNet_SocketSet setSocket = SDLNet_AllocSocketSet(1);;

    if (cl->conectar(pc->getHost(),pc->getPuerto()))
    {
        //Mandamos el paquete de Jugar
        cl->armarPaqueteBuscar(pc->getNombreJugador());
        cl->enviarBusquedaDeJuego();

        //Creamos la estructura del Poll
        SDLNet_TCP_AddSocket(setSocket, *(cl->getCliente()));

        //Establecemos las variables para el tiempo
        int n, res;

        double tiempo = SDL_GetTicks();
        double ptiempo = tiempo;

        int contador = 0;
        bool animar = true;

        SDL_Event e;

        //Iteramos hasta que se termine el tiempo o nos reciba el servidor
        while (animar)
        {
            SDL_PollEvent(&e);

            if (e.type == SDL_QUIT)
            {
                break;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_AC_BACK)
                {
                    break;
                }
            }

            //Transformamos a un número doble la hora
            tiempo = SDL_GetTicks();

            //Imprimimos un punto si han pasado 500 milisegundos
            if (tiempo - ptiempo > 500)
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

                    SDL_RenderPresent(renderizador);
                    ptiempo = tiempo;
                    contador++;

                    //15 Segundos de confirmacion
                    if (contador == 30)
                    {
                        animar = false;
                    }
                }
            }

            //Llamamos a poll para revisar si tenemos un evento en 50 milisegundos
            n = SDLNet_CheckSockets(setSocket, 50);

            if (n < 0)
            {
                //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
            }
            else if (n > 0)
            {
                //Leemos los datos del socket
                char buffer[256];
                memset(buffer, 0, 256);

                res = SDLNet_TCP_Recv(*(cl->getCliente()), buffer, 255);

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

        //Conexion Establecida
        if (iniciaJuego)
        {
            gestionarEventosRed(cl);
        }
        else
        {
            //Cerramos la conexion
            SDLNet_TCP_Close(*(cl->getCliente()));

            dibujarReversiChan(4);
            SDL_RenderPresent(renderizador);
            SDL_Delay(2500);
        }
    }
    else
    {
        dibujarReversiChan(4);
        SDL_RenderPresent(renderizador);
        SDL_Delay(2500);
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
    SDLNet_SocketSet setSocket = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(setSocket, *(cl->getCliente()));

    if (colorJugador != 1)
    {
    	PantallaJuego::dibujarTablero();
        dibujarReversiChan(5);
        SDL_RenderPresent(renderizador);
        SDL_Delay(3000);
    }
    else
    {
    	PantallaJuego::dibujarTablero();
        dibujarReversiChan(6);
        SDL_RenderPresent(renderizador);
        SDL_Delay(3000);
    }

    do
    {
        n = SDLNet_CheckSockets(setSocket, 30);

        if (n < 0)
        {
            //cerr<< "Error al llamar a poll: \"" <<  strerror(errno) << "\"" << endl;
        }
        else if (n > 0)
        {
            //Leemos los datos del socket
            char buffer[256];
            memset(buffer, 0, 256);

            res = SDLNet_TCP_Recv(*(cl->getCliente()), buffer, 255);

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
                    SDL_RenderPresent(renderizador);
                    SDL_Delay(3000);
                }
            }
        }


        if (Fin) //Si hay fin de juego
        {
            //Cambiamos al turno del jugador
            PantallaJuego::turnoJugador = PantallaJuego::colorJugador;

            if (not SDL_PollEvent(&Evento))
            {
                continue;
            }

            //Indicamos que tiene que dar click en el boton de abajo o salir
            if (Evento.type == SDL_MOUSEBUTTONDOWN)
            {
                int y = Evento.button.y;
                int x = Evento.button.x;

                if (x > f->calcularProporcion(TAM_CUADRO*6+10, 'w') &&
                    y > f->calcularProporcion(TAM_CUADRO*11+10, 'h') &&
                    x < f->calcularProporcion(TAM_CUADRO*6+110, 'w') &&
                    y < f->calcularProporcion(TAM_CUADRO*11+43, 'h'))
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
            SDL_RenderPresent(renderizador);

            if (not SDL_PollEvent(&Evento))
            {
                continue;
            }

            if (PantallaJuego::turnoJugador == PantallaJuego::colorJugador)
            {
                if (Evento.type == SDL_MOUSEMOTION)
                {
                    if (dadosSet) //No hay para poner dados
                    {
                        int y = Evento.button.y;
                        int x = Evento.button.x;

                        int tabY = ((y/f->calcularProporcion(TAM_CUADRO, 'h')) - 2);
                        int tabX = ((x/f->calcularProporcion(TAM_CUADRO, 'w')) - 0);

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
                        if (x > f->calcularProporcion(TAM_CUADRO*6+10, 'w') &&
                            y > f->calcularProporcion(TAM_CUADRO*11+10, 'h') &&
                            x < f->calcularProporcion(TAM_CUADRO*6+110, 'w') &&
                            y < f->calcularProporcion(TAM_CUADRO*11+43, 'h'))
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
                            int tabY = ((y/f->calcularProporcion(TAM_CUADRO, 'h')) - 2);
                            int tabX = ((x/f->calcularProporcion(TAM_CUADRO, 'w')) - 0);

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
            else if (Evento.type == SDL_KEYDOWN) //Salir
            {
                if (Evento.key.keysym.sym == SDLK_AC_BACK)
                {
                    cl->enviarPaqueteFin(PantallaJuego::colorJugador);
                }
            }
        }

    }while(!endgame);

    SDLNet_TCP_Close(*(cl->getCliente()));
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

    if (colorJugador != 1)
    {
    	PantallaJuego::dibujarTablero();
        dibujarReversiChan(5);
        SDL_RenderPresent(renderizador);
        SDL_Delay(2500);
    }
    else
    {
    	PantallaJuego::dibujarTablero();
        dibujarReversiChan(6);
        SDL_RenderPresent(renderizador);
        SDL_Delay(2500);
    }

    while (!endgame)
    {
        //Dibujamos el tablero
        PantallaJuego::dibujarTablero();
        SDL_RenderPresent(renderizador);

        if (Fin) //Si hay fin de juego
        {
            SDL_Delay(3000);
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
                    SDL_Delay(2000);

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
                            SDL_Delay(1000);

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
                if (not SDL_PollEvent(&Evento))
                {
                    continue;
                }

                if (Evento.type == SDL_MOUSEMOTION)
                {
                    if (dadosSet) //No hay para poner dados
                    {
                        int y = Evento.button.y;
                        int x = Evento.button.x;

                        int tabY = ((y/f->calcularProporcion(TAM_CUADRO, 'h')) - 2);
                        int tabX = ((x/f->calcularProporcion(TAM_CUADRO, 'w')) - 0);

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
                        if (x > f->calcularProporcion(TAM_CUADRO*6+10, 'w') &&
                            y > f->calcularProporcion(TAM_CUADRO*11+10, 'h') &&
                            x < f->calcularProporcion(TAM_CUADRO*6+110, 'w') &&
                            y < f->calcularProporcion(TAM_CUADRO*11+43, 'h'))
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
                            int tabY = ((y/f->calcularProporcion(TAM_CUADRO, 'h')) - 2);
                            int tabX = ((x/f->calcularProporcion(TAM_CUADRO, 'w')) - 0);

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
                    SDL_RenderPresent(renderizador);
                    SDL_Delay(3000);

                    endgame = true;
                }
                else if (Evento.type == SDL_KEYDOWN) //Salir
                {
                    if (Evento.key.keysym.sym == SDLK_AC_BACK)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                tablero.setFicha(i,j, colorJugador*(-1));
                            }
                        }

                        dibujarTablero();
                        SDL_RenderPresent(renderizador);
                        SDL_Delay(3000);

                        endgame = true;
                    }
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

