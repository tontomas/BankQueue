#include "sistema/SistemaBancario.h"
#include "utils/Utilidades.h" // Usa las herramientas
#include <iostream>
#include <string>

/**
 * @brief Constructor
 * Crea las ventanillas y las añade a la cola de ventanillas libres.
 */
SistemaBancario::SistemaBancario(int numVentanillas) {
    for (int i = 0; i < numVentanillas; ++i) {
        // 1. Crea la ventanilla (ID 1, 2, 3...) y la guarda en la lista maestra
        this->todasLasVentanillas.emplace_back(i + 1);
    }
    
    // 2. Llena la cola de "libres" con punteros a esas ventanillas
    for (auto& ventanilla : this->todasLasVentanillas) {
        this->ventanillasLibres.push(&ventanilla);
    }
}

/**
 * @brief Inicia el bucle principal del programa.
 */
void SistemaBancario::iniciar() {
    bool corriendo = true;
    while (corriendo) {
        // Llama al Menú actualizado
        int opcion = menu.mostrarMenuPrincipal();
        
        switch (opcion) {
            case 1: gestionarNuevoCliente(); break;
            case 2: procesarFila(); break;
            case 3: verEstadoFila(); break;
            case 4: verEstadoVentanillas(); break;
            case 5: verHistorial(); break;
            case 6: gestionarDeshacer(); break;
            case 7: cargarDatosPrueba(); break;
            case 0: corriendo = false; break;
        }
    }
    Utilidades::mostrarMensaje("Gracias por usar el Sistema Bancario. Adios.");
}

// --- Métodos de Lógica Privados ---

void SistemaBancario::gestionarNuevoCliente() {
    Utilidades::limpiarPantalla();
    std::cout << "--- Creacion de Nuevo Cliente ---\n";
    
    std::string nombre = Utilidades::leerString("Ingrese nombre: ");
    std::string apellido = Utilidades::leerString("Ingrese apellido: ");
    int edad = Utilidades::leerInt("Ingrese edad: ", 18, 99);
    
    // Usa el constructor de sobrecarga de Cliente.h
    int pManual = Utilidades::leerInt(
        "Asignar prioridad especial? (0=Automatico, 1=VIP, 2=PREFERENCIAL): ", 0, 2
    );

    // 1. Crear y guardar al cliente en la lista maestra
    if (pManual == 0) {
        listaMaestraClientes.emplace_back(nombre, apellido, edad);
    } else {
        if (pManual == 1) listaMaestraClientes.emplace_back(nombre, apellido, edad, VIP);
        else listaMaestraClientes.emplace_back(nombre, apellido, int(edad), PREFERENCIAL);
    }
    
    // 2. Obtener un puntero al cliente que acabamos de crear
    Cliente* nuevoCliente = &listaMaestraClientes.back();

    // 3. Crear y guardar su cuenta principal
    double saldoInicial = Utilidades::leerDouble("Ingrese saldo inicial: $");
    
    // Usa el constructor de Cuenta.h
    listaMaestraCuentas.emplace_back(nuevoCliente->getNombreCompleto(), saldoInicial);
    
    // 4. Obtener puntero a la cuenta (para info)
    Cuenta* nuevaCuenta = &listaMaestraCuentas.back();

    // 5. Añadir al cliente a la fila de espera
    filaDeEspera.push(nuevoCliente);
    
    Utilidades::mostrarMensaje("Cliente " + nuevoCliente->getNombreCompleto() + 
                               " agregado a la fila.\nCuenta creada: " + nuevaCuenta->getNumero());
}

void SistemaBancario::procesarFila() {
    if (filaDeEspera.empty()) {
        Utilidades::mostrarMensaje("La fila de espera esta vacia.");
        return;
    }
    
    if (ventanillasLibres.empty()) {
        Utilidades::mostrarMensaje("No hay ventanillas libres en este momento.");
        return;
    }

    // 1. Saca al cliente con MÁS prioridad
    Cliente* cliente = filaDeEspera.top();
    filaDeEspera.pop();

    // 2. Saca a la siguiente ventanilla libre
    Ventanilla* ventanilla = ventanillasLibres.front();
    ventanillasLibres.pop();

    // 3. Conéctalos (Ventanilla.cpp por ahora no existe, usamos la tuya)
    // Asumiré que existe un Ventanilla.cpp que implementa esto:
    ventanilla->atenderCliente(cliente);

    Utilidades::mostrarMensaje("Cliente " + cliente->getNombreCompleto() + 
                               " pasa a la Ventanilla " + 
                               std::to_string(ventanilla->getID()) + ".");
    
    // 4. Inicia el sub-menú de atención
    gestionarAtencion(ventanilla);
}

