#ifndef TRANSACCION_H
#define TRANSACCION_H

#include <string>
#include <ctime>
#include "Enums.h"
#include "Cuenta.h"

using namespace std;

class Transaccion {
private:
    static int contadorTransacciones;
    int id;
    TipoTransaccion tipo;
    string cuentaOrigen;
    string cuentaDestino;
    double monto;
    time_t fecha;
    string descripcion;
    bool revertida;
    
public:
    Transaccion(TipoTransaccion tipo, string origen, double monto, string destino = "");
    
    void marcarRevertida() { revertida = true; }
    bool estaRevertida() const { return revertida; }
    
    // Getters
    int getID() const { return id; }
    TipoTransaccion getTipo() const { return tipo; }
    string getCuentaOrigen() const { return cuentaOrigen; }
    string getCuentaDestino() const { return cuentaDestino; }
    double getMonto() const { return monto; }
    
    string getTipoStr() const;
    string toString() const;
};

#endif