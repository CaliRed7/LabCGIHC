/*
Pr�ctica 5: Optimizaci�n y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
//Model Auto;
Model Auto_Base;
Model Auto_Cofre;
Model Auto_Llanta1;
Model Auto_Llanta2;
Model Auto_Llanta3;
Model Auto_Llanta4;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	//Goddard_M = Model();
	//Goddard_M.LoadModel("Models/goddard_base.obj");
	Auto_Base = Model();
	Auto_Base.LoadModel("Models/autobase.obj");
	Auto_Cofre = Model();
	Auto_Cofre.LoadModel("Models/autocofre.obj");
	Auto_Llanta1 = Model();
	Auto_Llanta1.LoadModel("Models/autollantaizq1.obj");
	Auto_Llanta2 = Model();
	Auto_Llanta2.LoadModel("Models/autollantader1.obj");
	Auto_Llanta3 = Model();
	Auto_Llanta3.LoadModel("Models/autollantaizq2.obj");
	Auto_Llanta4 = Model();
	Auto_Llanta4.LoadModel("Models/autollantader2.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();

		//------------*INICIA DIBUJO DE NUESTROS DEM�S OBJETOS-------------------*

//	-	//Auto Base
		color = glm::vec3(0.0f, 0.0f, 0.0f); //modelo de auto de color negro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, -1.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getrotay()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0, 0.0f, mainWindow.getarticulacion5()));//traslado avanzar 'K'
		model = glm::translate(model, glm::vec3(0.0, 0.0f, -mainWindow.getarticulacion6()));//traslado retroceder 'L'
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Base.RenderModel();

//	-	//Auto Cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.055f, 0.295f, 1.275f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(-1.0f, 0.0f, 0.0f));//cofre abrir 'F'
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));//cofre cerrar 'G'
		color = glm::vec3(0.0f, 255.0f, 255.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Cofre.RenderModel();

//	-	//Auto Llanta delantera izquierda -> llanta1
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.875f, -0.501f, 1.45f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));//rotar llantas adelante 'H'
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(-1.0f, 0.0f, 0.0f));//rotar llantas atr�s  'J'
		color = glm::vec3(0.0f, 0.5f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Llanta1.RenderModel();

//	-	//Auto Llanta delantera derecha -> llanta2
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.978f, -0.49f, 1.45f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Llanta2.RenderModel();

//	-	//Auto llanta trasera izquierda -> llanta3
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.875f, -0.501f, -1.615f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Llanta3.RenderModel();

//	-	//Auto llanta trasera derecha -> llanta4
		model = modelaux;
		model = glm::translate(model, glm::vec3(-.978f, -0.49f, -1.615f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(-1.0f, 0.0f, 0.0f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Llanta4.RenderModel();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}