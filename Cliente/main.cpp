#include "Principal.h"

int main()
{
    Principal p;
    p.jugar();

    return 0;
}

//g++ `sdl-config --cflags --libs` -o interfaz interfaz.cpp -lSDL -lSDL_ttf
//sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev
//sudo dnf install SDL_ttf-devel.x86_64
