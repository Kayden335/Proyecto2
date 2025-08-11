#include <iostream>
#include <string>
#include "Datoscompartidos.h"
using namespace std;

// Verifica si el operador ingresado es válido para una inecuación
bool Esinnecuacionvalida(const string& simbolo) {
    return simbolo == "<=" || simbolo == ">=";
}

// Función que permite ingresar restricciones de producción
void ingresarRestricciones(int &coeficienteMesaHoras, int &coeficienteSillaHoras, string &Operador, int &Terminoindependiente) {
    // Solicita el coeficiente de horas para mesas, debe ser positivo
    do {
        cout << "Ingrese el coeficiente de horas de carpinteria por cada MESA: ";
        cin >> coeficienteMesaHoras;
        if (coeficienteMesaHoras < 0)
            cout << "El coeficiente debe ser un valor positivo.\n";
    } while (coeficienteMesaHoras < 0);

    // Solicita el coeficiente de horas para sillas, debe ser positivo
    do {
        cout << "Ingrese el coeficiente de horas de carpinteria por cada SILLA: ";
        cin >> coeficienteSillaHoras;
        if (coeficienteSillaHoras < 0)
            cout << "El coeficiente debe ser un valor positivo.\n";
    } while (coeficienteSillaHoras < 0);

    // Solicita el operador de la restricción (solo acepta <= o >=)
    do {
        cout << "Ingrese el operador de su condicion (<= o >=): ";
        cin >> Operador;
        if (!Esinnecuacionvalida(Operador))
            cout << "El operador debe ser valido.\n";
    } while (!Esinnecuacionvalida(Operador));

    // Solicita el término independiente, debe ser positivo
    do {
        cout << "Ingrese el termino independiente de su condicion: ";
        cin >> Terminoindependiente;
        if (Terminoindependiente < 0)
            cout << "El término independiente debe ser un valor positivo.\n";
    } while (Terminoindependiente < 0);

    // Crea una estructura de inecuación y la agrega al vector de restricciones
    InecuacionLineal ineq;
    ineq.coeficientes = {static_cast<double>(coeficienteMesaHoras), static_cast<double>(coeficienteSillaHoras)};
    ineq.operador = Operador;
    ineq.Terminoindependiente = Terminoindependiente;

    restriccionesRegistradas.push_back(ineq);

    // Muestra la restricción registrada al usuario
    cout << "\nRestricciones registradas correctamente:\n";
    cout << "Mesa: " << coeficienteMesaHoras << " h de carpinteria\n";
    cout << "Silla: " << coeficienteSillaHoras << " h de carpinteria\n";
    cout << "Su restriccion es: " << coeficienteMesaHoras << "X1 + " << coeficienteSillaHoras << "X2 " << Operador << " " << Terminoindependiente << endl;
}