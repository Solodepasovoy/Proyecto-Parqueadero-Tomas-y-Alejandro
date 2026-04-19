# README - Proyecto

## Integrantes
- Tomás Esteban Espinel Cohen
- Alejandro

## Desarrollos Innovadores

### 1. Implementación de múltiples parqueaderos por tipo de vehículo

**¿Para qué se implementó?**  
Se implementó para organizar correctamente los vehículos según su tipo, separando carros, motos y bicicletas en espacios diferentes.

**¿Por qué se consideró necesario?**  
Fue necesario para mejorar la gestión del sistema, evitar desorden y asegurar que cada vehículo se ubique en el parqueadero correspondiente a su tipo.

**¿Cómo se llevó a cabo su implementación?**  
Se crearon tres parqueaderos independientes dentro del sistema:
- Un parqueadero exclusivo para carros.
- Un parqueadero exclusivo para motos.
- Un parqueadero exclusivo para bicicletas.

Cada vehículo es validado antes de ingresar para asegurar que se almacene en el parqueadero correcto según su tipo.

---

### 2. Generación de placas aleatorias únicas

**¿Para qué se implementó?**  
Se implementó para asignar identificadores únicos a cada vehículo dentro del sistema y asegurando que ningún vehículo que sea diferente al del tipo de parqueadero este allí.

**¿Por qué se consideró necesario?**  
Fue necesario para evitar duplicados y garantizar un correcto registro y control de los vehículos, asegurando que cada uno pueda ser identificado de manera independiente.

**¿Cómo se llevó a cabo su implementación?**  
Se desarrolló un algoritmo que genera placas de forma aleatoria combinando letras y números, y posteriormente se valida que la placa generada no exista previamente en el sistema antes de asignarla.

---

### . Sistema de facturación visual

**¿Para qué se implementó?**  
Se implementó para mostrar de forma clara y visual la información de cada transacción realizada por los vehículos.

**¿Por qué se consideró necesario?**  
Se consideró importante mejorar la presentación de los datos, facilitando la lectura de la factura y haciendo el sistema más intuitivo y amigable para el usuario.

**¿Cómo se llevó a cabo su implementación?**  
Se diseñó un sistema que genera facturas incluyendo:
- Un dibujo del vehículo (moto, carro o bicicleta) usando caracteres.
- La placa o ID del vehículo.
- El valor total pagado.
- La propina dejada por el cliente.

---