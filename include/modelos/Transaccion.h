#pragma once

#include <string>
#include <ctime>
#include "utils/Enums.h"
#include "Cuenta.h"

class Transaccion {
private:
    static int contadorTransacciones;
    int id;
    TipoTransaccion tipo;
    std::string cuentaOrigen;
    std::string cuentaDestino;
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
    std::string getCuentaOrigen() const { return cuentaOrigen; }
    std::string getCuentaDestino() const { return cuentaDestino; }
    double getMonto() const { return monto; }
    
    std::string getTipoStr() const;
    std::string toString() const;
};
