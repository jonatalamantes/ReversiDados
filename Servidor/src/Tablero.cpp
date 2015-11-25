#include "Tablero.h"

Tablero::Tablero()
{
    memset (fichas, 0, sizeof(fichas));
    memset (dados, 0, sizeof(dados));
}

Tablero::Tablero(const Tablero& t)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Tablero::fichas[i][j] = t.getFicha(i,j);
        }
    }

    Tablero::dados[0] = t.getDado(0);
    Tablero::dados[1] = t.getDado(1);
    Tablero::dados[2] = t.getDado(2);
}

Tablero::Tablero(short int fichas[8][8],unsigned short int dados[3])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(i==4 && j ==4)
                fichas[i][j]=-1;
            else if(i==4 && j==5)
                fichas[i][j]=1;
            else if(i==5 && j==4)
                fichas[i][j]=1;
            else if(i==5 && j==5)
                fichas[i][j]=-1;
            else
                fichas[i][j]=0;
        }
    }
    dados[0]=0;
    dados[1]=0;
    dados[2]=0;
}

short int Tablero::getFicha(short int x, short int y) const
{
    if (x < 0 || x >= 8 || y < 0 || y >= 8)
    {
        return 0;
    }
    else
    {
        return Tablero::fichas[x][y];
    }
}

unsigned short int Tablero::getDado(short int p) const
{
    if (p >= 0 && p < 3)
    {
        return Tablero::dados[p];
    }
    else
    {
        return 0;
    }
}

void Tablero::setFicha(short int x, short int y, short int colorf)
{
    if (!(x < 0 || x >= 8 || y < 0 || y >= 8))
    {
        Tablero::fichas[x][y] = colorf;
    }
}

void Tablero::setDado(short int p, unsigned short int val)
{
    if (p >= 0 && p < 3)
    {
        Tablero::dados[p] = val;
    }
}

void Tablero::inicializar()
{
    memset (fichas, 0, sizeof(fichas));
    memset (dados, 0, sizeof(dados));
}

void Tablero::computerMove(short color, short *x, short *y)
{
    int randx = rand() % 8;
    int randy = rand() % 8;

    bool encontrado = false;

    for (int i = randx; i < 8; i++)
    {
        for (int j = randy; j < 8; j++)
        {
            if (j == dados[0]-1 || j == dados[1]-1 || j == dados[2]-1 ||
                i == dados[0]-1 || i == dados[1]-1 || i == dados[2]-1)
            {
                if (Tablero::validarMovimiento(i,j,color))
                {
                    *x = i;
                    *y = j;

                    encontrado = true;

                    break;
                }
            }
        }
    }

    if (!encontrado)
    {
        for (int i = 0; i < randx; i++)
        {
            for (int j = 0; j < randy; j++)
            {
                if (j == dados[0]-1 || j == dados[1]-1 || j == dados[2]-1 ||
                    i == dados[0]-1 || i == dados[1]-1 || i == dados[2]-1)
                {
                    if (Tablero::validarMovimiento(i,j,color))
                    {
                        *x = i;
                        *y = j;

                        break;
                    }
                }
            }
        }
    }
}

short Tablero::cantidadNegras()
{
    short cantidad = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Tablero::fichas[i][j] == 1)
            {
                cantidad++;
            }
        }
    }

    return cantidad;
}

short Tablero::cantidadBlancas()
{
    short cantidad = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Tablero::fichas[i][j] == -1)
            {
                cantidad++;
            }
        }
    }

    return cantidad;
}

short Tablero::turnoGlobalValido(short color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Tablero::validarMovimiento(i,j,color))
            {
                return i;
            }
        }
    }

    return -1;
}

