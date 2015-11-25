#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>

//Lista Doblemente Ligada manejando posicions fisicas, numericas y con operaciones adicionales
using namespace std;

//Clase de las excepciones
class ListException : public exception
{
    protected:
        string msj;

    public:
        ListException(string ss) { msj = ss; }
        const char* what() const throw() { return msj.c_str(); }

        ~ListException() throw () {}
};

//Clase qdel Nodo Doblemente ligado
template<class T>
class NodeDouble
{
    private:
    //Atributos
        T data;
        NodeDouble<T>* next;
        NodeDouble<T>* prev;

    public:
    //Constructor
        NodeDouble<T>();
        NodeDouble<T>(T);
        NodeDouble<T>(const NodeDouble<T>&);
        ~NodeDouble<T>();

    //Getters
        T getData() const;
        T& getReferenceData();
        NodeDouble<T>* getNext() const;
        NodeDouble<T>* getPrev() const;

    //Setters
        void setData(T);
        void setNext(NodeDouble<T>*);
        void setPrev(NodeDouble<T>*);

    //Operadores
        bool operator< (const NodeDouble<T>&);
        bool operator> (const NodeDouble<T>&);
        bool operator<= (const NodeDouble<T>&);
        bool operator>= (const NodeDouble<T>&);
        bool operator== (const NodeDouble<T>&);
        bool operator!= (const NodeDouble<T>&);
        NodeDouble<T>& operator= (const NodeDouble<T>&);
};

template<class T>
NodeDouble<T>::NodeDouble()
{
    NodeDouble<T>::next = NULL;
    NodeDouble<T>::prev = NULL;
}

template<class T>
NodeDouble<T>::NodeDouble(T one)
{
    NodeDouble<T>::data = one.getData();
    NodeDouble<T>::next = NULL;
    NodeDouble<T>::prev = NULL;
}

template<class T>
NodeDouble<T>::NodeDouble(const NodeDouble& one)
{
    NodeDouble<T>::data = one.getData();
    NodeDouble<T>::next = NULL;
    NodeDouble<T>::prev = NULL;
}

template<class T>
NodeDouble<T>::~NodeDouble()
{
    NodeDouble<T>::next = NULL;
    NodeDouble<T>::prev = NULL;
}

//Getters
template<class T>
T NodeDouble<T>::getData() const
{
    return NodeDouble<T>::data;
}

template<class T>
T& NodeDouble<T>::getReferenceData()
{
    return data;
}

template<class T>
NodeDouble<T>* NodeDouble<T>::getNext() const
{
    return NodeDouble<T>::next;
}

template<class T>
NodeDouble<T>* NodeDouble<T>::getPrev() const
{
    return NodeDouble<T>::prev;
}

//Setters
template<class T>
void NodeDouble<T>::setData(T newData)
{
    NodeDouble<T>::data = newData;
}

template<class T>
void NodeDouble<T>::setNext(NodeDouble<T>* newNext)
{
    next = newNext;
}

template<class T>
void NodeDouble<T>::setPrev(NodeDouble<T>* newPrev)
{
    prev = newPrev;
}

