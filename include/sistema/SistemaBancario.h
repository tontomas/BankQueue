#pragma once

#include "sistema/Menu.h"       // La interfaz
#include "modelos/Cliente.h"    // El modelo Cliente
#include "modelos/Cuenta.h"     // El modelo Cuenta
#include "modelos/Ventanilla.h" // El modelo Ventanilla
#include "modelos/Transaccion.h"// El modelo Transaccion
#include "Enums.h"              // Tus enums (StatusCliente, etc.)

#include <list>
#include <vector>
#include <queue>    // Para std::queue (ventanillas) y std::priority_queue (fila)
#include <stack>    // Para la pila de deshacer
#include <deque>    // Para el historial de transacciones
#include <string>

/**
 * @brief Struct comparador para la Cola de Prioridad.
 * Le enseña a la cola cómo ordenar dos punteros a Cliente.
 * Ordena para que el getPrioridad() MÁS ALTO salga PRIMERO.
 */
struct ComparadorClientePtr {
    bool operator()(const Cliente* a, const Cliente* b) const {
        // (Basado en tu Cliente.cpp, asumimos que un número mayor
        // tiene más prioridad, ej. ADULTO_MAYOR > REGULAR)
        if (a->getPrioridad() != b->getPrioridad()) {
            return a->getPrioridad() < b->getPrioridad(); // El de mayor prioridad sale primero
        }
        // Si la prioridad es igual, el que llegó primero sale primero
        return a->getHoraLlegada() > b->getHoraLlegada();
    }
};


/**
 * @brief El "Cerebro" del banco.
 * Gestiona tanto el flujo físico de clientes (lobby) como
 * la lógica de datos y transacciones (bóveda).
 */
class SistemaBancario {
private:
    Menu menu; // La interfaz

    // --- Listas Maestras (Almacenamiento Seguro) ---
    std::list<Cliente> listaMaestraClientes;
    std::list<Cuenta> listaMaestraCuentas;
    std::list<Ventanilla> todasLasVentanillas;
    
    // --- Lógica de Bóveda (Gestión de Datos) ---
    std::deque<Transaccion> historialTransacciones; // Guardamos objetos
    std::stack<Transaccion> pilaDeshacer;           // Guardamos objetos
    const int MAX_HISTORIAL = 50;

    // --- Lógica de Lobby (Flujo Físico) ---
    std::priority_queue<Cliente*, 
                        std::vector<Cliente*>, 
                        ComparadorClientePtr> filaDeEspera;
    
    std::queue<Ventanilla*> ventanillasLibres;

    // --- Métodos de Lógica Privados ---
    
    // Métodos del Lobby
    void gestionarNuevoCliente();
    void procesarFila();
    void gestionarAtencion(Ventanilla* ventanilla);
    void liberarVentanilla(Ventanilla* ventanilla);
    void verEstadoFila() const;
    void verEstadoVentanillas() const;

    // Métodos de la Bóveda
    void registrarTransaccion(const Transaccion& trans);
    void gestionarDeshacer();
    void verHistorial() const;

    // Métodos de Búsqueda (Ayudantes)
    Cuenta* buscarCuentaDeCliente(Cliente* cliente);
    Cuenta* buscarCuentaPorNumero(std::string numCuenta);
    Cliente* buscarClientePorID(int id);


public:
    SistemaBancario(int numVentanillas);
    // (No necesitamos un destructor ~SistemaBancario() porque
    // no usamos 'new' para las listas maestras)
    
    void iniciar(); // Inicia el bucle principal
    void cargarDatosPrueba(); // Para facilitar las pruebas
};