#include "../include/tavlcalendario.h"

/*########################################### TNODOAVL ###########################################*/
/******************************************** FORMA CANÓNICA ********************************************/
TNodoAVL::TNodoAVL() {
    this->fe = 0;
    this->item = TCalendario();
    this->iz = TAVLCalendario();
    this->de = TAVLCalendario();
}

TNodoAVL::TNodoAVL(const TNodoAVL &tnodoavl) {
    this->Copia(tnodoavl);
}

TNodoAVL::~TNodoAVL() {
    this->fe = 0;
    this->item.~TCalendario();
    this->iz.~TAVLCalendario();
    this->de.~TAVLCalendario();
}

/******************************************** OPERADORES ********************************************/
TNodoAVL & TNodoAVL::operator=(const TNodoAVL &tnodoavl) {
    if(this != &tnodoavl) {
        this->~TNodoAVL();
        this->Copia(tnodoavl);
    }
    return *this;
}

/******************************************** MÉTODOS ********************************************/
void TNodoAVL::Copia(const TNodoAVL &tnodoavl) {
    this->fe = tnodoavl.fe;
    this->item = tnodoavl.item;
    this->iz = tnodoavl.iz;
    this->de = tnodoavl.de;
}


/*########################################### TAVLCALENDARIO ###########################################*/
/******************************************** FORMA CANÓNICA ********************************************/
TAVLCalendario::TAVLCalendario() {
    this->raiz = nullptr;
}

TAVLCalendario::TAVLCalendario(const TAVLCalendario &avl) {
    if(avl.raiz) {
        this->Copia(avl);
    } else {
        this->raiz = nullptr;
    }
}

TAVLCalendario::~TAVLCalendario() {
    if(this->raiz) {
        this->raiz->iz.~TAVLCalendario();
        this->raiz->de.~TAVLCalendario();
        this->raiz->item.~TCalendario();
        this->raiz = nullptr;
    }
}

/******************************************** OPERADORES ********************************************/
TAVLCalendario & TAVLCalendario::operator=(const TAVLCalendario &avl) {
    if(this != &avl) {
        this->~TAVLCalendario();
        this->Copia(avl);
    }
    return *this;
}

bool TAVLCalendario::operator==(const TAVLCalendario &avl) const  {
    if(this->Nodos() == avl.Nodos()) {
        return this->opEqualsAux(avl);
    }
    return false;
}

bool TAVLCalendario::operator!=(const TAVLCalendario &avl) const {
    return !this->operator==(avl);
}

/******************************************** MÉTODOS ********************************************/
void TAVLCalendario::InordenAux(TVectorCalendario &vector, int &posicion) const {
    if(this->raiz->iz.raiz) {
        this->raiz->iz.InordenAux(vector, posicion);
    }
    vector[posicion] = this->raiz->item;
    posicion++;
    if(this->raiz->de.raiz) {
        this->raiz->de.InordenAux(vector, posicion);
    }
}

void TAVLCalendario::PreordenAux(TVectorCalendario &vector, int &posicion) const {
    vector[posicion] = this->raiz->item;
    posicion++;
    if(this->raiz->iz.raiz) {
        this->raiz->iz.PreordenAux(vector, posicion);
    }
    if(this->raiz->de.raiz) {
        this->raiz->de.PreordenAux(vector, posicion);
    }
}

void TAVLCalendario::PostordenAux(TVectorCalendario &vector, int &posicion) const {
    if(this->raiz->iz.raiz) {
        this->raiz->iz.PostordenAux(vector, posicion);
    }
    if(this->raiz->de.raiz) {
        this->raiz->de.PostordenAux(vector, posicion);
    }
    vector[posicion] = this->raiz->item;
    posicion++;
}


bool TAVLCalendario::opEqualsAux(const TAVLCalendario &avl) const {
    TNodoAVL *auxiliar = avl.raiz;
    if(auxiliar) {
        if(!this->Buscar(auxiliar->item)) {
            return false;
        }
        return this->opEqualsAux(auxiliar->iz) && this->opEqualsAux(auxiliar->de);
    }
    return true;
}

