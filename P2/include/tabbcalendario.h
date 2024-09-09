#ifndef __TABBCALENDARIO_H__
#define __TABBCALENDARIO_H__

#include<queue>

#include "tvectorcalendario.h"

using namespace std;

class TNodoABB;
class TABBCalendario;

class TABBCalendario {

    //Clases amigas
    friend class TNodoABB;

    //Funciones amigas
    friend ostream & operator<<(ostream &, const TABBCalendario &);     //Sobrecarga

    private:
        TNodoABB *raiz;
        void InordenAux(TVectorCalendario &, int &) const;
        void PreordenAux(TVectorCalendario &, int &) const;
        void PostordenAux(TVectorCalendario &, int &) const;
        void Copia(const TABBCalendario &);
        void SumaAuxiliar(const TABBCalendario &);
        void RestaAuxiliar(const TABBCalendario &, const TABBCalendario &);
        TNodoABB ObtenerMayor();

    public:
        TABBCalendario();
        TABBCalendario(const TABBCalendario &);
        ~TABBCalendario();

        TABBCalendario & operator=(const TABBCalendario &);     //Sobrecarga
        bool operator==(const TABBCalendario &);    //Sobrecarga
        TABBCalendario operator+(const TABBCalendario &);   //Sobrecarga
        TABBCalendario operator-(const TABBCalendario &);   //Sobrecarga

        bool EsVacio() const;   //Devuelve si es vacío
        bool Insertar(const TCalendario &);     //Inserta nodo
        bool Borrar(const TCalendario &);   //Borra nodo
        bool Buscar(const TCalendario &) const;     //Devuelve si existe el elemento
        TCalendario Raiz() const;   //Devuelve la raíz
        int Altura() const;     //Devuelve la altura
        int Nodos() const;  //Devuelve el númeor de nodos
        int NodosHoja() const;  //Devuelve el número de nodos hoja
        TVectorCalendario Inorden() const;
        TVectorCalendario Preorden() const;
        TVectorCalendario Postorden() const;
        TVectorCalendario Niveles() const;
};

class TNodoABB {

    //Clases amigas
    friend class TABBCalendario;

private:
    TCalendario item;
    TABBCalendario iz, de;
    void Copia(const TNodoABB &);

public:
    TNodoABB();     //Constructor por defecto
    TNodoABB(const TNodoABB &);     //Constructor de copia
    ~TNodoABB();

    TNodoABB & operator=(const TNodoABB &);     //Sobrecarga
};

#endif //__TABBCALENDARIO_H__