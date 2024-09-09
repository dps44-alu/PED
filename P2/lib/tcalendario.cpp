#include "../include/tcalendario.h"

/******************************************** FORMA CANÓNICA ********************************************/
TCalendario::TCalendario() {
    this->dia = 1;
    this->mes = 1;
    this->anyo = 1900;
    this->mensaje = nullptr;
}

TCalendario::TCalendario(int _dia, int _mes, int _anyo, char* _mensaje) {
    if(this->checkFecha(_dia, _mes, _anyo)) {
        this->dia = _dia;
        this->mes = _mes;
        this->anyo = _anyo;

        if(_mensaje != nullptr) {
            this->mensaje = new char[strlen(_mensaje) + 1];     //Reservar memoria
            strcpy(this->mensaje, _mensaje);    //Copiar el mensaje
        } else {
            this->mensaje = nullptr;
        }
    } else {
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = nullptr;
    }   
}  

TCalendario::TCalendario(const TCalendario &tcalendario) {
    this->Copia(tcalendario);
}

TCalendario::~TCalendario() {
    this->dia = 1;
    this->mes = 1;
    this->anyo = 1900;

    delete[] this->mensaje;
    this->mensaje = nullptr;
}

/******************************************** OPERADORES ********************************************/
TCalendario & TCalendario::operator=(const TCalendario &tcalendario) {
    if(this != &tcalendario) {
        this->~TCalendario();
        this->Copia(tcalendario);
    }
    return *this;
}

TCalendario TCalendario::operator+(int _dia) const {
    if(_dia >= 1) {
        if(this->checkFecha(this->dia + _dia, this->mes, this->anyo)) {
            return TCalendario(this->dia + _dia, this->mes, this->anyo, this->mensaje);
        } else {
            int totalDias = this->dia + _dia;
            int nuevoMes = this->mes;
            int nuevoAnyo = this->anyo;
            while(totalDias > this->maxDiasMes(nuevoMes, nuevoAnyo)) {
                totalDias -= this->maxDiasMes(this->mes, this->anyo);
                nuevoMes++;
                if(nuevoMes == 13) {
                    nuevoMes = 1;
                    nuevoAnyo++;
                }
            }
            return TCalendario(totalDias, nuevoMes, nuevoAnyo, this->mensaje);
        }
    }
    return TCalendario();
}

TCalendario TCalendario::operator-(int _dia) const {
    if(_dia >= 1) {
        if(this->dia > _dia) {
            return TCalendario(this->dia - _dia, this->mes, this->anyo, this->mensaje);
        } else {
            int totalDiasRestar = _dia;
            int totalDias = this->dia;
            int nuevoMes = this->mes;
            int nuevoAnyo = this->anyo;
            while(totalDiasRestar > 0) {
                nuevoMes--;
                if(nuevoMes == 0) {
                    nuevoMes = 12;
                    nuevoAnyo--;
                }
                if(totalDiasRestar > totalDias) {
                    totalDiasRestar -= totalDias;
                    totalDias = maxDiasMes(nuevoMes, nuevoAnyo);
                } else {
                    totalDias -= totalDiasRestar;
                    totalDiasRestar = 0;
                }
            }
            if(nuevoAnyo >= 1900) {
                return TCalendario(totalDias, nuevoMes, nuevoAnyo, this->mensaje);
            }
            return TCalendario();
        }
    }
    return TCalendario();
}

TCalendario TCalendario::operator++(int x) {
    TCalendario temporal = TCalendario(*this);
    if(this->checkFecha(this->dia + 1, this->mes, this->anyo)) {
        this->dia++;
    } else {
        this->dia = 1;
        this->mes++;
        if(this->mes == 13) {
            this->mes = 1;
            this->anyo++;
        }
    }
    return temporal;
}

TCalendario & TCalendario::operator++() {
    if(this->checkFecha(this->dia + 1, this->mes, this->anyo)) {
        this->dia++;
    } else {
        this->dia = 1;
        this->mes++;
        if(this->mes == 13) {
            this->mes = 1;
            this->anyo++;
        }
    }
    return *this;
}

TCalendario TCalendario::operator--(int x) {
    TCalendario temporal = TCalendario(*this);
    if(this->checkFecha(this->dia - 1, this->mes, this->anyo)) {
        this->dia--;
    } else {
        this->mes--;
        if(this->mes == 0) {
            this->mes = 12;
            this->anyo--;
        }
        this->dia = this->maxDiasMes(this->mes, this->anyo);
    }
    if(this->anyo < 1900) {
        this->~TCalendario();
    }
    return temporal;
}

TCalendario & TCalendario::operator--() {
    if(this->checkFecha(this->dia - 1, this->mes, this->anyo)) {
        this->dia--;
    } else {
        this->mes--;
        if(this->mes == 0) {
            this->mes = 12;
            this->anyo--;
        }
        this->dia = this->maxDiasMes(this->mes, this->anyo);
    }
    if(this->anyo >= 1900) {
        return *this;
    }
    this->~TCalendario();
    return *this;
}

