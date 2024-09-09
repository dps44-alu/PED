#include "../include/tlistacalendario.h"

/*########################################### TNODOCALENDARIO ###########################################*/
/******************************************** FORMA CANÓNICA ********************************************/
TNodoCalendario::TNodoCalendario() {
    this->c = TCalendario();
    this->siguiente = nullptr;
}

TNodoCalendario::TNodoCalendario(const TNodoCalendario &tnodocalendario) {
    this->Copia(tnodocalendario);
}

TNodoCalendario::~TNodoCalendario() {
    this->c.~TCalendario();
    this->siguiente = nullptr;
}

/******************************************** OPERADORES ********************************************/
TNodoCalendario & TNodoCalendario::operator=(const TNodoCalendario &tnodocalendario) {
    if(this != &tnodocalendario) {
        this->~TNodoCalendario();
        this->Copia(tnodocalendario);
    }
    return *this;
}

/******************************************** MÉTODOS ********************************************/
void TNodoCalendario::Copia(const TNodoCalendario &tnodocalendario) {
    this->c = tnodocalendario.c;
    this->siguiente = tnodocalendario.siguiente;
}

/*########################################### TLISTAPOS ###########################################*/
/******************************************** FORMA CANÓNICA ********************************************/
TListaPos::TListaPos() {
    this->pos = nullptr;
}

TListaPos::TListaPos(const TListaPos &tlistapos) {
    this->Copia(tlistapos);
}

TListaPos::~TListaPos() {
    this->pos = nullptr;
}

/******************************************** OPERADORES ********************************************/
TListaPos & TListaPos::operator=(const TListaPos &tlistapos) {
    if(this != &tlistapos) {
        this->~TListaPos();
        this->Copia(tlistapos);
    }
    return *this;
}

bool TListaPos::operator==(const TListaPos &tlistapos) {
    return this->pos == tlistapos.pos;
}

bool TListaPos::operator!=(const TListaPos &tlistapos) {
    return !(*this == tlistapos);
}

/******************************************** MÉTODOS ********************************************/
void TListaPos::Copia(const TListaPos &tlistapos) {
    this->pos = tlistapos.pos;
}

TListaPos TListaPos::Siguiente() const {
    TListaPos siguiente = TListaPos();
    if(this->pos) {     //Distinto de nullptr
        siguiente.pos = this->pos->siguiente;
    }
    return siguiente;
}

bool TListaPos::EsVacia() const {
    return !this->pos;  //Igual de nullptr
}

/*########################################### TLISTACALENDARIO ###########################################*/
/******************************************** FORMA CANÓNICA ********************************************/
TListaCalendario::TListaCalendario() {
    this->primero = nullptr;
}

TListaCalendario::TListaCalendario(const TListaCalendario &tlistacalendario) {
    this->primero = nullptr;
    this->Copia(tlistacalendario);
}

TListaCalendario::~TListaCalendario() {
    TNodoCalendario *actual = this->primero;
    while(actual) {
        this->primero = this->primero->siguiente;
        delete actual;
        actual = nullptr;
        actual = this->primero;
    }
}

/******************************************** OPERADORES ********************************************/
TListaCalendario & TListaCalendario::operator=(const TListaCalendario &tlistacalendario) {
    if(this != &tlistacalendario) {
        this->~TListaCalendario();
        this->Copia(tlistacalendario);
    }
    return *this;
}

bool TListaCalendario::operator==(const TListaCalendario &tlistacalendario) {
    TNodoCalendario *actual1 = this->primero;
    TNodoCalendario *auxiliar = tlistacalendario.primero;
    while(actual1 && auxiliar) {
        if(actual1->c != auxiliar->c) {
            return false;
        }
        actual1 = actual1->siguiente;
        auxiliar = auxiliar->siguiente;
    }
    if((actual1 && !auxiliar) || (!actual1 && auxiliar)) {
        return false;
    }
    return true;
}

