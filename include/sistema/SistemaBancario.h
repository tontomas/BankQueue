#pragma once

#include "sistema/Menu.h"       
#include "modelos/Cliente.h"    
#include "modelos/Cuenta.h"    
#include "modelos/Ventanilla.h" 
#include "modelos/Transaccion.h"
#include "utils/Enums.h"        

#include <list>
#include <vector>
#include <queue>    
#include <stack>    
#include <deque>    
#include <string>

struct ComparadorClientePtr {
    bool operator()(const Cliente* a, const Cliente* b) const {
        if (a->getPrioridad() != b->getPrioridad()) {
            return a->getPrioridad() > b->getPrioridad();
        }
        return a->getHoraLlegada() > b->getHoraLlegada();
    }
};

class SistemaBancario {
private:
    Menu menu; 

    std::list<Cliente> listaMaestraClientes;
    std::list<Cuenta> listaMaestraCuentas;
    std::list<Ventanilla> todasLasVentanillas;
    
    std::deque<Transaccion> historialTransacciones; 
    std::stack<Transaccion> pilaDeshacer;           
    const int MAX_HISTORIAL = 50;

    std::priority_queue<Cliente*, 
                        std::vector<Cliente*>, 
                        ComparadorClientePtr> filaDeEspera;
    
    std::queue<Ventanilla*> ventanillasLibres;

    void gestionarNuevoCliente();
    void procesarFila();
    void gestionarAtencion(Ventanilla* ventanilla);
    void liberarVentanilla(Ventanilla* ventanilla);
    void verEstadoFila() const;
    void verEstadoVentanillas() const;

    void registrarTransaccion(const Transaccion& trans);
    void gestionarDeshacer();
    void verHistorial() const;

    Cuenta* buscarCuentaDeCliente(Cliente* cliente);
    Cuenta* buscarCuentaPorNumero(std::string numCuenta);
    Cliente* buscarClientePorID(int id);

    void cargarDatos();
    void guardarDatos() const;

public:
    SistemaBancario(int numVentanillas);
    
    void iniciar(); 
    void cargarDatosPrueba(); 
};