void SistemaBancario::gestionarAtencion(Ventanilla* ventanilla) {
    Cliente* cliente = ventanilla->getClienteActual();
    
    // Busca la cuenta principal del cliente
    Cuenta* cuenta = buscarCuentaDeCliente(cliente);
    
    if (cuenta == nullptr) {
        Utilidades::mostrarMensaje("ERROR FATAL: El cliente no tiene cuenta asociada.");
        liberarVentanilla(ventanilla);
        return;
    }

    bool enAtencion = true;
    while (enAtencion) {
        int opcion = menu.mostrarMenuVentanilla(cliente->getNombreCompleto());
        
        switch (opcion) {
            case 1: { // <-- LLAVE DE INICIO (Habitación 1)
                double monto = Utilidades::leerDouble("Monto a depositar: $");
                if (cuenta->depositar(monto)) {
                    // Esta 't' solo existe dentro de estas llaves
                    Transaccion t((TipoTransaccion)DEPOSITO, cuenta->getNumero(), monto);
                    registrarTransaccion(t);
                    Utilidades::mostrarMensaje("Deposito exitoso.");
                }
                break;
            } // <-- LLAVE DE CIERRE

            case 2: { // <-- LLAVE DE INICIO (Habitación 2)
                double monto = Utilidades::leerDouble("Monto a retirar: $");
                if (cuenta->retirar(monto)) {
                    // Esta es una 't' completamente nueva
                    Transaccion t((TipoTransaccion)RETIRO, cuenta->getNumero(), monto);
                    registrarTransaccion(t);
                    Utilidades::mostrarMensaje("Retiro exitoso.");
                }
                break;
            } // <-- LLAVE DE CIERRE

            case 3: { // <-- LLAVE DE INICIO (Habitación 3)
                double monto = Utilidades::leerDouble("Monto a transferir: $");
                std::string numDestino = Utilidades::leerString("Numero de cuenta destino: ");
                Cuenta* cDestino = buscarCuentaPorNumero(numDestino);

                if (cDestino == nullptr) {
                    Utilidades::mostrarMensaje("Error: Cuenta destino no encontrada.");
                } else if (cuenta->transferirA(cDestino, monto)) {
                    // Y esta es la tercera 't', también nueva
                    Transaccion t((TipoTransaccion)TRANSFERENCIA, cuenta->getNumero(), monto, cDestino->getNumero());
                    registrarTransaccion(t);
                    Utilidades::mostrarMensaje("Transferencia exitosa.");
                }
                break;
            } // <-- LLAVE DE CIERRE

            case 0:
                enAtencion = false;
                break;
        }
    }
    
    liberarVentanilla(ventanilla);
}

void SistemaBancario::liberarVentanilla(Ventanilla* ventanilla) {
    // Asumimos Ventanilla.cpp tiene liberarCliente()
    Cliente* cliente = ventanilla->liberarCliente(); 
    ventanillasLibres.push(ventanilla); // La devuelve a la cola de libres
    
    Utilidades::mostrarMensaje("Atencion finalizada para " + 
                               cliente->getNombreCompleto() + 
                               ". Ventanilla " + 
                               std::to_string(ventanilla->getID()) + " esta libre.");
}

void SistemaBancario::verEstadoFila() const {
    Utilidades::limpiarPantalla();
    if (filaDeEspera.empty()) {
        Utilidades::mostrarMensaje("La fila de espera esta vacia.");
        return;
    }
    
    std::priority_queue<Cliente*, 
                        std::vector<Cliente*>, 
                        ComparadorClientePtr> filaTemporal = filaDeEspera;
    
    std::cout << "--- Estado de la Fila (" << filaTemporal.size() << " clientes) ---\n";
    int i = 1;
    while (!filaTemporal.empty()) {
        Cliente* c = filaTemporal.top();
        filaTemporal.pop();
        std::cout << i++ << ". " << c->toString() << "\n";
    }
    std::cout << "------------------------------------------\n";
    Utilidades::pausarPantalla();
}

void SistemaBancario::verEstadoVentanillas() const {
    Utilidades::limpiarPantalla();
    std::cout << "--- Estado de las Ventanillas ---\n";
    for (const auto& ventanilla : todasLasVentanillas) {
        // Asumimos Ventanilla.cpp tiene toString()
        std::cout << ventanilla.toString() << "\n";
    }
    std::cout << "---------------------------------\n";
    Utilidades::pausarPantalla();
}

// --- Métodos de la Bóveda ---

void SistemaBancario::registrarTransaccion(const Transaccion& trans) {
    // Añade al historial
    historialTransacciones.push_back(trans);
    // Si el historial es muy largo, borra la más antigua
    if (historialTransacciones.size() > MAX_HISTORIAL) {
        historialTransacciones.pop_front();
    }

    // Solo se pueden "deshacer" retiros y transferencias
    if (trans.getTipo() == RETIRO || trans.getTipo() == TRANSFERENCIA) {
        pilaDeshacer.push(trans);
    }
    
    // (Aviso: No tenemos lógica para limpiar la pilaDeshacer si es muy grande)
}

