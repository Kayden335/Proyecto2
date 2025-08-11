#ifndef DATOS_COMPARTIDOS_H
#define DATOS_COMPARTIDOS_H

#include <vector>
#include <string>
using namespace std;

// Estructura que representa una restricción lineal: ax + by <= c
struct InecuacionLineal {
    vector<double> coeficientes; // [a, b]
    string operador;             // "<=" o ">="
    int Terminoindependiente;    // c
};

// Estructura para almacenar la solución óptima
struct SolucionOptima {
    int x1;              // Cantidad óptima de mesas
    int x2;              // Cantidad óptima de sillas
    double ganancia;     // Ganancia máxima
};

// Declaración de variables compartidas
extern vector<InecuacionLineal> restriccionesRegistradas;
extern SolucionOptima solucion;

#endif
