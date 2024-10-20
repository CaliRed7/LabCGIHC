#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getmuevehelicoptero() { return muevehelicoptero; }
	//devuelven los valores de rotaci�n sobre los ejes X, Y y Z:
	GLfloat getrotay() { return rotay; }
	GLfloat getrotax() { return rotax; }
	GLfloat getrotaz() { return rotaz; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	GLboolean getLuzSuiche() { return LuzSuiche; }
	GLfloat getarticulacion1() { return articulacion1; }
	GLfloat getarticulacion2() { return articulacion2; }
	GLfloat getarticulacion3() { return articulacion3; }
	GLfloat getarticulacion4() { return articulacion4; }
	GLfloat getarticulacion5() { return articulacion5; }
	GLfloat getarticulacion6() { return articulacion6; }
	GLfloat getarticulacion7() { return articulacion7; }
	GLfloat getarticulacion8() { return articulacion8; }
	GLfloat getarticulacion9() { return articulacion9; }
	GLfloat getarticulacion10() { return articulacion10; }
	GLfloat getarticulacion11() { return articulacion11; }
	GLboolean getempezar() { return empezar; }
	//devuelven el estado de los interruptores booleanos que controlan distintos aspectos de la interacci�n:
	GLboolean getTURN_ON_OFF() { return TURN_ON_OFF; }
	GLboolean getTURN_ON_OFF2() { return TURN_ON_OFF2; }
	GLboolean getTURN_ON_OFF3() { return TURN_ON_OFF3; }
	GLboolean getTURN_ON_OFF4() { return TURN_ON_OFF4; }

	~Window();
private: 
	GLboolean TURN_ON_OFF;
	GLboolean TURN_ON_OFF2;
	GLboolean TURN_ON_OFF3;
	GLboolean TURN_ON_OFF4;
	GLboolean LuzSuiche;
	GLboolean empezar;
	GLFWwindow *mainWindow;
	GLint width, height;
	GLfloat rotax, rotay, rotaz, articulacion1, articulacion2, articulacion3, articulacion4, articulacion5, articulacion6, articulacion7, articulacion8, articulacion9, articulacion10, articulacion11, articulacion12;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat muevehelicoptero;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};