#include "../include/ProcesoPar.h"

Estado_t destruirProcesoPar(ProcesoPar_t *procesoPar)
{
    if (!procesoPar) return E_PAR_INC;

    CloseHandle(procesoPar->pipeLecturaPadre);
    CloseHandle(procesoPar->pipeEscrituraPadre);

    TerminateProcess(procesoPar->proceso, 0);
    CloseHandle(procesoPar->proceso);
    CloseHandle(procesoPar->hilo);

    delete procesoPar;
    return E_OK;
}