void SistemaBancario::gestionarDeshacer() {
    if (pilaDeshacer.empty()) {
        Utilidades::mostrarMensaje("No hay transacciones para deshacer.");
        return;
    }

    // 1. Obtener la última transacción (sin sacarla)
    Transaccion tOriginal = pilaDeshacer.top();
    
    // 2. Encontrar las cuentas
    Cuenta* cOrigen = buscarCuentaPorNumero(tOriginal.getCuentaOrigen());

    if (cOrigen == nullptr) {
        Utilidades::mostrarMensaje("Error fatal: No se encontró la cuenta de origen para deshacer.");
        pilaDeshacer.pop(); // Saca la transacción rota
        return;
    }

    // 3. Revertir la lógica
    if (tOriginal.getTipo() == RETIRO) {
        cOrigen->depositar(tOriginal.getMonto());
        Utilidades::mostrarMensaje("Retiro deshecho. $" + std::to_string(tOriginal.getMonto()) + 
                                   " devueltos a la cuenta " + cOrigen->getNumero());
    
    } else if (tOriginal.getTipo() == TRANSFERENCIA) {
        Cuenta* cDestino = buscarCuentaPorNumero(tOriginal.getCuentaDestino());
        if (cDestino == nullptr) {
             Utilidades::mostrarMensaje("Error: No se encontró la cuenta destino. No se puede deshacer.");
             pilaDeshacer.pop();
             return;
        }
        // Devuelve el dinero
        cDestino->retirar(tOriginal.getMonto());
        cOrigen->depositar(tOriginal.getMonto());
        Utilidades::mostrarMensaje("Transferencia deshecha. $" + std::to_string(tOriginal.getMonto()) +
                                   " devueltos de " + cDestino->getNumero() + " a " + cOrigen->getNumero());
    }

    // 4. Saca la transacción de la pila
    pilaDeshacer.pop();
}

void SistemaBancario::verHistorial() const {
    Utilidades::limpiarPantalla();
    std::cout << "--- Historial de Transacciones (" << historialTransacciones.size() << ") ---\n";
    if (historialTransacciones.empty()) {
        std::cout << "(No hay transacciones registradas)\n";
    } else {
        // Itera desde la más reciente (al final) a la más antigua (al inicio)
        for (auto it = historialTransacciones.rbegin(); it != historialTransacciones.rend(); ++it) {
            std::cout << it->toString() << "\n";
        }
    }
    std::cout << "------------------------------------------\n";
    Utilidades::pausarPantalla();
}


// --- Métodos de Búsqueda (Ayudantes) ---

Cuenta* SistemaBancario::buscarCuentaDeCliente(Cliente* cliente) {
    if (cliente == nullptr) return nullptr;
    
    // Usa getTitular() de Cuenta.h
    std::string nombreTitular = cliente->getNombreCompleto(); 
    
    for (auto& cuenta : listaMaestraCuentas) {
        if (cuenta.getTitular() == nombreTitular) {
            return &cuenta; // Devuelve un puntero a esta cuenta
        }
    }
    
    return nullptr; // No se encontró
}

Cuenta* SistemaBancario::buscarCuentaPorNumero(std::string numCuenta) {
    for (auto& cuenta : listaMaestraCuentas) {
        if (cuenta.getNumero() == numCuenta) {
            return &cuenta;
        }
    }
    return nullptr;
}

Cliente* SistemaBancario::buscarClientePorID(int id) {
     for (auto& cliente : listaMaestraClientes) {
        if (cliente.getID() == id) {
            return &cliente;
        }
    }
    return nullptr;
}


void SistemaBancario::cargarDatosPrueba() {
    Utilidades::limpiarPantalla();
    
    // Crear Clientes de Prueba
    listaMaestraClientes.emplace_back("Ana", "Gomez", 70); // ADULTO_MAYOR
    listaMaestraClientes.emplace_back("Luis", "Vega", 30, VIP); // VIP
    listaMaestraClientes.emplace_back("Sara", "Paz", 25);  // REGULAR
    
    // Crear Cuentas de Prueba
    listaMaestraCuentas.emplace_back("Ana Gomez", 5000);
    listaMaestraCuentas.emplace_back("Luis Vega", 20000);
    listaMaestraCuentas.emplace_back("Sara Paz", 1500);

    // Añadir a la fila (Nota: buscamos los punteros de la lista)
    for (auto& cliente : listaMaestraClientes) {
        filaDeEspera.push(&cliente);
    }
    
    Utilidades::mostrarMensaje("3 clientes de prueba y sus cuentas han sido creados y añadidos a la fila.");
}