TListaCalendario TListaCalendario::operator+(const TListaCalendario &tlistacalendario) {
    TListaCalendario nuevo = *this;     //Copio la primera parte
    TNodoCalendario *actual = tlistacalendario.primero;
    while(actual) {
        nuevo.Insertar(actual->c);  //Inserto la sengunda parte
        actual = actual->siguiente;
    }
    return nuevo;
}

//elementos de this que no existen en tlistacalendario
TListaCalendario TListaCalendario::operator-(const TListaCalendario &tlistacalendario) {
    TNodoCalendario *auxiliar;
    TNodoCalendario *actual = this->primero;
    TListaCalendario nuevo = TListaCalendario();
    bool insertar;
    while(actual) {
        auxiliar = tlistacalendario.primero;
        insertar = true;
        while(auxiliar) {
            if (actual->c == auxiliar->c) {
                insertar = false;
                break;
            }
            auxiliar = auxiliar->siguiente;
        }
        if(insertar) {
            nuevo.Insertar(actual->c);
        }
        actual = actual->siguiente;
    }
    return nuevo;
}

/******************************************** MÉTODOS ********************************************/
void TListaCalendario::Copia(const TListaCalendario &tlistacalendario) {
    TNodoCalendario *actual = this->primero;
    TNodoCalendario *auxiliar = tlistacalendario.primero;
    TNodoCalendario *nuevo;
    while(auxiliar) {
        nuevo = new TNodoCalendario();
        if(!this->primero) {
            this->primero = nuevo;
        } else {
            actual->siguiente = nuevo;  //nuevo se situa a continuacion de actual
        }
        nuevo->c = auxiliar->c;
        actual = nuevo;     //actual = actual->siguiente
        auxiliar = auxiliar->siguiente;     //Va uno por delante de actual
    }
}

bool TListaCalendario::Insertar(const TCalendario &tcalendario) {
    TNodoCalendario *actual = this->primero;
    TNodoCalendario *anterior = new TNodoCalendario();
    TNodoCalendario *nuevo = new TNodoCalendario();     //Nodo a insertar
    nuevo->c = tcalendario;
    if(!this->primero) {
        this->primero = nuevo;
        return true;
    } else {
        while(actual) {
            if(actual->c > tcalendario) {
                if(actual == this->primero) {   //Al principio
                    nuevo->siguiente = new TNodoCalendario(*this->primero);
                    this->primero = nuevo;
                } else {    //En medio
                    nuevo->siguiente = new TNodoCalendario(*actual);
                    anterior->siguiente = nuevo;
                } 
                return true;      
            }
            anterior = actual;
            actual = actual->siguiente;
            if(!actual) {   //Al final
                anterior->siguiente = nuevo;
                return true;
            }
        }
    }
    return false;
}

