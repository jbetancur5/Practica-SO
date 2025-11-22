#include "../include/ProcesoPar.h"

Estado_t enviarMensajeProcesoPar(ProcesoPar_t *procesoPar,
                                 const char *mensaje,
                                 int longitud)
{
    if (!procesoPar || !mensaje) return E_PAR_INC;

    DWORD escritos;
    BOOL ok = WriteFile(procesoPar->pipeEscrituraPadre, mensaje, longitud, &escritos, NULL);

    return ok ? E_OK : E_ERROR_WRITE;
}
