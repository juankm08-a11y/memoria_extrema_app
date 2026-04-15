#include "game.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

static const std::string COLORES[] = {
    "",
    "\033[1;31m",
    "\033[1;32m",
    "\033[1;33m",
    "\033[1;34m"
};
static const std::string RESET = "\033[0m";
static const std::string NEGRITA = "\033[1m";
static const std::string CIAN = "\033[1;36m";
static const std::string AMARILLO = "\033[1;33m";
static const std::string ROJO = "\033[1;31m";
static const std::string VERDE = "\033[1;32m";

static const std::string NOMBRES[] = {"", "ROJO [1]", "VERDE [2]", "AMARILLO [3]", "AZUL [4]"};

std::string obtenerNivelDificultad(int ronda) {
    if (ronda <= 3)  return "Facil";
    if (ronda <= 7)  return "Normal";
    if (ronda <= 12) return "Dificil";
    return "Experto";
}

int obtenerVelocidad(int ronda) {
    int velocidad = 900 - (ronda - 1) * 60;
    if (velocidad < 200) velocidad = 200;
    return velocidad;
}

static void mostrarEncabezado(const EstadoJuego& estado) {
    limpiarPantalla();
    std::cout << CIAN << "╔══════════════════════════════════════╗" << RESET << "\n";
    std::cout << CIAN << "║" << RESET;
    std::cout << NEGRITA << "        SIMON SAYS - MEMORIA          " << RESET;
    std::cout << CIAN << "║" << RESET << "\n";
    std::cout << CIAN << "╠══════════════════════════════════════╣" << RESET << "\n";
    std::cout << CIAN << "║" << RESET;
    std::cout << "  Ronda:      " << AMARILLO << std::setw(3) << estado.rondaActual << RESET;
    std::cout << "  Dificultad: " << VERDE << std::setw(7) << std::left << obtenerNivelDificultad(estado.rondaActual) << RESET;
    std::cout << CIAN << "║" << RESET << "\n";
    std::cout << CIAN << "╠══════════════════════════════════════╣" << RESET << "\n";
    std::cout << CIAN << "║" << RESET;
    std::cout << "  Botones:  " << COLORES[1] << "1=ROJO" << RESET
              << "  " << COLORES[2] << "2=VERDE" << RESET
              << "  " << COLORES[3] << "3=AMARI" << RESET
              << "  " << COLORES[4] << "4=AZUL " << RESET;
    std::cout << CIAN << "║" << RESET << "\n";
    std::cout << CIAN << "╚══════════════════════════════════════╝" << RESET << "\n\n";
}

void mostrarSecuencia(const EstadoJuego& estado) {
    mostrarEncabezado(estado);
    std::cout << NEGRITA << "  >> Memoriza la secuencia:" << RESET << "\n\n";
    pausar(800);

    int velocidad = obtenerVelocidad(estado.rondaActual);

    for (int num : estado.secuencia) {
        mostrarEncabezado(estado);
        std::cout << NEGRITA << "  >> Memoriza la secuencia:" << RESET << "\n\n";

        std::cout << "     ";
        std::cout << COLORES[num] << "[ " << num << " ] " << NOMBRES[num] << RESET << "\n";

        pausar(velocidad);

        mostrarEncabezado(estado);
        std::cout << NEGRITA << "  >> Memoriza la secuencia:" << RESET << "\n\n";
        std::cout << "     " << "      " << "\n";
        pausar(200);
    }

    mostrarEncabezado(estado);
}

std::vector<int> leerRespuestaJugador(int longitud) {
    std::vector<int> respuesta;
    std::cout << NEGRITA << "  Tu turno! Ingresa la secuencia (" << longitud << " numeros, 1-4):\n" << RESET;
    std::cout << "  > ";

    for (int i = 0; i < longitud; ++i) {
        int entrada = 0;
        bool valido = false;
        while (!valido) {
            std::cin >> entrada;
            if (std::cin.fail() || entrada < 1 || entrada > 4) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << ROJO << "  Numero invalido. Ingresa 1, 2, 3 o 4: " << RESET;
            } else {
                valido = true;
            }
        }
        respuesta.push_back(entrada);
        std::cout << "  ";
        for (int j = 0; j < (int)respuesta.size(); ++j) {
            std::cout << COLORES[respuesta[j]] << respuesta[j] << RESET;
            if (j < (int)respuesta.size() - 1) std::cout << " - ";
        }
        if (i < longitud - 1) {
            std::cout << " | ";
        }
        std::cout << std::flush;
    }
    std::cout << "\n";
    return respuesta;
}

