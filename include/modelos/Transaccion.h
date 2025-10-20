#pragma once 

#include <string> 
#include <ctime> 
#include "Enums.h"
#include "Cuenta.h"

class Transaccion {
private:
    static int contadorTransacciones;
    int id;
    TipoTransaccion tipo;
    Cuenta* cuentaOrigen;
    Cuenta* cuentaDestino;
    double monto;
    time_t fecha;
    std::string descripcion;
    bool revertida;
    
public:
    Transaccion(TipoTransaccion tipo, std::string origen, double monto, std::string destino = "");
    
    void marcarRevertida() { revertida = true; }
    bool estaRevertida() const { return revertida; }
    
    // Getters
    int getID() const { return id; }
    TipoTransaccion getTipo() const { return tipo; }
    Cuenta* getCuentaOrigen() const { return cuentaOrigen; }
    Cuenta* getCuentaDestino() const { return cuentaDestino; }
    double getMonto() const { return monto; }
    
    std::string getTipoStr() const;
    std::string toString() const;
};
