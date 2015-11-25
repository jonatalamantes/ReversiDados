#include "../include/stringConvert.h"

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

string stringConvert::intToStr(int number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

string stringConvert::intToStr(int number, unsigned tamMax)
{
    string aux;
    stringstream ss;
    ss << number;
    aux = ss.str();

    while (aux.size() < tamMax)
    {
        aux.insert(0, "0");
    }

    return aux;
}

string stringConvert::charToStr(char letter)
{
    stringstream ss;
    ss << letter;
    return ss.str();
}

string stringConvert::floatToStr(float number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

string stringConvert::floatToStr(float number, unsigned tamMax)
{
    string aux;
    stringstream ss;
    ss << number;
    aux = ss.str();

    while (aux.size() < tamMax)
    {
        aux.insert(0, "0");
    }

    return aux;
}

string stringConvert::unsignedToStr(unsigned number)
{
    stringstream ss;
    ss << number;
    return ss.str();
}

string stringConvert::unsignedToStr(unsigned number, unsigned tamMax)
{
    string aux;
    stringstream ss;
    ss << number;
    aux = ss.str();

    while (aux.size() < tamMax)
    {
        aux.insert(0, "0");
    }

    return aux;
}

string stringConvert::boolToStr(bool condition)
{
    if (condition == true)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

string stringConvert::deleteSubCad(string subCad, string cadena)
{
    if (cadena.size() > subCad.size())
    {
        string aux = cadena;

        //recorremos la cadena
        for (unsigned int i = 0; i < aux.size(); i++)
        {
            //revisamos que sea igual eltrozo con un trozo que encontremos
            if (subCad.compare(aux.substr(i, subCad.size())) == 0)
            {
                //lo eliminarmos si es así
                aux.erase(i, subCad.size());

                //y volvemos a iniciar el recorrido
                i = 0;
            }
        }

        return aux;
    }
    else
    {
        return cadena;
    }
}

string stringConvert::insertSpace(string cad, unsigned tam)
{
    string aux = cad;

    if (aux.size() < tam)
    {
        while (aux.size() != tam)
        {
            aux.append(" ");
        }
    }
    return aux;
}

string stringConvert::deleteAllSpace(string cad)
{
    string aux = stringConvert::deleteSubCad(" ", cad);
    aux = stringConvert::deleteSubCad("\t", aux);
    aux = stringConvert::deleteSubCad("\n", aux);

    return aux;
}

string stringConvert::deleteInicialSpace(string cadena)
{
    string aux = cadena;

    for (unsigned int i = 0; i < cadena.size(); i++)
    {
        if (aux[0] == ' ' || aux[0] == '\n' || aux[0] == '\t')
        {
            aux.erase(0, 1);
            i--;
        }
        else
        {
            break;
        }
    }

    return aux;
}

string stringConvert::deleteFinalSpace(string cadena)
{
    string aux = cadena;

    for (unsigned int i = cadena.size() - 1; i >= 0; i--)
    {
        if (aux[aux.size() - 1] == ' ' || aux[aux.size() - 1] == '\n' || aux[aux.size() - 1] == '\t')
        {
            aux.erase(aux.size() - 1, 1);
            i++;
        }
        else
        {
            break;
        }
    }

    return aux;
}

int stringConvert::automataTypeData(string cad)
{
    if ( (cad.compare("true") == 0) || (cad.compare("false") == 0) )
    {
        return 100; //es bool
    }
    else if (cad.size() == 1)
    {
        if (isdigit(cad[0]))
        {
            return 300; //es un int positivo
        }
        else
        {
            return 200; //es char
        }
    }
    else
    {
        int estadoActual = 1;
        bool negative = false;

        for(unsigned int i = 0; i < cad.size(); i++)
        {
            if (estadoActual == 1)
            {
                if (isdigit(cad[i]))
                {
                    estadoActual = 2;
                }
                else if (cad[i] == '+')
                {
                    estadoActual = 3;
                }
                else if (cad[i] == '-')
                {
                    estadoActual = 3;
                    negative = true;
                }
                else
                {
                    estadoActual = 0;
                }
            }
            else if (estadoActual == 3)
            {
                if (isdigit(cad[i]))
                {
                    estadoActual = 2;
                }
                else
                {
                    estadoActual = 0;
                }
            }
            else if (estadoActual == 2) //estado del int
            {
                if (isdigit(cad[i]))
                {
                    estadoActual = 2;
                }
                else if (cad[i] == '.')
                {
                    estadoActual = 4;
                }
                else
                {
                    estadoActual = 0;
                }
            }
            else if (estadoActual == 4)
            {
                if (isdigit(cad[i]))
                {
                    estadoActual = 5;
                }
                else
                {
                    estadoActual = 0;
                }
            }
            else if (estadoActual == 5)
            {
                if (isdigit(cad[i]))
                {
                    estadoActual = 5;
                }
                else
                {
                    estadoActual = 0;
                }
            }
            else
            {
                estadoActual = 0;
            }
        } //final del for

        if ( (estadoActual == 2) && (negative == false) )
        {
            return 300; //es unsigned o int positivo
        }
        else if ( (estadoActual == 2) && (negative == true) )
        {
            return 400; //es un int negativo
        }
        else if (estadoActual == 5)
        {
            return 500; //es un float
        }
        else
        {
            return 600; //es un string
        }
    }//final del else
}

int stringConvert::strToInt(string cad)
{
    int estado = automataTypeData(cad);

    if ( (estado == 300) || (estado == 400) )
    {
        return (atoi(cad.c_str()));
    }
    else
    {
        throw stringConvertException("Error, la cadena no es solo de enteros");
    }
}

unsigned stringConvert::strToUnsigned(string cad)
{
    int estado = automataTypeData(cad);

    if (estado == 300)
    {
        return (atoi(cad.c_str()));
    }
    else
    {
        throw stringConvertException("Error, la cadena no es solo de enteros");
    }
}

double stringConvert::strToFloat(string cad)
{
    int estado = automataTypeData(cad);

    if ( (estado == 400) || (estado == 300) )
    {
        return (atoi(cad.c_str()));
    }
    else if (estado == 500)
    {
        return (strtod(cad.c_str(), NULL));
    }
    else
    {
        throw stringConvertException("Error, la cadena no es solo de numeros");
    }
}

char stringConvert::strToChar(string cad)
{
    int estado = automataTypeData(cad);

    if (estado == 200)
    {
        return (cad[0]);
    }
    else
    {
        throw stringConvertException("Error, la cadena es demasiado larga");
    }
}

bool stringConvert::strToBool(string cad)
{
    int estado = automataTypeData(cad);

    if (estado == 100)
    {
        if (cad.compare("true") == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        throw stringConvertException("Error, la cadena no es bool");
    }
}

#ifdef WIN32

#include <conio.h>
#include <stdio.h>

string stringConvert::strToStrAcentos(string cad)
{
    string aux;

    for(unsigned int i = 0; i < cad.size(); i++)
    {
        if (isdigit(cad[i]) || isalpha(cad[i]) || islower(cad[i]) || isspace(cad[i]))
        {
            aux.append(cad.substr(i,1));
        }
        else if (cad[i] == -61)
        {
            if (cad[i + 1] == -111) //ha escrito Ñ Mayuscula
            {
                aux.append("\xA5");
                i++;
            }
            else if (cad[i + 1] == -79) //ha escrito ñ
            {
                aux.append("\xA4");
                i++;
            }
            else if (cad[i + 1] == -95) //ha escrito a con acento
            {
                aux.append("\xA0");
                i++;
            }
            else if (cad[i + 1] == -87) //ha escrito e con acento
            {
                aux.append("\x82");
                i++;
            }
            else if (cad[i + 1] == -83) //ha escrito i con acento
            {
                i++;
                aux.append("\xA1");
            }
            else if (cad[i + 1] == -70) //ha escrito u con acento
            {
                aux.append("\xA3");
                i++;
            }
            else if (cad[i + 1] == -162 || cad[i+1] == -94 || cad[i+1] == -77) //ha escrito o con acento
            {
                aux.append("\xA2");
                i++;
            }
            else if (cad[i + 1] == -127 || cad[i+1] == -75) //ha escrito Á con acento
            {
                aux.append("\xB5");
                i++;
            }
            else if (cad[i + 1] == -119) //ha escrito É con acento
            {
                aux.append("\x90");
                i++;
            }
            else if (cad[i + 1] == -115) //ha escrito Í con acento
            {
                aux.append("\xD6");
                i++;
            }
            else if (cad[i + 1] == -109) //ha escrito Ó con acento
            {
                aux.append("\xE0");
                i++;
            }
            else if (cad[i + 1] == -102 || cad[i] == -23 || cad[i] == 233) //ha escrito Ú con acento
            {
                aux.append("\xE9");
                i++;
            }
            else if (cad[i + 1] == -100) //ha escrito Ü con acento
            {
                aux.append("\x9A");
                i++;
            }
            else if (cad[i + 1] == -68) //ha escrito ü con acento
            {
                aux.append("\x81");
                i++;
            }
            else
            {
                aux.append("");
            }
        }
        else if (cad[i] == -62)
        {
            if (cad[i+1] == -65) //escribio ¿
            {
                aux.append("\xA8");
                i++;
            }
        }
        else if (cad[i] == -84 || cad[i] == -65) //escribio ¿
        {
            aux.append("\xA8");
        }
        else if (cad[i] == 63) //escribio ?
        {
            aux.append("\x3f");
        }
        else if (cad[i] == -15) //escribio ñ
        {
            aux.append("\xA4");
        }
        else if (cad[i] == -47) //escribio Ñ
        {
            aux.append("\xA5");
        }
        else if (cad[i] == -31) //ha escrito a con acento
        {
            aux.append("\xA0");
        }
        else if (cad[i] == -126 || cad[i] == -23) //ha escrito e con acento
        {
            aux.append("\x82");
        }
        else if (cad[i] == -19) //ha escrito i con acento
        {
            aux.append("\xA1");
        }
        else if (cad[i] == -6) //ha escrito u con acento
        {
            aux.append("\xA3");
        }
        else if (cad[i] == -77 || cad[i] == 162 || cad[i] == 179 || cad[i] == -13) //ha escrito o con acento
        {
            aux.append("\xA2");
        }
        else if (cad[i] == -63 || cad[i] == -75) //ha escrito Á con acento
        {
            aux.append("\xB5");
        }
        else if (cad[i] == -55) //ha escrito É con acento
        {
            aux.append("\x90");
        }
        else if (cad[i] == -51) //ha escrito Í con acento
        {
            aux.append("\xD6");
        }
        else if (cad[i] == -45 || cad[i] == 224) //ha escrito Ó con acento
        {
            aux.append("\xE0");
        }
        else if (cad[i] == -36 || cad[i] == -38 || cad[i] == 233 || cad[i] == -116) //ha escrito Ú con acento
        {
            aux.append("\xE9");
        }
        else if (cad[i] == -100 || cad[i] == 181) //ha escrito Ü con acento
        {
            aux.append("\x9A");
        }
        else if (cad[i] == -4 || cad[i] == 129) //ha escrito ü con acento
        {
            aux.append("\x81");
        }

        else
        {
            aux.append(cad.substr(i,1));
        }
    }

    return aux;
}



string stringConvert::strToStrUpper(string cad)
{
    string aux = cad;

    aux = strToStrAcentos(aux);

    for (unsigned int i = 0; i < aux.size(); i++)
    {
        if (islower(aux[i]))
        {
            aux[i] = toupper(aux[i]);
        }
        else if (compareStrAcentos(aux, "\xB5", i, 1))
        {
            continue;
        }
        else if (compareStrAcentos(aux, "\xA0", i, 1)) //a con acento minuscula
        {
            aux.replace(i,1, "\xB5"); //A con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\x82", i, 1)) //e con acento minuscula
        {
            aux.replace(i,1, "\x90"); //e con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA1", i, 1)) //i con acento minuscula
        {
            aux.replace(i,1, "\xD6"); //i con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA2", i, 1)) //o con acento minuscula
        {
            aux.replace(i,1, "\xE0"); //o con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA3", i, 1)) //u con acento minuscula
        {
            aux.replace(i,1, "\xE9"); //u con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA4", i, 1)) //ñ con acento minuscula
        {
            aux.replace(i,1, "\xA5"); //Ñ con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\x81", i, 1)) //u con dieresis minuscula
        {
            aux.replace(i,1, "\x9A"); //u con dieresis mayuscula
        }
        else
        {
            continue;
        }
    }

    return aux;
}

string stringConvert::strToStrLower(string cad)
{
    string aux = strToStrAcentos(cad);

    for (unsigned int i = 0; i < aux.size(); i++)
    {
        if (isupper(aux[i]))
        {
            aux[i] = tolower(aux[i]);
        }
        else if (compareStrAcentos(aux, "\xB5", i, 1)) //A con acento mayuscula
        {
            aux.replace(i,1, "\xA0"); //a con acento minuscula
        }
        else if (compareStrAcentos(aux, "\x90", i, 1)) //e con acento mayuscula
        {
            aux.replace(i,1, "\x82"); //e con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xD6", i, 1)) //i con acento mayuscula
        {
            aux.replace(i,1, "\xA1"); //i con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xE0", i, 1)) //o con acento mayuscula
        {
            aux.replace(i,1, "\xA2"); //o con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xE9", i, 1)) //u con acento mayuscula
        {
            aux.replace(i,1, "\xA3"); //u con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xA5", i, 1)) //Ñ con acento mayuscula
        {
            aux.replace(i,1, "\xA4"); //ñ con acento minuscula
        }
        else if (compareStrAcentos(aux, "\x9A", i, 1)) //u con dieresis mayuscula
        {
            aux.replace(i,1, "\x81"); //u con dieresis minuscula
        }
        else
        {
            continue;
        }
    }

    return aux;
}

string stringConvert::strToStrCapital(string cad)
{
    string aux = cad;

    for (unsigned int i = 0; i < aux.size(); i++)
    {
        if (isupper(aux[i]))
        {
            aux[i] = tolower(aux[i]);
        }
        else if (compareStrAcentos(aux, "\xB5", i, 1)) //A con acento mayuscula
        {
            aux.replace(i,1, "\xA0"); //a con acento minuscula
        }
        else if (compareStrAcentos(aux, "\x90", i, 1)) //e con acento mayuscula
        {
            aux.replace(i,1, "\x82"); //e con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xD6", i, 1)) //i con acento mayuscula
        {
            aux.replace(i,1, "\xA1"); //i con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xE0", i, 1)) //o con acento mayuscula
        {
            aux.replace(i,1, "\xA2"); //o con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xE9", i, 1)) //u con acento mayuscula
        {
            aux.replace(i,1, "\xA3"); //u con acento minuscula
        }
        else if (compareStrAcentos(aux, "\xA5", i, 1)) //Ñ con acento mayuscula
        {
            aux.replace(i,1, "\xA4"); //ñ con acento minuscula
        }
        else if (compareStrAcentos(aux, "\x9A", i, 1)) //u con dieresis mayuscula
        {
            aux.replace(i,1, "\x81"); //u con dieresis minuscula
        }
        else
        {
            continue;
        }
    }

    if (aux != "")
    {
        if (islower(aux[0]))
        {
            aux[0] = toupper(aux[0]);
        }
        else if (compareStrAcentos(aux, "\xA0", 0, 1)) //a con acento minuscula
        {
            aux.replace(0,1, "\xB5"); //A con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\x82", 0, 1)) //e con acento minuscula
        {
            aux.replace(0,1, "\x90"); //e con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA1", 0, 1)) //i con acento minuscula
        {
            aux.replace(0,1, "\xD6"); //i con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA2", 0, 1)) //o con acento minuscula
        {
            aux.replace(0,1, "\xE0"); //o con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA3", 0, 1)) //u con acento minuscula
        {
            aux.replace(0,1, "\xE9"); //u con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\xA4", 0, 1)) //ñ con acento minuscula
        {
            aux.replace(0,1, "\xA5"); //Ñ con acento mayuscula
        }
        else if (compareStrAcentos(aux, "\x81", 0, 1)) //u con dieresis minuscula
        {
            aux.replace(0,1, "\x9A"); //u con dieresis mayuscula
        }
        else
        {
            //no actues
        }
    }

    return aux;
}

int stringConvert::pressButtom()
{
    while (true)
    {
        int c;

        if(kbhit())
        {
            c = getch();
            //std:://cout << c << "|";

            if (c == 13)
            {
                return 10;
            }
            else if (c == -32 || c == 224)
            {
                int a = getch();
                //std:://cout << a << "*";

                if (a == 75) //flecha izq.
                {
                    return FLECHA_LEFT;
                }
                else if ((a == 72) || (a == 79)) //Flecha arriba o fin
                {
                    return FLECHA_UP;
                }
                else if ((a == 80) || (a == 71)) //Flecha abajo o inicio
                {
                    return FLECHA_DOWN;
                }
                else if (a == 77) //Flecha derecha
                {
                    return FLECHA_RIGHT;
                }
                else if (a == 224)
                {
                    return 0;
                }
                else
                {
                    return c;
                }
            }
            else
            {
                return c;
            }
        }
    }
}


int stringConvert::compareStrAcentos(string cad1, string cad2, int inicio1, int rango1, int inicio2, int rango2)
{
    string aux1 = strToStrAcentos((cad1).substr(inicio1, rango1));
    string aux2 = strToStrAcentos((cad2).substr(inicio2, rango2));

    if (aux1.compare(aux2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

    return 0;
}

int stringConvert::compareStrAcentos(string cad1, string cad2, int inicio1, int rango1)
{
    string aux1 = strToStrAcentos((cad1).substr(inicio1, rango1));

    if (aux1.compare(strToStrAcentos(cad2)) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#else //Asumiendo Linux

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <cstdlib>

static struct termios old, new1;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new1 = old; /* make new settings same as old settings */
  new1.c_lflag &= ~ICANON; /* disable buffered i/o */
  new1.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new1); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void)
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
  return getch_(1);
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int stringConvert::pressButtom()
{
    while (true)
    {
        int c;

        if(kbhit())
        {
            c = getch();
            //std:://cout << c << "|";

            if (c == 27)
            {
				int a = getch();

                //std:://cout << a << "*";

                if (a == 91)
                {
					int b = getch();
                    //std:://cout << b << "/";

                    if (b == 68) //flecha izq.
                    {
						return FLECHA_LEFT;
					}
                    else if (b == 65) //flecha arriba
                    {
                        return FLECHA_UP;
                    }
                    else if (b == 66) //Flecha abajo o inicio
                    {
                        return FLECHA_DOWN;
                    }
                    else if (b == 67) //Flecha derecha
                    {
                        return FLECHA_RIGHT;
                    }
                    else
                    {
                        //std:://cout << b << ":";
                    }
                }
                else
                {
                    //nada
                }
            }
            else if (c == 127)
            {
                return 8;
            }
            else if ( (c == 39) || (c == -61) )
            {
                int a = getch();
                //std:://cout << a << "*";
                return a;
            }
            else
            {
                return c % 257;
            }
        }
    }
}

string stringConvert::strToStrAcentos(string cad)
{
    string aux;

    for(unsigned int i = 0; i < cad.size(); i++)
    {
        if (isdigit(cad[i]) || isalpha(cad[i]) || islower(cad[i]) || isspace(cad[i]))
        {
            aux.append(cad.substr(i,1));
        }
        else if (cad[i] == -61) //Simbolo de acento
        {
            if (cad[i + 1] == -111) //ha escrito Ñ Mayuscula
            {
                aux.append("Ñ");
                i++;
            }
            else if (cad[i + 1] == -79) //ha escrito ñ
            {
                aux.append("ñ");
                i++;
            }
            else if (cad[i + 1] == -95) //ha escrito a con acento
            {
                aux.append("á");
                i++;
            }
            else if (cad[i + 1] == -87) //ha escrito e con acento
            {
                aux.append("é");
                i++;
            }
            else if (cad[i + 1] == -83) //ha escrito i con acento
            {
                i++;
                aux.append("í");
            }
            else if (cad[i + 1] == -70 || cad[i + 1] == -6) //ha escrito u con acento
            {
                aux.append("ú");
                i++;
            }
            else if (cad[i + 1] == -77) //ha escrito o con acento
            {
                aux.append("ó");
                i++;
            }
            else if (cad[i + 1] == -127) //ha escrito Á con acento
            {
                aux.append("Á");
                i++;
            }
            else if (cad[i + 1] == -119) //ha escrito É con acento
            {
                aux.append("É");
                i++;
            }
            else if (cad[i + 1] == -115) //ha escrito Í con acento
            {
                aux.append("Í");
                i++;
            }
            else if (cad[i + 1] == -109) //ha escrito Ó con acento
            {
                aux.append("Ó");
                i++;
            }
            else if (cad[i + 1] == -102) //ha escrito Ú con acento
            {
                aux.append("Ú");
                i++;
            }
            else if (cad[i + 1] == -100) //ha escrito Ü con acento
            {
                aux.append("Ü");
                i++;
            }
            else if (cad[i + 1] == -68) //ha escrito ü con acento
            {
                aux.append("ü");
                i++;
            }
            else
            {
                aux.append("");
            }
        }
        else if (cad[i] == -62)
        {
            if (cad[i+1] == -65) //escribio ¿
            {
                aux.append("¿");
                i++;
            }
        }
        else if (cad[i] == -65 || cad[i] == -84) //escribio ¿
        {
            aux.append("¿");
        }
        else if (cad[i] == 63) //escribio ?
        {
            aux.append("?");
        }
        else if ( (cad[i] == -15) || (cad[i] == -79) )//escribio ñ
        {
            aux.append("ñ");
        }
        else if ( (cad[i] == -47) || (cad[i] == -111) ) //escribio Ñ
        {
            aux.append("Ñ");
        }
        else if ( (cad[i] == -31) || (cad[i] == -95) ) //ha escrito a con acento
        {
            aux.append("á");
        }
        else if ( (cad[i] == -23) || (cad[i] == -126) || (cad[i] == -87)) //ha escrito e con acento
        {
            aux.append("é");
        }
        else if ( (cad[i] == -19) || (cad[i] == -83) ) //ha escrito i con acento
        {
            aux.append("í");
        }
        else if ( (cad[i] == -6) || (cad[i] == -70)) //ha escrito u con acento
        {
            aux.append("ú");
        }
        else if ( (cad[i] == -13) || (cad[i] == -77) ) //ha escrito o con acento
        {
            aux.append("ó");
        }
        else if ( (cad[i] == -63)  || (cad[i] == -127) ) //ha escrito Á con acento
        {
            aux.append("Á");
        }
        else if ( (cad[i] == -55)  || (cad[i] == -119) ) //ha escrito É con acento
        {
            aux.append("É");
        }
        else if ( (cad[i] == -51)  || (cad[i] == -115) ) //ha escrito Í con acento
        {
            aux.append("Í");
        }
        else if ( (cad[i] == -45)  || (cad[i] == -109) ) //ha escrito Ó con acento
        {
            aux.append("Ó");
        }
        else if ( (cad[i] == -36)  || (cad[i] == -102) ) //ha escrito Ú con acento
        {
            aux.append("Ú");
        }
        else if ( (cad[i] == -100)  || (cad[i] == -100) ) //ha escrito Ü con acento
        {
            aux.append("Ü");
        }
        else if ( (cad[i] == -4)  || (cad[i] == -68) ) //ha escrito ü con acento
        {
            aux.append("ü");
        }

        else
        {
            aux.append(cad.substr(i,1));
        }
    }

    return aux;
}

string stringConvert::strToStrUpper(string cad)
{
    string aux = cad;

    aux = strToStrAcentos(aux);

    for (unsigned int i = 0; i < aux.size(); i++)
    {
        if (islower(aux[i]))
        {
            aux[i] = toupper(aux[i]);
        }
        else if (compareStrAcentos(aux, "á", i, 1)) //a con acento minuscula
        {
            aux.replace(i,1, "Á"); //A con acento mayuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "é", i, 1)) //e con acento minuscula
        {
            aux.replace(i, 1, "É"); //e con acento mayuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "í", i, 1)) //i con acento minuscula
        {
            aux.replace(i,1, "Í"); //i con acento mayuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "ó", i, 1)) //o con acento minuscula
        {
            aux.replace(i,1, "Ó"); //o con acento mayuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "ú", i, 1)) //u con acento minuscula
        {
            aux.replace(i,1, "Ú"); //u con acento mayuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "ñ", i ,1)) //ñ con acento minuscula
        {
            aux.replace(i,1, "Ñ"); //Ñ con acento mayuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "ü", i, 1)) //ü con dieresis minuscula
        {
            aux.replace(i,1, "Ü"); //u con dieresis mayuscula
            aux.erase(i,1);
        }
        else
        {
            continue;
        }
    }

    return strToStrAcentos(aux);
}

string stringConvert::strToStrLower(string cad)
{
    string aux = strToStrAcentos(cad);

    for (unsigned int i = 0; i < aux.size(); i++)
    {
        if (isupper(aux[i]))
        {
            aux[i] = tolower(aux[i]);
        }
        else if (compareStrAcentos(aux, "Á", i, 1)) //A con acento mayuscula
        {
            aux.replace(i,1, "á"); //a con acento minuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "É", i, 1)) //e con acento mayuscula
        {
            aux.replace(i,1, "é"); //e con acento minuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "Í", i, 1)) //i con acento mayuscula
        {
            aux.replace(i,1, "í"); //i con acento minuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "Ó", i, 1)) //o con acento mayuscula
        {
            aux.replace(i,1, "ó"); //o con acento minuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "Ú", i, 1)) //u con acento mayuscula
        {
            aux.replace(i,1, "ú"); //u con acento minuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "Ñ", i, 1)) //Ñ con acento mayuscula
        {
            aux.replace(i,1, "ñ"); //ñ con acento minuscula
            aux.erase(i,1);
        }
        else if (compareStrAcentos(aux, "Ü", i, 1)) //u con dieresis mayuscula
        {
            aux.replace(i,1, "ü"); //u con dieresis minuscula
            aux.erase(i,1);
        }
        else
        {
            continue;
        }
    }

    return strToStrAcentos(aux);
}

string stringConvert::strToStrCapital(string cad)
{
    string aux = cad;

    aux = strToStrLower(aux);

    if (aux != "")
    {
        if (islower(aux[0]))
        {
            aux[0] = toupper(aux[0]);
        }
        else if (compareStrAcentos(aux, "á", 0, 1)) //a con acento minuscula
        {
            aux.replace(0,1, "Á"); //A con acento mayuscula
            aux.erase(0,1);
        }
        else if (compareStrAcentos(aux, "é", 0, 1)) //e con acento minuscula
        {
            aux.replace(0,1, "É"); //e con acento mayuscula
            aux.erase(0,1);
        }
        else if (compareStrAcentos(aux, "í", 0, 1)) //i con acento minuscula
        {
            aux.replace(0,1, "Í"); //i con acento mayuscula
            aux.erase(0,1);
        }
        else if (compareStrAcentos(aux, "ó", 0, 1)) //o con acento minuscula
        {
            aux.replace(0,1, "Ó"); //o con acento mayuscula
            aux.erase(0,1);
        }
        else if (compareStrAcentos(aux, "ú", 0, 1)) //u con acento minuscula
        {
            aux.replace(0,1, "Ú"); //u con acento mayuscula
            aux.erase(0,1);
        }
        else if (compareStrAcentos(aux, "ñ", 0, 1)) //ñ con acento minuscula
        {
            aux.replace(0,1, "Ñ"); //Ñ con acento mayuscula
            aux.erase(0,1);
        }
        else if (compareStrAcentos(aux, "ü", 0, 1)) //u con dieresis minuscula
        {
            aux.replace(0,1, "Ü"); //u con dieresis mayuscula
            aux.erase(0,1);
        }
        else
        {
            //no actues
        }
    }

    return strToStrAcentos(aux);
}

int stringConvert::compareStrAcentos(string cad1, string cad2, int inicio1, int rango1, int inicio2, int rango2)
{
    string aux1 = strToStrAcentos((cad1).substr(inicio1, rango1));
    string aux2 = strToStrAcentos((cad2).substr(inicio2, rango2));

    string aux3 = strToStrAcentos((cad1).substr(inicio1, rango1 + 1));
    string aux4 = strToStrAcentos((cad2).substr(inicio2, rango2 + 1));

    if (aux1.compare(aux2) == 0)
    {
        return 1;
    }
    else if (aux3.compare(aux4) == 0)
    {
        return 2;
    }
    else
    {
        return 0;
    }

    return 0;
}

int stringConvert::compareStrAcentos(string cad1, string cad2, int inicio1, int rango1)
{
    string aux1 = strToStrAcentos((cad1).substr(inicio1, rango1));
    string aux2 = strToStrAcentos((cad1).substr(inicio1, rango1 + 1));

    if (aux1.compare(strToStrAcentos(cad2)) == 0)
    {
        return 1;
    }
    else if (aux2.compare(strToStrAcentos(cad2)) == 0)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

#endif


string stringConvert::keepBooton(string msj)
{
    string clave = strToStrAcentos(msj);
    char letra;
    int entero;
    unsigned int iniciaTam = msj.size();

    std::cout << std::endl;

    do
    {
        std::cout << "\r";
        std::cout << clave;

        entero = pressButtom();
        letra = entero;

        if (entero == BACKSPACE)
        {
            if (clave.size() <= iniciaTam)
            {
                std::cout << "";
            }
            else
            {
                std::cout << "\b" << "\b" << "  " << "\b" << "\b";
                clave.erase(clave.size() - 1, 1);
            }
        }
        else if (letra == '\n')
        {
            if (clave.size() <= iniciaTam)
            {
                letra = 'a';
            }

            std::cout << "\b\b";
        }
        else
        {
            if (entero >= 0)
            {
                clave.append(charToStr(letra));
            }
            else
            {
                clave.append(strToStrAcentos(charToStr(letra)));
            }
        }

    }while (letra != '\n');

    clave = clave.erase(0, iniciaTam);
    clave = deleteInicialSpace(clave);
    clave = deleteFinalSpace(clave);

    return strToStrAcentos(clave);
}

bool stringConvert::setPassword(string password)
{
    string clave = stringConvert::giveStringPassword();

    if (compareStrAcentos(password, clave, 0, password.size() - 1, 0, clave.size() - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool stringConvert::setPassword(string msj, string password)
{
    string clave = stringConvert::giveStringPassword(msj);

    if (compareStrAcentos(password, clave, 0, password.size() - 1, 0, clave.size() - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

char stringConvert::giveChar(string cad)
{
    int x;

    std::cout << strToStrAcentos(cad);

    x = pressButtom();

    return x;
}

char stringConvert::giveChar()
{
    return giveChar("");
}

string stringConvert::giveString(string msj)
{
    string cad = keepBooton(msj);

    return cad;
}

string stringConvert::giveString()
{
    string cad = keepBooton("");

    return cad;
}

int stringConvert::giveUnsigned(string msj)
{
    string clave = strToStrAcentos(msj);
    char letra;
    int entero;
    unsigned int iniciaTam = msj.size();

    std::cout << std::endl;

    do
    {
        std::cout << "\r";
        std::cout << clave;

        entero = pressButtom();
        letra = entero;

        if (entero == BACKSPACE)
        {
            if (clave.size() <= iniciaTam)
            {
                std::cout << "";
            }
            else
            {
                std::cout << "\b" << "\b" << "  " << "\b" << "\b";
                clave.erase(clave.size() - 1, 1);
            }
        }
        else if (entero == SALTO_LINEA)
        {
            if (clave.size() <= iniciaTam)
            {
                entero = 50;
            }
            else
            {
                break;
            }

            std::cout << "\b\b";
        }
        else if (isdigit(letra))
        {
            clave = clave + charToStr(letra);
        }

    }while (entero != SALTO_LINEA);

    clave = clave.erase(0, iniciaTam);
    clave = deleteAllSpace(clave);

    return strToUnsigned(clave);
}

int stringConvert::giveUnsigned()
{
    return giveUnsigned("");
}

float stringConvert::giveFloat(string msj)
{
    string clave = strToStrAcentos(msj);
    char letra;
    int entero;
    bool decimalUsado = false;
    unsigned int iniciaTam = msj.size();

    std::cout << std::endl;

    do
    {
        std::cout << "\r";
        std::cout << clave;

        entero = pressButtom();
        letra = entero;

        if (entero == BACKSPACE)
        {
            if (clave.size() <= iniciaTam)
            {
                std::cout << "";
            }
            else
            {
                std::cout << "\b" << "\b" << "  " << "\b" << "\b";

                if (clave[clave.size() - 1] == '.')
                {
                    decimalUsado = false;
                }

                clave.erase(clave.size() - 1, 1);
            }
        }
        else if (letra == '\n')
        {
            if (clave.size() <= iniciaTam)
            {
                letra = 'a';
            }

            if (not isdigit(clave[clave.size() - 1]))
            {
                letra = 'a';
            }

            std::cout << "\b\b";
        }
        else if (isdigit(letra))
        {
            clave.append(charToStr(letra));
        }
        else if (letra == '.')
        {
            if (not decimalUsado)
            {
                decimalUsado = true;
                clave.append(charToStr(letra));
            }
        }
        else if (letra == '+' || letra == '-')
        {
            if (clave.size() <= iniciaTam)
            {
                clave.append(charToStr(letra));
            }
        }
        else
        {
            //No actues
        }

    }while (letra != '\n');

    clave = clave.erase(0, iniciaTam);
    clave = deleteAllSpace(clave);

    return strToFloat(clave);
}

float stringConvert::giveFloat()
{
    return giveFloat("");
}

int stringConvert::giveInt(string msj)
{
    string clave = strToStrAcentos(msj);
    char letra;
    int entero;
    unsigned int iniciaTam = msj.size();

    std::cout << std::endl;

    do
    {
        std::cout << "\r";
        std::cout << clave;

        entero = pressButtom();
        letra = entero;

        if (entero == BACKSPACE)
        {
            if (clave.size() <= iniciaTam)
            {
                std::cout << "";
            }
            else
            {
                std::cout << "\b" << "\b" << "  " << "\b" << "\b";
                clave.erase(clave.size() - 1, 1);
            }
        }
        else if (letra == '\n')
        {
            if (clave.size() <= iniciaTam)
            {
                letra = 'a';
            }

            if (not isdigit(clave[clave.size() - 1]))
            {
                letra = 'a';
            }

            std::cout << "\b\b";
        }
        else if (isdigit(letra))
        {
            clave.append(charToStr(letra));
        }
        else if (letra == '+' || letra == '-')
        {
            if (clave.size() <= iniciaTam)
            {
                clave.append(charToStr(letra));
            }
        }
        else
        {
            //No actues
        }

    }while (letra != '\n');

    clave = clave.erase(0, iniciaTam);
    clave = deleteAllSpace(clave);

    return strToInt(clave);
}

int stringConvert::giveInt()
{
    return giveInt("");
}

string stringConvert::giveStringPassword(string msj)
{
    string clave;
    string asterisco;
    char a;

    std::cout << std::endl;
    std::cout << strToStrAcentos(msj);

    do
    {
        a = pressButtom();

        if (a == BACKSPACE)
        {
            if (clave.size() > 0)
            {
                clave.erase(clave.size() - 1, 1);
                asterisco.erase(asterisco.size() - 1, 1);
                std::cout << "\b" << "  ";
            }
            else if (clave.size() <= 0)
            {
                std::cout << "";
            }

            std::cout << "\r";
            std::cout << strToStrAcentos(msj);

            for (unsigned int i = 0; i+1 < asterisco.size(); i++)
            {
                std::cout << asterisco.substr(i,1);
            }

            if (asterisco.size() > 0)
            {
                std::cout << strToStrAcentos(clave.substr(asterisco.size() - 1, 1));
            }
        }
        else if (a == '\n')
        {
            std::cout << "\b\b";
            std::cout << "\r";
            std::cout << strToStrAcentos(msj);
            std::cout << asterisco;
        }
        else
        {
            if (a == ' ')
            {
                clave.append(" ");
                asterisco.append("*");
            }
            else
            {
                clave.append(charToStr(a));
                asterisco.append("*");
            }

            std::cout << "\r";
            std::cout << strToStrAcentos(msj);

            for (unsigned int i = 0; i+1 < asterisco.size(); i++)
            {
                std::cout << asterisco.substr(i,1);
            }

            if (asterisco.size() > 0)
            {
                std::cout << strToStrAcentos(clave.substr(asterisco.size() - 1, 1));
            }
        }

    }while(a != '\n');

    return clave;
}

string stringConvert::giveStringPassword()
{
    return stringConvert::giveStringPassword("");
}
