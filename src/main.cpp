#include "sistema/SistemaBancario.h" // El "Cerebro"
#include "utils/Enums.h"             // Los Enums necesarios
#include <iostream>

/**
 * @brief Punto de entrada principal del programa.
 *
 * Su única responsabilidad es:
 * 1. Crear el objeto SistemaBancario (el "Cerebro").
 * 2. Llamar a su método iniciar() para comenzar el bucle principal.
 */
int main() {
    // ---- Configuración Inicial ----
    const int NUMERO_DE_VENTANILLAS = 3;

    std::cout << "Iniciando Sistema Bancario con " 
              << NUMERO_DE_VENTANILLAS << " ventanillas..." 
              << std::endl;
    
    // 1. Crear el Cerebro
    SistemaBancario banco(NUMERO_DE_VENTANILLAS);
    
    std::cout << "Sistema cargado. ¡Bienvenido!" << std::endl;
    
    // (Opcional) Carga clientes de prueba para no empezar en blanco
    // banco.cargarDatosPrueba(); 
    
    // 2. Iniciar el bucle principal del programa
    banco.iniciar();

    // 3. El programa termina cuando banco.iniciar() finaliza
    std::cout << "Cerrando el sistema..." << std::endl;
    
    return 0;
}