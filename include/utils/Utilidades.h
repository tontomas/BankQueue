#pragma once

#include <string>
#include <ctime>
#include <vector>

/**
 * @brief Clase de utilidad estática.
 * Contiene funciones de ayuda para limpiar la pantalla, pausar
 * y leer entradas de usuario de forma segura.
 */
class Utilidades {
private:
    /**
     * @brief El constructor es privado para prevenir
     * que se creen instancias de esta clase (ej. Utilidades miUtil;).
     * Solo se deben usar sus métodos estáticos.
     */
    Utilidades() {}

public:
    // --- Métodos de Consola ---
    static void limpiarPantalla();
    static void pausarPantalla();
    static void mostrarMensaje(std::string mensaje);

    // --- Métodos de Lectura Segura (Validación) ---

    /**
     * @brief Pide un string al usuario, asegurando que no esté vacío.
     * @param prompt El mensaje que se le muestra al usuario.
     * @return El string ingresado por el usuario.
     */
    static std::string leerString(std::string prompt);

    /**
     * @brief Pide un número entero al usuario, validando que sea un número
     * y que esté dentro de un rango [min, max].
     * @param prompt El mensaje que se le muestra al usuario.
     * @param min El valor mínimo aceptado (inclusivo).
     * @param max El valor máximo aceptado (inclusivo).
     * @return El entero validado.
     */
    static int leerInt(std::string prompt, int min, int max);

    /**
     * @brief Pide un número decimal al usuario, validando que sea
     * un número positivo (mayor o igual a 0).
     * @param prompt El mensaje que se le muestra al usuario.
     * @return El double validado.
     */
    static double leerDouble(std::string prompt);

    // --- Métodos de Formato ---

    /**
     * @brief Convierte un objeto time_t a un string legible.
     * @param fecha El objeto time_t a formatear.
     * @return Un string (ej. "2025-10-20 09:30:00")
     */
    static std::string formatearFecha(time_t fecha);

    static std::vector<std::string> splitString(const std::string& s, char delimiter);

};