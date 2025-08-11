#include <iostream>
#include <string>
using namespace std;

// Construye la funcion de ganancia con los precios ingresados por consola
string FuncionGanancia(int precioDeVentaMesa, int precioDeVentaSilla) {
    string funcion = "Z = ";

    // Funcion para P1: Precio de Mesas
        if (precioDeVentaMesa < 0) {
        funcion += "- " + to_string(abs(precioDeVentaMesa)) + "x1";
    } else {
        funcion += to_string(precioDeVentaMesa) + "x1";
    }

    //Funcion para P2: Precio de sillas
    if (precioDeVentaSilla >= 0) {
        funcion += " + " + to_string(precioDeVentaSilla) + "x2";
    } else {
        funcion += " - " + to_string(abs(precioDeVentaSilla)) + "x2";
    }

    return funcion;
}