#include "modelos/Cuenta.h" 
#include "modelos/Transaccion.h"
#include <iostream>
#include <sstream> 
#include <iomanip>

int Cuenta::contadorCuentas = 100000;

Cuenta::Cuenta(std::string titular, double saldoInicial) 
    : titular(titular), saldo(saldoInicial), estado(ACTIVA) {
    this->numeroCuenta = generarNumeroCuenta();
    this->fechaCreacion = time(nullptr);
}

// --- NUEVO CONSTRUCTOR para cargar desde archivo ---
Cuenta::Cuenta(std::string titular, double saldoInicial, std::string numExistente, EstadoCuenta estadoExistente) {
    this->numeroCuenta = numExistente;
    this->titular = titular;
    this->saldo = saldoInicial;
    this->estado = estadoExistente;
    // NO actualizamos contadorCuentas aquí, lo hace actualizarContador()
}

std::string Cuenta::generarNumeroCuenta() {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(8) << ++contadorCuentas;
    return ss.str();
}

bool Cuenta::depositar(double monto) {
    if (monto <= 0) {
        std::cout << "Error: Monto debe ser positivo" << std::endl;
        return false;
    }
    if (!estaActiva()) {
        std::cout << "Error: Cuenta bloqueada o inactiva" << std::endl;
        return false;
    }
    saldo += monto;
    return true;
}

bool Cuenta::retirar(double monto) {
    if (monto <= 0) {
        std::cout << "Error: Monto debe ser positivo" << std::endl;
        return false;
    }
    if (!estaActiva()) {
        std::cout << "Error: Cuenta bloqueada o inactiva" << std::endl;
        return false;
    }
    if (monto > saldo) {
        std::cout << "Error: Saldo insuficiente" << std::endl;
        return false;
    }
    saldo -= monto;
    return true;
}

bool Cuenta::transferirA(Cuenta* destino, double monto) {
    if (destino == nullptr) return false;
    if (this->retirar(monto)) {
        return destino->depositar(monto);
    }
    return false;
}

std::string Cuenta::toString() const {
    std::stringstream ss;
     ss << "Cuenta: " << numeroCuenta << " | "
         << "Titular: " << titular << " | "
         << "Saldo: $" << std::fixed << std::setprecision(2) << saldo;
    return ss.str();
}

Cuenta& Cuenta::operator+=(double monto) {
    depositar(monto);
    return *this;
}

Cuenta& Cuenta::operator-=(double monto) {
    retirar(monto);
    return *this;
}

void Cuenta::actualizarContador(int numMasAlto) {
    if (numMasAlto > contadorCuentas) {
        contadorCuentas = numMasAlto;
    }
}