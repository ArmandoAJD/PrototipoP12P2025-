//Armando José De León Ovando
//9959-24-155

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Equipo {
private:
    std::string nombre;
    std::vector<int> puntuaciones;

public:
    Equipo(std::string nombre) : nombre(nombre) {
        puntuaciones.resize(4, 0); // Años 2020 a 2023
    }

    void generarPuntuacionesAleatorias() {
        for (int &p : puntuaciones) {
            p = rand() % 51; // De 0 a 50
        }
    }

    double calcularPromedio() const {
        int suma = 0;
        for (int p : puntuaciones) suma += p;
        return static_cast<double>(suma) / puntuaciones.size();
    }

    int obtenerPuntuacionMayor() const {
        int mayor = puntuaciones[0];
        for (int p : puntuaciones) if (p > mayor) mayor = p;
        return mayor;
    }

    int obtenerPuntuacionMenor() const {
        int menor = puntuaciones[0];
        for (int p : puntuaciones) if (p < menor) menor = p;
        return menor;
    }

    std::string getNombre() const { return nombre; }

    std::vector<int> getPuntuaciones() const { return puntuaciones; }
};

class Liga {
private:
    std::string nombre;
    std::vector<Equipo> equipos;

public:
    Liga(std::string nombre) : nombre(nombre) {}

    void inicializarEquipos() {
        for (int i = 1; i <= 5; ++i) {
            Equipo e(nombre + "_Equipo" + std::to_string(i));
            e.generarPuntuacionesAleatorias();
            equipos.push_back(e);
        }
    }

    void mostrarDatos() const {
        std::cout << "Liga: " << nombre << std::endl;
        for (const auto& eq : equipos) {
            std::cout << eq.getNombre() << ": ";
            for (int p : eq.getPuntuaciones()) std::cout << p << " ";
            std::cout << " | Promedio: " << eq.calcularPromedio() << std::endl;
        }
    }

    double promedioGeneral() const {
        double suma = 0;
        for (const auto& eq : equipos) {
            suma += eq.calcularPromedio();
        }
        return suma / equipos.size();
    }

    std::string equipoConMayorPuntaje() const {
        double maxProm = -1;
        std::string nombreEq;
        for (const auto& eq : equipos) {
            double prom = eq.calcularPromedio();
            if (prom > maxProm) {
                maxProm = prom;
                nombreEq = eq.getNombre();
            }
        }
        return nombreEq;
    }

    std::string equipoConMenorPuntaje() const {
        double minProm = 999;
        std::string nombreEq;
        for (const auto& eq : equipos) {
            double prom = eq.calcularPromedio();
            if (prom < minProm) {
                minProm = prom;
                nombreEq = eq.getNombre();
            }
        }
        return nombreEq;
    }

    std::string getNombre() const {
        return nombre;
    }
};

int main() {
    srand(time(0));
    char continuar;
    double mejorPromedio = 0;
    std::string mejorLigaNombre;

    do {
        std::vector<Liga> ligas = {
            Liga("LigaNacional"),
            Liga("LigaAscenso"),
            Liga("LigaMetropolitana")
        };

        for (auto& liga : ligas) {
            liga.inicializarEquipos();
            liga.mostrarDatos();
            std::cout << "Promedio General de la liga: " << liga.promedioGeneral() << std::endl;
            std::cout << "Mejor equipo: " << liga.equipoConMayorPuntaje() << std::endl;
            std::cout << "Peor equipo: " << liga.equipoConMenorPuntaje() << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }

        for (const auto& liga : ligas) {
            if (liga.promedioGeneral() > mejorPromedio) {
                mejorPromedio = liga.promedioGeneral();
                mejorLigaNombre = liga.getNombre();
            }
        }

        std::cout << "¿Desea repetir el proceso? (s/n): ";
        std::cin >> continuar;
    } while (continuar == 's' || continuar == 'S');

    std::cout << "\nLa mejor liga de todas las iteraciones fue: " << mejorLigaNombre << std::endl;
    std::cout << "Con un promedio de: " << mejorPromedio << std::endl;

    return 0;
}
