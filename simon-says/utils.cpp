#include "utils.h"
#include <cstdlib>
#include <chrono>
#include <thread>

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(int milisegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milisegundos));
}

int generarNumeroAleatorio(int min, int max) {
    return min + (rand() % (max - min + 1));
}
