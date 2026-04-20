# Informe Entrega 1 - Bases de datos IIC2413

## Datos del Alumno

| **Apellidos**       | **Nombres**          | **Número de Alumno** |
|---------------------|----------------------|----------------------|
| Huenchul Guzmán | Benjamín Esteban    |25663046              |

## 0.1 Consideraciones aplicadas (supuestos)

- se asume que usuarios solo sean usuarios del sistema (trabajadoes), apartados de los socios regulares ya que el enunciado no lo deja claro. (se dice que usuarios del sistema son empleados del club o socios titulares, pero luego se dice que usuarios del sistema son aquellos con cargos en DCColo, lo que no incluye a los socios titulares):
![alt text](image.png)

- se asume que invitado_evnto solo depende del evento al que fue invitado y no de la persona que la invitara al envento como tal (entidad debil dependiente de que exista un evento)
- se asume que pueden haber varias sucursales en una comuna
- se asume que los atributos del esquema E/R seran observados en el modelo entidad relacion normalizado, esto por temas de visibilidad del propio esquema (la cantidad de elementos en el esquema empeora notablemente la visibilidad, clariadad y entendimiento de este)
- se asume que la forma de representar el esquema relacional normalizado a BCNF sera la siguiente:

    &nbsp;&nbsp;&nbsp;&nbsp;Entidad(atributo_1 PK, atributo_2 FK -> entidad_referenciada(atributo_relacionado), atributo_3, etc...)

## 1. Descripción y análisis del problema

El principal problema consistio en construir una base (o mejor dicho esquema) de datos para el Club DCColo, que básicamente necesita poder registrar todo lo que pasa en el club, asi como el manejo de los datos de los socios que pertenecen al club, qué instalaciones tienen disponibles en las distintas sucursales, la capacidad de arrendar estas instalaciones o agendar eventos y permitir manejar el cobro de las membresías.

Los usuarios del club (en este caso, usuarios como todas las personas que se relacionan con el club) se debian modelar en más de una entidad, ya que existen usuarios titulares que son aquellos que reciben los cobros de las membresias, beneficiarios que no pagan pero dependen del titular, adicionales que generan un cobro extra para el titular, etc... El club cuenta con varias sucursales, y cada una tiene sus propias tarifas tanto de membresía como de arriendo de lugares, los cuales tienen precios cambiantes según el día y la hora, lo que obliga a modelar las tarifas de forma separada y con vigencia ya que ademas los registros de cobro, uso y reservas deben quedar registrados para su posterior uso (variable segun las consultas que deseemos realizar).

## 2. Solución aplicada

La idea central de la solución fue modelar a todas las personas del sistema bajo una entidad Persona la cual sirve como directorio común, y desde ahí usar jerarquías para separar los distintos roles. Evitando asi tener que repetir atributos como el RUN, nombre, correo y teléfono en cada subtipo, asi los socios heredan de "persona" y a su vez se dividen en Titular, Beneficiario y Adicional, los cuales tienen reglas de negocio muy distintas entre sí, Lo mismo aplica para los Usuarios del sistema, que se dividen en Administradores y Gerentes (socios titulares no pertenecen a usuarios del sistema por lo aclarado en la seccion 0.1 "Consideraciones aplicadas (supuestos)").

Para el tema de las tarifas, se crearon dos entidades separadas: Tarifa_lugar para los precios de arriendo (que varían por lugar, día, hora y vigencia) y Tarifa_sucursal para los valores de membresía (que varían por sucursal). Esto permite actualizar un precio sin tocar los registros históricos de cuotas o reservas ya emitidas.

La entidad "reserva" concentra todos los arriendos, tanto pasados, presentes o futuros con un atributo de estado que indica si se ejecutó o no, ademas los eventos se modelan aparte porque tienen datos propios (código único, nombre, contratante) pero siempre generan una reserva de lugar, por lo que se conectan a "reserva" mediante la relación Genera. Así no se duplica la lógica de ocupación de lugares.

Para los contratantes de eventos se usaron dos relaciones separadas (Persona_realiza_evento y Empresa_realiza_evento, estas dos relaciones generan tablas a pesar de ser relaciones 1:n, el porque de esto se explica en la parte de referencias) ya que el enunciado dice que puede ser persona o empresa, y modelarlo con una sola relación lo haria más dificil de mantener sin perder la logica principal del esquema (esto en mi caso ya que son demaciadas cosas a considerar).

Finalmente, los asistentes a eventos se modelaron como entidad débil Invitado_evento porque solo existen en el contexto de un evento específico y se guardan datos mínimos de ellos, por lo que su identificación solo depende del evento al que asisten.

### 2.1 Modelo Entidad Relación

![Esquema BD](DCColo.svg)

### 2.2 Modelo Entidad Relación normalizado

- Region(codigo_region PK, nombre)

- Comuna(codigo_comuna PK, nombre, codigo_region FK -> Region(codigo_region))

