#pragma once 

#include <string> 
#include <ctime>  
#include "Enums.h" 

class Cliente {
private: 
    int id;
    std::string nombre; 
    std::string apellido;
    int edad;
    StatusCliente Prioridad;
    time_t horaLlegada;

public:
    Cliente(std::string nombre, std::string apellido, int edad);

    int getPrioridad() const;
    std::string getNombreCompleto() const;
    std::string toString() const;
};