//Operadores
template<class T>
bool NodeDouble<T>::operator< (const NodeDouble<T>& other)
{
    if (NodeDouble::data < other.getData())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool NodeDouble<T>::operator> (const NodeDouble<T>& other)
{
    if (NodeDouble::data > other.getData())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool NodeDouble<T>::operator<= (const NodeDouble<T>& other)
{
    if (NodeDouble::data <= other.getData())
    {
        return true;
    }
    else
    {
        return false;
    }

}

template<class T>
bool NodeDouble<T>::operator>= (const NodeDouble<T>& other)
{
    if (NodeDouble::data >= other.getData())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool NodeDouble<T>::operator== (const NodeDouble<T>& other)
{
    if (NodeDouble::data == other.getData())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
bool NodeDouble<T>::operator!= (const NodeDouble<T>& other)
{
    if (NodeDouble::data != other.getData())
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
NodeDouble<T>& NodeDouble<T>::operator= (const NodeDouble<T>& y)
{
    NodeDouble<T>::setData(y.getData());
    NodeDouble<T>::setNext(y.getNext());
    NodeDouble<T>::setPrev(y.getPrev());

    return *this;
}

//Clase que es la lista en Sí
template<class T>
class List
{
    private:
    //Atributos
        NodeDouble<T>* firstNode;
        NodeDouble<T>* lastNode;
        unsigned Size;

    public:
    //Constructores

        List();
        ~List();
        List(const List&);
        List(NodeDouble<T>* f, NodeDouble<T>* l, unsigned a);

    //Métodos de la lista

        unsigned getSize() const;
        //Retorna la cantidad de Elementos que contenga la lista

        void inicialize();
        //inicializa la lista de modo que este vacia para iniciar correctamente

        bool isEmpty() const;
        //regresa verdadero si la lista esta vacia; sino regresa falso

        void print(ostream&) const;
        //imprime el contenido de la lista recibiendo un flujo de salida

        void insertElement(unsigned position, T thing);
        //insertas el elemento 'thing' en la posicion 'position'

        void insertElement(NodeDouble<T>* position, T thing);
        //Inserta despues del nodo position

        void deleteForPosition(unsigned position);
        //elimina el elemento que se encuentre en la posicion 'position'

        void deleteForPosition(NodeDouble<T>* position);
        //Elimina el nodo position de la lista

        NodeDouble<T>* first();
        //regresa el primer nodo

        NodeDouble<T>* last();
        //regresa el ultimo nodo

        NodeDouble<T>* next(NodeDouble<T>* position);
        //Regresa el nodo sigueitne a position

        unsigned next(unsigned position);
        //regresa el numero del nodo siguiente a al nodo en la posicion position

        NodeDouble<T>* previous(NodeDouble<T>* position);
        //Regresa el nodo anterior a position

        unsigned previous(unsigned position);
        //regresa el numero del nodo anterior a al nodo en la posicion position

        T recover(unsigned position) const;
        //devuelve el elemento que se encuetra en la posicion 'position'

        T recover(NodeDouble<T>* node) const;
        //devuelve el elemento que se encuentra en el nodo indicado

        int searchInList(T thing);
        //busca el elemento 'thing' la lista y regresa su posicion, s

        void sorted();
        //ordena la lista de menor a mayor con método de quicksort moviendo pibote

        void sorted(short atribute);
        //ordena la lista de menor a mayor con método de quicksort moviendo pibote
        //ordena segun el número del atributo especificado.

        void otherSorted();
        //ordena la lista de mayor a menor con método de quicksort

        void reverseList();
        //invierte el orden de la lista

        void nullify();
        //elimina todos los elementos de la lista dejandola vacia

        unsigned NodeToNumber(NodeDouble<T>* node);
        //regresa el numero correspondiente de ese nodo

        NodeDouble<T> NumberToNode(unsigned position);
        //regresa el nodo correspondiente en una determinada posicion

    //Operadores Sobrecargados
        bool operator==(const List<T>&);
        bool operator!=(const List<T>&);
        List<T>& operator=(const List<T>&);
        List<T> operator+(const List<T>&);
        T& operator[] (unsigned);

    //operaciones de Pila y Cola

        void pushBack(T thing);
        //inserta el elemento Thing al final de la lista

        void pushFront(T thing);
        //inserta el elemento Thing al inicio de la lista

        T popBack();
        //saca y regresa el dato de la ultima posicion

        T popFront();
        //saca y regresa el dato de la primera posicion

    //Como una lista de Python

        void append(T thing);
        //igual que pushback

        void pop();
        //Saca y regresa el dato en la ultima posicion

        T pop(unsigned position);
        //Saca y regresa el dato que existe en el nodo en la posicion 'position'

        void extendList(List<T> lista);
        //inserta los datos de la lsita 'lista', al final de la lista.

        unsigned countElement(T thing);
        //Devuelve la cantidad de veces que aparece el elemento 'thing' en la lista

    private:
        void quickSort(NodeDouble<T>** a, int began, int latest, short atribute);
        //ordena la lista con el método de quicksort moviendo pibote
        //ademas recibe el número del atributo por el que se quiera ordenar
        //debe estar una funcion llamada "compareTo(obj, int)" para funcionar.

        void quickSort(NodeDouble<T>** a, int began, int latest);
        //ordena la lista con el método de quicksort moviendo pibote

        void otherQuickSort(NodeDouble<T>** a, int, int);
        //ordena la lista con el método de quicksort sin mover pibote

        void doReverse(NodeDouble<T>** a);
        //invierte el orden del arreglo, a un orden inverso
};

//Constructores
template<class T>
List<T>::List()
{
    //inicializamos todo en 0
    List<T>::firstNode = NULL;
    List<T>::lastNode = NULL;
    List<T>::Size = 0;
}

template<class T>
List<T>::~List()
{
    //vaciamos la lista
    List<T>::nullify();
}

template<class T>
List<T>::List(const List& one)
{
    //iniicalizmaos todo en 0
    List<T>::firstNode = NULL;
    List<T>::lastNode = NULL;
    List<T>::Size = 0;

    unsigned contador = 0;

    //hacemos un recorrido en la lista derecha
    while (contador < one.getSize())
    {
        T element;
        //insertamos cada elemento de la lsita derecha en la lista izquierda
        element = one.recover(contador);
        List<T>::append(element);
        contador++;
    }
}

template<class T>
List<T>::List(NodeDouble<T>* f, NodeDouble<T>* l, unsigned a)
{
    //inicializamos todo segun lo que se proporcione
    List<T>::firstNode = f;
    List<T>::lastNode = l;
    List<T>::Size = a;
}


//Métodos de la lista
template<class T>
unsigned List<T>::getSize() const
{
    return List<T>::Size;
}

template<class T>
void List<T>::inicialize()
{
    //se inicializa la lista, si esta vacia lo hace como el contructor, sino llama a nullify
    if (List<T>::isEmpty())
    {
        List<T>::firstNode = NULL;
        List<T>::lastNode = NULL;
        List<T>::Size = 0;
    }
    else
    {
        List<T>::nullify();
    }

}

template<class T>
bool List<T>::isEmpty() const
{
    if (List::getSize() <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class T>
void List<T>::insertElement(unsigned position, T thing)
{
    if (position < 0 || position > List<T>::Size) //posicion invalida
    {
        throw ListException("Error, no puede insertar al elemento en la posicion indicada");
    }

    else if (List<T>::isEmpty())
    {
        //creamos nuevo elemento
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direcionan tanto el inicio como el fin al nuevo elemento
        List<T>::firstNode = temp;
        List<T>::lastNode = temp;

        //El nuevo elemento no apunta a nada y se aumenta las ponderaciones
        temp->setNext(NULL);
        temp->setPrev(NULL);

        List<T>::Size = List<T>::Size + 1;
    }

    else if (position == 0) //insertar al inicio
    {
        //se crear un nuevo elemento y se le ponen datos
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direciona el nuevo elemento al primer nodo y el inicio al nuevo elemento,
        //de este modo el nuevo se hace el 1° elemento
        temp->setNext(List<T>::firstNode);
        temp->setPrev(NULL);
        List<T>::firstNode->setPrev(temp);
        List<T>::firstNode = temp;

        List<T>::Size = List<T>::Size + 1;
    }

    else if (position == List<T>::Size || position == List<T>::Size - 1) //inserta la final
    {
        //se crear un nuevo elemento y se le ponen datos
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direciona el nuevo elemento al ultimo nodo nodo y el inicio al nuevo elemento,
        //de este modo el nuevo se hace el ultimo elemento
        temp->setPrev(List<T>::lastNode);
        temp->setNext(NULL);
        List<T>::lastNode->setNext(temp);
        List<T>::lastNode = temp;

        List<T>::Size = List<T>::Size + 1;
    }

    else //cualquier otra posicion valida
    {
        //se crean 3 variables para hacer recorridos
        NodeDouble<T>* temp1 = List<T>::firstNode;
        NodeDouble<T>* temp2 = List<T>::firstNode;
        NodeDouble<T>* temp3 = new NodeDouble<T>;

        //el tercer elemento tendra los datos del nuevo nodo
        temp3->setData(thing);

        unsigned int counter[2];

        counter[0] = 0;
        counter[1] = 0;

        //vamos haciendo un contador de modo que el primer de los elementos creado apunte a un nodo menor a la posicion
        while (counter[0] < position - 1)
        {
            temp1 = temp1->getNext();
            counter[0]++;
        }

        //mientras que con el otro hacemos que el segundo elemento apunte a el nodo mayor a la posicion
        while (counter[1] < position)
        {
            temp2 = temp2->getNext();
            counter[1]++;
        }

        //se direciona el elemento 1 de modo que apunte al 3° que es el que contiene los datos
        //mientras que se diracciona al 3° al 2° que era el elemento anterior al que estaba la posicion
        //de este modo el nuevo nodo ya se inserto en la lista
        temp3->setPrev(temp1);
        temp1->setNext(temp3);

        temp3->setNext(temp2);
        temp2->setPrev(temp3);

        //se eliminan los nodos de recorrida y se aumenta la poderacion.
        temp1 = NULL;
        delete temp1;

        temp2 = NULL;
        delete temp1;

        List<T>::Size = List<T>::Size + 1;
    }
}

template<class T>
void List<T>::insertElement(NodeDouble<T>* position, T thing)
{
    if (position == NULL && not List<T>::isEmpty())
    {
        throw ListException("Error no puede insertar el Nodo");
    }

    else if (List<T>::isEmpty())
    {
        //creamos nuevo elemento
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direcionan tanto el inicio como el fin al nuevo elemento
        List<T>::firstNode = temp;
        List<T>::lastNode = temp;

        //El nuevo elemento no apunta a nada y se aumenta las ponderaciones
        temp->setNext(NULL);
        temp->setPrev(NULL);

        List<T>::Size = List<T>::Size + 1;
    }
    else if (position == List<T>::firstNode || position == NULL) //insertar al inicio
    {
        //se crear un nuevo elemento y se le ponen datos
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direciona el nuevo elemento al primer nodo y el inicio al nuevo elemento,
        //de este modo el nuevo se hace el 1° elemento
        temp->setNext(List<T>::firstNode);
        temp->setPrev(NULL);
        List<T>::firstNode->setPrev(temp);
        List<T>::firstNode = temp;

        List<T>::Size = List<T>::Size + 1;
    }

    else if (position == List<T>::lastNode) //inserta la final
    {
        //se crear un nuevo elemento y se le ponen datos
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direciona el nuevo elemento al ultimo nodo nodo y el inicio al nuevo elemento,
        //de este modo el nuevo se hace el ultimo elemento
        temp->setPrev(List<T>::lastNode);
        temp->setNext(NULL);
        List<T>::lastNode->setNext(temp);
        List<T>::lastNode = temp;

        List<T>::Size = List<T>::Size + 1;
    }
    else //insertamos en el nodo siguiente
    {
        NodeDouble<T>* temp = new NodeDouble<T>;

        if (temp == NULL)
        {
            throw ListException("Error, no hay suficiente Memoria");
        }

        //le ponemos el dato
        temp->setData(thing);

        //realizamos los enlaces
        temp->setNext(position->getNext());
        position->getNext()->setPrev(temp);
        temp->setPrev(position);
        position->setNext(temp);

        //aumentamos la ponderacion
        List<T>::Size = List<T>::Size + 1;
    }
}

template<class T>
void List<T>::deleteForPosition(unsigned position)
{
    if (List<T>::isEmpty() || position <  0 || position > Size) //posicion invalida
    {
        throw ListException("Error, no puede eliminar al elemento en la posicion indicada");
    }
    else
    {
        if (List<T>::Size == 1)
        {
            NodeDouble<T>* temp = List<T>::firstNode;

            delete temp;

            List<T>::firstNode = NULL;
            List<T>::lastNode = NULL;

            List<T>::Size = List<T>::Size - 1;
        }

        else if (position == 0) //al inicio
        {
            //creamos un nuevo nodo que apuntará al inicio
            NodeDouble<T>* temp = List<T>::firstNode;

            //el inicio apuntará al siguiente
            temp->getNext()->setPrev(NULL);
            List<T>::firstNode = temp->getNext();

            //disminuimos la poderacion y eliminados el nuevo nodo que apuntaba al anterior inicio
            List<T>::Size = List<T>::Size - 1;
            delete temp;
        }
        else if (position == List<T>::Size - 1 || position == List<T>::Size)
        {
            //creamos un nuevo nodo que apuntará al final
            NodeDouble<T>* temp = List<T>::lastNode;

            //el inicio apuntará al siguiente
            temp->getPrev()->setNext(NULL);
            List<T>::lastNode = temp->getPrev();

            //disminuimos la poderacion y eliminados el nuevo nodo que apuntaba al anterior inicio
            List<T>::Size = List<T>::Size - 1;
            delete temp;
        }
        else //Cualquier otra posicion
        {
            //creamos un nuevo nodo que apuntará al inicio y que hará el recorrido de la lista
            NodeDouble<T>* temp = List<T>::firstNode;

            for (unsigned int i = 0; i < position; i++)
            {
                temp = temp->getNext();
            }


            //el inicio apuntará al siguiente
            temp->getNext()->setPrev(temp->getPrev());
            temp->getPrev()->setNext(temp->getNext());

            //disminuimos la poderacion y eliminados el nuevo nodo que apuntaba al elemento
            List<T>::Size = List<T>::Size - 1;
            delete temp;
        }
    }
}

template<class T>
void List<T>::deleteForPosition(NodeDouble<T>* position)
{
    if (List<T>::isEmpty() || position == NULL) //posicion invalida
    {
        throw ListException("Error, no puede acceder a dicho Nodo");
    }
    else
    {
        if (List<T>::Size == 1)
        {
            NodeDouble<T>* temp = List<T>::firstNode;

            delete temp;

            List<T>::firstNode = NULL;
            List<T>::lastNode = NULL;

            List<T>::Size = List<T>::Size - 1;
        }
        else if (position == firstNode) //al inicio
        {
            //creamos un nuevo nodo que apuntará al inicio
            NodeDouble<T>* temp = List<T>::firstNode;

            //el inicio apuntará al siguiente
            temp->getNext()->setPrev(NULL);
            List<T>::firstNode = temp->getNext();

            //disminuimos la poderacion y eliminados el nuevo nodo que apuntaba al anterior inicio
            List<T>::Size = List<T>::Size - 1;
            delete temp;
        }
        else if (position == List<T>::lastNode)
        {
            //creamos un nuevo nodo que apuntará al final
            NodeDouble<T>* temp = List<T>::lastNode;

            //el inicio apuntará al siguiente
            temp->getPrev()->setNext(NULL);
            List<T>::lastNode = temp->getPrev();

            //disminuimos la poderacion y eliminados el nuevo nodo que apuntaba al anterior inicio
            List<T>::Size = List<T>::Size - 1;
            delete temp;
        }
        else
        {
            //creamos un apuntador Nodo
            NodeDouble<T>* temp = position;

            //realizamos los enlaces
            position->getNext()->setPrev(position->getPrev());
            position->getPrev()->setNext(position->getNext());

            //eliminas el nodo
            delete temp;

            //reducimos la ponderacion
            List<T>::Size = List<T>::Size - 1;
        }
    }
}

template<class T>
NodeDouble<T>* List<T>::first()
{
    return List<T>::firstNode;
}

template<class T>
NodeDouble<T>* List<T>::last()
{
    return List<T>::lastNode;
}

template<class T>
unsigned List<T>::next(unsigned position)
{
    if (position < 0 || position >= List<T>::Size) //invalida
    {
        throw ListException("Error, no puede el siguiente");
    }
    else
    {
        return position + 1;
    }
}

template<class T>
NodeDouble<T>* List<T>::next(NodeDouble<T>* position)
{
    if (position == NULL || position->getNext() == NULL) //invalida
    {
        throw ListException("Error, no puede el siguiente");
    }
    else
    {
        return position->getNext();
    }
}


template<class T>
unsigned List<T>::previous(unsigned position)
{
    if (position < 1 || position > List<T>::Size) //invalida
    {
        throw ListException("Error, no puede obtener el anterior");
    }
    else
    {
        return position - 1;
    }
}

template<class T>
NodeDouble<T>* List<T>::previous(NodeDouble<T>* position)
{
    if (position == NULL || position->getPrev() == NULL) //invalida
    {
        throw ListException("Error, no puede el anterior nodo");
    }
    else
    {
        return position->getPrev();
    }
}

template<class T>
T List<T>::recover(unsigned position) const
{
    if (List<T>::isEmpty() || position <  0 || position >= List<T>::Size) //invalida
    {
        throw ListException("Error, no puede acceder al elemento en la posicion indicada");
    }
    else
    {
        //creamos un nuevo nodo
        NodeDouble<T>* temp = List<T>::firstNode;
        unsigned int x = 0;

        //buscamos en la lista linealmente la posicion
        while (x < position)
        {
            temp = temp->getNext();
            x++;
        }

        //regresamos el dato que haya en esa posicion
        return temp->getData();
    }

    //sino creamos un nuevo nodo y enviaremos basura, esto para que no aparezca un warning
    NodeDouble<T>* temp = NULL;
    return temp->getData();
}

template<class T>
T List<T>::recover(NodeDouble<T>* position) const
{
    return position->getData();
}

template<class T>
int List<T>::searchInList(T thing) //regresa la posicion de cierto elemento
{
    if (List<T>::isEmpty())
    {
        return -1;
    }
    else
    {
        //cremos un nuevo nodo y hacemos que apunte al inicio
        NodeDouble<T>* temp = List::firstNode;

        //hacemos el recorrido de la lista y devolvemos su posicion
        for (int i = 0; i < int(List::Size); i++)
        {
            if (thing == temp->getData())
            {
                temp = NULL;
                delete temp;
                return i;
            }
            else
            {
                temp = temp->getNext();
            }
        }

        //si no lo encuentra regresa -1
        temp = NULL;
        delete temp;
        return -1;
    }
}

template<class T>
void List<T>::nullify()
{
    //mientras que no este vacia, elimina todos los nodos que contenga
    while (not List<T>::isEmpty())
    {
        List<T>::deleteForPosition(unsigned(0));
    }

    //hace que los nodos apunten a ningun lado
    List::firstNode = NULL;
    List::lastNode = NULL;
}

template<class T>
void List<T>::print(ostream& os) const
{
    if (List<T>::isEmpty())
    {
        os << "[ vacia ]";
    }
    else if (List<T>::Size == 1)
    {
        os << "[ " << List<T>::firstNode->getData() << " ]";
    }
    else
    {
        NodeDouble<T>* temp = List::firstNode;

        os << "[ " << temp->getData() << " * ";
        temp = temp->getNext();

        for (unsigned int i = 1; i < List<T>::Size - 1; i++)
        {
            os << temp->getData() << " * ";

            temp = temp->getNext();
        }

        os << temp->getData() << " ]";
    }
}

template<class T>
void List<T>::sorted() //ordena
{
    //creamos un arreglo de apuntadores que contenga la direccion de cada nodo
    NodeDouble<T>** arreglo = new NodeDouble<T>*[List<T>::getSize()];
    //y un nodo temporacal capaz de decirnos en que nodo estamos
    NodeDouble<T>* temp = List<T>::firstNode;

    //redirecionamos cada indice del arreglo al nodo correspondiente
    for (unsigned int i = 0; i < List<T>::getSize(); i++)
    {
        arreglo[i] = temp;
        temp = temp->getNext();
    }

    //ordenamos el arreglo con algun método de ordenamiento
    quickSort(arreglo, 0, List<T>::getSize() - 1);

    //comenzamos religando el ancla
    List<T>::firstNode = arreglo[0];
    List<T>::firstNode->setNext(arreglo[1]);
    List<T>::firstNode->setPrev(NULL);

    //hacemos que nodo temp vaya recorroriendo el arreglo para religar la lista
    temp = arreglo[1];
    for (unsigned int i = 1; i < List<T>::getSize() - 1; i++)
    {
        temp->setNext(arreglo[i + 1]);
        temp->setPrev(arreglo[i - 1]);
        temp = arreglo[i + 1];
    }

    //Religamos la ultima ancla
    List<T>::lastNode = arreglo[List<T>::getSize() - 1];
    List<T>::lastNode->setPrev(arreglo[List<T>::getSize() - 2]);
    List<T>::lastNode->setNext(NULL);

    //eliminamos todo lo que no necesitamos
    temp = NULL;
    delete temp;
    delete [] arreglo;
}

template<class T>
void List<T>::quickSort(NodeDouble<T>** a, int began, int latest)
{
    NodeDouble<T>* temp = List<T>::firstNode;

    if (began > latest)
    {
        //saliendo
    }
    else
    {
        //Creamos un pibote en la mitad de la posicion
        int pibot = (latest + began)/2;
        //Hacemos el recorrido de la mitad a nuestro pibote
        for (int i = began; i < pibot; i++)
        {
            if (a[i]->getData() <= a[pibot]->getData())
            {
                //Si el elemento de la izquierda es menor, no hacemos nada
                continue;
            }
            else
            {
                if (i == pibot - 1)
                {
                    //Si esta al lado del pibote, sólo los intercambia
                    temp = a[pibot];
                    a[pibot] = a[pibot - 1];
                    a[pibot - 1] = temp;

                    //List<T>::changeValues(pibot, pibot - 1);
                    pibot = pibot - 1;
                }
                else
                {

                    //movemos el pibote para abrir un espacio
                    temp = a[pibot];
                    a[pibot] = a[pibot - 1];
                    a[pibot - 1] = temp;

                    //List<T>::changeValues(pibot, pibot - 1);
                    pibot = pibot - 1;

                    //insertamos el la posicion vacia
                    temp = a[pibot + 1];
                    a[pibot + 1] = a[i];
                    a[i] = temp;
                    //List<T>::changeValues(pibot + 1, i);

                    i--;
                }
            }
        }

        //Realizamos el mismo proceso, sólo que invertido con el otro lado de la lista
        for (int i = latest; i > pibot; i--)
        {
            if (a[i]->getData() >= a[pibot]->getData())
            {
                continue;
            }
            else
            {
                if (i == pibot + 1)
                {
                    temp = a[pibot];
                    a[pibot] = a[pibot + 1];
                    a[pibot + 1] = temp;

                    //List<T>::changeValues(pibot + 1, pibot);
                    pibot = pibot + 1;
                }
                else
                {
                    //movemos el pibote
                    temp = a[pibot];
                    a[pibot] = a[pibot + 1];
                    a[pibot + 1] = temp;

                    //List<T>::changeValues(pibot, pibot + 1);

                    pibot = pibot + 1;

                    //insertamos el la posicion vacia
                    temp = a[i];
                    a[i] = a[pibot - 1];
                    a[pibot - 1] = temp;

                    //List<T>::changeValues(i, pibot - 1);

                    i++;
                }
            }
        }

        //Finalmente ordenamos cada una de las sublistas con recusión
        List<T>::quickSort(a, began, pibot - 1);
        List<T>::quickSort(a, pibot + 1, latest);
    }

    temp = NULL;
    delete temp;
}

template<class T>
void List<T>::sorted(short atribute) //ordena
{
    //creamos un arreglo de apuntadores que contenga la direccion de cada nodo
    NodeDouble<T>** arreglo = new NodeDouble<T>*[List<T>::getSize()];
    //y un nodo temporacal capaz de decirnos en que nodo estamos
    NodeDouble<T>* temp = List<T>::firstNode;

    //redirecionamos cada indice del arreglo al nodo correspondiente
    for (unsigned int i = 0; i < List<T>::getSize(); i++)
    {
        arreglo[i] = temp;
        temp = temp->getNext();
    }

    //ordenamos el arreglo con algun método de ordenamiento
    quickSort(arreglo, 0, List<T>::getSize() - 1, atribute);

    //comenzamos religando el ancla
    List<T>::firstNode = arreglo[0];
    List<T>::firstNode->setNext(arreglo[1]);
    List<T>::firstNode->setPrev(NULL);

    //hacemos que nodo temp vaya recorroriendo el arreglo para religar la lista
    temp = arreglo[1];
    for (unsigned int i = 1; i < List<T>::getSize() - 1; i++)
    {
        temp->setNext(arreglo[i + 1]);
        temp->setPrev(arreglo[i - 1]);
        temp = arreglo[i + 1];
    }

    //Religamos la ultima ancla
    List<T>::lastNode = arreglo[List<T>::getSize() - 1];
    List<T>::lastNode->setPrev(arreglo[List<T>::getSize() - 2]);
    List<T>::lastNode->setNext(NULL);

    //eliminamos todo lo que no necesitamos
    temp = NULL;
    delete temp;
    delete [] arreglo;
}

template<class T>
void List<T>::quickSort(NodeDouble<T>** a, int began, int latest, short atribute)
{
    NodeDouble<T>* temp = List<T>::firstNode;

    if (began > latest)
    {
        //saliendo
    }
    else
    {
        //Creamos un pibote en la mitad de la posicion
        int pibot = (latest + began)/2;
        //Hacemos el recorrido de la mitad a nuestro pibote
        for (int i = began; i < pibot; i++)
        {
            if (a[i]->getData().compareTo(a[pibot]->getData(), atribute) < 0)
            {
                //Si el elemento de la izquierda es menor, no hacemos nada
                continue;
            }
            else
            {
                if (i == pibot - 1)
                {
                    //Si esta al lado del pibote, sólo los intercambia
                    temp = a[pibot];
                    a[pibot] = a[pibot - 1];
                    a[pibot - 1] = temp;

                    //List<T>::changeValues(pibot, pibot - 1);
                    pibot = pibot - 1;
                }
                else
                {

                    //movemos el pibote para abrir un espacio
                    temp = a[pibot];
                    a[pibot] = a[pibot - 1];
                    a[pibot - 1] = temp;

                    //List<T>::changeValues(pibot, pibot - 1);
                    pibot = pibot - 1;

                    //insertamos el la posicion vacia
                    temp = a[pibot + 1];
                    a[pibot + 1] = a[i];
                    a[i] = temp;
                    //List<T>::changeValues(pibot + 1, i);

                    i--;
                }
            }
        }

        //Realizamos el mismo proceso, sólo que invertido con el otro lado de la lista
        for (int i = latest; i > pibot; i--)
        {
            if (a[i]->getData().compareTo(a[pibot]->getData(), atribute) > 0)
            {
                continue;
            }
            else
            {
                if (i == pibot + 1)
                {
                    temp = a[pibot];
                    a[pibot] = a[pibot + 1];
                    a[pibot + 1] = temp;

                    //List<T>::changeValues(pibot + 1, pibot);
                    pibot = pibot + 1;
                }
                else
                {
                    //movemos el pibote
                    temp = a[pibot];
                    a[pibot] = a[pibot + 1];
                    a[pibot + 1] = temp;

                    //List<T>::changeValues(pibot, pibot + 1);

                    pibot = pibot + 1;

                    //insertamos el la posicion vacia
                    temp = a[i];
                    a[i] = a[pibot - 1];
                    a[pibot - 1] = temp;

                    //List<T>::changeValues(i, pibot - 1);

                    i++;
                }
            }
        }

        //Finalmente ordenamos cada una de las sublistas con recusión
        List<T>::quickSort(a, began, pibot - 1, atribute);
        List<T>::quickSort(a, pibot + 1, latest, atribute);
    }

    temp = NULL;
    delete temp;
}

template<class T>
void List<T>::otherSorted() //ordena
{
    //creamos un arreglo de apuntadores que contenga la direccion de cada nodo
    NodeDouble<T>** arreglo = new NodeDouble<T>*[List<T>::getSize()];
    //y un nodo temporacal capaz de decirnos en que nodo estamos
    NodeDouble<T>* temp = List<T>::firstNode;

    //redirecionamos cada indice del arreglo al nodo correspondiente
    for (unsigned int i = 0; i < List<T>::getSize(); i++)
    {
        arreglo[i] = temp;
        temp = temp->getNext();
    }

    //ordenamos el arreglo con algun método de ordenamiento
    otherQuickSort(arreglo, 0, List<T>::getSize() - 1);

    //comenzamos religando el ancla
    List<T>::firstNode = arreglo[0];
    List<T>::firstNode->setNext(arreglo[1]);
    List<T>::firstNode->setPrev(NULL);

    //hacemos que nodo temp vaya recorroriendo el arreglo para religar la lista
    temp = arreglo[1];
    for (unsigned int i = 1; i < List<T>::getSize() - 1; i++)
    {
        temp->setNext(arreglo[i + 1]);
        temp->setPrev(arreglo[i - 1]);
        temp = arreglo[i + 1];
    }

    //Religamos la ultima ancla
    List<T>::lastNode = arreglo[List<T>::getSize() - 1];
    List<T>::lastNode->setPrev(arreglo[List<T>::getSize() - 2]);
    List<T>::lastNode->setNext(NULL);

    //eliminamos todo lo que no necesitamos
    temp = NULL;
    delete temp;
    delete [] arreglo;
}

template<class T>
void List<T>::otherQuickSort(NodeDouble<T>** a, int inicio, int fin)
{
    int i, j;
    T pivote;
    i = inicio;
    j = fin;

    //señecionamos un pibote
    pivote = a[((inicio + fin) / 2)]->getData();

    do
    {
        //recorremos el arreglo hasta encontrar un numero menor en la izquierda del pibote
        while (a[i]->getData() < pivote)
        {
            i++;
        }

        //recorrdemos el arreglo hasta encontrar un numero mayor en la derecha del pibote
        while (a[j]->getData() > pivote)
        {
            j--;
        }

        //si el numero i resulta ser menor que el j, entonces intercambiamos nodo
        if (i <= j)
        {
            NodeDouble<T>* temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            temp = NULL;
            delete temp;

            //bajamos las ponderaciones para repetir el proceso
            i++;
            j--;
        }

    //y así sucesivamente hasta que el numero i sea mayor al numero j
    } while(i <= j);

    //relizamos el razonamiento recursivo para ordenar cada sublista
    if(inicio < j)
    {
        otherQuickSort(a, inicio, j);
    }

    if(fin > i)
    {
        otherQuickSort(a, i, fin);
    }
}

template<class T>
void List<T>::reverseList() //ordena
{
    //creamos un arreglo de apuntadores que contenga la direccion de cada nodo
    NodeDouble<T>** arreglo = new NodeDouble<T>*[List<T>::getSize()];
    //y un nodo temporacal capaz de decirnos en que nodo estamos
    NodeDouble<T>* temp = List<T>::firstNode;

    //redirecionamos cada indice del arreglo al nodo correspondiente
    for (unsigned int i = 0; i < List<T>::getSize(); i++)
    {
        arreglo[i] = temp;
        temp = temp->getNext();
    }

    //ordenamos el arreglo con algun método de ordenamiento
    doReverse(arreglo);

    //comenzamos religando el ancla
    List<T>::firstNode = arreglo[0];
    List<T>::firstNode->setNext(arreglo[1]);
    List<T>::firstNode->setPrev(NULL);

    //hacemos que nodo temp vaya recorroriendo el arreglo para religar la lista
    temp = arreglo[1];
    for (unsigned int i = 1; i < List<T>::getSize() - 1; i++)
    {
        temp->setNext(arreglo[i + 1]);
        temp->setPrev(arreglo[i - 1]);
        temp = arreglo[i + 1];
    }

    //Religamos la ultima ancla
    List<T>::lastNode = arreglo[List<T>::getSize() - 1];
    List<T>::lastNode->setPrev(arreglo[List<T>::getSize() - 2]);
    List<T>::lastNode->setNext(NULL);

    //eliminamos todo lo que no necesitamos
    temp = NULL;
    delete temp;
    delete [] arreglo;
}

template <class T>
void List<T>::doReverse(NodeDouble<T>** a)
{
    NodeDouble<T>* temp = a[0];

    for (unsigned int i = 0; i < List<T>::getSize()/2; i++)
    {
        temp = a[i];
        a[i] = a[List<T>::getSize() - i - 1];
        a[List<T>::getSize() - i - 1] = temp;
    }

    temp = NULL;
    delete temp;
}

template<class T>
unsigned List<T>::NodeToNumber(NodeDouble<T>* node)
{
    if (node == NULL)
    {
        throw ListException("Error, No puede acceder a dicha posicion");
    }

    NodeDouble<T>* temp = List<T>::firstNode;

    for (unsigned i = 0; i < List<T>::getSize(); i++)
    {
        if (temp == node)
        {
            return i;
        }

        temp = temp->getNext();
    }

    return 796144;
}

template<class T>
NodeDouble<T> List<T>::NumberToNode(unsigned position)
{
    if (position < 0 || position > List<T>::getSize())
    {
        throw ListException("Error, No puede acceder a dicha posicion");
    }

    NodeDouble<T>* temp = List<T>::firstNode;

    for (unsigned i = 0; i < position; i++)
    {
        temp = temp->getNext();
    }

    return temp;
}

//Operadores Sobrecargados
template<class T>
bool List<T>::operator == (const List<T>& one)
{
    bool result = true;
    unsigned counter = 0;

    //si hay una cantidad diferentes de nodo implica que no son iguales
    if (List<T>::Size != one.Size)
    {
        return false;
    }

    //hace el recorrido y compara cada nodo hasta encontrar alguno que sea diferente
    while (counter < one.Size - 1)
    {
        if ( not (List<T>::recover(counter) == one.recover(counter)))
        {
            result = false;
        }

        counter = counter + 1;
    }

    return result;
}

template<class T>
bool List<T>::operator != (const List<T>& one)
{
    //me devuelve lo opuesto a la igualdad
    return (not List<T>::operator== (one));
}

template<class T>
List<T>& List<T>::operator = (const List<T>& one)
{
    //vaciamos la lista izquierda e inicializamos
    List<T>::nullify();

    unsigned contador = 0;

    //hacemos un recorrido en la lista derecha
    while (contador < one.getSize())
    {
        T element;
        //insertamos cada elemento de la lsita derecha en la lista izquierda
        element = one.recover(contador);
        List<T>::append(element);
        contador++;
    }

    //retornamos la lista izquierda
    return *this;
}

template<class T>
List<T> List<T>::operator + (const List<T>& one)
{
    //creamos una nueva lista
    List<T> newLista;

    //todos los elementos de la lista izquierda se insertan a la nueva lista
    for (unsigned int i = 0; i < List<T>::Size; i++)
    {
        newLista.insertElement(List<T>::first(), List<T>::recover(i));
    }

    //insertamos todos elementos de la lista derecha en la nueva lista
    for (unsigned int contador = 0; contador < one.getSize(); contador++)
    {
        newLista.insertElement(List<T>::first(), one.recover(contador));
    }

    //devolvemos la lista con los elementos de ambas listas
    return newLista;

}

template<class T>
ostream& operator << (ostream& os, const List<T>& lista)
{
    //impirmimos la lista
    lista.print(os);
    os << endl;

    return os;
}

template<class T>
T& List<T>::operator[] (unsigned position)
{
    if (List<T>::isEmpty() || position >= List<T>::Size) //invalida
    {
        throw ListException("Error, no puede acceder al elemento en la posicion indicada");
    }
    else
    {
        //creamos un nuevo nodo
        NodeDouble<T>* temp = List<T>::firstNode;
        unsigned int x = 0;

        //buscamos en la lista linealmente la posicion
        while (x < position)
        {
            temp = temp->getNext();
            x++;
        }

        //regresamos el dato que haya en esa posicion
        return temp->getReferenceData();
    }

    //sino creamos un nuevo nodo y enviaremos basura, esto para que no aparezca un warning
    NodeDouble<T>* temp = NULL;
    return temp->getReferenceData();
}

template<class T>
void List<T>::pushBack(T thing)
{
    List<T>::append(thing);
}

template<class T>
void List<T>::pushFront(T thing)
{
    if (List<T>::isEmpty())
    {
        //creamos nuevo elemento
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direcionan tanto el inicio como el fin al nuevo elemento
        List<T>::firstNode = temp;
        List<T>::lastNode = temp;

        //El nuevo elemento no apunta a nada y se aumenta las ponderaciones
        temp->setNext(NULL);
        temp->setPrev(NULL);

        List<T>::Size = List<T>::Size + 1;
    }

    else //insertar al inicio
    {
        //se crear un nuevo elemento y se le ponen datos
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direciona el nuevo elemento al primer nodo y el inicio al nuevo elemento,
        //de este modo el nuevo se hace el 1° elemento
        temp->setNext(List<T>::firstNode);
        temp->setPrev(NULL);
        List<T>::firstNode->setPrev(temp);
        List<T>::firstNode = temp;

        List<T>::Size = List<T>::Size + 1;
    }
}

template<class T>
T List<T>::popBack()
{
    T retorno = List<T>::recover(List<T>::last());
    List<T>::deleteForPosition(List<T>::last());

    return retorno;
}

template<class T>
T List<T>::popFront()
{
    T retorno = List<T>::recover(List<T>::first());
    List<T>::deleteForPosition(List<T>::first());

    return retorno;
}

template<class T>
void List<T>::append(T thing)
{
    if (List<T>::isEmpty())
    {
        //creamos nuevo elemento
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direcionan tanto el inicio como el fin al nuevo elemento
        List<T>::firstNode = temp;
        List<T>::lastNode = temp;

        //El nuevo elemento no apunta a nada y se aumenta las ponderaciones
        temp->setNext(NULL);
        temp->setPrev(NULL);

        List<T>::Size = List<T>::Size + 1;
    }
    else
    {
        //se crear un nuevo elemento y se le ponen datos
        NodeDouble<T>* temp = new NodeDouble<T>;
        temp->setData(thing);

        //se direciona el nuevo elemento al ultimo nodo nodo y el inicio al nuevo elemento,
        //de este modo el nuevo se hace el ultimo elemento
        temp->setPrev(List<T>::lastNode);
        temp->setNext(NULL);
        List<T>::lastNode->setNext(temp);
        List<T>::lastNode = temp;

        List<T>::Size = List<T>::Size + 1;
    }
}

template<class T>
void List<T>::pop()
{
    T retorno = List<T>::recover(List<T>::last());
    List<T>::deleteForPosition(List<T>::last());

    return retorno;
}

template<class T>
T List<T>::pop(unsigned position)
{
    T retorno = List<T>::recover(position);
    List<T>::deleteForPosition(position);

    return retorno;
}

template<class T>
void extendList(List<T> lista)
{
    for (unsigned i = 0; i < List<T>::getSize(); i++)
    {
        List<T>::append(lista.recover(i));
    }
}

template<class T>
unsigned List<T>::countElement(T thing)
{
    unsigned counter = 0;
    unsigned total = 0;

    //creamos un nodo que apunte al inicio
    NodeDouble<T>* temp = List<T>::firstNode;

    //hacemos un recorrido de inicio a fin de la lista
    while (total < List<T>::Size)
    {
        if (temp->getData() == thing)
        {
            //nos dice la cantidad de veces que hay un elemento
            counter++;
        }

        temp = temp->getNext();
        total++;
    }

    //eliminamos nuestra variable de recorrido
    temp = NULL;
    delete temp;

    return counter;
}

#endif // LIST_H
