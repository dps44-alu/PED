#ifndef __TCALENDARIO_H__
#define __TCALENDARIO_H__

#include <iostream>
#include <cstring>

using namespace std;

class TCalendario {

    //Funciones Amigas
    friend ostream & operator<<(ostream &, const TCalendario &);    //Sobrecarga

    private:
        int dia;
        int mes;
        int anyo;
        char* mensaje;
        void Copia(const TCalendario &);
        bool checkFecha(int, int, int) const;
        int maxDiasMes(int, int) const;

    public:
        TCalendario();  //Constructor por defecto
        TCalendario(int, int, int, char*);  
        TCalendario(const TCalendario &);   //Constructor de copia
        ~TCalendario();

        TCalendario & operator=(const TCalendario &);    //Sobrecarga
        TCalendario operator+(int) const;   //Sobrecarga
        TCalendario operator-(int) const;   //Sobrecarga
        TCalendario operator++(int);    //Modifica dia++ (post)
        TCalendario & operator++();     //Modifica dia++ (pre)
        TCalendario operator--(int);    //Modifica dia-- (post)
        TCalendario & operator--();     //Modifica dia-- (pre)    
        bool operator==(const TCalendario &) const;     //Sobrecarga
        bool operator!=(const TCalendario &) const;     //Sobrecarga
        bool operator>(const TCalendario &);    //Sobrecarga
        bool operator<(const TCalendario &);    //Sobrecarga

        bool ModFecha(int, int, int);   
        bool ModMensaje(char*); 
        bool EsVacio() const;
        int Dia() const;    //Devuelve dia
        int Mes() const;    //Devuelve mes
        int Anyo() const;   //Devuelve año
        char* Mensaje() const;  //Devuelve mensaje
};

#endif //__TCALENDARIO_H__