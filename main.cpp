#include <iostream>      
#include "op4.cpp"      
#include "op2.cpp"      
#include "op3.cpp"      
#include "op5.cpp"      
#include <string>       
#include <limits>       
#include "Datoscompartidos.h" 
using namespace std;


// Variable global para almacenar la solución óptima
SolucionOptima solucion = {0, 0, 0.0};

// Verifica si el precio de venta es negativo
bool esNegativo(double precioDeVenta){
    if(precioDeVenta<0){
        return true;
    }
    return false;
}


int main()
{

    //se declaran las variables que se van a utilizar
    int opcion, coeficienteSillaHoras, coeficienteMesaHoras, Terminoindependiente; 
    double precioDeVentaSilla, precioDeVentaMesa;
    string Operador, OpcionRepetir;

    do
    {
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

        switch (opcion)
        {
        case 1:
        {   
            cout<<"Ingrese el precio de venta de las sillas"<<endl;    
            
            do{
                cin>>precioDeVentaSilla;
                if(esNegativo(precioDeVentaSilla)){

    // Se declaran las variables que se van a utilizar en el menú principal
    int opcion, coeficienteSillaHoras, coeficienteMesaHoras, Terminoindependiente; 
    double precioDeVentaSilla, precioDeVentaMesa;
    string Operador, OpcionRepetir;

    do {
        // Menú principal de opciones
        cout << "\n*******MENU********" << endl;
        cout << "Opcion 1: Ingreso de precios de venta" << endl;
        cout << "Opcion 2: Ingreso de restricciones de produccion" << endl;
        cout << "Opcion 3: Ingreso de la funcion de ganancia" << endl;
        cout << "Opcion 4: Calculo de la solucion optima" << endl;
        cout << "Opcion 5: Solucion grafica del problema de optimizacion" << endl;
        cout << "Opcion 6: Salir del programa" << endl;

        // Validación de entrada para la opción del menú
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida. Por favor, ingrese un número entre 1 y 6: ";
        }

        switch (opcion)
        {
        case 1:
        {   // Ingreso de precios de venta
            cout << "Ingrese el precio de venta de las sillas" << endl;    
            do {
                cin >> precioDeVentaSilla;
                if (esNegativo(precioDeVentaSilla)) {
                    cout << "El precio debe ser positivo";
                }
            } while (precioDeVentaSilla < 0);

            cout << "Ingrese el precio de venta de las mesas" << endl;    
            do {
                cin >> precioDeVentaMesa;
                if (esNegativo(precioDeVentaMesa)) {
                    cout << "El precio debe ser positivo";
                }
            } while (precioDeVentaMesa < 0);

            cout << "Los precios fueron registrados: Mesas USD " << precioDeVentaMesa << " y sillas USD " << precioDeVentaSilla << endl;
        }
        break;
        case 2:
        {   // Ingreso de restricciones de producción
            do {
                ingresarRestricciones(coeficienteMesaHoras, coeficienteSillaHoras, Operador, Terminoindependiente);
                cout << "\nDesea Ingresar otra innecuacion?(S/N)";
                cin >> OpcionRepetir; 
                do {
                    if (OpcionRepetir != "S" && OpcionRepetir != "s" && OpcionRepetir != "N" && OpcionRepetir != "n") {
                        cout << "Ingrese una opción válida (S/N): ";
                        cin >> OpcionRepetir;
                    }
                } while (OpcionRepetir != "S" && OpcionRepetir != "s" && OpcionRepetir != "N" && OpcionRepetir != "n");
            } while (OpcionRepetir == "S" || OpcionRepetir == "s");
        }
        break;
        case 3:
        {   // Muestra la función de ganancia construida
            try {
                cout << "Funcion de Ganancia (Z = P1x1 + P2x2). P1: Precio de Mesa. P2: Precio de Silla.\n";
                string funcionObjetivo = FuncionGanancia(precioDeVentaMesa, precioDeVentaSilla);
                cout << "Funcion de ganancia a maximizar obtenida: " << funcionObjetivo << endl;
            } catch (...) {
                cout << "Se produjo un error durante la ejecucion.\n";
            }
        }
        break;
        case 4:
        {   // Calcula la solución óptima del problema
            calcularSolucionOptima(precioDeVentaMesa,
                                  precioDeVentaSilla,
                                  coeficienteMesaHoras,
                                  coeficienteSillaHoras);
        }
        break;
        case 5:
        {   // Muestra la solución gráfica
            graficarMaximizacion();
        }
        break;
        case 6:
        {   // Sale del programa
            cout << "Gracias por usar el programa" << endl;
        }
        break;
        default:
        {   // Opción inválida
            cout << "La opcion debe estar entre 1 y 6" << endl;
        }
        }

    } while (opcion != 6);

    return 0;
}