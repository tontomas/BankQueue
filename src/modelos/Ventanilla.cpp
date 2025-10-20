#include "modelos/Ventanilla.h"
#include <sstream> 

Ventanilla::Ventanilla(int id) {
    this->id = id;
    this->libre = true;
    this->clienteActual = nullptr;
}
bool Ventanilla::isLibre() const {
    return this->libre;
}

void Ventanilla::atenderCliente(Cliente* cliente) {
    this->clienteActual = cliente;
    this->libre = false;
}

Cliente* Ventanilla::liberarCliente() {
    Cliente* clienteAtendido = this->clienteActual;
    this->clienteActual = nullptr;                 
    this->libre = true;                            
    return clienteAtendido;
}

bool Ventanilla::realizarDeposito(Cuenta* cuenta, double monto) {
    if (isLibre() || clienteActual == nullptr || cuenta == nullptr) {
        return false; 
    }
    return cuenta->depositar(monto);
}

bool Ventanilla::realizarRetiro(Cuenta* cuenta, double monto) {
    if (isLibre() || clienteActual == nullptr || cuenta == nullptr) {
        return false; 
    }
    return cuenta->retirar(monto);
}

bool Ventanilla::realizarTransferencia(Cuenta* cuentaOrigen, Cuenta* cuentaDestino, double monto) {
    if (isLibre() || clienteActual == nullptr || cuentaOrigen == nullptr || cuentaDestino == nullptr) {
        return false;
    }
    return cuentaOrigen->transferirA(cuentaDestino, monto);
}

std::string Ventanilla::toString() const {
    std::stringstream ss;
    ss << "Ventanilla Nro: " << this->id << " | Estado: ";
    
    if (this->libre) {
        ss << "Libre";
    } else if (this->clienteActual != nullptr) {
        ss << "Atendiendo a: " << this->clienteActual->getNombreCompleto();
    } else {
        ss << "Ocupada (estado desconocido)";
    }
    
    return ss.str();
}