#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <cstdlib> // Para rand()
#include <ctime>   // Para time()
#include <atomic>  // Para manejar el orden de llegada

std::mutex cout_mutex; // Para controlar el acceso a la salida en consola
std::atomic<int> posicion_llegada(1); // Para gestionar la llegada de los autos

void carreraAuto(int id, int M) {
    int distancia_recorrida = 0;

    while (distancia_recorrida < M) {
        // Generar distancia aleatoria (máx 10 metros) y tiempo de pausa (100-500 ms)
        int avance = rand() % 11; // Aleatorio entre 0 y 10
        int pausa = 100 + rand() % 401; // Aleatorio entre 100 y 500 ms

        // Avanzar el auto
        distancia_recorrida += avance;
        if (distancia_recorrida > M) distancia_recorrida = M;

        // Imprimir el progreso del auto (usamos un mutex para evitar que se mezcle la salida de varios autos)
        {
            std::lock_guard<std::mutex> guard(cout_mutex);
            std::cout << "Auto" << id << " avanza " << avance << " metros (total: " << distancia_recorrida << " metros)\n";
        }

        // Pausar la hebra (simular la velocidad)
        std::this_thread::sleep_for(std::chrono::milliseconds(pausa));
    }

    // Auto termina la carrera
    {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << "Auto" << id << " termina la carrera en el lugar " << posicion_llegada++ << "!\n";
    }
}

int main(int argc, char* argv[]) {
    // Validar argumentos
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <distancia_total> <num_autos>\n";
        return 1;
    }

    int M = std::stoi(argv[1]);  // Distancia total
    int N = std::stoi(argv[2]);  // Número de autos

    srand(time(0)); // Inicializar semilla para números aleatorios

    std::vector<std::thread> autos;
    for (int i = 0; i < N; ++i) {
        autos.push_back(std::thread(carreraAuto, i, M));
    }

    // Esperar a que todas las hebras terminen
    for (auto& auto_thread : autos) {
        auto_thread.join();
    }

    std::cout << "¡La carrera ha terminado!\n";
    return 0;
}
