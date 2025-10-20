#pragma once 

#include <string> 
#include <ctime> 
#include "Cliente.h"

class Cuenta {
private:
    static int contadorCuentas;
    std::string numeroCuenta;
    std::string titular;
    double saldo;
    EstadoCuenta estado;
    time_t fechaCreacion;
    
    std::string generarNumeroCuenta();
    
public:
    Cuenta(std::string titular, double saldoInicial = 0.0);
    
    bool depositar(double monto);
    bool retirar(double monto);
    bool transferirA(Cuenta* destino, double monto);
    
    std::string getNumero() const { return numeroCuenta; }
    std::string getTitular() const { return titular; }
    double getSaldo() const { return saldo; }
    bool estaActiva() const { return estado == ACTIVA; }
    
    void bloquear() { estado = BLOQUEADA; }
    void activar() { estado = ACTIVA; }
    
    std::string toString() const;
    
    Cuenta& operator+=(double monto); // Depósito
    Cuenta& operator-=(double monto); // Retiro
};