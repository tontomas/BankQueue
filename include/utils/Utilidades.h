#pragma once

#include <string>
#include <ctime>
#include <vector>

class Utilidades {
private:
    Utilidades() {}

public:
    static void limpiarPantalla();
    static void pausarPantalla();
    static void mostrarMensaje(std::string mensaje);

    static std::string leerString(std::string prompt);

    static int leerInt(std::string prompt, int min, int max);

    static double leerDouble(std::string prompt);

    static std::string formatearFecha(time_t fecha);

    static std::vector<std::string> splitString(const std::string& s, char delimiter);

};