bool Tablero::turnoValido(short color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j == dados[0]-1 || j == dados[1]-1 || j == dados[2]-1 ||
                i == dados[0]-1 || i == dados[1]-1 || i == dados[2]-1)
            {

                if (Tablero::validarMovimiento(i,j,color))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Tablero::validarMovimiento(int x, int y, int color)
{
    if (fichas[x][y] != 0)
    {
        return false;
    }

    bool valido = false;
    bool posible = false;

    //Revisar la izquierda del eje x

    for (int i = x-1; i >= 0; i--)
    {
        if (fichas[i][y] == 0)
        {
            break;
        }
        else if (fichas[i][y] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    posible = false;
    //Revisar la derecha del eje x
    for (int i = x+1; i < 8; i++)
    {
        if (fichas[i][y] == 0)
        {
            break;
        }
        else if (fichas[i][y] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    posible = false;
    //Revisar la parte de arriba del eje y
    for (int i = y-1; i >= 0; i--)
    {
        if (fichas[x][i] == 0)
        {
            break;
        }
        else if (fichas[x][i] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    //Revisar la parte de abajo del eje y
    posible = false;
    for (int i = y+1; i < 8; i++)
    {
        if (fichas[x][i] == 0)
        {
            break;
        }
        else if (fichas[x][i] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    posible = false;
    //Revisar la diagonal superior izquierda
    for (int i = x-1, j = y-1; i > 0 && j > 0; i--, j--)
    {
        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    posible = false;
    //Revisar la diagonal superior derecha
    for (int i = x+1, j = y-1; i < 8 && j > 0; i++, j--)
    {
        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    posible = false;
    //Revisar la diagonal inferior derecha
    for (int i = x+1, j = y+1; i < 8 && j < 8; i++, j++)
    {
        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    posible = false;
    //Revisar la diagonal inferior izquierda
    for (int i = x-1, j = y+1; i > 0 && j < 8; i--, j++)
    {
        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                valido = true;
            }

            break;
        }
    }

    return valido;
}

void Tablero::colocarFicha(int x, int y, int color)
{
    bool posible = false;

    //Revisar la izquierda del eje x
    for (int i = x-1; i >= 0; i--)
    {
        if (fichas[i][y] == 0)
        {
            break;
        }
        else if (fichas[i][y] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                //Revisar la derecha del eje x
                for (int j = i; j < 8; j++)
                {
                    if (fichas[j][y] == 0)
                    {
                        break;
                    }
                    else if (fichas[j][y] != color)
                    {
                        fichas[j][y]=color;
                    }
                }
            }
            break;
        }
    }

    posible = false;
    //Revisar la derecha del eje x
    for (int i = x+1; i < 8; i++)
    {
        if (fichas[i][y] == 0)
        {
            break;
        }
        else if (fichas[i][y] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                for (int j = i; j >= 0; j--)
                {
                    if (fichas[j][y] == 0)
                    {
                        break;
                    }
                    else if (fichas[j][y] != color)
                    {
                        fichas[j][y]=color;

                    }
                }
            }

            break;
        }
    }

    posible = false;
    //Revisar la parte de arriba del eje y Ya funciona
    for (int i = y-1; i >= 0; i--)
    {
        if (fichas[x][i] == 0)
        {
            break;
        }
        else if (fichas[x][i] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                for (int j = i; j < 8; j++)
                {
                    if (fichas[x][j] == 0)
                    {
                        break;
                    }
                    else if (fichas[x][j] != color)
                    {
                        fichas[x][j]=color;

                    }
                }
            }

            break;
        }
    }

    //Revisar la parte de abajo del eje y Ya sirve
    posible = false;
    for (int i = y+1; i < 8; i++)
    {
        if (fichas[x][i] == 0)
        {
            break;
        }
        else if (fichas[x][i] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                for (int j = i; j >= 0; j--)
                {
                    if (fichas[x][j] == 0)
                    {
                        break;
                    }
                    else if (fichas[x][j] != color)
                    {
                        fichas[x][j]=color;

                    }
                }
            }
            break;
        }
    }

    posible = false;
    //Revisar la diagonal superior izquierda
    for (int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--)
    {

        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
               for (int k = i, l = j; k < 8 && l < 8; k++, l++)
                {
                    if (fichas[k][l] == 0)
                    {
                        break;
                    }
                    else if (fichas[k][l] != color)
                    {
                        fichas[k][l]=color;
                    }
                }
            }
            break;
        }
    }

    posible = false;
    //Revisar la diagonal superior derecha
    for (int i = x+1, j = y-1; i < 8 && j >= 0; i++, j--)
    {
        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                for (int k = i, l = j; k >= 0 && l < 8; k--, l++)
                {
                     if (fichas[k][l] == 0)
                    {
                        break;
                    }
                    else if (fichas[k][l] != color)
                    {
                        fichas[k][l]=color;
                    }
                }
            }

            break;
        }
    }

    posible = false;
    //Revisar la diagonal inferior derecha
    for (int i = x+1, j = y+1; i < 8 && j < 8; i++, j++)
    {
        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
                for (int k = i, l = j; k >= 0 && l >= 0; k--, l--)
                {
                    if (fichas[k][l] == 0)
                    {
                        break;
                    }
                    else if (fichas[k][l] != color)
                    {
                        fichas[k][l]=color;
                    }
                }

            }

            break;
        }
    }

    posible = false;
    //Revisar la diagonal inferior izquierda
    for (int i = x-1, j = y+1; i >= 0 && j < 8; i--, j++)
    {
        if (fichas[i][j] == 0)
        {
            break;
        }
        else if (fichas[i][j] != color)
        {
            posible = true;
        }
        else
        {
            if (posible)
            {
               for (int k = i, l = j; k < 8 && l >= 0; k++, l--)
                {
                    if (fichas[k][l] == 0)
                    {
                        break;
                    }
                    else if (fichas[k][l] != color)
                    {
                        fichas[k][l]=color;
                    }
                }
            }

            break;
        }
    }

    Tablero::setFicha(x, y, color);
}

