#ifndef PROCESOPAR_H
#define PROCESOPAR_H

#include <windows.h>

typedef unsigned int Estado_t;

#define E_OK 0
#define E_PAR_INC 1
#define E_ERROR_PIPE 2
#define E_ERROR_PROCESS 3
#define E_ERROR_WRITE 4
#define E_ERROR_READ 5

typedef struct ProcesoPar {
    HANDLE pipeLecturaHijo;
    HANDLE pipeEscrituraHijo;

    HANDLE pipeLecturaPadre;
    HANDLE pipeEscrituraPadre;

    HANDLE proceso;
    HANDLE hilo;

    Estado_t (*funcionEscucha)(const char*, int);

} ProcesoPar_t;

Estado_t lanzarProcesoPar(const char *nombreArchivoEjecutable,
                          const char **listaLineaComando,
                          ProcesoPar_t **procesoPar);

Estado_t enviarMensajeProcesoPar(ProcesoPar_t *procesoPar,
                                 const char *mensaje,
                                 int longitud);

Estado_t establecerFuncionDeEscucha(ProcesoPar_t *procesoPar,
                                    Estado_t (*f)(const char*, int));

Estado_t destruirProcesoPar(ProcesoPar_t *procesoPar);

#endif
