#include "../include/tvectorcalendario.h"

/******************************************** FORMA CANÓNICA ********************************************/
TVectorCalendario::TVectorCalendario() {
    this->c = nullptr;
    this->tamano = 0;
}

TVectorCalendario::TVectorCalendario(int _tamano) {
    if(_tamano <= 0) {
        this->c = nullptr;
        this->tamano = 0;
    } else {
        this->c = new TCalendario[_tamano];
        for(unsigned i = 0; i < _tamano; i++) {
            this->c[i] = TCalendario();
        }
        this->tamano = _tamano;
    }
}

TVectorCalendario::TVectorCalendario(const TVectorCalendario &tvectorcalendario) {
    if(*this != tvectorcalendario) {
        this->~TVectorCalendario();
        this->Copia(tvectorcalendario);
    }
}

TVectorCalendario::~TVectorCalendario() {
    delete[] this->c;
    this->c = nullptr;
    this->tamano = 0;
}

/******************************************** OPERADORES ********************************************/
TVectorCalendario & TVectorCalendario::operator=(const TVectorCalendario &tvectorcalendario) {
    if(this != &tvectorcalendario) {
        this->~TVectorCalendario();
        this->Copia(tvectorcalendario);
    }
    return *this;
}

bool TVectorCalendario::operator==(const TVectorCalendario &tvectorcalendario) const {
    bool iguales = false;
    if(this->tamano == tvectorcalendario.tamano) {
        iguales = true;
        for(unsigned i = 0; i < this->tamano; i++) {
            if(this->c[i] != tvectorcalendario.c[i]) {
                iguales = false;
                break;
            }
        }
    }
    return iguales;
}

bool TVectorCalendario::operator!=(const TVectorCalendario &tvectorcalendario) const {
    return !(*this == tvectorcalendario);
}

TCalendario & TVectorCalendario::operator[](int _posicion) {
    if(this->tamano >= _posicion) {
        return this->c[_posicion - 1];
    }
    this->error = TCalendario();
    return this->error;
}

TCalendario TVectorCalendario::operator[](int _posicion) const {
    if(this->tamano >= _posicion) {
        return this->c[this->tamano - _posicion + 1];
    }
    return TCalendario();
}

/******************************************** MÉTODOS ********************************************/
void TVectorCalendario::Copia(const TVectorCalendario &tvectorcalendario) {
    this->c = new TCalendario[tvectorcalendario.tamano];
    for(unsigned i = 0; i < tvectorcalendario.tamano; i++) {
        this->c[i] = tvectorcalendario.c[i];
    }
    this->tamano = tvectorcalendario.tamano;
}

int TVectorCalendario::Tamano() const {
    return this->tamano;
}

int TVectorCalendario::Ocupadas() const {
    TCalendario calendarioVacio = TCalendario();
    int contador = 0;
    for(unsigned i = 0; i < this->tamano; i++) {
        if(this->c[i] != calendarioVacio) {
            contador++;
        }
    }
    return contador;
}

bool TVectorCalendario::ExisteCal(const TCalendario &tcalendario) const {
    for(unsigned i = 0; i < this->tamano; i++) {
        if(this->c[i] == tcalendario) {
            return true;
        }
    }
    return false;
}

void TVectorCalendario::MostrarMensajes(int _dia, int _mes, int _anyo) const {
    TCalendario fecha = TCalendario(_dia, _mes, _anyo, nullptr);
    int posicionesVector[this->tamano];
    int contadorPosiciones = 0;
    for(unsigned i = 0; i < this->tamano; i++) {
        fecha.ModMensaje(this->c[i].Mensaje());     //Mismo mensaje para comparar fechas
        if(this->c[i] == fecha || this->c[i] > fecha) {
            posicionesVector[contadorPosiciones] = i + 1;
            contadorPosiciones++;
        }
    }
    cout << "[";
    for(unsigned i = 0; i < contadorPosiciones; i++) {
        cout << this->c[posicionesVector[i] - 1];
        if (i + 1 < contadorPosiciones) {
            cout << ", ";
        }
    }
    cout << "]";
}

bool TVectorCalendario::Redimensionar(int _tamano) {
    if(_tamano > 0 && this->tamano != _tamano) {
        TCalendario *temporal = new TCalendario[_tamano];
        if(_tamano > this->tamano) {
            for(unsigned i = 0; i < _tamano; i++) {
                if(i < this->tamano) {
                    temporal[i] = this->c[i];
                } else {
                    temporal[i] = TCalendario();
                }
            }
        } else {
            for(unsigned i = 0; i < _tamano; i++) {
                temporal[i] = this->c[i];
            }
        }
        delete[] this->c;
        this->c = temporal;
        this->tamano = _tamano;
        return true;
    }
    return false;
}

/******************************************** FUNCIONES AMIGAS ********************************************/
ostream & operator<<(ostream &s, const TVectorCalendario &tvectorcalendario) {
    s << "[";
    for(unsigned i = 0; i < tvectorcalendario.tamano; i++) {
        s << "(" << i + 1 << ") " << tvectorcalendario.c[i];
        if(i + 1 < tvectorcalendario.tamano) {
            s << ", ";
        }
    }
    s << "]";
    return s;
}
