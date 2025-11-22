#include "../include/ProcesoPar.h"

Estado_t establecerFuncionDeEscucha(ProcesoPar_t *procesoPar,
                                    Estado_t (*f)(const char*, int))
{
    if (!procesoPar) return E_PAR_INC;

    procesoPar->funcionEscucha = f;
    return E_OK;
}
