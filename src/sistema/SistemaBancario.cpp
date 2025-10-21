#include "sistema/SistemaBancario.h"
#include "utils/Utilidades.h" 
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream> 
#include <sstream> 

SistemaBancario::SistemaBancario(int numVentanillas) {
    for (int i = 0; i < numVentanillas; ++i) {
        this->todasLasVentanillas.emplace_back(i + 1);
    }
    
    for (auto& ventanilla : this->todasLasVentanillas) {
        this->ventanillasLibres.push(&ventanilla);
    }

    cargarDatos(); 
}

void SistemaBancario::iniciar() {
    bool corriendo = true;
    while (corriendo) {
        
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
            default: Utilidades::mostrarMensaje("Opcion no reconocida."); break;
        }
    }
    guardarDatos(); 
    Utilidades::mostrarMensaje("Gracias por usar el Sistema Bancario. Adios.");
}

void SistemaBancario::gestionarNuevoCliente() {
    Utilidades::limpiarPantalla();
    std::cout << "--- Creacion de Nuevo Cliente ---\n";
    
    std::string nombre = Utilidades::leerString("Ingrese nombre: ");
    std::string apellido = Utilidades::leerString("Ingrese apellido: ");
    int edad = Utilidades::leerInt("Ingrese edad: ", 18, 99);
    
    int pManual = Utilidades::leerInt(
        "Asignar prioridad especial? (0=Automatico, 1=VIP, 2=PREFERENCIAL): ", 0, 2
    );

    if (pManual == 0) {
        listaMaestraClientes.emplace_back(nombre, apellido, edad);
    } else {
        if (pManual == 1) listaMaestraClientes.emplace_back(nombre, apellido, edad, VIP);
        else listaMaestraClientes.emplace_back(nombre, apellido, int(edad), PREFERENCIAL);
    }
    
    Cliente* nuevoCliente = &listaMaestraClientes.back();

    double saldoInicial = Utilidades::leerDouble("Ingrese saldo inicial: $");
    
    listaMaestraCuentas.emplace_back(nuevoCliente->getNombreCompleto(), saldoInicial);
    
    Cuenta* nuevaCuenta = &listaMaestraCuentas.back();

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

    Cliente* cliente = filaDeEspera.top();
    filaDeEspera.pop();

    Ventanilla* ventanilla = ventanillasLibres.front();
    ventanillasLibres.pop();

    ventanilla->atenderCliente(cliente);

    Utilidades::mostrarMensaje("Cliente " + cliente->getNombreCompleto() + 
                               " pasa a la Ventanilla " + 
                               std::to_string(ventanilla->getID()) + ".");
    
    gestionarAtencion(ventanilla);
}

void SistemaBancario::gestionarAtencion(Ventanilla* ventanilla) {
    Cliente* cliente = ventanilla->getClienteActual();
    
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
            case 1: { 
                double monto = Utilidades::leerDouble("Monto a depositar: $");
                if (cuenta->depositar(monto)) {
                    
                    Transaccion t((TipoTransaccion)DEPOSITO, cuenta->getNumero(), monto);
                    registrarTransaccion(t);
                    Utilidades::mostrarMensaje("Deposito exitoso.");
                }
                break;
            } 

            case 2: { 
                double monto = Utilidades::leerDouble("Monto a retirar: $");
                if (cuenta->retirar(monto)) {
                    
                    Transaccion t((TipoTransaccion)RETIRO, cuenta->getNumero(), monto);
                    registrarTransaccion(t);
                    Utilidades::mostrarMensaje("Retiro exitoso.");
                }
                break;
            } 

            case 3: { 
                double monto = Utilidades::leerDouble("Monto a transferir: $");
                std::string numDestino = Utilidades::leerString("Numero de cuenta destino: ");
                Cuenta* cDestino = buscarCuentaPorNumero(numDestino);

                if (cDestino == nullptr) {
                    Utilidades::mostrarMensaje("Error: Cuenta destino no encontrada.");
                } else if (cuenta->transferirA(cDestino, monto)) {
                    
                    Transaccion t((TipoTransaccion)TRANSFERENCIA, cuenta->getNumero(), monto, cDestino->getNumero());
                    registrarTransaccion(t);
                    Utilidades::mostrarMensaje("Transferencia exitosa.");
                }
                break;
            } 

            case 0:
                enAtencion = false;
                break;
        }
    }
    
    liberarVentanilla(ventanilla);
}

