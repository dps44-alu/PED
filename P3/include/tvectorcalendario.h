#ifndef __TVECTORCALENDARIO_H__
#define __TVECTORCALENDARIO_H__

#include "tcalendario.h"

using namespace std;

class TVectorCalendario {

    //Funciones Amigas
    friend ostream & operator<<(ostream &, const TVectorCalendario &);    //Sobrecarga

    private:
        TCalendario *c;
        int tamano;
        TCalendario error;
        void Copia(const TVectorCalendario &);

    public:
        TVectorCalendario();    //Constructor por defecto
        TVectorCalendario(int);  
        TVectorCalendario(const TVectorCalendario &);   //Constructor de copia
        ~TVectorCalendario();
        
        TVectorCalendario & operator=(const TVectorCalendario &);   //Sobrecarga
        bool operator==(const TVectorCalendario &) const;   //Sobrecarga
        bool operator!=(const TVectorCalendario &) const;   //Sobrecarga
        TCalendario & operator[](int);  //Sobrecarga izquierda
        TCalendario operator[](int) const;  //Sobrecarga derecha

        int Tamano() const;     //Deuelve total posiciones 
        int Ocupadas() const;   //Devuelve total posiciones no vacías
        bool ExisteCal(const TCalendario &) const;    //Devuelve si existe el calendario en el vector
        void MostrarMensajes(int, int, int) const;   //Muestra los mensajes de TCalendario >= fecha
        bool Redimensionar(int);    //Redimensiona el vector
};

#endif //__TVECTORCALENDARIO_H__