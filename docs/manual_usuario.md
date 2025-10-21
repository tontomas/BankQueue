# Manual de Usuario - Sistema Bancario

## Bienvenido al Sistema de Gestión Bancaria

Este manual le guiará paso a paso en el uso del sistema de atención bancaria automatizado. El sistema gestiona clientes, cuentas, ventanillas y transacciones de manera eficiente y segura.

---

## Índice

1. [Inicio del Sistema](#inicio-del-sistema)
2. [Menú Principal](#menú-principal)
3. [Gestión de Clientes](#gestión-de-clientes)
4. [Atención en Ventanilla](#atención-en-ventanilla)
5. [Operaciones Bancarias](#operaciones-bancarias)
6. [Consultas y Reportes](#consultas-y-reportes)
7. [Funciones Especiales](#funciones-especiales)
8. [Preguntas Frecuentes](#preguntas-frecuentes)

---

## Inicio del Sistema

### Arranque Inicial
Al iniciar el programa, se le solicitará configurar el número de ventanillas disponibles. El sistema creará automáticamente todas las ventanillas necesarias y las marcará como disponibles.

**Recomendación:** Para una sucursal pequeña, use 2-3 ventanillas. Para una sucursal grande, use 5-8 ventanillas.

---

## Menú Principal

Al iniciar, verá el siguiente menú:

```
=== SISTEMA BANCARIO ===
1. Crear Nuevo Cliente
2. Procesar Siguiente en Fila
3. Ver Estado de la Fila
4. Ver Estado de Ventanillas
5. Ver Historial de Transacciones
6. Deshacer Última Transacción
7. Cargar Datos de Prueba
0. Salir del Sistema
```

**Instrucciones:** Ingrese el número de la opción deseada y presione Enter.

---

## Gestión de Clientes

### Opción 1: Crear Nuevo Cliente

Esta opción le permite registrar un nuevo cliente y añadirlo automáticamente a la fila de espera.

#### Paso a Paso:

1. **Seleccione la opción 1** del menú principal

2. **Ingrese los datos personales:**
   - **Nombre:** Escriba el nombre del cliente
   - **Apellido:** Escriba el apellido del cliente
   - **Edad:** Ingrese un número entre 18 y 99 años

3. **Asigne la prioridad:**
   ```
   Opciones:
   0 = Automático (el sistema decide según la edad)
   1 = VIP (máxima prioridad)
   2 = PREFERENCIAL (alta prioridad)
   ```

   **Nota:** Si elige "0", el sistema asignará automáticamente:
   - ADULTO_MAYOR (si tiene 60+ años)
   - REGULAR (si tiene menos de 60 años)

4. **Ingrese el saldo inicial:**
   - Monto mínimo recomendado: $0
   - El sistema creará automáticamente una cuenta con este saldo

5. **Confirmación:**
   El sistema mostrará un mensaje confirmando:
   - Nombre completo del cliente
   - Que fue añadido a la fila
   - Número de cuenta asignado

#### Ejemplo:
```
Ingrese nombre: María
Ingrese apellido: Torres
Ingrese edad: 45
Asignar prioridad especial? (0=Automático, 1=VIP, 2=PREFERENCIAL): 0
Ingrese saldo inicial: $5000

CONFIRMACIÓN:
Cliente María Torres agregado a la fila.
Cuenta creada: ACC-00123456
```

---

## Atención en Ventanilla

### Opción 2: Procesar Siguiente en Fila

Esta opción atiende al siguiente cliente según su prioridad.

#### Cómo Funciona:

1. **Seleccione la opción 2**

2. **El sistema automáticamente:**
   - Identifica al cliente con mayor prioridad
   - Asigna una ventanilla libre
   - Muestra el número de ventanilla asignada

3. **Orden de Prioridad:**
   ```
   1. VIP (Prioridad máxima)
   2. PREFERENCIAL (Alta prioridad)
   3. ADULTO_MAYOR (Prioridad media)
   4. REGULAR (Prioridad estándar)
   ```

#### Mensajes del Sistema:

**EXITOSO:**
```
Cliente Juan Pérez pasa a la Ventanilla 3.
```

**ADVERTENCIAS:**
```
La fila de espera está vacía.
```
```
No hay ventanillas libres en este momento.
```

---

## Operaciones Bancarias

Una vez que un cliente está en ventanilla, se abre el **Menú de Ventanilla** con las siguientes opciones:

### Menú de Ventanilla
```
=== ATENDIENDO A: [Nombre del Cliente] ===
1. Realizar Depósito
2. Realizar Retiro
3. Realizar Transferencia
0. Finalizar Atención
```

---

### OPERACIÓN 1: Realizar Depósito

Añade dinero a la cuenta del cliente.

#### Procedimiento:
1. Seleccione la opción **1**
2. Ingrese el monto a depositar (ej: 1000)
3. Presione Enter

#### Validaciones:
- El monto debe ser positivo
- No hay límite máximo

#### Ejemplo:
```
Monto a depositar: $1500
RESULTADO: Depósito exitoso.
Nuevo saldo: $6500
```

---

### OPERACIÓN 2: Realizar Retiro

Extrae dinero de la cuenta del cliente.

#### Procedimiento:
1. Seleccione la opción **2**
2. Ingrese el monto a retirar
3. Presione Enter

#### Validaciones:
- El monto debe ser positivo
- Debe haber saldo suficiente
- **IMPORTANTE:** Esta operación puede deshacerse (ver Opción 6)

#### Ejemplo Exitoso:
```
Monto a retirar: $800
RESULTADO: Retiro exitoso.
Nuevo saldo: $5700
```

#### Ejemplo con Error:
```
Monto a retirar: $10000
ERROR: Saldo insuficiente.
Saldo actual: $5700
```

---

### OPERACIÓN 3: Realizar Transferencia

Transfiere dinero desde la cuenta del cliente actual hacia otra cuenta.

#### Procedimiento:
1. Seleccione la opción **3**
2. Ingrese el monto a transferir
3. Ingrese el número de cuenta destino (ej: ACC-00123457)
4. Presione Enter

#### Validaciones:
- El monto debe ser positivo
- Debe haber saldo suficiente
- La cuenta destino debe existir
- **IMPORTANTE:** Esta operación puede deshacerse (ver Opción 6)

#### Ejemplo Exitoso:
```
Monto a transferir: $500
Número de cuenta destino: ACC-00123457
RESULTADO: Transferencia exitosa.
Nuevo saldo: $5200
```

#### Ejemplo con Error:
```
Número de cuenta destino: ACC-99999999
ERROR: Cuenta destino no encontrada.
```

---

### OPERACIÓN 0: Finalizar Atención

Libera al cliente de la ventanilla y marca la ventanilla como disponible.

#### Qué Sucede:
- La ventanilla queda libre para el siguiente cliente
- El cliente sale del sistema
- Se muestra un mensaje de confirmación

#### Ejemplo:
```
CONFIRMACIÓN: Atención finalizada para María Torres.
Ventanilla 2 está libre.
```

---

## Consultas y Reportes

### Opción 3: Ver Estado de la Fila

Muestra todos los clientes en espera, ordenados por prioridad.

#### Información Mostrada:
- Número de posición
- ID del cliente
- Nombre completo
- Edad
- Tipo de prioridad

#### Ejemplo:
```
--- Estado de la Fila (3 clientes) ---
1. [ID: 1] Ana Gómez (70 años) - ADULTO_MAYOR
2. [ID: 3] Sara Paz (25 años) - REGULAR
3. [ID: 4] Pedro López (35 años) - REGULAR
------------------------------------------
```

**Nota:** Los clientes VIP y PREFERENCIALES siempre aparecen primero.

---

### Opción 4: Ver Estado de Ventanillas

Muestra el estado de todas las ventanillas del sistema.

#### Información Mostrada:
- Número de ventanilla
- Estado (LIBRE u OCUPADA)
- Cliente siendo atendido (si aplica)

#### Ejemplo:
```
--- Estado de las Ventanillas ---
Ventanilla 1: LIBRE
Ventanilla 2: OCUPADA - Atendiendo a: Juan Pérez
Ventanilla 3: OCUPADA - Atendiendo a: María Torres
Ventanilla 4: LIBRE
Ventanilla 5: LIBRE
---------------------------------
```

---

### Opción 5: Ver Historial de Transacciones

Muestra todas las transacciones realizadas, desde la más reciente hasta la más antigua.

#### Información por Transacción:
- Fecha y hora
- Tipo de operación (DEPÓSITO, RETIRO, TRANSFERENCIA)
- Cuenta de origen
- Monto
- Cuenta de destino (solo en transferencias)

#### Ejemplo:
```
--- Historial de Transacciones (15) ---
[2025-10-20 14:35:22] TRANSFERENCIA
  Desde: ACC-00123456 → Hacia: ACC-00123457
  Monto: $500.00

[2025-10-20 14:30:15] RETIRO
  Cuenta: ACC-00123456
  Monto: $800.00

[2025-10-20 14:25:08] DEPÓSITO
  Cuenta: ACC-00123456
  Monto: $1500.00
------------------------------------------
```

**Límite:** El sistema guarda las últimas 100 transacciones.

---

## Funciones Especiales

### Opción 6: Deshacer Última Transacción

Revierte la última operación de retiro o transferencia realizada.

#### ¿Qué se puede deshacer?
- **SÍ:** Retiros
- **SÍ:** Transferencias
- **NO:** Depósitos

#### Cómo Funciona:

**Para Retiros:**
- El dinero retirado se devuelve a la cuenta

**Para Transferencias:**
- El dinero se retira de la cuenta destino
- El dinero se devuelve a la cuenta origen

#### Ejemplo - Deshacer Retiro:
```
CONFIRMACIÓN: Retiro deshecho.
$800.00 devueltos a la cuenta ACC-00123456
```

#### Ejemplo - Deshacer Transferencia:
```
CONFIRMACIÓN: Transferencia deshecha.
$500.00 devueltos de ACC-00123457 a ACC-00123456
```

#### Advertencia:
```
ADVERTENCIA: No hay transacciones para deshacer.
```

**Importante:** Solo se puede deshacer UNA transacción a la vez. Si deshace una operación, no podrá deshacer la anterior a esa.

---

### Opción 7: Cargar Datos de Prueba

Esta opción es útil para demostración o capacitación.

#### Qué Hace:
- Crea 3 clientes de prueba con diferentes prioridades
- Crea 3 cuentas con saldos iniciales
- Los añade automáticamente a la fila de espera

#### Clientes Creados:
```
1. Ana Gómez (70 años) - ADULTO_MAYOR - Saldo: $5,000
2. Luis Vega (30 años) - VIP - Saldo: $20,000
3. Sara Paz (25 años) - REGULAR - Saldo: $1,500
```

**Uso Recomendado:** Ideal para probar el sistema sin tener que ingresar datos manualmente.

---

### Opción 0: Salir del Sistema

Cierra el programa de forma segura.

#### Qué Sucede:
- Se muestra un mensaje de despedida
- El programa se cierra
- **IMPORTANTE:** Los datos NO se guardan automáticamente

**Mensaje:**
```
Gracias por usar el Sistema Bancario. Adiós.
```

---

## Preguntas Frecuentes

### ¿Qué pasa si intento procesar la fila sin clientes?
El sistema mostrará el mensaje: "La fila de espera está vacía." Debe crear clientes primero (Opción 1).

### ¿Qué pasa si todas las ventanillas están ocupadas?
El sistema mostrará: "No hay ventanillas libres en este momento." Debe finalizar la atención de algún cliente primero.

### ¿Puedo crear un cliente con prioridad VIP después de crearlo como REGULAR?
No. La prioridad se asigna al momento de crear el cliente y no puede cambiarse después.

### ¿Cuántas transacciones se guardan en el historial?
El sistema guarda las últimas 100 transacciones. Las más antiguas se eliminan automáticamente.

### ¿Se guardan los datos al cerrar el programa?
No. Los datos existen solo mientras el programa está en ejecución. Si necesita conservar la información, use la opción de datos de prueba para recargarlos.

### ¿Puedo deshacer un depósito?
No. Solo los retiros y transferencias pueden deshacerse, ya que son operaciones que sacan dinero de las cuentas.

### ¿Qué pasa si intento transferir a una cuenta que no existe?
El sistema mostrará: "Error: Cuenta destino no encontrada." y NO realizará la transferencia.

### ¿Puedo atender a un cliente específico fuera de orden?
No. El sistema siempre atiende según la prioridad automáticamente. No es posible saltar clientes manualmente.

---

## Consejos de Uso

### Para Operadores Nuevos:
1. Comience usando la **Opción 7** (Cargar Datos de Prueba)
2. Practique procesando la fila (Opción 2)
3. Realice operaciones simples primero (depósitos)
4. Después pruebe operaciones más complejas (transferencias)

### Para Operación Diaria:
1. Cree los clientes conforme lleguen (Opción 1)
2. Procese la fila regularmente (Opción 2)
3. Monitoree el estado de ventanillas (Opción 4)
4. Revise el historial periódicamente (Opción 5)

### Para Supervisores:
1. Use la Opción 3 para ver la longitud de la fila
2. Use la Opción 4 para verificar ventanillas ocupadas
3. Use la Opción 5 para auditar transacciones
4. Use la Opción 6 para corregir errores inmediatamente

---

## Soporte Técnico

Si encuentra algún problema o error no descrito en este manual, por favor contacte al administrador del sistema con la siguiente información:

- Descripción del problema
- Opción del menú que estaba usando
- Mensaje de error mostrado (si aplica)
- Pasos para reproducir el problema

---

## Notas Finales

- **Seguridad:** Verifique siempre los montos antes de confirmar operaciones
- **Eficiencia:** Finalice las atenciones rápidamente para liberar ventanillas
- **Precisión:** Verifique los números de cuenta antes de realizar transferencias
- **Respaldo:** Use la función de deshacer solo en casos de error inmediato

---

**Versión del Manual:** 1.0  
**Fecha:** Octubre 2025  
**Sistema:** Sistema Bancario v1.0

---

*Gracias por usar nuestro Sistema Bancario*
