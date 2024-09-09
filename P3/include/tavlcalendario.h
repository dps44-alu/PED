#ifndef __TAVLCALENDARIO_H__
#define __TAVLCALENDARIO_H__

#include "tvectorcalendario.h"

using namespace std;

class TNodoAVL;
class TAVLCalendario;

class TAVLCalendario {

    //Clases amigas
    friend class TNodoAVL;

    //Funciones amigas
    friend ostream & operator<<(ostream &, const TAVLCalendario &);     //Sobrecarga

private:
    TNodoAVL *raiz;
    void InordenAux(TVectorCalendario &, int &) const;
    void PreordenAux(TVectorCalendario &, int &) const;
    void PostordenAux(TVectorCalendario &, int &) const;
    bool opEqualsAux(const TAVLCalendario &) const;
    bool InsertarAux(const TCalendario &);
    void ActualizarFe();
    void Rotar();
    TNodoAVL ObtenerMayor();
    void Copia(const TAVLCalendario &);

public:
    TAVLCalendario();   //Constructor
    TAVLCalendario(const TAVLCalendario &);     //Constructor de copia
    ~TAVLCalendario();

    TAVLCalendario & operator=(const TAVLCalendario &);     //Sobrecarga
    bool operator==(const TAVLCalendario &) const;     //Sobrecarga
    bool operator!=(const TAVLCalendario &) const;     //Sobrecarga

    bool EsVacio() const;     //Devuelve si el árbol está vacío
    bool Insertar(const TCalendario &);     //Inserta el elemento
    bool Buscar(const TCalendario &) const;   //Devuelve si el elemento está en el árbol
    int Altura() const;   //Devuelve la altura del árbol (vacío = 0)
    int Nodos() const;    //Devuelve el número de nodos (vacío = 0)
    int NodosHoja() const;    //Devuelve el número de nodos (árbol de sólo raiz = 1)
    TVectorCalendario Inorden() const;    //Devuelve recorrido INORDEN
    TVectorCalendario Preorden() const;   //Devuelve recorrido PREORDEN
    TVectorCalendario Postorden() const;  //Devuelve recorrido POSTORDEN
    bool Borrar(const TCalendario &);   //Borra un TCalendario
    TCalendario Raiz() const;     //Devuelve el TCalanedario de la raíz
};

class TNodoAVL {

    //Clases amigas
    friend class TAVLCalendario;

private:
    int fe;
    TCalendario item;
    TAVLCalendario iz, de;
    void Copia(const TNodoAVL &);

public:
    TNodoAVL();     //Constructor por defecto
    TNodoAVL(const TNodoAVL &);     //Constructor de copia
    ~TNodoAVL();

    TNodoAVL & operator=(const TNodoAVL &);     //Sobrecarga
};

#endif //__TAVLCALENDARIO_H__