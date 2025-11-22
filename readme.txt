Implementación de Proceso Par en Windows (WinAPI)

Este repositorio contiene la implementación completa del mecanismo Proceso Par usando tuberías anónimas y creación de procesos en Windows con la WinAPI.
Forma parte de la Práctica #1 del curso de Sistemas Operativos.

Descripción del Proyecto

Un Proceso Par es un proceso hijo que se crea desde un proceso padre y se comunica con él mediante un canal full-duplex basado en pipes.

Este proyecto implementa:

Creación del proceso hijo (CreateProcessA)

Redirección de STDIN y STDOUT

Tuberías full-duplex (CreatePipe)

Lectura asíncrona mediante un hilo (CreateThread)

Biblioteca estática reutilizable (libprocesopar.a)

Programas de prueba totalmente funcionales (test.cpp y child.cpp)

Todo está probado y funcionando correctamente.

📁 Estructura del Repositorio
´
PRACTICA/
│── README.md                → Este archivo (descripción general)
│
└── windows/
      ├── readme.txt         → Instrucciones técnicas específicas (versión .txt)
      │
      ├── include/
      │     └── ProcesoPar.h
      │
      ├── lib/
      │     └── libprocesopar.a
      │
      └── src/
            ├── lanzarProcesoPar.cpp
            ├── enviarMensajeProcesoPar.cpp
            ├── establecerFuncionDeEscucha.cpp
            ├── destruirProcesoPar.cpp
            ├── child.cpp
            ├── test.cpp
            └── Makefile
' 
⚙️ Requisitos para Compilar (Windows)

Este proyecto se compila en MSYS2 MinGW64.

Debes tener instalado:

✔ MSYS2

https://www.msys2.org/

✔ Compilador g++

Se instala automáticamente con MSYS2 al usar:

pacman -S mingw-w64-x86_64-gcc

✔ WinAPI

Incluida de forma nativa en Windows.

🔨 Cómo Compilar

Abrir MSYS2 MinGW64 y navegar a:

windows/src/

1️⃣ Compilar la biblioteca
make


Esto generará:

../lib/libprocesopar.a

2️⃣ Compilar los programas de prueba
g++ test.cpp ../lib/libprocesopar.a -o test.exe
g++ child.cpp -o child.exe

▶️ Cómo Ejecutar

Desde la carpeta src:

./test.exe


Si todo está correcto aparecerá:

[B → A] Recibido: Hola hijo


Esto demuestra que:

El padre envió un mensaje al hijo

El hijo respondió correctamente

El listener del padre recibió el mensaje

La comunicación full-duplex funciona

🧠 Explicación Conceptual
🔹 1. Tuberías full-duplex

Se crean dos pipes:

Pipe 1: padre escribe → hijo lee

Pipe 2: hijo escribe → padre lee

🔹 2. Redirección de E/S

El hijo recibe:

STDIN  = pipeLecturaHijo
STDOUT = pipeEscrituraHijo


Esto permite que:

WriteFile() del padre al pipe = input del hijo

WriteFile() del hijo a pipe = listener del padre

🔹 3. Proceso hijo

El hijo simplemente:

Lee desde STD_INPUT_HANDLE

Responde por STD_OUTPUT_HANDLE

Se mantiene vivo esperando nuevos datos

🔹 4. Listener en el padre

El padre crea un hilo que:

Llama ReadFile() de forma continua

Cada mensaje recibido ejecuta una función callback definida por el usuario

📌 Funciones Implementadas
✔ lanzarProcesoPar

Crea el proceso hijo, pipes y el hilo listener.

✔ enviarMensajeProcesoPar

Escribe datos al STDIN del hijo.

✔ establecerFuncionDeEscucha

Define la función callback que se ejecuta cuando el hijo envía datos.

✔ destruirProcesoPar

Finaliza el proceso par y libera recursos.

🧪 Programas de Prueba
test.cpp

Crea un proceso par

Configura el listener

Envía "Hola hijo"

Imprime respuesta

child.cpp

Lee desde STDIN

Responde con un mensaje formateado

Se mantiene corriendo

🏁 Estado del Proyecto

Este proyecto está:

✔ Completamente funcional
✔ Probado en Windows
✔ Ordenado según la práctica
✔ Compilado como biblioteca
✔ Con pruebas totalmente operativas

La práctica está lista para entregar y sustentar.

👤 Autor

Juanmartin Betancur
Práctica #1 – Sistemas Operativos
