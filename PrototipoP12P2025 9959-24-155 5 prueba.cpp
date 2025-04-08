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
    std::vector<int> puntuaciones;// puntuaciones de equipos

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
        int suma = 0;   //suma de quipos
        for (int p : puntuaciones) suma += p;//puntuaciones
        return static_cast<double>(suma) / puntuaciones.size();
    }

    int obtenerPuntuacionMayor() const {
        int mayor = puntuaciones[0];//mayor puntaje
        for (int p : puntuaciones) if (p > mayor) mayor = p;
        return mayor;
    }

    int obtenerPuntuacionMenor() const {
        int menor = puntuaciones[0];//puntuaciones
        for (int p : puntuaciones) if (p < menor) menor = p;
        return menor;
    }

    std::string getNombre() const { return nombre; }

    std::vector<int> getPuntuaciones() const { return puntuaciones; }//puntuaciones
};

class Liga {
private:
    std::string nombre;
    std::vector<Equipo> equipos;//equipos

public:
    Liga(std::string nombre) : nombre(nombre) {}

    void inicializarEquipos() {
        for (int i = 1; i <= 5; ++i) {//tanto equipos hay
            Equipo e(nombre + "_Equipo" + std::to_string(i));
            e.generarPuntuacionesAleatorias();//puntuaciones aleatorias
            equipos.push_back(e);
        }
    }

    void mostrarDatos() const {
        std::cout << "Liga: " << nombre << std::endl;//nombre equipo
        for (const auto& eq : equipos) {
            std::cout << eq.getNombre() << ": ";
            for (int p : eq.getPuntuaciones()) std::cout << p << " ";//puntuacioes equipo
            std::cout << " | Promedio: " << eq.calcularPromedio() << std::endl;//promedio equipo
        }
    }

    double promedioGeneral() const {
        double suma = 0; //suma
        for (const auto& eq : equipos) {
            suma += eq.calcularPromedio();//calcular promedio equipos
        }
        return suma / equipos.size();//suma equipos
    }

    std::string equipoConMayorPuntaje() const {
        double maxProm = -1;
        std::string nombreEq;
        for (const auto& eq : equipos) {
            double prom = eq.calcularPromedio();//calcular promedio
            if (prom > maxProm) {
                maxProm = prom;//promedio maximo
                nombreEq = eq.getNombre();//nombre promedio maximo
            }
        }
        return nombreEq;
    }

    std::string equipoConMenorPuntaje() const {
        double minProm = 999;
        std::string nombreEq;
        for (const auto& eq : equipos) {
            double prom = eq.calcularPromedio();//cacular promedio
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
    double mejorPromedio = 0;  //mejo promedio
    std::string mejorLigaNombre;

    do {
        std::vector<Liga> ligas = {
            Liga("LigaNacional"),
            Liga("LigaAscenso"),                 //equipos jugando
            Liga("LigaMetropolitana")
        };

        for (auto& liga : ligas) {
            liga.inicializarEquipos();
            liga.mostrarDatos();
            std::cout << "Promedio General de la liga: " << liga.promedioGeneral() << std::endl;
            std::cout << "Mejor equipo: " << liga.equipoConMayorPuntaje() << std::endl;             //todas las partes del equipo y lo que va a decir
            std::cout << "Peor equipo: " << liga.equipoConMenorPuntaje() << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }

        for (const auto& liga : ligas) {
            if (liga.promedioGeneral() > mejorPromedio) {
                mejorPromedio = liga.promedioGeneral();//promedio general
                mejorLigaNombre = liga.getNombre();
            }
        }

        std::cout << "¿Desea repetir el proceso? (s/n): "; //repetir para ver otras respuestas
        std::cin >> continuar;
    } while (continuar == 's' || continuar == 'S');  //si quere seguir o no

    std::cout << "\nLa mejor liga de todas las iteraciones fue: " << mejorLigaNombre << std::endl;// la mejor liga de ta equipo
    std::cout << "Con un promedio de: " << mejorPromedio << std::endl;//promeido final

    return 0;
}