bool verificarRespuesta(const EstadoJuego& estado, const std::vector<int>& respuesta) {
    if (respuesta.size() != estado.secuencia.size()) return false;
    for (int i = 0; i < (int)estado.secuencia.size(); ++i) {
        if (respuesta[i] != estado.secuencia[i]) return false;
    }
    return true;
}

void iniciarJuego() {
    srand(static_cast<unsigned int>(time(nullptr)));

    limpiarPantalla();
    std::cout << CIAN << "\n";
    std::cout << "  ╔══════════════════════════════════════╗\n";
    std::cout << "  ║                                      ║\n";
    std::cout << "  ║        SIMON SAYS - MEMORIA          ║\n";
    std::cout << "  ║                                      ║\n";
    std::cout << "  ║  Repite la secuencia de numeros      ║\n";
    std::cout << "  ║  correctamente para avanzar.         ║\n";
    std::cout << "  ║                                      ║\n";
    std::cout << "  ║  Botones: 1 = Rojo                   ║\n";
    std::cout << "  ║           2 = Verde                  ║\n";
    std::cout << "  ║           3 = Amarillo               ║\n";
    std::cout << "  ║           4 = Azul                   ║\n";
    std::cout << "  ║                                      ║\n";
    std::cout << "  ╚══════════════════════════════════════╝\n";
    std::cout << RESET << "\n";

    std::cout << "  Presiona ENTER para comenzar...";
    std::cin.ignore(10000, '\n');
    std::cin.get();

    EstadoJuego estado;
    estado.rondaActual = 0;
    estado.enJuego = true;

    while (estado.enJuego) {
        estado.rondaActual++;
        estado.secuencia.push_back(generarNumeroAleatorio(1, 4));

        mostrarSecuencia(estado);

        std::vector<int> respuesta = leerRespuestaJugador((int)estado.secuencia.size());

        if (!verificarRespuesta(estado, respuesta)) {
            limpiarPantalla();
            std::cout << ROJO;
            std::cout << "\n  ╔══════════════════════════════════════╗\n";
            std::cout << "  ║          ERROR - JUEGO TERMINADO     ║\n";
            std::cout << "  ╚══════════════════════════════════════╝\n";
            std::cout << RESET << "\n";
            std::cout << "  La secuencia correcta era:\n  ";
            for (int i = 0; i < (int)estado.secuencia.size(); ++i) {
                int n = estado.secuencia[i];
                std::cout << COLORES[n] << n << RESET;
                if (i < (int)estado.secuencia.size() - 1) std::cout << " - ";
            }
            std::cout << "\n\n";
            std::cout << AMARILLO << "  Rondas superadas: " << NEGRITA << (estado.rondaActual - 1) << RESET << "\n";
            std::cout << AMARILLO << "  Longitud maxima:  " << NEGRITA << (estado.rondaActual - 1) << RESET << "\n";
            std::cout << AMARILLO << "  Nivel alcanzado:  " << NEGRITA << obtenerNivelDificultad(estado.rondaActual) << RESET << "\n\n";
            estado.enJuego = false;
        } else {
            mostrarEncabezado(estado);
            std::cout << VERDE << "  ✓ Correcto! Avanzando a la siguiente ronda...\n" << RESET;
            pausar(1200);
        }
    }

    char jugarDeNuevo;
    std::cout << "  Jugar de nuevo? (s/n): ";
    std::cin >> jugarDeNuevo;
    if (jugarDeNuevo == 's' || jugarDeNuevo == 'S') {
        iniciarJuego();
    } else {
        limpiarPantalla();
        std::cout << CIAN << "\n  Gracias por jugar Simon Says!\n\n" << RESET;
    }
}
