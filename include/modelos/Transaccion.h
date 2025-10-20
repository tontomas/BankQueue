<<<<<<< HEAD
#pragma once 

#include <string> 
#include <ctime> 
#include "Enums.h"
#include "Cuenta.h"

=======
#ifndef TRANSACCION_H
#define TRANSACCION_H

#include <string>
#include <ctime>
#include "Enums.h"
#include "Cuenta.h"

using namespace std;

>>>>>>> 5f5fe79a842b18c928377f31358a6ea9b5fd30a6
class Transaccion {
private:
    static int contadorTransacciones;
    int id;
    TipoTransaccion tipo;
<<<<<<< HEAD
    Cuenta* cuentaOrigen;
    Cuenta* cuentaDestino;
    double monto;
    time_t fecha;
    std::string descripcion;
    bool revertida;
    
public:
    Transaccion(TipoTransaccion tipo, std::string origen, double monto, std::string destino = "");
=======
    string cuentaOrigen;
    string cuentaDestino;
    double monto;
    time_t fecha;
    string descripcion;
    bool revertida;
    
public:
    Transaccion(TipoTransaccion tipo, string origen, double monto, string destino = "");
>>>>>>> 5f5fe79a842b18c928377f31358a6ea9b5fd30a6
    
    void marcarRevertida() { revertida = true; }
    bool estaRevertida() const { return revertida; }
    
    // Getters
    int getID() const { return id; }
    TipoTransaccion getTipo() const { return tipo; }
<<<<<<< HEAD
    Cuenta* getCuentaOrigen() const { return cuentaOrigen; }
    Cuenta* getCuentaDestino() const { return cuentaDestino; }
    double getMonto() const { return monto; }
    
    std::string getTipoStr() const;
    std::string toString() const;
};
=======
    string getCuentaOrigen() const { return cuentaOrigen; }
    string getCuentaDestino() const { return cuentaDestino; }
    double getMonto() const { return monto; }
    
    string getTipoStr() const;
    string toString() const;
};

#endif
>>>>>>> 5f5fe79a842b18c928377f31358a6ea9b5fd30a6
