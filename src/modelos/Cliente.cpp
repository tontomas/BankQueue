#include "modelos/Cliente.h"
#include <sstream>
#include <iomanip>

int Cliente::contadorID = 1000;

Cliente::Cliente(std::string nombre, std::string apellido, int edad) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->edad = edad;
    this->id = ++contadorID;
    this->prioridad = calcularPrioridad();
    this->horaLlegada = std::time(nullptr);
}

Cliente::Cliente(std::string nombre, std::string apellido, int edad, StatusCliente prioridadManual) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->edad = edad;
    this->id = ++contadorID;
    this->prioridad = prioridadManual;
    this->horaLlegada = std::time(nullptr);
}

int Cliente::getID() const {
    return this->id;
}

std::string Cliente::getNombreCompleto() const {
    return this->nombre + " " + this->apellido;
}

std::string Cliente::getNombre() const {
    return this->nombre;
}

std::string Cliente::getApellido() const {
    return this->apellido;
}

int Cliente::getEdad() const {
    return this->edad;
}

StatusCliente Cliente::calcularPrioridad() {
    if (edad >= 65) {
        return ADULTO_MAYOR;
    }
    return REGULAR;
}

int Cliente::getPrioridad() const {
    // Tuvimos que mover esta lógica del .h al .cpp
    return static_cast<int>(this->prioridad);
}

time_t Cliente::getHoraLlegada() const {
    // Tuvimos que mover esta lógica del .h al .cpp
    return this->horaLlegada;
}

std::string Cliente::getTipoPrioridadStr() const {
    switch(prioridad) {
        case VIP: return "VIP";
        case ADULTO_MAYOR: return "Adulto Mayor";
        case PREFERENCIAL: return "Preferencial";
        case REGULAR: return "Regular";
        default: return "Desconocido";
    }
}

std::string Cliente::toString() const {
    std::stringstream ss;
    ss << "ID: " << this->id << " | ";
    ss << this->getNombreCompleto() << " (" << edad << " años) | ";
    ss << "Prioridad: " << getTipoPrioridadStr();
    return ss.str();
}