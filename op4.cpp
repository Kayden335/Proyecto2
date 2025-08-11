#include <iostream>
#include <iomanip>
#include "Datoscompartidos.h"

using namespace std;
int puntoOptimoMesas = 0;
int puntoOptimoSillas = 0;
double gananciaOptima = 0.0;


// Esta función calcula y muestra la solución óptima del problema
void calcularSolucionOptima(double precioDeVentaMesa,
                            double precioDeVentaSilla,
                            int coeficienteMesaHoras,
                            int coeficienteSillaHoras)
{
    try {
        // Validación básica
        if (precioDeVentaMesa <= 0 || precioDeVentaSilla <= 0 ||
            coeficienteMesaHoras <= 0 || coeficienteSillaHoras <= 0)
        {
            throw runtime_error("Error: Datos insuficientes o no válidos. Asegúrese de ingresar los precios y restricciones correctamente.");
        }

        // Restricciones fijas del problema
        const int maxHorasCarpinteria = 240;
        const int maxHorasPintura = 100;
        const int maxSillas = 60;

        // Ahora se usan los coeficientes ingresados por el usuario
        int mejorCantidadMesas = 0;
        int mejorCantidadSillas = 0;
        double gananciaMaxima = 0.0;

        // Búsqueda exhaustiva
        for (int mesas = 0; mesas <= maxHorasCarpinteria / coeficienteMesaHoras; mesas++)
        {
            for (int sillas = 0; sillas <= maxSillas; sillas++)
            {
                int totalCarpinteria = coeficienteMesaHoras * mesas + coeficienteSillaHoras * sillas;
                int totalPintura = 2 * mesas + 1 * sillas; // se mantiene según el enunciado

                if (totalCarpinteria <= maxHorasCarpinteria && totalPintura <= maxHorasPintura)
                {
                    double ganancia = precioDeVentaMesa * mesas + precioDeVentaSilla * sillas;

                    if (ganancia > gananciaMaxima)
                    {
                        gananciaMaxima = ganancia;
                        mejorCantidadMesas = mesas;
                        mejorCantidadSillas = sillas;
                    }
                }
            }
        }
        solucion.x1 = mejorCantidadMesas;
        solucion.x2 = mejorCantidadSillas;
        solucion.ganancia = gananciaMaxima;

        // Mostrar resultado
        cout << fixed << setprecision(2);
        cout << "\nSolución óptima:\n";
        cout << "Número de mesas a fabricar: " << mejorCantidadMesas << endl;
        cout << "Número de sillas a fabricar: " << mejorCantidadSillas << endl;
        cout << "Ganancia máxima: $" << gananciaMaxima << endl;

    } catch (exception& e) {
        cout << "Se produjo un error: " << e.what() << endl;
    }
}