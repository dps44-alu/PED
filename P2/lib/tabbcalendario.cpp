#include "../include/tabbcalendario.h"

/*########################################### TNODOABB ###########################################*/
/******************************************** FORMA CANÓNICA ********************************************/
TNodoABB::TNodoABB() {
    this->item = TCalendario();
    this->iz = TABBCalendario();
    this->de = TABBCalendario();
}

TNodoABB::TNodoABB(const TNodoABB &tnodoabb) {
    this->Copia(tnodoabb);
}

TNodoABB::~TNodoABB() {
    this->item.~TCalendario();
    this->iz.~TABBCalendario();
    this->de.~TABBCalendario();
}

/******************************************** OPERADORES ********************************************/
TNodoABB & TNodoABB::operator=(const TNodoABB &tnodoabb) {
    if(this != &tnodoabb) {
        this->~TNodoABB();
        this->Copia(tnodoabb);
    }
    return *this;
}

/******************************************** MÉTODOS ********************************************/
void TNodoABB::Copia(const TNodoABB &tnodoabb) {
    this->item = tnodoabb.item;
    this->iz = tnodoabb.iz;
    this->de = tnodoabb.de;
}

/*########################################### TABBCALENDARIO ###########################################*/
/******************************************** FORMA CANÓNICA ********************************************/
TABBCalendario::TABBCalendario() {
    this->raiz = nullptr;
}

TABBCalendario::TABBCalendario(const TABBCalendario &tabbcalendario) {
    if(tabbcalendario.raiz) {
        this->Copia(tabbcalendario);
    } else {
        this->raiz = nullptr;
    }
}

TABBCalendario::~TABBCalendario() {
    if(this->raiz) {
        this->raiz->iz.~TABBCalendario();
        this->raiz->de.~TABBCalendario();
        this->raiz->item.~TCalendario();
        this->raiz = nullptr;
    }
}

/******************************************** OPERADORES ********************************************/
TABBCalendario & TABBCalendario::operator=(const TABBCalendario &tabbcalendario) {
    if(this != &tabbcalendario) {
        this->~TABBCalendario();
        this->Copia(tabbcalendario);
    }
    return *this;
}

bool TABBCalendario::operator==(const TABBCalendario &tabbcalendario) {
    TNodoABB *auxiliar = tabbcalendario.raiz;
    if(auxiliar) {
        if(!this->Buscar(auxiliar->item)) {
            return false;
        }
        return this->operator==(auxiliar->iz) && this->operator==(auxiliar->de);
    }
    return true;
}

TABBCalendario TABBCalendario::operator+(const TABBCalendario &tabbcalendario) {
    TABBCalendario nuevo = TABBCalendario(*this);
    nuevo.SumaAuxiliar(tabbcalendario);
    return nuevo;
}

TABBCalendario TABBCalendario::operator-(const TABBCalendario &tabbcalendario) {
    TABBCalendario nuevo;
    nuevo.RestaAuxiliar(*this, tabbcalendario);
    return nuevo;
}

/******************************************** MÉTODOS ********************************************/
void TABBCalendario::InordenAux(TVectorCalendario &vector, int &posicion) const {
    if(this->raiz->iz.raiz) {
        this->raiz->iz.InordenAux(vector, posicion);
    }
    vector[posicion] = this->raiz->item;
    posicion++;
    if(this->raiz->de.raiz) {
        this->raiz->de.InordenAux(vector, posicion);
    }
}

void TABBCalendario::PreordenAux(TVectorCalendario &vector, int &posicion) const {
    vector[posicion] = this->raiz->item;
    posicion++;
    if(this->raiz->iz.raiz) {
        this->raiz->iz.PreordenAux(vector, posicion);
    }
    if(this->raiz->de.raiz) {
        this->raiz->de.PreordenAux(vector, posicion);
    }
}

void TABBCalendario::PostordenAux(TVectorCalendario &vector, int &posicion) const {
    if(this->raiz->iz.raiz) {
        this->raiz->iz.PostordenAux(vector, posicion);
    }
    if(this->raiz->de.raiz) {
        this->raiz->de.PostordenAux(vector, posicion);
    }
    vector[posicion] = this->raiz->item;
    posicion++;
}

void TABBCalendario::Copia(const TABBCalendario &tabbcalendario) {
    if(tabbcalendario.raiz) {
        this->raiz = new TNodoABB();
        this->raiz->item = tabbcalendario.raiz->item;
        this->raiz->iz = tabbcalendario.raiz->iz;
        this->raiz->de = tabbcalendario.raiz->de;
        this->raiz->iz.Copia(tabbcalendario.raiz->iz);
        this->raiz->de.Copia(tabbcalendario.raiz->de);
    }
}

void TABBCalendario::SumaAuxiliar(const TABBCalendario &tabbcalendario) {
    if(tabbcalendario.raiz) {
        if(tabbcalendario.raiz->iz.raiz) {
            this->SumaAuxiliar(tabbcalendario.raiz->iz);
        }
        this->Insertar(tabbcalendario.raiz->item);
        if(tabbcalendario.raiz->de.raiz) {
            this->SumaAuxiliar(tabbcalendario.raiz->de);
        }
    }
}

