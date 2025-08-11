#include <iostream>
#include <string>
#include <vector>
#include "Datoscompartidos.h"
using namespace std;


bool Esinnecuacionvalida(const string& simbolo) {
    return simbolo == "<=" || simbolo == ">=";
}

vector<InecuacionLineal> restriccionesRegistradas;

// Función que permite ingresar restricciones de producción
void ingresarRestricciones(int &coeficienteMesaHoras, int &coeficienteSillaHoras, string &Operador, int &Terminoindependiente) {
    do {
        cout << "Ingrese el coeficiente de horas de carpinteria por cada MESA: ";
        cin >> coeficienteMesaHoras;
        if (coeficienteMesaHoras < 0)
            cout << "El coeficiente debe ser un valor positivo.\n";
    } while (coeficienteMesaHoras < 0);

    do {
        cout << "Ingrese el coeficiente de horas de carpinteria por cada SILLA: ";
        cin >> coeficienteSillaHoras;
        if (coeficienteSillaHoras < 0)
            cout << "El coeficiente debe ser un valor positivo.\n";
    } while (coeficienteSillaHoras < 0);

    do
    {
      cout << "Ingrese el operador de su condicion:\n ";
        cin >> Operador;
        if (!Esinnecuacionvalida(Operador))
            cout << "El operador debe ser valido.\n";  
    } while (!Esinnecuacionvalida(Operador));
    
        do
    {
      cout << "Ingrese el termino independiente de su condicion:\n ";
        cin >> Terminoindependiente;
        if (Terminoindependiente<0)
            cout << "El operador debe ser valido.\n";  
    } while (Terminoindependiente<0);

    InecuacionLineal ineq;
    ineq.coeficientes = {static_cast<double>(coeficienteMesaHoras), static_cast<double>(coeficienteSillaHoras)};
    ineq.operador = Operador;
    ineq.Terminoindependiente = Terminoindependiente;

    restriccionesRegistradas.push_back(ineq);


    cout << "\nRestricciones registradas correctamente:\n";
    cout << "Mesa: " << coeficienteMesaHoras << " h de carpinteria\n";
    cout << "Silla: " << coeficienteSillaHoras << " h de carpinteria\n";
    cout<< "Su restriccion es: "<<coeficienteMesaHoras<<"X1 + "<<coeficienteSillaHoras<<"X2 "<<Operador<<" "<<Terminoindependiente;
}