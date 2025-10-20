#include "modelos/Transaccion.h" 
#include <sstream>              
#include <iomanip>              

int Transaccion::contadorTransacciones = 10000; 

Transaccion::Transaccion(TipoTransaccion tipo, string origen, double monto, string destino) {
    
    this->tipo = tipo;
    this->cuentaOrigen = origen;
    this->monto = monto;
    this->cuentaDestino = destino;
    
    this->id = ++contadorTransacciones; 
    this->fecha = time(nullptr);        
    this->revertida = false;           
    
    stringstream ss;
    ss << fixed << setprecision(2) << "$" << monto;
    
    if (tipo == DEPOSITO) {
        ss << " depositado en la cuenta " << origen;
    } else if (tipo == RETIRO) {
        ss << " retirado de la cuenta " << origen;
    } else if (tipo == TRANSFERENCIA) {
        ss << " transferido de " << origen << " a " << destino;
    }
    this->descripcion = ss.str();
}

string Transaccion::getTipoStr() const {
    switch (this->tipo) {
        case DEPOSITO:      return "Deposito";
        case RETIRO:        return "Retiro";
        case TRANSFERENCIA: return "Transferencia";
        default:            return "Desconocido";
    }
}

string Transaccion::toString() const {
    stringstream ss;

    char bufferFecha[100];
    strftime(bufferFecha, sizeof(bufferFecha), "%Y-%m-%d %H:%M:%S", localtime(&this->fecha));

    ss << "--- Transaccion ID: " << this->id << " ---" << endl;
    ss << "  Tipo:     " << this->getTipoStr() << endl;
    ss << "  Fecha:    " << bufferFecha << endl;
    ss << "  Monto:    $" << fixed << setprecision(2) << this->monto << endl;
    ss << "  Desde:    " << this->cuentaOrigen << endl;
    
    if (this->tipo == TRANSFERENCIA) {
        ss << "  Hacia:    " << this->cuentaDestino << endl;
    }
    ss << "  Estado:   " << (this->revertida ? "REVERTIDA" : "Completada") << endl;
    ss << "---------------------------------";
    
    return ss.str();
}