bool TAVLCalendario::InsertarAux(const TCalendario &calendario) {
    if(this->raiz) {
        if(this->raiz->item == calendario) {
            return false;
        } else if(this->raiz->item > calendario) {
            return this->raiz->iz.InsertarAux(calendario);
        } else if(this->raiz->item < calendario) {
            return this->raiz->de.InsertarAux(calendario);
        }
    }
    this->raiz = new TNodoAVL();
    this->raiz->item = calendario;
    return true;
}

void TAVLCalendario::ActualizarFe() {
    if(this->raiz) {
        this->raiz->fe = this->raiz->de.Altura() - this->raiz->iz.Altura();
        this->raiz->iz.ActualizarFe();
        this->raiz->de.ActualizarFe();
    }
}

void TAVLCalendario::Rotar() {
    if(this->raiz) {
        this->raiz->iz.Rotar();
        this->ActualizarFe();
        this->raiz->de.Rotar();
        this->ActualizarFe();
        if(this->raiz->fe == 2 || this->raiz->fe == -2) {   //Desequilibrio
            TNodoAVL *aux1 = this->raiz;
            if(this->raiz->fe >= 2) {   //(+2, ?)
                if(this->raiz->de.raiz->fe == 1 || this->raiz->de.raiz->fe == 0) {  //(+2, +1) (+2, 0)
                    TNodoAVL *aux2 = this->raiz->de.raiz->iz.raiz ? this->raiz->de.raiz->iz.raiz : nullptr;
                    this->raiz = this->raiz->de.raiz;
                    this->raiz->iz.raiz = aux1;
                    this->raiz->iz.raiz->de.raiz = aux2;
                } else {    //(+2, -1)
                    TNodoAVL *aux2 = this->raiz->de.raiz->iz.raiz->iz.raiz
                            ? this->raiz->de.raiz->iz.raiz->iz.raiz : nullptr;
                    TNodoAVL *aux3 = this->raiz->de.raiz->iz.raiz->de.raiz
                                     ? this->raiz->de.raiz->iz.raiz->de.raiz : nullptr;
                    TNodoAVL *aux4 = this->raiz->de.raiz ? this->raiz->de.raiz : nullptr;
                    this->raiz = this->raiz->de.raiz->iz.raiz;
                    this->raiz->de.raiz = aux4;
                    this->raiz->de.raiz->iz.raiz = aux3;
                    this->raiz->iz.raiz = aux1;
                    this->raiz->iz.raiz->de.raiz = aux2;
                }
            } else {    //(-2, ?)
                if(this->raiz->iz.raiz->fe == -1 || this->raiz->iz.raiz->fe == 0) {  //(-2, -1) (-2, 0)
                    TNodoAVL *aux2 = this->raiz->iz.raiz->de.raiz ? this->raiz->iz.raiz->de.raiz : nullptr;
                    this->raiz = this->raiz->iz.raiz;
                    this->raiz->de.raiz = aux1;
                    this->raiz->de.raiz->iz.raiz = aux2;
                } else {    //(-2, +1)
                    TNodoAVL *aux2 = this->raiz->iz.raiz->de.raiz->iz.raiz
                                     ? this->raiz->iz.raiz->de.raiz->iz.raiz : nullptr;
                    TNodoAVL *aux3 = this->raiz->iz.raiz->de.raiz->de.raiz
                                     ? this->raiz->iz.raiz->de.raiz->de.raiz : nullptr;
                    TNodoAVL *aux4 = this->raiz->iz.raiz ? this->raiz->iz.raiz : nullptr;
                    this->raiz = this->raiz->iz.raiz->de.raiz;
                    this->raiz->iz.raiz = aux4;
                    this->raiz->iz.raiz->de.raiz = aux2;
                    this->raiz->de.raiz = aux1;
                    this->raiz->de.raiz->iz.raiz = aux3;
                }
            }
        }
    }
}

