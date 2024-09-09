#ifndef __TLISTACALENDARIO_H__
#define __TLISTACALENDARIO_H__

#include "tcalendario.h"

using namespace std;

class TNodoCalendario;
class TListaPos;
class TListaCalendario;

class TNodoCalendario {

    //Clases amigas
    friend class TListaPos;
    friend class TListaCalendario;

    //Funciones amigas
    friend ostream & operator<<(ostream &, const TListaCalendario &);     //Sobrecarga

    private:
        TCalendario c;
        TNodoCalendario *siguiente;
        void Copia(const TNodoCalendario &);

    public:
        TNodoCalendario();  //Constructor por defecto
        TNodoCalendario(const TNodoCalendario &);    //Constructor de copia
        ~TNodoCalendario();
        TNodoCalendario & operator=(const TNodoCalendario &);     //Sobrecarga
};

class TListaPos {

    //Clases amigas
    friend class TNodoCalendario;
    friend class TListaCalendario;

    private:
        TNodoCalendario *pos;
        void Copia(const TListaPos &);

    public:
        TListaPos();    //Contructor por defecto
        TListaPos(const TListaPos &);     //Constructor de copia
        ~TListaPos();

        TListaPos & operator=(const TListaPos &);     //Sobrecarga
        bool operator==(const TListaPos &);   //Sobrecarga
        bool operator!=(const TListaPos &);   //Sobrecarga

        TListaPos Siguiente() const;  //Devuelve siguiente posición
        bool EsVacia() const;     //Devuelve si posición vacía
};

class TListaCalendario {

    //Funciones amigas
    friend ostream & operator<<(ostream &, const TListaCalendario &);     //Sobrecarga

    private:
        TNodoCalendario *primero;
        void Copia(const TListaCalendario &);

    public:
        TListaCalendario();     //Constructor por defecto
        TListaCalendario(const TListaCalendario &);   // Constructor de copia
        ~TListaCalendario();

        TListaCalendario & operator=(const TListaCalendario &);     //Sobrecarga
        bool operator==(const TListaCalendario &);  //Sobrecarga
        TListaCalendario operator+(const TListaCalendario &);     //Sobrecarga
        TListaCalendario operator-(const TListaCalendario &);     //Sobrecarga

        bool Insertar(const TCalendario &);     //Inserta al final
        bool Borrar(const TCalendario &);   //Busca y borra
        bool Borrar(const TListaPos &);     //Borra posición
        bool Borrar(int, int, int);     //Borra calendarios anteriores
        bool EsVacia() const;   //Devuelve si es vacía
        TCalendario Obtener(const TListaPos &) const;   //Devuelve elemento de la posición
        bool Buscar(const TCalendario &) const;     //Devuelve si existe el calendario
        int Longitud() const;   //Devuelve el tamaño
        TListaPos Primera() const;  //Devuelve primera posición
        TListaPos Ultima() const;   //Devuelve última posición
        TListaCalendario SumarSubl(int I_L1, int F_L1, const TListaCalendario &L2, int I_L2, int F_L2) const;   //Suma dos sublistas
        TListaCalendario ExtraerRango(int n1, int n2);  //Devuelve un rango de nodos
};

#endif  //__TLISTACALENDARIO_H__