bool TCalendario::operator==(const TCalendario &tcalendario) const {
    if(!this->mensaje || !tcalendario.mensaje) {
        if((!this->mensaje && tcalendario.mensaje) || (this->mensaje && !tcalendario.mensaje)) {
            return false;
        } else {
            return (this->dia == tcalendario.dia && this->mes == tcalendario.mes && this->anyo == tcalendario.anyo);
        }
    }
    return (this->dia == tcalendario.dia && this->mes == tcalendario.mes 
    && this->anyo == tcalendario.anyo && strcmp(this->mensaje, tcalendario.mensaje) == 0);
}

bool TCalendario::operator!=(const TCalendario &tcalendario) const {
    return !(*this == tcalendario);
}

bool TCalendario::operator>(const TCalendario &tcalendario) {
    if(this->anyo > tcalendario.anyo || (this->anyo == tcalendario.anyo && this->mes > tcalendario.mes)
    || (this->anyo == tcalendario.anyo && this->mes == tcalendario.mes && this->dia > tcalendario.dia)) {   //Fecha mayor
        return true;
    }
    if(this->anyo < tcalendario.anyo || (this->anyo == tcalendario.anyo && this->mes < tcalendario.mes)
       || (this->anyo == tcalendario.anyo && this->mes == tcalendario.mes && this->dia < tcalendario.dia)) {   //Fecha mayor
        return false;
    }
    if(!this->mensaje || !tcalendario.mensaje) {
        if(this->mensaje) {
            return true;
        }
    } else {
        if(strcmp(this->mensaje, tcalendario.mensaje) > 0) {
            return true;
        }
    }
    return false;
}

bool TCalendario::operator<(const TCalendario &tcalendario) {
    return !(*this == tcalendario) && !(*this > tcalendario);
}

/******************************************** MÉTODOS ********************************************/
void TCalendario::Copia(const TCalendario &tcalendario) {
    this->dia = tcalendario.dia;
    this->mes = tcalendario.mes;
    this->anyo = tcalendario.anyo;

    if(tcalendario.mensaje != nullptr) {
        this->mensaje = new char[strlen(tcalendario.mensaje) + 1];  //Reservar memoria
        strcpy(this->mensaje, tcalendario.mensaje);     //Copiar el mensaje
    } else {
        this->mensaje = nullptr;
    }
}

bool TCalendario::checkFecha(int _dia, int _mes, int _anyo) const {
    if(_anyo >= 1900) { 
        if(_mes >= 1 && _mes <= 12) {
            if(_dia >= 1 && _dia <= this->maxDiasMes(_mes, _anyo)) {
                return true;
            }
        }
    }
    return false;
}

int TCalendario::maxDiasMes(int _mes, int _anyo) const {
    if(_mes % 2 != 0 || _mes == 8) {
        return 31;
    } else {
        if(_mes == 2) {
            if(_anyo % 400 == 0 || (_anyo % 4 == 0 && _anyo % 100 != 0)) {     //Bisiesto
                return 29;
            } else {
                return 28;
            }
        } else {
            return 30;
        }
    }  
}

bool TCalendario::ModFecha(int _dia, int _mes, int _anyo) {
    if(checkFecha(_dia, _mes, _anyo)) {
        this->dia  = _dia;
        this->mes = _mes;
        this->anyo = _anyo;
        return true;
    }
    return false;
} 

bool TCalendario::ModMensaje(char* _mensaje) {
    delete[] this->mensaje;
    if(_mensaje != nullptr) {
        this->mensaje = new char[strlen(_mensaje) + 1];     //Reservar memoria
        strcpy(this->mensaje, _mensaje);    //Copiar el mensaje
    } else {
        this->mensaje = nullptr;
    }
    return true;
}

bool TCalendario::EsVacio() const {
    TCalendario temporal = TCalendario();
    return *this == temporal;
}

int TCalendario::Dia() const {
    return this->dia;
}

int TCalendario::Mes() const {
    return this->mes;
}

int TCalendario::Anyo() const {
    return this->anyo;
}

char* TCalendario::Mensaje() const {
    return this->mensaje;
}

/******************************************** FUNCIONES AMIGAS ********************************************/
ostream & operator<<(ostream &s, const TCalendario &tcalendario) {
    if(tcalendario.dia < 10) {
        s << 0;
    }
    s << tcalendario.dia << "/"; 
    if(tcalendario.mes < 10) {
        s << 0;
    }
    s << tcalendario.mes << "/" << tcalendario.anyo << " ";
    if(tcalendario.mensaje == nullptr) {
        s << '"' << '"';
    } else {
        s << '"' << tcalendario.mensaje << '"';
    }
    return s;
}