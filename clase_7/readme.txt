% UNO(1) uno 1.0.0
% Andrés Isaac Biso
% 30/04/2023

# NOMBRE
uno - levanta y escribe a memoria compartida

# SINOPSIS
**uno**

# DESCRIPCIÓN
**uno** se encarga de levantar un proceso que inicia la memoria compartida para
que instancias del proceso **dos** puedan leer el contenido

# OPCIONES
**uno** no tiene opciones disponibles

# EJEMPLOS
**uno**
: muestra mensaje de que la memoria compartida está lista

# VALORES DE SALIDA
**0**
: Éxito

# AUTOR
Escrito por Andrés Isaac Biso

# COPYRIGHT
Copyright 2023 Andrés Isaac Biso

---

% DOS(1) dos 1.0.0
% Andrés Isaac Biso
% 30/04/2023

# NOMBRE
dos - lee la memoria compartida

# SINOPSIS
**dos**

# DESCRIPCIÓN
**dos** se encarga de levantar un proceso que lee la memoria compartida

## Requisitos Previos
Para que instancias del proceso **dos** puedan leer el contenido, el proceso "uno"
debe estar en ejecución

# OPCIONES
**dos** no tiene opciones disponibles

# EJEMPLOS
**dos**
: muestra contenido de la memoria compartida

# VALORES DE SALIDA
**0**
: Éxito

# AUTOR
Escrito por Andrés Isaac Biso

# COPYRIGHT
Copyright 2023 Andrés Isaac Biso
