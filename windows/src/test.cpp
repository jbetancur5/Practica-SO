#include <iostream>
#include "../include/ProcesoPar.h"

Estado_t listener(const char* msg, int len) {
    std::string s(msg, len);
    std::cout << "[B → A] " << s << std::endl;
    return E_OK;
}

int main() {

    ProcesoPar_t *pp;

    const char* args[] = { NULL };

    lanzarProcesoPar("child.exe", args, &pp);

    establecerFuncionDeEscucha(pp, listener);

    enviarMensajeProcesoPar(pp, "Hola hijo\n", 11);

    Sleep(2000);

    destruirProcesoPar(pp);

    return 0;
}
