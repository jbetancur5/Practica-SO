Práctica #1 – Sistemas Operativos
IMPLEMENTACIÓN DE PROCESO PAR – WINDOWS

Este proyecto desarrolla la implementación del mecanismo Proceso Par, requerido en la práctica del curso de Sistemas Operativos.
Un Proceso Par es un proceso creado por el proceso principal y conectado mediante un par de tuberías anónimas que permiten comunicación full-duplex (doble vía).

La implementación utiliza WinAPI en Windows para la creación de procesos y manejo de tuberías, cumpliendo estrictamente con los requisitos de la práctica.

📂 ESTRUCTURA DEL PROYECTO
PRACTICA/
   readme.txt              → README general del proyecto
   windows/                → Implementación específica para Windows
        include/           → Archivos .h con la API pública
        lib/               → Biblioteca generada (libprocesopar.a)
        src/               → Código fuente, objetos y Makefile
        readme.txt         → README técnico para el sistema Windows


OBJETIVO DE LA PRÁCTICA 

IMPLEMENTAR UN MÓDULO QUE PERMITA:

✔ CREEAR UN PROCESO HILO
- Usando CreateProcessA con redirección de entradas/salidas.

✔ ESTABLECER COMUNICACIÓN FULL-DUPLEX
- Mediante tuberías anónimas (CreatePipe), permitiendo:
- Padre escribe → Hijo lee
- Hijo escribe → Padre lee

✔ LISTENER ASÍNCRONO
- Captura los mensajes del hijo mediante un hilo (CreateThread) que ejecuta la función de escucha configurada por el usuario.

✔ BIBLIOTECA REUTILIZABLE
- El módulo se compila en una biblioteca estática:
libprocesopar.a


PRUEBAS INCLUIDAS

EL PROYECTO INCLUYE DOS PROGRAMAS:

test.cpp → Programa padre que crea un proceso par, le envía un mensaje y recibe la respuesta.

child.cpp → Proceso hijo que lee desde STDIN y responde por STDOUT.

✔ ESTADO DEL PROYECTO
- Todo el sistema está completamente funcional en Windows:
- Las tuberías funcionan correctamente
- La comunicación es bidireccional
- El proceso hijo se lanza correctamente
- Los mensajes se reciben mediante el listener
- La biblioteca se construye con Makefile
- La práctica cumple con todos los requerimientos formales

AUTOR:
Juanmartin Betancur
Sistemas Operativos — Práctica #1