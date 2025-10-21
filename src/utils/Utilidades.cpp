#include "utils/Utilidades.h"
#include <iostream>
#include <limits>    
#include <iomanip>   
#include <sstream>   


void Utilidades::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Utilidades::pausarPantalla() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Utilidades::mostrarMensaje(std::string mensaje) {
    std::cout << "\n=================================\n";
    std::cout << "[SISTEMA] " << mensaje << "\n";
    std::cout << "=================================\n";
    pausarPantalla();
}

std::string Utilidades::leerString(std::string prompt) {
    std::string input = "";
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input); 
        
        if (!input.empty()) {
            break; 
        }
        std::cout << "Error: La entrada no puede estar vacia. Intente de nuevo.\n";
    }
    return input;
}

int Utilidades::leerInt(std::string prompt, int min, int max) {
    int input;
    while (true) {
        std::cout << prompt;
        
        if (!(std::cin >> input) || input < min || input > max) {
            std::cout << "Error: Debe ingresar un numero entero entre " 
                      << min << " y " << max << ".\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
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
        
        if (!(std::cin >> input) || input < 0) {
            std::cout << "Error: Debe ingresar un numero positivo (ej. 150.50).\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return input;
}



std::string Utilidades::formatearFecha(time_t fecha) {
    char bufferFecha[100];
    strftime(bufferFecha, sizeof(bufferFecha), "%Y-%m-%d %H:%M:%S", localtime(&fecha));
    return std::string(bufferFecha);
}

std::vector<std::string> Utilidades::splitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}