void SistemaBancario::liberarVentanilla(Ventanilla* ventanilla) {
    
    Cliente* cliente = ventanilla->liberarCliente(); 
    ventanillasLibres.push(ventanilla); 
    
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
        
        std::cout << ventanilla.toString() << "\n";
    }
    std::cout << "---------------------------------\n";
    Utilidades::pausarPantalla();
}



void SistemaBancario::registrarTransaccion(const Transaccion& trans) {
    
    historialTransacciones.push_back(trans);
    
    if (historialTransacciones.size() > MAX_HISTORIAL) {
        historialTransacciones.pop_front();
    }

    
    if (trans.getTipo() == RETIRO || trans.getTipo() == TRANSFERENCIA) {
        pilaDeshacer.push(trans);
    }
    
}

void SistemaBancario::gestionarDeshacer() {
    if (pilaDeshacer.empty()) {
        Utilidades::mostrarMensaje("No hay transacciones para deshacer.");
        return;
    }

    Transaccion tOriginal = pilaDeshacer.top();
    
    Cuenta* cOrigen = buscarCuentaPorNumero(tOriginal.getCuentaOrigen());

    if (cOrigen == nullptr) {
        Utilidades::mostrarMensaje("Error fatal: No se encontró la cuenta de origen para deshacer.");
        pilaDeshacer.pop();
        return;
    }

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
        cDestino->retirar(tOriginal.getMonto());
        cOrigen->depositar(tOriginal.getMonto());
        Utilidades::mostrarMensaje("Transferencia deshecha. $" + std::to_string(tOriginal.getMonto()) +
                                   " devueltos de " + cDestino->getNumero() + " a " + cOrigen->getNumero());
    }

    pilaDeshacer.pop();
}

void SistemaBancario::verHistorial() const {
    Utilidades::limpiarPantalla();
    std::cout << "--- Historial de Transacciones (" << historialTransacciones.size() << ") ---\n";
    if (historialTransacciones.empty()) {
        std::cout << "(No hay transacciones registradas)\n";
    } else {
        for (auto it = historialTransacciones.rbegin(); it != historialTransacciones.rend(); ++it) {
            std::cout << it->toString() << "\n";
        }
    }
    std::cout << "------------------------------------------\n";
    Utilidades::pausarPantalla();
}



Cuenta* SistemaBancario::buscarCuentaDeCliente(Cliente* cliente) {
    if (cliente == nullptr) return nullptr;
    
    std::string nombreTitular = cliente->getNombreCompleto(); 
    
    for (auto& cuenta : listaMaestraCuentas) {
        if (cuenta.getTitular() == nombreTitular) {
            return &cuenta; 
        }
    }
    
    return nullptr;
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
    Utilidades::mostrarMensaje("Reiniciando el sistema con datos de prueba. Se borraran los datos actuales.");
    
    listaMaestraClientes.clear();
    listaMaestraCuentas.clear();
    filaDeEspera = {}; 
    historialTransacciones.clear();
    while(!pilaDeshacer.empty()) pilaDeshacer.pop(); 

    Cliente::actualizarContador(1000); 
    Cuenta::actualizarContador(100000); 
    
    listaMaestraClientes.emplace_back("Ana", "Gomez", 70);
    listaMaestraClientes.emplace_back("Luis", "Vega", 30, VIP); 
    listaMaestraClientes.emplace_back("Sara", "Paz", 25);  
    
    listaMaestraCuentas.emplace_back("Ana Gomez", 5000); 
    listaMaestraCuentas.emplace_back("Luis Vega", 20000); 
    listaMaestraCuentas.emplace_back("Sara Paz", 1500); 

    for (auto& cliente : listaMaestraClientes) {
        filaDeEspera.push(&cliente);
    }
    
    Utilidades::mostrarMensaje("3 clientes de prueba y sus cuentas han sido creados y añadidos a la fila.");
    guardarDatos();
}

