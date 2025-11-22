#include <iostream>
#include <string>
#include <windows.h>
#include "../include/ProcesoPar.h"

static DWORD WINAPI hiloEscucha(LPVOID parametro) {
    ProcesoPar_t* p = (ProcesoPar_t*)parametro;

    char buffer[1024];
    DWORD leidos;

    while (true) {
        BOOL ok = ReadFile(p->pipeLecturaPadre, buffer, sizeof(buffer), &leidos, NULL);
        if (!ok || leidos == 0) break;

        if (p->funcionEscucha)
            p->funcionEscucha(buffer, leidos);
    }
    return 0;
}

Estado_t lanzarProcesoPar(const char *nombreArchivoEjecutable,
                          const char **listaLineaComando,
                          ProcesoPar_t **procesoPar)
{
    if (!nombreArchivoEjecutable) return E_PAR_INC;

    ProcesoPar_t* p = new ProcesoPar_t();
    p->funcionEscucha = NULL;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;

    // PIPE para Hijo → Padre (Padre LEE, Hijo ESCRIBE)
    if (!CreatePipe(&p->pipeLecturaPadre, &p->pipeEscrituraHijo, &sa, 0))
        return E_ERROR_PIPE;

    // Evitar que el padre herede su lado de escritura
    SetHandleInformation(p->pipeLecturaPadre, HANDLE_FLAG_INHERIT, 0);

    // PIPE para Padre → Hijo (Padre ESCRIBE, Hijo LEE)
    if (!CreatePipe(&p->pipeLecturaHijo, &p->pipeEscrituraPadre, &sa, 0))
        return E_ERROR_PIPE;

    // Evitar que el padre herede su lado de escritura
    SetHandleInformation(p->pipeEscrituraPadre, HANDLE_FLAG_INHERIT, 0);

    // --- Construir ruta absoluta del ejecutable hijo ---
    CHAR ruta[MAX_PATH];
    GetFullPathNameA(nombreArchivoEjecutable, MAX_PATH, ruta, NULL);

    std::string cmd = ruta;
    for (int i = 0; listaLineaComando[i] != NULL; i++) {
        cmd += " ";
        cmd += listaLineaComando[i];
    }

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    si.dwFlags = STARTF_USESTDHANDLES;

    // LO MÁS IMPORTANTE:
    si.hStdInput  = p->pipeLecturaHijo;      // Hijo lee aquí
    si.hStdOutput = p->pipeEscrituraHijo;    // Hijo escribe aquí
    si.hStdError  = p->pipeEscrituraHijo;

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    BOOL ok = CreateProcessA(
        NULL,
        (LPSTR)cmd.c_str(),
        NULL,
        NULL,
        TRUE,  // permitir herencia
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!ok) {
        std::cout << "Error CreateProcessA: " << GetLastError() << std::endl;
        return E_ERROR_PROCESS;
    }

    p->proceso = pi.hProcess;
    p->hilo    = pi.hThread;

    // El padre cierra LOS EXTREMOS QUE NO USA
    CloseHandle(p->pipeLecturaHijo);    // padre no necesita leer desde aquí
    CloseHandle(p->pipeEscrituraHijo);  // padre no escribe en salida hijo

    // Crear hilo de escucha
    CreateThread(NULL, 0, hiloEscucha, p, 0, NULL);

    *procesoPar = p;
    return E_OK;
}
