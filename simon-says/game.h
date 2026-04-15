#pragma once
#include <vector>
#include <string>

struct EstadoJuego {
    std::vector<int> secuencia;
    int rondaActual;
    bool enJuego;
};

std::string obtenerNivelDificultad(int ronda);
int obtenerVelocidad(int ronda);

void iniciarJuego();
void mostrarSecuencia(const EstadoJuego& estado);
std::vector<int> leerRespuestaJugador(int longitud);
bool verificarRespuesta(const EstadoJuego& estado, const std::vector<int>& respuesta);
