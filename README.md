# ProgramaLavadora
Gestiona Todo el mecanismo de un Lavadora
el Sitema de Hidronivel Esta Gestinado Atravez de un sensor de Presion Diferencial MPX2010DP ya como este sensor maneja una señal en milivoltios, se utilizo un LM358P, para poder manejar el rango adecuado en el Arduino A travez del pin analogo A0 y este rango se mapeo en el programa el rango de salida va desde 0v - 6volt que esta en el promedio aceptable que puede manejar comodamente el arduino uno o atmega328p
tambien se uso un Display 20x4, y este se gestina a travez de interfaz I2C
Adjuntare el esquema para el mismo Hidronivel en: Esquema para Hidronivel Digital.png
