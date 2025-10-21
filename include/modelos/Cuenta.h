#pragma once 

#include <string> 
#include <vector>
#include <ctime> 
#include "utils/Enums.h"

class Transaccion;

class Cuenta {
private:
    static int contadorCuentas;
    std::string numeroCuenta;
    std::string titular;
    double saldo;
    EstadoCuenta estado;
    time_t fechaCreacion;
    std::vector<Transaccion> historialTransacciones;
    std::string generarNumeroCuenta();
    
public:
    Cuenta(std::string titular, double saldoInicial = 0.0);
    Cuenta(std::string titular, double saldoInicial, std::string numExistente, EstadoCuenta estadoExistente);    

    bool depositar(double monto);
    bool retirar(double monto);
    bool transferirA(Cuenta* destino, double monto);
    
    std::string getNumero() const { return numeroCuenta; }
    std::string getTitular() const { return titular; }
    double getSaldo() const { return saldo; }
    EstadoCuenta getEstado() const { return estado; }
    bool estaActiva() const { return estado == ACTIVA; }
    static void actualizarContador(int numMasAlto);
    void bloquear() { estado = BLOQUEADA; }
    void activar() { estado = ACTIVA; }
    
    std::string toString() const;
    
    Cuenta& operator+=(double monto); // Depósito
    Cuenta& operator-=(double monto); // Retiro
};