void SistemaBancario::cargarDatos() {
    Utilidades::limpiarPantalla();
    std::cout << "Cargando datos desde archivos...\n";

    int maxClienteID = 0;
    int maxCuentaID = 0;

    std::ifstream fileClientes("data/clientes.txt");
    if (fileClientes.is_open()) {
        std::string line;
        while (std::getline(fileClientes, line)) {
            std::vector<std::string> tokens = Utilidades::splitString(line, ',');
            if (tokens.size() == 6) { 
                int id = std::stoi(tokens[0]);
                std::string nombre = tokens[1];
                std::string apellido = tokens[2];
                int edad = std::stoi(tokens[3]);
                StatusCliente prioridad = static_cast<StatusCliente>(std::stoi(tokens[4]));
                time_t horaLlegada = static_cast<time_t>(std::stoll(tokens[5])); 

                listaMaestraClientes.emplace_back(nombre, apellido, edad, prioridad, horaLlegada, id);
                Cliente* clienteCargado = &listaMaestraClientes.back();
                filaDeEspera.push(clienteCargado);
                if (id > maxClienteID) maxClienteID = id;
            }
        }
        fileClientes.close();
        Cliente::actualizarContador(maxClienteID); 
        std::cout << "Clientes cargados: " << listaMaestraClientes.size() << std::endl;
    } else {
        std::cout << "Advertencia: No se encontro 'data/clientes.txt'. Se iniciara con clientes vacios.\n";
    }

    std::ifstream fileCuentas("data/cuentas.txt");
    if (fileCuentas.is_open()) {
        std::string line;
        while (std::getline(fileCuentas, line)) {
            std::vector<std::string> tokens = Utilidades::splitString(line, ',');
            if (tokens.size() == 4) { 
                std::string numero = tokens[0];
                std::string titular = tokens[1];
                double saldo = std::stod(tokens[2]);
                EstadoCuenta estado = static_cast<EstadoCuenta>(std::stoi(tokens[3]));

                listaMaestraCuentas.emplace_back(titular, saldo, numero, estado);
                int numParte = std::stoi(numero); 

                if (numParte > maxCuentaID) {
                    maxCuentaID = numParte;
                }
            }
        }
        fileCuentas.close();
        Cuenta::actualizarContador(maxCuentaID); 
        std::cout << "Cuentas cargadas: " << listaMaestraCuentas.size() << std::endl;
    } else {
        std::cout << "Advertencia: No se encontro 'data/cuentas.txt'. Se iniciara con cuentas vacias.\n";
    }

    Utilidades::pausarPantalla();
}

void SistemaBancario::guardarDatos() const {
    Utilidades::limpiarPantalla();
    std::cout << "Guardando datos en archivos...\n";

    std::ofstream fileClientes("data/clientes.txt");
    if (fileClientes.is_open()) {
        for (const auto& cliente : listaMaestraClientes) {
            fileClientes << cliente.getID() << ","
                         << cliente.getNombre() << ","
                         << cliente.getApellido() << ","
                         << cliente.getEdad() << ","
                         << static_cast<int>(cliente.getPrioridad()) << "," 
                         << cliente.getHoraLlegada() << "\n";
        }
        fileClientes.close();
        std::cout << "Clientes guardados.\n";
    } else {
        std::cerr << "Error: No se pudo abrir 'data/clientes.txt' para guardar.\n";
    }

    std::ofstream fileCuentas("data/cuentas.txt");
    if (fileCuentas.is_open()) {
        for (const auto& cuenta : listaMaestraCuentas) {
            fileCuentas << cuenta.getNumero() << ","
                         << cuenta.getTitular() << ","
                         << std::fixed << std::setprecision(2) << cuenta.getSaldo() << ","
                         << static_cast<int>(cuenta.getEstado()) << "\n";
        }
        fileCuentas.close();
        std::cout << "Cuentas guardadas.\n";
    } else {
        std::cerr << "Error: No se pudo abrir 'data/cuentas.txt' para guardar.\n";
    }

    Utilidades::pausarPantalla();
}