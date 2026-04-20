# README - Proyecto Parqueadero

## Sistema de Parqueadero

### Desarrollos Innovadores

1. Implementación de múltiples parqueaderos por tipo de vehículo (Carros, motos y bicicletas)
2. Generación de placas aleatorias únicas (Para moto, carro y bicicleta)
3. Sistema de facturación visual (Con imagenes del vehiculo)
4. Hora en tiempo real en el menú (Hora local)
5. Registro de hora de salida (Hora local)
6. Consulta de placa por posición
7. Sistema de propina
8. Sistema de actualización automática de precios por tiempo (uso de hilos)

---

### Detalle de Desarrollos Innovadores

#### 1. Implementación de múltiples parqueaderos por tipo de vehículo

**¿Para qué se implementó?**
Se implementó para organizar correctamente los vehículos según su tipo, separando carros, motos y bicicletas en espacios diferentes.

**¿Por qué se consideró necesario?**
Fue necesario para mejorar la gestión del sistema, evitar desorden y asegurar que cada vehículo se ubique en el parqueadero correspondiente a su tipo.

**¿Cómo se llevó a cabo su implementación?**
Se crearon tres parqueaderos independientes dentro del sistema: uno exclusivo para carros, uno para motos y uno para bicicletas. Cada vehículo es validado antes de ingresar para asegurar que se almacene en el parqueadero correcto según su tipo. Aun así, se siguió manteniendo la estructura de mínimo 16x16 para el parqueadero de carros.

---

#### 2. Generación de placas aleatorias únicas

**¿Para qué se implementó?**
Se implementó para asignar identificadores únicos a cada vehículo dentro del sistema, asegurando que ningún vehículo tenga una placa repetida.

**¿Por qué se consideró necesario?**
Fue necesario para evitar duplicados y garantizar un correcto registro y control de los vehículos, asegurando que cada uno pueda ser identificado de manera independiente.

**¿Cómo se llevó a cabo su implementación?**
Se desarrolló un algoritmo que genera placas de forma aleatoria combinando letras y números con formato diferente según el tipo de vehículo. Antes de asignarla, se valida que la placa generada no exista previamente en el sistema.

---

#### 3. Sistema de facturación visual

**¿Para qué se implementó?**
Se implementó para mostrar de forma clara y visual la información de cada transacción realizada por los vehículos.

**¿Por qué se consideró necesario?**
Se consideró importante mejorar la presentación de los datos, facilitando la lectura de la factura y haciendo el sistema más intuitivo y amigable para el usuario.

**¿Cómo se llevó a cabo su implementación?**
Se diseñó un sistema que genera facturas en el archivo Facturas.txt incluyendo un dibujo del vehículo usando caracteres ASCII (diferente para carro, moto o bicicleta), la placa o ID del vehículo, el valor total pagado, la propina dejada por el cliente y la hora de salida.

---

#### 4. Hora en tiempo real en el menú

**¿Para qué se implementó?**
Se implementó para que el usuario siempre sepa la hora exacta del sistema al momento de interactuar con el menú.

**¿Por qué se consideró necesario?**
Se consideró necesario para mejorar la experiencia del usuario y darle contexto temporal en cada acción que realiza dentro del sistema.

**¿Cómo se llevó a cabo su implementación?**
Se creó la función ObtenerHora() que lee la hora local del computador usando la librería ctime y la retorna como string en formato Horas:Minutos:Segundos. Esta función se llama al inicio de cada vez que se muestra el menú principal.

---

#### 5. Registro de hora de salida (Nos ayudó la IA)

**¿Para qué se implementó?**
Se implementó para mostrar y registrar la hora exacta en que cada vehículo abandona el parqueadero.

**¿Por qué se consideró necesario?**
El enunciado solo exige registrar la hora de entrada. Agregar la hora de salida permite tener un registro completo del tiempo de permanencia de cada vehículo, mejorando la localización del vehículo en sistema.

**¿Cómo se llevó a cabo su implementación?**
Se reutilizó la función ObtenerHora() al momento de procesar la salida del vehículo, mostrando en consola la hora exacta en que el vehículo salió del parqueadero.

---

#### 6. Consulta de placa por posición

**¿Para qué se implementó?**
Se implementó para que el usuario pueda buscar en qué fila y columna del parqueadero se encuentra un vehículo específico ingresando su placa o ID.

**¿Por qué se consideró necesario?**
Fue necesario para facilitar la localización de vehículos dentro del parqueadero sin tener que revisar manualmente toda la tabla.

**¿Cómo se llevó a cabo su implementación?**
Se desarrolló la función ConsultarPlaca() que lee el archivo del parqueadero seleccionado, recorre la matriz con ciclos for y compara cada celda con la placa ingresada, retornando la fila y columna donde se encuentra.

---

#### 7. Sistema de propina

**¿Para qué se implementó?**
Se implementó para permitir que el usuario pague un valor superior al precio mínimo del parqueadero como propina voluntaria.

**¿Por qué se consideró necesario?**
Fue necesario para simular de manera más realista el funcionamiento de un parqueadero real, donde los clientes pueden dar propina al momento de pagar.

**¿Cómo se llevó a cabo su implementación?**
Al momento de sacar el vehículo, el sistema calcula la diferencia entre el valor ingresado por el usuario y el precio total del parqueadero. Si el valor ingresado es mayor al precio, la diferencia se registra como propina y se guarda en la factura.

---

#### 8. Sistema de actualización automática de precios por tiempo (Nos ayudó la IA)

**¿Para qué se implementó?**
Se implementó para que el costo del parqueadero aumente automáticamente con el paso del tiempo sin intervención del usuario.

**¿Por qué se consideró necesario?**
Fue necesario para simular el funcionamiento real de un parqueadero, donde el cobro depende del tiempo que el vehículo permanece dentro.

**¿Cómo se llevó a cabo su implementación?**
Se utilizó un hilo (thread) que se ejecuta en segundo plano y cada cierto tiempo actualiza los precios almacenados en el sistema. Esto permite que el cálculo del costo sea dinámico sin afectar la ejecución principal del programa.


### Instrucciones para Correr el Programa
**Paso 1**
Ve a la subcarpeta `src`.
**Paso 2**
Compilar el programa:
g++ main.cpp -pthread -o programa.exe
**Paso 3**
Ejecutar:
./programa.exe

### Notas
- Los archivos del sistema se generan automáticamente dentro de la carpeta `/data` al ejecutar el programa.