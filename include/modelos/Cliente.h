#pragma once 

#include <string> 
#include <ctime>  
#include "utils/Enums.h" 

class Cliente {
private: 
    static int contadorClientes;
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
    Cliente(std::string nombre, std::string apellido, int edad, StatusCliente prioridadManual, time_t llegada, int idExistente);

    int getID() const;
    int getPrioridad() const; 
    std::string getNombreCompleto() const;
    std::string getNombre() const;
    std::string getApellido() const;
    int getEdad() const;
    time_t getHoraLlegada() const;
    static void actualizarContador(int idMasAlto);
    std::string getTipoPrioridadStr() const;
    std::string toString() const;

};