bool TListaCalendario::Borrar(const TCalendario &tcalendario) {
    TNodoCalendario *actual, *anterior = actual = this->primero;
    while(actual) {
        if(actual->c == tcalendario) {
            if(actual == this->primero) {   //Al principio
                this->primero = this->primero->siguiente;
            } else {    //En medio o al final
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

bool TListaCalendario::Borrar(const TListaPos &tlistapos) {
    TNodoCalendario *actual, *anterior = actual = this->primero;
    while(actual) {
        if(actual == tlistapos.pos) {
            if(actual == this->primero) {   //Al principio
                this->primero = this->primero->siguiente;
            } else {    //En medio o al final
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

bool TListaCalendario::Borrar(int dia, int mes, int anyo) {
    bool borrar = false;
    TNodoCalendario *actual = this->primero;
    TCalendario calendario = TCalendario(dia, mes, anyo, nullptr);
    TCalendario calendarioActual;
    while(actual) {
        calendarioActual = TCalendario(actual->c.Dia(), actual->c.Mes(), actual->c.Anyo(), nullptr);
        if(calendarioActual < calendario) {
            this->primero = this->primero->siguiente;
            actual = this->primero;
            borrar = true;
        } else {
            return borrar;
        }
    }
    return false;
}

bool TListaCalendario::EsVacia() const {
    return !this->primero;
}

TCalendario TListaCalendario::Obtener(const TListaPos &tlistapos) const {
    TNodoCalendario *actual = this->primero;
    while(actual) {
        if(actual == tlistapos.pos) {
            break;
        }
        actual = actual->siguiente;
    }
    return actual ? actual->c : TCalendario();     //si actual!=null entonces actual->c sino TCalendario()
}

bool TListaCalendario::Buscar(const TCalendario &tcalendario) const {
    TNodoCalendario *actual = this->primero;
    while(actual) {
        if(actual->c == tcalendario) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

int TListaCalendario::Longitud() const {
    TNodoCalendario *actual = this->primero;
    int contador = 0;
    while(actual) {
        actual = actual->siguiente;
        contador++;
    }
    return contador;
}

TListaPos TListaCalendario::Primera() const {
    TListaPos posicion = TListaPos();
    posicion.pos = this->primero;
    return posicion;
}

TListaPos TListaCalendario::Ultima() const {
    TNodoCalendario *actual = this->primero;
    TListaPos posicion = TListaPos();
    while(actual) {
        posicion.pos = actual;
        actual = actual->siguiente;
    }
    return posicion;
}

TListaCalendario TListaCalendario::SumarSubl(int I_L1, int F_L1, const TListaCalendario &L2, int I_L2, int F_L2) const {
    TListaCalendario subL1, subL2 = TListaCalendario();
    TNodoCalendario *actual = this->primero;
    TNodoCalendario  *auxiliar = L2.primero;
    int contador = 1;
    while(actual) {
        if(contador >= I_L1 && contador <= F_L1) {
            subL1.Insertar(actual->c);
        }
        actual = actual->siguiente;
        contador++;
    }
    contador = 1;
    while(auxiliar) {
        if(contador >= I_L2 && contador <= F_L2) {
            subL2.Insertar(auxiliar->c);
        }
        auxiliar = auxiliar->siguiente;
        contador++;
    }
    TListaCalendario nuevo = TListaCalendario(subL1);
    TNodoCalendario *auxiliarL1;
    TNodoCalendario *auxiliarL2 = subL2.primero;
    bool insertar;
    while(auxiliarL2) {
        insertar = true;
        auxiliarL1 = subL1.primero;
        while(auxiliarL1) {
            if(auxiliarL2->c == auxiliarL1->c) {
                insertar = false;
            }
            auxiliarL1 = auxiliarL1->siguiente;
        }
        if(insertar) {
            nuevo.Insertar(auxiliarL2->c);
        }
        auxiliarL2 = auxiliarL2->siguiente;
    }
    return nuevo;
}

TListaCalendario TListaCalendario::ExtraerRango(int n1, int n2) {
    TListaCalendario nuevo = TListaCalendario();
    TNodoCalendario *actual = this->primero;
    TListaPos posicion = TListaPos();
    posicion.pos = actual;
    int contador = 1;
    bool insertado;
    while(actual) {
        insertado = false;
        if(contador >= n1 && contador <= n2) {
            nuevo.Insertar(actual->c);
            insertado = true;
        }
        actual = actual->siguiente;
        if(insertado) {
            this->Borrar(posicion);
        }
        posicion.pos = actual;
        contador++;
    }
    return nuevo;
}

/******************************************** FUNCIONES AMIGAS ********************************************/
ostream & operator<<(ostream &s, const TListaCalendario &tlistacalendario) {
    TNodoCalendario *actual = tlistacalendario.primero;
    s << "<";
    while(actual) {
        s << actual->c;
        actual = actual->siguiente;
        if(actual) {
            s << " ";
        }
    }
    s << ">";
    return s;
}