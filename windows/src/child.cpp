#include <iostream>
#include <string>
#include <windows.h>

int main() {

    char buffer[256];
    DWORD leidos;

    while (ReadFile(GetStdHandle(STD_INPUT_HANDLE), buffer, sizeof(buffer), &leidos, NULL)) {
        if (leidos > 0) {
            std::string msg(buffer, leidos);

            std::string respuesta = "Recibido: " + msg;

            DWORD escritos;
            WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),
                      respuesta.c_str(),
                      respuesta.size(),
                      &escritos,
                      NULL);
        }
    }

    return 0;
}
