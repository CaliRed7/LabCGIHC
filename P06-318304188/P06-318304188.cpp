/*
Pr�ctica 6: Texturizado
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
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture dadoTexture;
Texture logofiTexture;

Model Auto_M;
Model Llanta_M;
Model Dado_M;//dado importado
Model Auto_Cofre;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_texture.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_texture.frag";




//c�lculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}



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

	unsigned int vegetacionIndices[] = {
		0, 1, 2,
		0, 2, 3,
		4,5,6,
		4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,
	};
	calcAverageNormals(indices, 12, vertices, 32, 8, 5);


	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearDado()
{
	unsigned int dado_indices[] = {
		// up
		0, 1, 2,
		2, 3, 0,
		
		// up
		8, 9, 10,
		10, 11, 8,

		// up
		12, 13, 14,
		14, 15, 12,
		// up
		16, 17, 18,
		18, 19, 16,
		// up
		20, 21, 22,
		22, 23, 20,

		// down
		4, 5, 6,
		6, 7, 4,
		//RESTO D10
		// down
		24, 25, 26,
		26, 27, 24,
		// down
		28, 29, 30,
		30, 31, 28,
		// down
		32, 33, 34,
		34, 35, 32,
		// down
		36, 37, 38,
		38, 39, 36
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
// average normals
	GLfloat dado_vertices[] = {
		// up - 
		//x		y		z		S		T					NX		NY		NZ
		-0.5f, 0.0f,  0.5f,	0.05f,    0.3f,		0.0f,	0.0f,	-1.0f,	//0
		0.0f, -0.83,   0.7f,	0.0f,	0.175f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f, 0.0f,   0.5f,	0.15f,	0.1f,		0.0f,	0.0f,	-1.0f,	//2
		0.0f,  0.75f,  -0.25f,	0.4,	0.25,		0.0f,	0.0f,	-1.0f,	//3
		// up - 
		//x		y		z		S		T
		0.9f, 0.0f,   -0.5f,	0.9f,	0.85f,		1.0f,	0.0f,	0.0f,
		0.6f, -0.35f,  -1.15f,	0.9f,	1.0f,		1.0f,	0.0f,	0.0f,
		0.0f,  0.0f,  -1.25f,	0.5f,	1.0f,		1.0f,	0.0f,	0.0f,
		0.0f,  0.75f,  -0.25f,	0.5f,	0.72f,		1.0f,	0.0f,	0.0f,
		// up - 
		//x		y		z		S		T
		0.5f, 0.0f,   0.5f,    0.3,    0.9f,		-1.0f,	0.0f,	0.0f,
		1.f,  -0.83f,  0.1f,	0.2f,    0.8f,		-1.0f,	0.0f,	0.0f,
		0.9f, 0.0f,   -0.5f,	0.2f,	0.7f,		-1.0f,	0.0f,	0.0f,
		0.0f,  0.75f,  -0.25f,	0.5f,	0.75f,		-1.0f,	0.0f,	0.0f,
		// up - 
		//x		y		z		S		T
		-0.9f, 0.0f,   -0.5f,	0.25f,	0.5f,		0.0f,	1.0f,	0.0f,
		-0.6f, -0.35f,  -1.15f,	0.4f,	0.5f,		0.0f,	1.0f,	0.0f,
		0.0f,  0.0f,  -1.25f,	0.5f,	0.5f,		0.0f,	1.0f,	0.0f,
		0.0f,  0.75f,  -0.25f,	0.4f,	0.25f,		0.0f,	1.0f,	0.0f,

		// up - 
		-0.5f, 0.0f,  0.5f,	0.4f,	0.0f,		0.0f,	0.0f,	1.0f,
		-1.f,  -0.83f, 0.1f,    0.2f,	0.0f,		0.0f,	0.0f,	1.0f,
		-0.9f, 0.0f,  -0.5f,	0.15f,	0.0f,		0.0f,	0.0f,	1.0f,
		0.0f,  0.75f,  -0.25f,	0.4f,	0.25f,		0.0f,	0.0f,	1.0f,

		//down - 
		//x		y		z		S		T
	   1.f,  -0.83f,  0.1f,    0.2f,	0.7f,		-1.0f,	0.0f,	0.0f,
	   0.9f, 0.0f,   -0.5f,	0.25f,	0.5f,		-1.0f,	0.0f,	0.0f,
	   0.6f, -0.35f,  -1.15f,	0.4f,	0.5f,		-1.0f,	0.0f,	0.0f,
	   0.0f,  -1.25f,  -0.25f,	0.5f,	0.75f,		-1.0f,	0.0f,	0.0f,

		//down - 
		 //x		y		z		S		T
		0.0f, -0.83f,   0.7f,   0.4f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, 0.0f,    0.5f,	0.4f,	1.0f,		-1.0f,	0.0f,	0.0f,
		1.f,  -0.83f,   0.1f,	0.6f,	1.0f,		-1.0f,	0.0f,	0.0f,
		0.0f,  -1.25f,  -0.25f,	0.6f,	0.75f,		-1.0f,	0.0f,	0.0f,

		 //down - 
		 //x		y		z		S		T
		0.0f, -0.83f,   0.7f,   0.25f,	0.45f,		-1.0f,	0.0f,	0.0f,
		-0.5f, 0.0f,   0.5f,	0.f,    0.4f,		-1.0f,	0.0f,	0.0f,
		-1.f,  -0.83f,   0.1f,	0.0f,	0.3f,		-1.0f,	0.0f,	0.0f,
		0.0f,  -1.25f,  -0.25f,	0.4f,	0.25f,		-1.0f,	0.0f,	0.0f,

		//down - 
		 //x		y		z		S		T
		0.6f, -0.35f,  -1.15f,  0.75f,	0.5f,		-1.0f,	0.0f,	0.0f,
		0.0f,  0.0f,  -1.25f,	0.6f,	0.45f,		-1.0f,	0.0f,	0.0f,
		-0.6f, -0.35f,  -1.15f,	0.4f,	0.5f,		-1.0f,	0.0f,	0.0f,
		0.0f,  -1.25f,  -0.25f,	0.6f,	0.75f,		-1.0f,	0.0f,	0.0f,

		 //down - 
		 //x		y		z		S		T
		-1.f,  -0.83f,  0.1f,   0.4f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.9f, 0.0f,   -0.5f,	0.65f,	0.0f,		-1.0f,	0.0f,	0.0f,
		-0.6f, -0.35f,  -1.15f,	0.75f,	0.15f,		-1.0f,	0.0f,	0.0f,
		0.0f,  -1.25f,  -0.25f,	0.4f,	0.25f,		-1.0f,	0.0f,	0.0f,




	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(dado_vertices, dado_indices, 320, 60);//modificado decaedro
	meshList.push_back(dado);

}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearDado();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	//dadoTexture = Texture("Textures/dado-de-numeros.png");
	dadoTexture = Texture("Textures/diez.tga");
	dadoTexture.LoadTextureA();//siempre verificar la existencia del canal alfa
	logofiTexture = Texture("Textures/escudo_fi_color.tga");
	logofiTexture.LoadTextureA();
	
	
	Auto_M = Model();
	Auto_M.LoadModel("Models/cochebase.obj");
	Auto_Cofre = Model();
	Auto_Cofre.LoadModel("Models/autocofre.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta.obj");
	Dado_M = Model();
	Dado_M.LoadModel("Models/dado_importado.dae");

	
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
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		color = glm::vec3(1.0f, 1.0f, 1.0f);//color blanco, multiplica a la informaci�n de color de la textura

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();


		//Dado de Opengl
		//Ejercicio 1: Texturizar su cubo con la imagen dado_animales ya optimizada por ustedes
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 8.5f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshList[4]->RenderMesh();
		
		//Ejercicio 2:Importar el cubo texturizado en el programa de modelado con 
		//la imagen dado_animales ya optimizada por ustedes
		/*
		//Dado importado
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, 3.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado_M.RenderModel();
		*/

		
		
		/*Reporte de pr�ctica :
		Ejercicio 1: Crear un dado de 8 caras y texturizarlo por medio de c�digo
		Ejercicio 2: Importar el modelo de su coche con sus 4 llantas acomodadas
		y tener texturizadas las 4 llantas (diferenciar caucho y rin)  y 
		texturizar el logo de la Facultad de ingenier�a en el cofre de su propio modelo de coche
	
		*/
		
		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex() , 0.5f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_M.RenderModel();

		//Auto Cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.25f, 0.67f, -0.11f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.4f, 2.4f, 2.4f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Cofre.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.71f, -1.3f, 2.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(3.91f, -1.3f, 2.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.71f, -1.3f, -2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(3.91f, -1.3f, -2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.4f, 2.4f, 2.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
/*
//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		logofiTexture.UseTexture(); //textura con transparencia o traslucidez
		FIGURA A RENDERIZAR de OpenGL, si es modelo importado no se declara UseTexture
		glDisable(GL_BLEND);
*/