#include "sistema/Menu.h"
#include "utils/Utilidades.h" 
#include <iostream>

Menu::Menu() {}

int Menu::mostrarMenuPrincipal() {
    Utilidades::limpiarPantalla();
    std::cout << "=================================\n";
    std::cout << "      SISTEMA BANCARIO 2.0 (Hibrido)       \n";
    std::cout << "=================================\n";
    std::cout << "--- Lobby ---\n";
    std::cout << "1. Agregar nuevo cliente a la fila\n";
    std::cout << "2. Procesar fila (llamar cliente)\n";
    std::cout << "3. Ver estado de la fila de espera\n";
    std::cout << "4. Ver estado de las ventanillas\n";
    std::cout << "\n--- Boveda ---\n";
    std::cout << "5. Ver historial de transacciones\n";
    std::cout << "6. Deshacer ultima transaccion\n";
    std::cout << "7. Cargar datos de prueba\n";
    std::cout << "\n0. Salir del sistema\n";
    std::cout << "=================================\n";
    
    return Utilidades::leerInt("Ingrese su opcion: ", 0, 7);
}

int Menu::mostrarMenuVentanilla(std::string nombreCliente) {
    Utilidades::limpiarPantalla();
    std::cout << "=================================\n";
    std::cout << "     ATENCION EN VENTANILLA    \n";
    std::cout << "=================================\n";
    std::cout << "Atendiendo a: " << nombreCliente << "\n\n";
    std::cout << "1. Realizar Deposito\n";
    std::cout << "2. Realizar Retiro\n";
    std::cout << "3. Realizar Transferencia\n";
    std::cout << "\n0. Terminar atencion\n";
    std::cout << "=================================\n";
    
    return Utilidades::leerInt("Ingrese su opcion: ", 0, 3);
}