void TABBCalendario::RestaAuxiliar(const TABBCalendario &tabb1, const TABBCalendario &tabb2) {
    if(tabb1.raiz) {
        if(tabb1.raiz->iz.raiz) {
            this->RestaAuxiliar(tabb1.raiz->iz, tabb2);
        }
        if(!tabb2.Buscar(tabb1.raiz->item)) {
            this->Insertar(tabb1.raiz->item);
        }
        if(tabb1.raiz->de.raiz) {
            this->RestaAuxiliar(tabb1.raiz->de, tabb2);
        }
    }
}

TNodoABB TABBCalendario::ObtenerMayor() {
    if(this->raiz->de.raiz) {
       return this->raiz->de.ObtenerMayor();
    }
    TNodoABB nodo = *this->raiz;
    if(this->raiz->iz.raiz) {
        this->raiz = this->raiz->iz.raiz;
    } else {
        this->raiz = nullptr;
    }
    return nodo;
}

bool TABBCalendario::EsVacio() const {
    return !this->raiz;
}

bool TABBCalendario::Insertar(const TCalendario &calendario) {
    if(this->raiz) {
        if(this->raiz->item == calendario) {
            return false;
        } else if(this->raiz->item > calendario) {
            return this->raiz->iz.Insertar(calendario);
        } else if(this->raiz->item < calendario) {
            return this->raiz->de.Insertar(calendario);
        }
    }
    this->raiz = new TNodoABB();
    this->raiz->item = calendario;
    return true;
}

bool TABBCalendario::Borrar(const TCalendario &calendario) {
    if(this->Buscar(calendario)) {
        if(this->raiz->item == calendario) {
            if(!this->raiz->iz.raiz) {  //No hay hijo izquierdo
                this->raiz = this->raiz->de.raiz;
            } else {
                TNodoABB mayor = this->raiz->iz.ObtenerMayor();
                mayor.iz = this->raiz->iz;
                mayor.de = this->raiz->de;
                *this->raiz = mayor;
            }
            return true;
        } else if(this->raiz->iz.Buscar(calendario)) {
            this->raiz->iz.Borrar(calendario);
        } else if(this->raiz->de.Buscar(calendario)) {
            this->raiz->de.Borrar(calendario);
        }
    }
    return false;
}

bool TABBCalendario::Buscar(const TCalendario &calendario) const {
    if(this->raiz) {
        if(this->raiz->item == calendario) {
            return true;
        } else {
            return this->raiz->iz.Buscar(calendario) || this->raiz->de.Buscar(calendario);
        }
    }
    return false;
}

TCalendario TABBCalendario::Raiz() const {
    if(this->raiz) {
        return this->raiz->item;
    }
    return TCalendario();
}

int TABBCalendario::Altura() const {
    if(this->raiz) {
        return 1 + max(this->raiz->iz.Altura(), this->raiz->de.Altura());
    }
    return 0;
}

int TABBCalendario::Nodos() const {
    if(this->raiz) {
        return 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
    }
    return 0;
}

int TABBCalendario::NodosHoja() const {
    if(this->raiz) {
        if(!this->raiz->iz.raiz && !this->raiz->de.raiz) {
            return 1;
        }
        return this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
    }
    return 0;
}

TVectorCalendario TABBCalendario::Inorden() const {
    TVectorCalendario vector = TVectorCalendario(this->Nodos());
    if(this->raiz) {
        int posicion = 1;
        this->InordenAux(vector, posicion);
    }
    return vector;
}

TVectorCalendario TABBCalendario::Preorden() const {
    TVectorCalendario vector = TVectorCalendario(this->Nodos());
    if(this->raiz) {
        int posicion = 1;
        this->PreordenAux(vector, posicion);
    }
    return vector;
}

TVectorCalendario TABBCalendario::Postorden() const {
    TVectorCalendario vector = TVectorCalendario(this->Nodos());
    if(this->raiz) {
        int posicion = 1;
        this->PostordenAux(vector, posicion);
    }
    return vector;
}

TVectorCalendario TABBCalendario::Niveles() const {
    TVectorCalendario vector = TVectorCalendario(this->Nodos());
    if(this->raiz) {
        TABBCalendario auxiliar = TABBCalendario(*this);
        queue<TABBCalendario> cola;
        cola.push(auxiliar);
        int posicion = 1;

        while(!cola.empty()) {
            auxiliar = cola.front();
            vector[posicion] = auxiliar.Raiz();
            posicion++;
            cola.pop();
            if(auxiliar.raiz->iz.raiz) {
                cola.push(auxiliar.raiz->iz);
            }
            if(auxiliar.raiz->de.raiz) {
                cola.push(auxiliar.raiz->de);
            }
        }
    }
    return vector;
}

ostream & operator<<(ostream &s, const TABBCalendario &tabbcalendario) {
    TVectorCalendario vector = tabbcalendario.Niveles();
    s << vector;
    return s;
}
