#include "modelos/Cuenta.h" 
#include <sstream> 
#include <iomanip>

Cuenta::Cuenta(Cliente* titular, double saldoInicial){

    this->titular = titular; 
    this->saldo = saldoInicial;
    this->activa = true;
    this->fechaCreacion = std::time(nullptr);
    
    static long long contadorID = 1000000001; 
    this->numeroCuenta = "CTA-" + std::to_string(contadorID);
    contadorID++;

}

bool Cuenta::depositar(double monto) {
    if (monto < 0) {
        return false; 
    }

    if (!this->activa) {
        return false; 
    }

    this->saldo += monto;
    return true;
}

bool Cuenta::tranferir(Cuenta* destino, double monto) {
    if (monto < 0) {
        return false; 
    }

    if (!this->activa || !destino->activa) {
        return false; 
    }

    if (this->saldo >= monto) {
        this->saldo -= monto;
        destino->depositar(monto);
        return true;
    }

    return false;
}

double Cuenta::getSaldo() const {
    return this->saldo;
}

Cliente* Cuenta::getTitular() {
    return this->titular;
}

std::string Cuenta::toString() const {
    std::stringstream ss; 
    
    ss << "Cuenta Nro: " << this->numeroCuenta << "\n";
    ss << "Titular:    " << this->titular->getNombreCompleto() << "\n"; 
    ss << "Saldo:      $" << std::fixed << std::setprecision(2) << this->saldo << "\n";
    ss << "Estado:     " << (this->activa ? "Activa" : "Desactivada") << "\n";

    return ss.str();
}