- Sucursal(id_sucursal PK, nombre, direccion, codigo_comuna FK -> Comuna(codigo_comuna))

- Lugar(id_lugar PK, nombre, tipo, capacidad, unidad_cobro, id_sucursal FK -> Sucursal(id_sucursal))

- Tarifa_lugar(id_tarifa PK, id_lugar FK -> Lugar(id_lugar), dia_semana, hora_inicio, hora_fin, valor, fecha_inicio_vigencia, fecha_fin_vigencia)

- Tarifa_sucursal(id_tarifa PK, id_sucursal FK -> Sucursal(id_sucursal), tipo_socio, valor, fecha_inicio, fecha_fin)

- Persona(RUN PK, nombre_completo, correo, direccion_calle, codigo_comuna FK -> Comuna(codigo_comuna), telefono_celular, telefono_alternativo)

- Socios(RUN PK FK -> Persona(RUN), fecha_incorporacion, fecha_fin_membresia)

- Titular(RUN PK FK -> Socios(RUN), estado)

- Beneficiario(RUN PK FK -> Socios(RUN), fecha_nacimiento, tipo_parentesco, RUN_titular FK -> Titular(RUN))

- Adicionales(RUN PK FK -> Socios(RUN), fecha_nacimiento, tipo_parentesco, RUN_titular FK -> Titular(RUN))

- Cuotas(id_cuota PK, RUN_titular FK -> Titular(RUN), id_tarifa FK -> Tarifa_sucursal(id_tarifa), numero_cuota, monto, fecha_vencimiento, fecha_pago, estado)

- Invitado_socio(RUN PK, nombre_completo, correo, telefono)

- Invita_a(RUN_socio PK FK -> Socios(RUN), RUN_invitado PK FK -> Invitado_socio(RUN), fecha_visita PK, id_lugar FK -> Lugar(id_lugar))

- Reserva(id_reserva PK, RUN_socio FK -> Socios(RUN), id_lugar FK -> Lugar(id_lugar), fecha_inicio, hora_inicio, fecha_fin, hora_fin, monto_total, monto_pagado, estado, n_asistentes)

- Evento(codigo_evento PK, id_reserva FK -> Reserva(id_reserva), nombre, fecha, estado)

- Empresa_realiza_evento(codigo_evento PK FK -> Evento(codigo_evento), RUT_empresa FK -> Empresa(RUT), RUN_contacto FK -> Contacto_empresa(RUN))

- Persona_realiza_evento(codigo_evento PK FK -> Evento(codigo_evento), RUN_persona FK -> Persona(RUN))

- Empresa(RUT PK, nombre)

- Contacto_empresa(RUN PK FK -> Persona(RUN), RUT_empresa FK -> Empresa(RUT), cargo)

- Usuarios(RUN PK FK -> Persona(RUN), email, clave_encriptada)

- Administradores(RUN PK FK -> Usuarios(RUN))

- Gerentes(RUN PK FK -> Usuarios(RUN), id_sucursal FK -> Sucursal(id_sucursal), fecha_inicio_cargo, fecha_fin_cargo)

- Invitado_evento(identificador PK, codigo_evento PK FK -> Evento(codigo_evento), nombre)

### 2.3 Consultas SQL

## 3. Referencias y bibliografía externa

- consulta a gemini pro (utilizado para una duda respecto a la vinculacion de las dos relaciones de registro de eventos, lo que explica porque en el esquema existe una tabla para la relacion de registro eventos cuando esta es una relacion 1:n):

Prompt utilizado: "una foreign key puede estar vacia?, te pongo un ejemplo, hay dos relaciones las cuales una va desde una entidad persona y otra desde entidad empresa, y van a parar a evento mediante "persona _realiza_evento" y "empresa_realiza_evento" como son tablas con cardinalidad 1:n, la key de persona y empresa se las lleva la entidad evento, pero un evento no puede ser realizado por una empresa y una persona al mismo tiempo, por lo que una de las foreign key no va a tener la key respectiva, como funciona esto?, genera algun error?"

respuesta: "Para ir directo al grano: Sí, una Llave Foránea (Foreign Key) puede estar vacía (tener un valor NULL). No genera ningún error en la base de datos a menos que tú, como programador, le agregues la restricción explícita de que no pueda estar vacía (NOT NULL). pero puede dar a errores logicos.
 Solucion: En lugar de ensuciar la tabla Evento con atributos nulos, dejas la tabla Evento limpia y creas tablas para registrar quién lo realizó.

\- Evento(codigo_evento PK, nombre...) -> No tiene FKs de quién lo organiza.

\- Persona_realiza_evento(codigo_evento PK FK, RUN_persona FK)

\- Empresa_realiza_evento(codigo_evento PK FK, RUT_empresa FK)

Por qué es buena: Cumple a la perfección con la normalización (BCNF) porque eliminas por completo los valores nulos (NULL). Cada tabla tiene solo la información que le corresponde."
