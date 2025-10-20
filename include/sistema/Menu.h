#pragma once
#include <string>

/**
 * @brief Maneja la interfaz de usuario de la consola.
 * (Versión actualizada para el sistema híbrido)
 */
class Menu {
public:
    Menu();

    /**
     * @brief Muestra el menú principal del banco.
     * @return El entero (0-7) de la opción seleccionada.
     */
    int mostrarMenuPrincipal();

    /**
     * @brief Muestra el sub-menú de operaciones en ventanilla.
     * @param nombreCliente El nombre del cliente siendo atendido.
     * @return El entero (0-3) de la opción seleccionada.
     */
    int mostrarMenuVentanilla(std::string nombreCliente);
};