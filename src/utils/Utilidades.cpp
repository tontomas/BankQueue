#include "utils/Utilidades.h"
#include <iostream>
#include <limits>    // Para std::numeric_limits
#include <iomanip>   // Para std::setw, std::setfill
#include <sstream>   // Para std::stringstream

// --- Métodos de Consola ---

void Utilidades::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Utilidades::pausarPantalla() {
    std::cout << "\nPresione Enter para continuar...";
    // Limpia el buffer por si había algo antes
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Espera a que el usuario presione Enter
    std::cin.get();
}

void Utilidades::mostrarMensaje(std::string mensaje) {
    std::cout << "\n=================================\n";
    std::cout << "[SISTEMA] " << mensaje << "\n";
    std::cout << "=================================\n";
    pausarPantalla();
}


// --- Métodos de Lectura Segura (Validación) ---

std::string Utilidades::leerString(std::string prompt) {
    std::string input = "";
    while (true) {
        std::cout << prompt;
        // getline lee la línea completa, incluyendo espacios
        std::getline(std::cin, input); 
        
        if (!input.empty()) {
            break; // Éxito, rompe el bucle
        }
        std::cout << "Error: La entrada no puede estar vacia. Intente de nuevo.\n";
    }
    return input;
}

int Utilidades::leerInt(std::string prompt, int min, int max) {
    int input;
    while (true) {
        std::cout << prompt;
        
        // Si la entrada NO es un número (ej. "hola") O está fuera de rango
        if (!(std::cin >> input) || input < min || input > max) {
            std::cout << "Error: Debe ingresar un numero entero entre " 
                      << min << " y " << max << ".\n";
            std::cin.clear(); // Limpia el flag de error de cin
            // Descarta la línea incorrecta del buffer (ej. "hola\n")
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            // Éxito, es un número Y está en rango
            // Limpia el "Enter" que quedó en el buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return input;
}

double Utilidades::leerDouble(std::string prompt) {
    double input;
    while (true) {
        std::cout << prompt;
        
        // Si NO es un número O es negativo
        if (!(std::cin >> input) || input < 0) {
            std::cout << "Error: Debe ingresar un numero positivo (ej. 150.50).\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            // Éxito
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return input;
}


// --- Métodos de Formato ---

std::string Utilidades::formatearFecha(time_t fecha) {
    char bufferFecha[100];
    // Formato: "Año-Mes-Día Hora:Minuto:Segundo"
    strftime(bufferFecha, sizeof(bufferFecha), "%Y-%m-%d %H:%M:%S", localtime(&fecha));
    return std::string(bufferFecha);
}