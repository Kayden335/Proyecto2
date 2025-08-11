#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "Datoscompartidos.h"

// Constantes para límites y escala del gráfico
const float LIMITE_GRAFICO_X = 150;
const float LIMITE_GRAFICO_Y = 150;
const float SCALE = 5.f;

// Verifica si el punto (x, y) cumple todas las restricciones ingresadas
bool cumpleTodasLasRestricciones(float x, float y) {
    for (const auto& ineq : restriccionesRegistradas) {
        double a = ineq.coeficientes[0];
        double b = ineq.coeficientes[1];
        double c = ineq.Terminoindependiente;
        if (a * x + b * y > c)
            return false;
    }
    return true;
}

// Función principal para graficar la maximización y mostrar la región factible
void graficarMaximizacion() {
    // Verifica si hay restricciones antes de graficar
    if (restriccionesRegistradas.empty()) {
        std::cout << "No hay restricciones ingresadas.\nPor favor ingrese datos antes de graficar.\n";
        return;
    }

    // Crea la ventana de gráficos
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Grafica de Maximización");

    // Carga la fuente para etiquetas
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "No se pudo cargar la fuente 'arial.ttf'.\n";
        return;
    }

    // Define el origen de los ejes en la ventana
    sf::Vector2f origin(50, 750);

    // Función para convertir coordenadas matemáticas a pantalla
    auto toScreen = [&](float x, float y) {
        return sf::Vector2f(origin.x + x * SCALE, origin.y - y * SCALE);
    };

    // Dibuja los ejes X y Y
    sf::Vertex xAxis[] = {
        sf::Vertex(toScreen(0, 0), sf::Color::White),
        sf::Vertex(toScreen(LIMITE_GRAFICO_X, 0), sf::Color::White)
    };
    sf::Vertex yAxis[] = {
        sf::Vertex(toScreen(0, 0), sf::Color::White),
        sf::Vertex(toScreen(0, LIMITE_GRAFICO_Y), sf::Color::White)
    };

    // Etiquetas de los ejes y valores
    std::vector<sf::Text> labels;
    for (int i = 0; i <= LIMITE_GRAFICO_X; i += 10) {
        sf::Text labelX(std::to_string(i), font, 12);
        labelX.setFillColor(sf::Color::White);
        labelX.setPosition(toScreen(i, 0).x - 10, toScreen(i, 0).y + 5);
        labels.push_back(labelX);
    }
    for (int i = 0; i <= LIMITE_GRAFICO_Y; i += 10) {
        sf::Text labelY(std::to_string(i), font, 12);
        labelY.setFillColor(sf::Color::White);
        labelY.setPosition(toScreen(0, i).x - 30, toScreen(0, i).y - 8);
        labels.push_back(labelY);
    }

    // Etiquetas de los ejes principales
    sf::Text etiquetaX1("x1", font, 16);
    etiquetaX1.setFillColor(sf::Color::Yellow);
    etiquetaX1.setPosition(toScreen(LIMITE_GRAFICO_X, 0).x + 10, toScreen(LIMITE_GRAFICO_X, 0).y - 20);
    labels.push_back(etiquetaX1);

    sf::Text etiquetaX2("x2", font, 16);
    etiquetaX2.setFillColor(sf::Color::Yellow);
    etiquetaX2.setPosition(toScreen(0, LIMITE_GRAFICO_Y).x - 25, toScreen(0, LIMITE_GRAFICO_Y).y - 30);
    labels.push_back(etiquetaX2);

    // Dibuja las líneas de las restricciones
    std::vector<sf::VertexArray> lineas;
    std::vector<sf::Text> etiquetasRestricciones;

    // Define los colores para las líneas
    std::vector<sf::Color> colores = {
        sf::Color::White,
        sf::Color::Red,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color::Yellow,
        sf::Color(255, 165, 0),
        sf::Color(128, 0, 128)
    };

    // Recorre las restricciones y dibuja cada línea con su color y etiqueta
    for (size_t i = 0; i < restriccionesRegistradas.size(); ++i) {
        const auto& ineq = restriccionesRegistradas[i];
        double a = ineq.coeficientes[0];
        double b = ineq.coeficientes[1];
        double c = ineq.Terminoindependiente;

        sf::VertexArray linea(sf::Lines, 2);
        sf::Vector2f puntoMedioPantalla;

        if (b != 0) {
            float x1 = -20;
            float x2 = LIMITE_GRAFICO_X + 50;
            float y1 = (c - a * x1) / b;
            float y2 = (c - a * x2) / b;
            linea[0].position = toScreen(x1, y1);
            linea[1].position = toScreen(x2, y2);

            puntoMedioPantalla = toScreen((x1 + x2) / 2, (y1 + y2) / 2);
        } else if (a != 0) {
            float x = c / a;
            float y1 = -20;
            float y2 = LIMITE_GRAFICO_Y + 50;
            linea[0].position = toScreen(x, y1);
            linea[1].position = toScreen(x, y2);

            puntoMedioPantalla = toScreen(x, (y1 + y2) / 2);
        }

        sf::Color colorActual = colores[i % colores.size()];
        linea[0].color = colorActual;
        linea[1].color = colorActual;
        lineas.push_back(linea);

        // Etiqueta para cada restricción
        std::string etiqueta = std::to_string((int)a) + "x + " + std::to_string((int)b) + "y <= " + std::to_string((int)c);
        sf::Text textoRestriccion(etiqueta, font, 12);
        textoRestriccion.setFillColor(colorActual);
        textoRestriccion.setPosition(puntoMedioPantalla.x + 5, puntoMedioPantalla.y - 10);
        etiquetasRestricciones.push_back(textoRestriccion);
    }

    // Sombrear la región factible (donde se cumplen todas las restricciones)
    std::vector<sf::RectangleShape> sombreado;
    for (int x = 0; x < LIMITE_GRAFICO_X; ++x) {
        for (int y = 0; y < LIMITE_GRAFICO_Y; ++y) {
            if (cumpleTodasLasRestricciones(x, y)) {
                sf::RectangleShape pixel(sf::Vector2f(1.5f, 1.5f));
                pixel.setFillColor(sf::Color(255, 0, 0, 100)); // color de la región factible
                pixel.setPosition(toScreen(x, y));
                sombreado.push_back(pixel);
            }
        }
    }

    // Bucle principal de la ventana gráfica
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);

        for (auto& linea : lineas)
            window.draw(linea);
        for (auto& texto : etiquetasRestricciones)
            window.draw(texto);
        for (auto& label : labels)
            window.draw(label);
        for (auto& rect : sombreado)
            window.draw(rect);

        // Dibuja el punto óptimo como un círculo verde
        sf::CircleShape puntoOptimo(5.f);
        puntoOptimo.setFillColor(sf::Color::Green);
        puntoOptimo.setPosition(toScreen(solucion.x1, solucion.x2).x - 5,
                               toScreen(solucion.x1, solucion.x2).y - 5);
        window.draw(puntoOptimo);

        // Etiqueta para el punto óptimo
        sf::Text textoPunto("Punto óptimo (" + std::to_string(solucion.x1) + ", " +
                            std::to_string(solucion.x2) + ")", font, 14);
        textoPunto.setFillColor(sf::Color::Green);
        textoPunto.setPosition(toScreen(solucion.x1, solucion.x2).x + 10,
                              toScreen(solucion.x1, solucion.x2).y - 20);
        window.draw(textoPunto);

        window.display();
    }
}