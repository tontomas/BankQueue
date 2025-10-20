#pragma once 

#include <string> 
#include <ctime> 
#include "Cliente.h"

class Cuenta{

private:
    std::string numeroCuenta;
    Cliente* titular;
    double saldo;
    bool activa;
    time_t fechaCreacion;

public:
    Cuenta(Cliente* titular, double saldoInicial);
    bool depositar(double monto);
    bool tranferir(Cuenta* destino, double monto);
    double getSaldo() const;
    Cliente* getTitular();
    std::string toString() const;

};