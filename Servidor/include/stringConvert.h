#ifndef STRINGCONVERT_H
#define STRINGCONVERT_H

#include <string>
#include <iostream>
#include <exception>

const int FLECHA_RIGHT = 300;
const int FLECHA_LEFT = 302;
const int FLECHA_UP = 301;
const int FLECHA_DOWN = 303;
const int SALTO_LINEA = 10;
const int BACKSPACE = 8;

//Clase de las excepciones
class stringConvertException : public std::exception
{
    protected:
        std::string msj;

    public:
        stringConvertException(std::string ss) { msj = ss; }
        const char* what() const throw() { return msj.c_str(); }

        ~stringConvertException() throw () {}
};

class stringConvert
{
    public:
    //Operaciones
        std::string intToStr(int);
        //transforma el entero a un std::string

        std::string intToStr(int, unsigned);
        //transforma el entero a un std::string con un tamaño

        std::string unsignedToStr(unsigned);
        //transforma un unsigned en un std::string

        std::string unsignedToStr(unsigned, unsigned);
        //transforma un unsigned en un std::string con un tamaño

        std::string charToStr(char);
        //transforma un char en un std::string

        std::string boolToStr(bool);
        //trasforma un bool en un std::string

        std::string floatToStr(float);
        //trasforma un float en un std::string

        std::string floatToStr(float, unsigned tam);
        //trasforma un float en un std::string con un tamaño

        std::string insertSpace(std::string, unsigned tam);
        //inserta espacioes en blanco al inicio hasta alcanzar un cierto tamaño

        std::string deleteSubCad(std::string subCad, std::string cadena);
        //eliminar todos los caracteres de 'caracter' en la cadena 'cadena' y la retorna

        std::string deleteInicialSpace(std::string cadena);
        //elimina todos los espacios en blanco que se hayan introducido al inicio

        std::string deleteFinalSpace(std::string cadena);
        //elimina todos los espacios en blanco que se hayan introducido al final

        std::string deleteAllSpace(std::string cadena);
        //elimina todos los espacios en blanco de toda la cadena

        int automataTypeData(std::string);
        //automata que devuelve el tipo de dato que es una cadena
        //100 si es Bool, 200 si es char, 300 si es unsigned, 400 si es int, 500 si es float, 600 si es un string

        int strToInt(std::string);
        //transforma un std::string en un int

        unsigned strToUnsigned(std::string);
        //transforma un std::string en un unsigned

        double strToFloat(std::string);
        //tranfosma un std::string en un double/float

        char strToChar(std::string);
        //transforma un std::string en un char

        bool strToBool(std::string);
        //tranfosma un std::string en un bool

        std::string strToStrUpper(std::string cad);
        //devuelve la forma maysucula de alguna palabra

        std::string strToStrLower(std::string cad);
        //devuelve la forma minuscula de alguna palabra

        std::string strToStrCapital(std::string cad);
        //devuelve la forma capital de alguna palabra

        std::string strToStrAcentos(std::string cad);
        //devuelve una cadena con los acentos bien puestos

        int compareStrAcentos(std::string cad1, std::string cad2, int inicio1, int rango1, int inicio2, int rango2);
        //compara 2 cadenas desde un inicio y un rango definido en caso de ser iguales
        //regresa 0 si son diferentes, 1 si son iguales y 2 si son iguales en linux

        int compareStrAcentos(std::string cad1, std::string cad2, int inicio1, int rango1);
        //compara la primer cadena desde un rango en relacion de otra cadena
        //regresa 0 si son diferentes, 1 si son iguales y 2 si son iguales en linux

        int pressButtom();
        //cuando aprieta algun botón, regresa el numero de ese boton apretado
        //adicialmente puede usar kbhit() y getch()

        std::string keepBooton(std::string);
        //realiza el ciclo para escribir en pantalla con un mensaje

        bool setPassword(std::string password);
        //permite escribir asteriscos mientras se escribe.
        //devuelve true o false en relación de lo que se aprieta y lo comapra con password
        //si son iguales regresa true, sino regresa false

        bool setPassword(std::string msj, std::string password);
        //permite escribir asteriscos mientras se escribe.
        //devuelve true o false en relación de lo que se aprieta y lo comapra con password
        //imprime el mensaje msj y despues permite escribir

        char giveChar(std::string);
        //Este método recibe un mensaje y devuelve un caracter

        char giveChar();
        //Este método devuelve un char

        std::string giveString(std::string);
        //Este método recibe un mensaje y devuelve una cadena simple

        std::string giveString();
        //este método devuelve un string

        std::string giveStringPassword();
        //este método devuelve un string pero imprime asteriscos mientras se escribe

        std::string giveStringPassword(std::string);
        //este método devuelve un string pero imprimer asterisco mientras se escribe

        int giveUnsigned(std::string);
        //Este método recibe un mensaje y devuelve un numero entero

        int giveUnsigned();
        //Este método devuelve un entero

        float giveFloat(std::string);
        //Este método recibe un mensaje y devuelve un numero real

        float giveFloat();
        //este modoto devuelve un numero real

        int giveInt(std::string);
        //Este método recibe un mensaje y devuelve un numero real

        int giveInt();
        //este modoto devuelve un numero real

};

#endif // STRINGCONVERT_H
