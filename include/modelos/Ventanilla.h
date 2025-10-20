#pragma once

#include <string>
#include "modelos/Cliente.h" 
#include "modelos/Cuenta.h"   

class Ventanilla {
private:
    int id;
    bool libre;
    Cliente* clienteActual; 

public:
    
    Ventanilla(int id);
    
    bool isLibre() const;
    void atenderCliente(Cliente* cliente);
    Cliente* liberarCliente();
    bool realizarDeposito(Cuenta* cuenta, double monto);
    bool realizarRetiro(Cuenta* cuenta, double monto);
    bool realizarTransferencia(Cuenta* cuentaOrigen, Cuenta* cuentaDestino, double monto);
    int getID() const { return id; }
    Cliente* getClienteActual() const { return clienteActual; }
    std::string toString() const;
};