TNodoAVL TAVLCalendario::ObtenerMayor() {
    if(this->raiz->de.raiz) {
        return this->raiz->de.ObtenerMayor();
    }
    TNodoAVL nodo = *this->raiz;
    if(this->raiz->iz.raiz) {
        this->raiz = this->raiz->iz.raiz;
    } else {
        this->raiz = nullptr;
    }
    return nodo;
}

void TAVLCalendario::Copia(const TAVLCalendario &avl) {
    if(avl.raiz) {
        this->raiz = new TNodoAVL();
        this->raiz->fe = avl.raiz->fe;
        this->raiz->item = avl.raiz->item;
        this->raiz->iz = avl.raiz->iz;
        this->raiz->de = avl.raiz->de;
        this->raiz->iz.Copia(avl.raiz->iz);
        this->raiz->de.Copia(avl.raiz->de);
    }
}

bool TAVLCalendario::EsVacio() const {
    return !this->raiz;
}

bool TAVLCalendario::Insertar(const TCalendario &calendario) {
    if(this->InsertarAux(calendario)) {
        this->ActualizarFe();
        this->Rotar();
        this->ActualizarFe();
        return true;
    }
    return false;
}

bool TAVLCalendario::Buscar(const TCalendario &calendario) const {
    if(this->raiz) {
        if(this->raiz->item == calendario) {
            return true;
        } else {
            return this->raiz->iz.Buscar(calendario) || this->raiz->de.Buscar(calendario);
        }
    }
    return false;
}

int TAVLCalendario::Altura() const {
    if(this->raiz) {
        return 1 + max(this->raiz->iz.Altura(), this->raiz->de.Altura());
    }
    return 0;
}

int TAVLCalendario::Nodos() const {
    if(this->raiz) {
        return 1 + this->raiz->iz.Nodos() + this->raiz->de.Nodos();
    }
    return 0;
}

int TAVLCalendario::NodosHoja() const {
    if(this->raiz) {
        if(!this->raiz->iz.raiz && !this->raiz->de.raiz) {
            return 1;
        }
        return this->raiz->iz.NodosHoja() + this->raiz->de.NodosHoja();
    }
    return 0;
}

TVectorCalendario TAVLCalendario::Inorden() const {
    TVectorCalendario v(Nodos());
    if(this->raiz) {
        int posicion = 1;
        this->InordenAux(v, posicion);
    }
    return v;
}

TVectorCalendario TAVLCalendario::Preorden() const {
    TVectorCalendario v(Nodos());
    if(this->raiz) {
        int posicion = 1;
        this->PreordenAux(v, posicion);
    }
    return v;
}

TVectorCalendario TAVLCalendario::Postorden() const {
    TVectorCalendario v(Nodos());
    if(this->raiz) {
        int posicion = 1;
        this->PostordenAux(v, posicion);
    }
    return v;
}

bool TAVLCalendario::Borrar(const TCalendario &calendario) {
    if(this->Buscar(calendario)) {
        if(this->raiz->item == calendario) {
            if(!this->raiz->iz.raiz) {  //No hay hijo izquierdo
                this->raiz = this->raiz->de.raiz;
            } else {
                TNodoAVL mayor = this->raiz->iz.ObtenerMayor();
                mayor.iz = this->raiz->iz;
                mayor.de = this->raiz->de;
                *this->raiz = mayor;
            }
            this->ActualizarFe();
            this->Rotar();
            this->ActualizarFe();
            return true;
        } else if(this->raiz->iz.Buscar(calendario)) {
            this->raiz->iz.Borrar(calendario);
            this->ActualizarFe();
            this->Rotar();
            this->ActualizarFe();
            return true;
        } else if(this->raiz->de.Buscar(calendario)) {
            this->raiz->de.Borrar(calendario);
            this->ActualizarFe();
            this->Rotar();
            this->ActualizarFe();
            return true;
        }
    }
    return false;
}

TCalendario TAVLCalendario::Raiz() const {
    if(this->raiz) {
        return this->raiz->item;
    }
    return TCalendario();
}

ostream & operator<<(ostream &s, const TAVLCalendario &avl) {
    TVectorCalendario vector = avl.Inorden();
    s << vector;
    return s;
}