IMPLEMENTACIÓN DE PROCESO PAR (WINDOWS)

Este directorio contiene la implementación completa del módulo Proceso Par para Windows utilizando funciones de la API de Win32 (WinAPI).

LA IMPLEMENTACIÓN CUMPLE:
- Creación del proceso hijo
- Redirección de STDIN y STDOUT hacia tuberías
- Comunicación full-duplex
- Listener asíncrono en un hilo separado
- Biblioteca estática generada mediante Makefile

📁 Estructura del directorio
windows/
   include/
        ProcesoPar.h        → API pública del módulo
   lib/
        libprocesopar.a     → Biblioteca generada por el Makefile
   src/
        lanzarProcesoPar.cpp
        enviarMensajeProcesoPar.cpp
        establecerFuncionDeEscucha.cpp
        destruirProcesoPar.cpp
        child.cpp
        test.cpp
        Makefile

1. REQUERIMIENTOS
- Para compilar en Windows se utiliza:
- MSYS2 MinGW64
- g++ versión 15.2.0 o superior
- Path configurado automáticamente por MSYS2

2. COMO COMPILAR LA BIBLIOTECA
- Desde MSYS2 MinGW64, navegar a la carpeta src:
cd "C:/Users/Asus/Documents/Sistemas operativos/Práctica/windows/src"
make
-El Makefile generará:
../lib/libprocesopar.a

3. COMPILAR LOS PROGRAMAS DE PRUEBA
- Ejecutar:
g++ test.cpp ../lib/libprocesopar.a -o test.exe
g++ child.cpp -o child.exe
- Esto genera:
test.exe (proceso padre)
child.exe (proceso hijo)

4. EJECUTAR LA PRUEBA
- ./test.exe
- Salida esperada:
[B → A] Recibido: Hola hijo

Esta salida demuestra que:
- El padre puede escribir al hijo
- El hijo puede leer y responder
- El listener asíncrono funciona
- Las tuberías están funcionando correctamente

5. DESCRIPCIÓN DE ARCHIVOS PRINCIPALES
- ProcesoPar.h

Define:
- Estado_t
- ProcesoPar_t

Firmas de:
- lanzarProcesoPar
- enviarMensajeProcesoPar
- establecerFuncionDeEscucha
- destruirProcesoPar
- lanzarProcesoPar.cpp

Responsable de:
- Crear dos tuberías anónimas
- Configurar handles heredables
- Configurar STARTUPINFOA con redirección de STDIN/STDOUT
- Llamar a CreateProcessA
- Crear un hilo que ejecuta el listener
- enviarMensajeProcesoPar.cpp
Envia un mensaje del padre al hijo escribiendo en la tubería "padre → hijo".
- establecerFuncionDeEscucha.cpp
Permite asignar la función callback que se ejecuta cuando se recibe un mensaje desde el hijo.
- destruirProcesoPar.cpp
Cierra handles, mata el proceso si es necesario y libera memoria.


child.cpp

Lectura:
- ReadFile(STD_INPUT_HANDLE, ...)

Respuesta:
- WriteFile(STD_OUTPUT_HANDLE, ...)


test.cpp

Ejemplo básico que:
- Lanza el hijo
- Define una función de escucha
- Envía mensajes
- Recibe la respuesta desde el listener

✔ IMPLEMENTACIÓN COMPLETADA

Toda la funcionalidad está operativa:
- Comunicación full-duplex
- Proceso hijo ejecutando correctamente
- Librería estática
- Código modular
- Makefile funcionando
- Pruebas exitosas

FIN DEL DOCUMENTO
- Implementación para Windows — Práctica #1