void Tablero::tirarDados(int forceColor)
{
    srand (time(NULL));

    dados[0] = forceColor+1;

    for (int i = 1; i < 3; i++)
    {
        short myval = rand() % 8 + 1;
        dados[i] = myval;

        for (int j = 0; j < i; j++)
        {
            if (myval == dados[j])
            {
                i--;
            }
        }
    }
}

bool Tablero::numInDados(short x)
{
    if (dados[0] == x || dados[1] == x || dados[2] == x)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Tablero::inicializarDados()
{
    memset (dados, 0, sizeof(dados));
}

uint8_t Tablero::standardValor(short int x)
{
    if (x < 0)
    {
        return 2;
    }
    else if (x > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

short int Tablero::tableroValor(uint8_t x)
{
    if (x == 1)
    {
        return 1;
    }
    else if (x == 2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

uint128_t Tablero::tableroToBytes(Tablero x)
{
    uint128_t bytes;
    int contador = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j+=4)
        {
            uint8_t oneByte;

            oneByte = (standardValor(x.getFicha(i,j)) << 6)   | (standardValor(x.getFicha(i,j+1)) << 4) |
                      (standardValor(x.getFicha(i,j+2)) << 2) | (standardValor(x.getFicha(i,j+3)));

            bytes.byte[contador] = oneByte;
            contador++;
        }
    }

    return bytes;
}

Tablero Tablero::bytesToTablero(uint128_t x)
{
    Tablero tab;

    int contador = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j+=4)
        {
            uint8_t oneByte = x.byte[contador];
            uint8_t temp;

            temp = (oneByte & 0xC0) >> 6;
            tab.setFicha(i,j, tableroValor(temp));

            temp = (oneByte & 0x30) >> 4;
            tab.setFicha(i,j+1, tableroValor(temp));

            temp = (oneByte & 0x0C) >> 2;
            tab.setFicha(i,j+2, tableroValor(temp));

            temp = (oneByte & 0x03);
            tab.setFicha(i,j+3, tableroValor(temp));

            contador++;
        }
    }

    return tab;
}

void Tablero::imprimirTablero()
{
    //cout << endl;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Tablero::fichas[i][j] == 1)
            {
                //cout << "X";
            }
            else if (Tablero::fichas[i][j] == -1)
            {
                //cout << "Y";
            }
            else
            {
                //cout << "#";
            }
        }

        //cout << endl;
    }
}
