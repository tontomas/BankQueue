#include "modelos/Transaccion.h"
#include <sstream>
#include <iomanip>

int Transaccion::contadorTransacciones = 10000;

Transaccion::Transaccion(TipoTransaccion tipo, std::string origen, double monto, std::string destino) {
    
    this->tipo = tipo;
    this->cuentaOrigen = origen;
    this->monto = monto;
    this->cuentaDestino = destino;
    
    this->id = ++contadorTransacciones; 
    this->fecha = time(nullptr);        
    this->revertida = false;           
    
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << "$" << monto;
    
    if (tipo == DEPOSITO) {
        ss << " depositado en la cuenta " << origen;
    } else if (tipo == RETIRO) {
        ss << " retirado de la cuenta " << origen;
    } else if (tipo == TRANSFERENCIA) {
        ss << " transferido de " << origen << " a " << destino;
    }
    this->descripcion = ss.str();
}

std::string Transaccion::getTipoStr() const {
    switch (this->tipo) {
        case DEPOSITO:      return "Deposito";
        case RETIRO:        return "Retiro";
        case TRANSFERENCIA: return "Transferencia";
        default:            return "Desconocido";
    }
}

std::string Transaccion::toString() const {
    std::stringstream ss;

    char bufferFecha[100];
    strftime(bufferFecha, sizeof(bufferFecha), "%Y-%m-%d %H:%M:%S", localtime(&this->fecha));

    ss << "--- Transaccion ID: " << this->id << " ---" << std::endl;
    ss << "  Tipo:     " << this->getTipoStr() << std::endl;
    ss << "  Fecha:    " << bufferFecha << std::endl;
    ss << "  Monto:    $" << std::fixed << std::setprecision(2) << this->monto << std::endl;
    ss << "  Desde:    " << this->cuentaOrigen << std::endl;
    
    if (this->tipo == TRANSFERENCIA) {
        ss << "  Hacia:    " << this->cuentaDestino << std::endl;
    }
    ss << "  Estado:   " << (this->revertida ? "REVERTIDA" : "Completada") << std::endl;
    ss << "---------------------------------";
    
    return ss.str();
}