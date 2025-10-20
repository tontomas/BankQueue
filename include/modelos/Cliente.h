#pragma once 

#include <string> 
#include <ctime>  
#include "Enums.h" 

class Cliente {
private: 
    int id;
    static int contadorID;
    std::string nombre; 
    std::string apellido;
    int edad;
    StatusCliente prioridad;
    StatusCliente calcularPrioridad();
    time_t horaLlegada;

public:
    Cliente(std::string nombre, std::string apellido, int edad);
    Cliente(std::string nombre, std::string apellido, int edad, StatusCliente prioridadManual);

    int getID() const { return id; };
    int getPrioridad() const { return static_cast<int>(prioridad); };
    std::string getNombreCompleto() const { return nombre + " " + apellido; };
    std::string getNombre() const { return nombre; };
    std::string getApellido() const { return apellido; };
    int getEdad() const { return edad; };
    time_t getHoraLlegada() const { return horaLlegada; };
    
    std::string getTipoPrioridadStr() const;
    std::string toString() const;

};