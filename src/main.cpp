#include "sistema/SistemaBancario.h" 
#include "utils/Enums.h"             
#include <iostream>

int main() {
    const int NUMERO_DE_VENTANILLAS = 3;

    std::cout << "Iniciando Sistema Bancario con " 
              << NUMERO_DE_VENTANILLAS << " ventanillas..." 
              << std::endl;
    
    SistemaBancario banco(NUMERO_DE_VENTANILLAS);
    
    std::cout << "Sistema cargado. ¡Bienvenido!" << std::endl;
    banco.iniciar();
    std::cout << "Cerrando el sistema..." << std::endl;
    
    return 0;
}