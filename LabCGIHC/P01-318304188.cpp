#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

// Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
float red = 0.0f, green = 0.0f, blue = 1.0f;
GLuint VAO, VBO, shader;
GLuint vertexCount = 54; // Total de triángulos para todas las letras

// Vertex Shader
static const char* vShader = R"(
#version 330
layout (location = 0) in vec3 pos;
void main() {
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
}
)";

// Fragment Shader
static const char* fShader = R"(
#version 330
out vec4 color;
void main() {
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)";

// Vértices para las letras L, A y C
GLfloat vertices[] = {
    // Letra L
        //Triángulo 1
        -0.63f, 0.79f, 0.0f,
        -0.63f,0.23f, 0.0f,
        -0.45f, 0.23f, 0.0f,
        //Triángulo 2
        -0.45f, 0.79f, 0.0f,
        -0.63f,0.79f, 0.0f,
        -0.45, 0.23f, 0.0f,
        //Triángulo 3
        -0.45f, 0.23f, 0.0f,
        -0.45f,0.35f, 0.0f,
        -0.25, 0.23f, 0.0f,
        //Triángulo 4
        -0.45f,0.35f, 0.0f,
        -0.25f,0.23f, 0.0f,
        -0.25, 0.35f, 0.0f,

    // Letra A
        //Triángulo 1
        0.6f, 0.69f, 0.0f,
        0.4f,0.69f, 0.0f,
        0.19f, 0.13f, 0.0f,
        //Triángulo 2
        0.19f, 0.13f, 0.0f,
        0.37f,0.13f, 0.0f,
        0.49, 0.53f, 0.0f,
        //Triángulo 3
        0.63f, 0.13f, 0.0f,
        0.8f,0.13f, 0.0f,
        0.6f, 0.69f, 0.0f,
        //Triángulo 4
        0.6f, 0.69f, 0.0f,
        0.63f,0.13f, 0.0f,
        0.49f, 0.53f, 0.0f,
        //Triángulo 5
        0.44f, 0.35f, 0.0f,
        0.4f,0.22f, 0.0f,
        0.55f, 0.35f, 0.0f,
        //Triángulo 6
        0.59f, 0.22f, 0.0f,
        0.55f,0.35f, 0.0f,
        0.4f, 0.22f, 0.0f,

    // Letra C
        //Triángulo 1
        -0.19f, -0.21f, 0.0f,
        -0.19f,-0.31f, 0.0f,
        -0.76f, -0.21f, 0.0f,
        //Triángulo 2
        -0.19f, -0.31f, 0.0f,
        -0.76f,-0.31f, 0.0f,
        -0.76, -0.21f, 0.0f,
        //Triángulo 3
        -0.76f, -0.21f, 0.0f,
        -0.76f,-0.79f, 0.0f,
        -0.88, -0.21f, 0.0f,
        //Triángulo 4
        -0.88f, -0.21f, 0.0f,
        -0.76f,-0.79f, 0.0f,
        -0.88, -0.89f, 0.0f,
        //Triángulo 5
        -0.88f, -0.89f, 0.0f,
        -0.76f,-0.79f, 0.0f,
        -0.19, -0.89f, 0.0f,
        //Triángulo 6
        -0.19f, -0.79f, 0.0f,
        -0.76f,-0.79f, 0.0f,
        -0.19, -0.89f, 0.0f,
};

// Crear triángulo
void CrearTriangulo() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// Agregar shader
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);
    glShaderSource(theShader, 1, &shaderCode, NULL);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error al compilar el shader %d: %s\n", shaderType, eLog);
        return;
    }
    glAttachShader(theProgram, theShader);
}

// Compilar shaders
void CompileShaders() {
    shader = glCreateProgram();
    if (!shader) {
        printf("Error creando el shader\n");
        return;
    }
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error al linkear el shader: %s\n", eLog);
        return;
    }
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error al validar el shader: %s\n", eLog);
        return;
    }
}

int main() {
    // Inicialización de GLFW
    if (!glfwInit()) {
        printf("Falló inicializar GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Práctica 1", NULL, NULL);
    if (!mainWindow) {
        printf("Fallo en crearse la ventana con GLFW\n");
        glfwTerminate();
        return 1;
    }

    int BufferWidth, BufferHeight;
    glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);
    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("Falló inicialización de GLEW\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glViewport(0, 0, BufferWidth, BufferHeight);

    CrearTriangulo();
    CompileShaders();

    // Inicializar la semilla del generador de códigos RGB aleatorios
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Generar un primer color aleatorio (formato RGB)
    red = static_cast<float>(std::rand() % 100) / 100.0f;
    green = static_cast<float>(std::rand() % 100) / 100.0f;
    blue = static_cast<float>(std::rand() % 100) / 100.0f;

    // Variables para manejar el tiempo
    float lastTime = 0.0f;
    float currentTime = 0.0f;

    // Bucle principal
    while (!glfwWindowShouldClose(mainWindow)) {
        currentTime = glfwGetTime();
        if (currentTime - lastTime >= 2.0f) {
            lastTime = currentTime;
            // Cambiar color de fondo
            red = static_cast<float>(std::rand() % 100) / 100.0f;
            green = static_cast<float>(std::rand() % 100) / 100.0f;
            blue = static_cast<float>(std::rand() % 100) / 100.0f;
        }

        glfwPollEvents();

        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);

        glUseProgram(0);
        glfwSwapBuffers(mainWindow);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}
