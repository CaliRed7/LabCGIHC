#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <cmath>

// Dimensiones de la ventana
int windowHeight = 600;
int windowWidth = 800;

// Función para dibujar una circunferencia usando el algoritmo de Bresenham
void drawCircle(int centerX, int centerY, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius; // Valor inicial del discriminante

    glColor3f(0.0f, 0.0f, 1.0f); // Establece el color de la circunferencia a azul
    glBegin(GL_POINTS); // Inicia el dibujo de puntos en OpenGL
    while (x <= y) {
        // Dibujar puntos en las 8 partes simétricas del círculo
        glVertex2i(centerX + x, centerY + y); // Octante 1
        glVertex2i(centerX + x, centerY - y); // Octante 2
        glVertex2i(centerX - x, centerY + y); // Octante 3
        glVertex2i(centerX - x, centerY - y); // Octante 4
        glVertex2i(centerX + y, centerY + x); // Octante 5
        glVertex2i(centerX + y, centerY - x); // Octante 6
        glVertex2i(centerX - y, centerY + x); // Octante 7
        glVertex2i(centerX - y, centerY - x); // Octante 8

        // Actualizar el discriminante para la siguiente posición del píxel
        if (d < 0)
            d += 4 * x + 6; // Si d < 0, se selecciona el píxel del este
        else {
            d += 4 * (x - y) + 10; // Si d >= 0, se selecciona el píxel del sureste
            y -= 1;
        }
        x += 1;
    }
    glEnd(); // Finaliza el dibujo de puntos
}

// Función para dibujar los ejes X e Y
void drawAxes() {
    // Dibuja el eje X en blanco
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
    glBegin(GL_LINES);
    glVertex2i(0, windowHeight / 2);  // Punto inicial (0, centro Y)
    glVertex2i(windowWidth, windowHeight / 2);  // Punto final (ancho ventana, centro Y)
    glEnd();

    // Dibuja el eje Y en blanco
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
    glBegin(GL_LINES);
    glVertex2i(windowWidth / 2, 0);  // Punto inicial (centro X, 0)
    glVertex2i(windowWidth / 2, windowHeight);  // Punto final (centro X, alto ventana)
    glEnd();
}

// Inicializa GLFW y configura OpenGL
void init() {
    glfwInit(); // Inicializa GLFW
    // Crear la ventana y el contexto de OpenGL
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Dibujo de Circunferencia usando Bresenham", NULL, NULL);
    glfwMakeContextCurrent(window); // Establece el contexto actual
    // Configura la proyección ortográfica para coordenadas 2D
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);
    // Establecer el color de fondo en negro
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Función que realiza el renderizado en cada iteración
void display(int centerX, int centerY, int radius) {
    glClear(GL_COLOR_BUFFER_BIT); // Limpia la ventana
    glColor3f(1.0f, 1.0f, 1.0f); // Establece el color de los puntos a blanco
    glPointSize(1.0f); // Tamaño de los puntos a dibujar

    // Llama a la función para dibujar la circunferencia y los ejes
    drawCircle(centerX, centerY, radius); // Dibuja la circunferencia
    drawAxes(); // Dibuja los ejes X e Y

    // Intercambia los buffers para mostrar lo dibujado en pantalla
    glfwSwapBuffers(glfwGetCurrentContext());
}

int main() {
    init(); // Inicializar GLFW y OpenGL

    int centerX, centerY, radius;

    // Solicita las coordenadas del centro y el radio al usuario
    std::cout << "Por favor ingrese las coordenadas del centro (x y): ";
    std::cin >> centerX >> centerY;
    std::cout << "Ingrese el radio (debe ser un valor positivo): ";
    std::cin >> radius;

    // Asegurar que el radio ingresado sea mayor a 0
    while (radius <= 0) {
        std::cout << "El radio debe ser un valor positivo. Intente de nuevo: ";
        std::cin >> radius;
    }

    // Calcula el radio máximo para que la circunferencia ocupe tres cuartos de la ventana
    int maxRadius = std::min(windowWidth, windowHeight) * 3 / 8;

    // Ajusta el radio en caso de ser mayor al permitido
    radius = std::min(radius, maxRadius);

    // Bucle principal de la aplicación
    while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
        // Llama a la función de renderizado pasando las coordenadas ajustadas
        display(centerX + windowWidth / 2, centerY + windowHeight / 2, radius);
        glfwPollEvents(); // Procesa eventos de la ventana
    }

    // Finaliza GLFW antes de salir del programa
    glfwTerminate();
    return 0;
}
