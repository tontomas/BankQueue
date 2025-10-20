#include "modelos/Cliente.h" 
#include <sstream> 

Cliente::Cliente(std::string nombre, std::string apellido, int edad) {
    this->nombre = nombre;
    this->apellido = apellido;
    this->edad = edad;
    this->id = 0; 
    this->Prioridad = NORMAL; 
    this->horaLlegada = std::time(nullptr); 
}

int Cliente::getPrioridad() const {
    return static_cast<int>(this->Prioridad); 
}

std::string Cliente::getNombreCompleto() const {
    return this->nombre + " " + this->apellido;
}

std::string Cliente::toString() const {
    std::stringstream ss;
    ss << "ID: " << this->id << ", Nombre: " << getNombreCompleto();
    return ss.str();
}