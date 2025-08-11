#include <iostream>
#include "op4.h"
#include "op2.h"
#include "op3.h"
#include "op5.h"
#include <string>
#include <limits>
#include "Datoscompartidos.h"
using namespace std;

// Definición ÚNICA de las variables globales
vector<InecuacionLineal> restriccionesRegistradas;
SolucionOptima solucion;

bool esNegativo(double precioDeVenta) {
    return precioDeVenta < 0;
}

int main() {
    int opcion, coeficienteSillaHoras = 0, coeficienteMesaHoras = 0, Terminoindependiente = 0;
    double precioDeVentaSilla = 0, precioDeVentaMesa = 0;
    string Operador, OpcionRepetir;

    do {
        cout << "\n*******MENU********" << endl;
        cout << "Opcion 1: Ingreso de precios de venta" << endl;
        cout << "Opcion 2: Ingreso de restricciones de produccion" << endl;
        cout << "Opcion 3: Ingreso de la funcion de ganancia" << endl;
        cout << "Opcion 4: Calculo de la solucion optima" << endl;
        cout << "Opcion 5: Solucion grafica del problema de optimizacion" << endl;
        cout << "Opcion 6: Salir del programa" << endl;

        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida. Por favor, ingrese un número entre 1 y 6: ";
        }

        switch (opcion) {
        case 1:
            cout << "Ingrese el precio de venta de las sillas" << endl;
            do {
                cin >> precioDeVentaSilla;
                if (esNegativo(precioDeVentaSilla)) {
                    cout << "El precio debe ser positivo\n";
                }
            } while (precioDeVentaSilla < 0);

            cout << "Ingrese el precio de venta de las mesas" << endl;
            do {
                cin >> precioDeVentaMesa;
                if (esNegativo(precioDeVentaMesa)) {
                    cout << "El precio debe ser positivo\n";
                }
            } while (precioDeVentaMesa < 0);

            cout << "Los precios fueron registrados: Mesas USD " << precioDeVentaMesa << " y sillas USD " << precioDeVentaSilla << endl;
            break;
        case 2:
            do {
                ingresarRestricciones(coeficienteMesaHoras, coeficienteSillaHoras, Operador, Terminoindependiente);
                cout << "\nDesea Ingresar otra innecuacion?(S/N)";
                cin >> OpcionRepetir;
                while (OpcionRepetir != "S" && OpcionRepetir != "s" && OpcionRepetir != "N" && OpcionRepetir != "n") {
                    cout << "Ingrese una opción válida (S/N): ";
                    cin >> OpcionRepetir;
                }
            } while (OpcionRepetir == "S" || OpcionRepetir == "s");
            break;
        case 3:
            try {
                cout << "Funcion de Ganancia (Z = P1x1 + P2x2). P1: Precio de Mesa. P2: Precio de Silla.\n";
                string funcionObjetivo = FuncionGanancia(static_cast<int>(precioDeVentaMesa), static_cast<int>(precioDeVentaSilla));
                cout << "Funcion de ganancia a maximizar obtenida: " << funcionObjetivo << endl;
            } catch (...) {
                cout << "Se produjo un error durante la ejecucion.\n";
            }
            break;
        case 4:
            calcularSolucionOptima(precioDeVentaMesa, precioDeVentaSilla, coeficienteMesaHoras, coeficienteSillaHoras);
            break;
        case 5:
            graficarMaximizacion();
            break;
        case 6:
            cout << "Gracias por usar el programa" << endl;
            break;
        default:
            cout << "La opcion debe estar entre 1 y 6" << endl;
        }
    } while (opcion != 6);

    return 0;
}