#ifndef FUNCIONESPANTALLA_H
#define FUNCIONESPANTALLA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "List.h"
#include "Fuente.h"

using namespace std;

/**
* Clase Encargada de realizar funciones en la pantalla facilmente
*
* @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
**/
class FuncionesPantalla
{
    private:
    ///Atributos
        List<Fuente> fuentes;
        string path;

    public:
    ///Constructor
        FuncionesPantalla();

    ///Getters
        string getPath();

    ///Funciones útiles para SDL
    
    	/**
    	 * Carga una textura a partir de un archivo de imagen
    	 *
    	 * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
    	 * @param  file    Nombre del archivo a abrir
    	 * @param  ren     Renderizador
    	 * @return         Textura resultante o NULL
    	 */
        SDL_Texture* cargarTextura(string file, SDL_Renderer *ren);

        /**
         * Crea una Textura de un texto en específico
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  message  Texto a Renderizar
         * @param  fontFile Nombre del archivo de la fuente
         * @param  color    Color que se usará
         * @param  fontSize Tamaño de la fuente
         * @param  renderer Renderizador
         * @return          Textura creada o NULL
         */
        SDL_Texture* renderizarTexto(string message, string fontFile, SDL_Color color, int fontSize, 
        						     SDL_Renderer *renderer);

        /**
         * Copia una Textura en la memoria de un Renderizador
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  tex Textura a poner en el Renderizador
         * @param  ren Renderizador Objetivo
         * @param  x   Posicion X del objetivo
         * @param  y   Posicion Y del objetivo
         * @param  w   Tamaño del largo de la textura
         * @param  h   Tamaño del alto de la textura
         */
        void renderizarTextura(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

        /**
         * Copia una Textura en la memoria de un Renderizador
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param  tex Textura a poner en el Renderizador
         * @param  ren Renderizador Objetivo
         * @param  x   Posicion X del objetivo
         * @param  y   Posicion Y del objetivo
         */
        void renderizarTextura(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
        
        /**
         * Carga la imagen de una ficha segun el estado
         *
         * @author Jonathan Sandoval <jonathan_s_pisis@yahoo.com.mx>
         * @param Renderer Apuntador con la direccion del renderizador en SDL
         * @param fila     Fila donde poner la ficha (0-7)
         * @param columna  Columna donde poner la ficha (0-7)
         * @param tipo     'B' para Blanco o 'N' para negro
         * @param estado   Estado de la ficha
         */
        void cargarFicha(SDL_Renderer* ren, int fila, int columna, char tipo, string estado);
};

#endif // FUNCIONESPANTALLA_H
