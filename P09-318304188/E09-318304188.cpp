/*
Semestre 2025-2
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transforomación geométrica se ve modificada
Sesión 2
Compleja: Por medio de funciones y algoritmos.
Adicional.- ,Textura Animada
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
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;//guarda los datos, aquí la traslación
float movOffset;//guarda los incrementos decrementos
float rotllanta;
float rotllantaOffset;
float movLetrero;
float movOffsetLetrero;
float rotletrero;
float rotletreroOffset;
bool avanza = true;
float timer;
float wait;
int i;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture tableroTexture;
Texture arcoTexture;
Texture letreroTexture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Letrero;
Model Arco;
/*Model Casilla_0;
Model Casilla_1;
Model Casilla_2;
Model Casilla_3;
Model Casilla_4;
Model Casilla_5;
Model Casilla_6;
Model Casilla_7;
Model Casilla_8;
Model Casilla_9;
Model Casilla_10;
Model Casilla_11;
Model Casilla_12;
Model Casilla_13;
Model Casilla_14;
Model Casilla_15;
Model Casilla_16;
Model Casilla_17;
Model Casilla_18;
Model Casilla_19;
Model Casilla_20;
Model Casilla_21;
Model Casilla_22;
Model Casilla_23;
Model Casilla_24;
Model Casilla_25;
Model Casilla_26;
Model Casilla_27;
Model Casilla_28;
Model Casilla_29;
Model Casilla_30;
Model Casilla_31;
Model Casilla_32;
Model Casilla_33;
Model Casilla_34;
Model Casilla_35;
Model Casilla_36;
Model Casilla_37;
Model Casilla_38;
Model Casilla_39;*/



Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
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

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
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
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	tableroTexture = Texture("Textures/pisop.png");
	tableroTexture.LoadTextureA();
	arcoTexture = Texture("Textures/mggate_alb.png");
	arcoTexture.LoadTextureA();
	letreroTexture = Texture("Textures/mggateopa_alb.png");
	letreroTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Letrero = Model();
	Letrero.LoadModel("Models/letrero.obj");
	Arco = Model();
	Arco.LoadModel("Models/arco.obj");
	/*Casilla_0 = Model();
	Casilla_0.LoadModel("Models/casilla0.obj");
	Casilla_1 = Model();
	Casilla_1.LoadModel("Models/casilla1.obj");
	Casilla_2 = Model();
	Casilla_2.LoadModel("Models/casilla2.obj");
	Casilla_3 = Model();
	Casilla_3.LoadModel("Models/casilla3.obj");
	Casilla_4 = Model();
	Casilla_4.LoadModel("Models/casilla4.obj");
	Casilla_5 = Model();
	Casilla_5.LoadModel("Models/casilla5.obj");
	Casilla_6 = Model();
	Casilla_6.LoadModel("Models/casilla6.obj");
	Casilla_7 = Model();
	Casilla_7.LoadModel("Models/casilla7.obj");
	Casilla_8 = Model();
	Casilla_8.LoadModel("Models/casilla8.obj");
	Casilla_9 = Model();
	Casilla_9.LoadModel("Models/casilla9.obj");
	Casilla_10 = Model();
	Casilla_10.LoadModel("Models/casilla10.obj");
	Casilla_11 = Model();
	Casilla_11.LoadModel("Models/casilla11.obj");
	Casilla_12 = Model();
	Casilla_12.LoadModel("Models/casilla12.obj");
	Casilla_13 = Model();
	Casilla_13.LoadModel("Models/casilla13.obj");
	Casilla_14 = Model();
	Casilla_14.LoadModel("Models/casilla14.obj");
	Casilla_15 = Model();
	Casilla_15.LoadModel("Models/casilla15.obj");
	Casilla_16 = Model();
	Casilla_16.LoadModel("Models/casilla16.obj");
	Casilla_17 = Model();
	Casilla_17.LoadModel("Models/casilla17.obj");
	Casilla_18 = Model();
	Casilla_18.LoadModel("Models/casilla18.obj");
	Casilla_19 = Model();
	Casilla_19.LoadModel("Models/casilla19.obj");
	Casilla_20 = Model();
	Casilla_20.LoadModel("Models/casilla20.obj");
	Casilla_21 = Model();
	Casilla_21.LoadModel("Models/casilla21.obj");
	Casilla_22 = Model();
	Casilla_22.LoadModel("Models/casilla22.obj");
	Casilla_23 = Model();
	Casilla_23.LoadModel("Models/casilla23.obj");
	Casilla_24 = Model();
	Casilla_24.LoadModel("Models/casilla24.obj");
	Casilla_25 = Model();
	Casilla_25.LoadModel("Models/casilla25.obj");
	Casilla_26 = Model();
	Casilla_26.LoadModel("Models/casilla26.obj");
	Casilla_27 = Model();
	Casilla_27.LoadModel("Models/casilla27.obj");
	Casilla_28 = Model();
	Casilla_28.LoadModel("Models/casilla28.obj");
	Casilla_29 = Model();
	Casilla_29.LoadModel("Models/casilla29.obj");
	Casilla_30 = Model();
	Casilla_30.LoadModel("Models/casilla30.obj");
	Casilla_31 = Model();
	Casilla_31.LoadModel("Models/casilla31.obj");
	Casilla_32 = Model();
	Casilla_32.LoadModel("Models/casilla32.obj");
	Casilla_33 = Model();
	Casilla_33.LoadModel("Models/casilla33.obj");
	Casilla_34 = Model();
	Casilla_34.LoadModel("Models/casilla34.obj");
	Casilla_35 = Model();
	Casilla_35.LoadModel("Models/casilla35.obj");
	Casilla_36 = Model();
	Casilla_36.LoadModel("Models/casilla36.obj");
	Casilla_37 = Model();
	Casilla_37.LoadModel("Models/casilla37.obj");
	Casilla_38 = Model();
	Casilla_38.LoadModel("Models/casilla38.obj");
	Casilla_39 = Model();
	Casilla_39.LoadModel("Models/casilla39.obj");*/


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	movCoche = 0.0f;
	movOffset = 0.3f;//cambiar velocidad de animación coche moviéndose
	rotllanta = 0.0f;
	rotllantaOffset = 5.0f;
	movLetrero = 12.0f;
	movOffsetLetrero = .12f;
	rotletrero = 0.0f;//controla la rotación del letrero en el eje X
	rotletreroOffset = 3.0f;
	timer = 0.0f;
	wait = 2.0f;
	i = 0;//contador para controlar el ciclo de animaciones
	////Loop mientras no se cierra la ventana
	double tiempoActual = glfwGetTime();
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		timer = glfwGetTime();
		if (mainWindow.getempezar() == true) {
			if (avanza) {
				if (movCoche > -306.0f)
				{
					movCoche -= movOffset * deltaTime;
					rotllanta += rotllantaOffset * deltaTime;
				}
				else {
					avanza = !avanza;
				}
			}
			else {
				if (movCoche < 284.0f) {
					movCoche += movOffset * deltaTime;
					rotllanta -= rotllantaOffset * deltaTime;
				}
				else {
					avanza = !avanza;
				}
			}
		}

	/*
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;//nos sirve para tomar en cuenta el tiempo de cada ciclo de reloj en el procesador y estandarizarlo (de esta manera al ejecutar en dos computadoras la velocidad es la misma)
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		//hacer glfwset time para que en lugar de ciclos de reloj deltatime cuente segundos

		if (movCoche < 30.0f)
		//if (movCoche > -300.0f) //así el auto no avanzará más allá del piso

		{
			movCoche -= movOffset * deltaTime;//
			//printf("avanza%f \n ",movCoche);
			//rotllanta += rotllantaOffset * deltaTime; //si descomentamos esta línea aquí la llanta dejará de rotar cuando llegue al borde
		}
		rotllanta += rotllantaOffset * deltaTime;//todo el tiempo está sucediendo la rotación de las llantas
	*/

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
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movCoche, 0.5f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -rotllanta * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Helicóptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//=========================================================
		float baseTime = i * 8;

		if (timer < 2 + baseTime) {//durante los primeros 2 segundos del ciclo, el letrero sube
			movLetrero += movOffsetLetrero * deltaTime;
		}
		else if (timer < 4 + baseTime) {//mantiene la rotación mientras en los próximos 2 segundos, el letrero gira alrededor de su eje X
			rotletrero += rotletreroOffset * deltaTime;
		}
		else if (timer < 6 + baseTime) {//mantiene el movimiento y después de los primeros 4 segundos, el letrero baja
			movLetrero -= movOffsetLetrero * deltaTime;
		}
		else if (timer < 8 + baseTime) {//los últimos 2 segundos del ciclo invierten la rotación del letrero, regresando a su posición original
			rotletrero -= rotletreroOffset * deltaTime;
		}
		else {//fin del ciclo
			i++;
		}

		//Letrero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, movLetrero+4.25f, -25.0f));
		model = glm::rotate(model, rotletrero * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letrero.RenderModel();

		//Arco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.25f, -25.0));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arco.RenderModel();
		//=========================================================

		/*
		//=========================TABLERO=========================
		//Casilla 0 - Salida
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_0.RenderModel();

		//Casilla 1 - 343 Guilty Spark
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -10.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_1.RenderModel();

		//Casilla 2 - Anti-Kirby
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -15.25f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_2.RenderModel();

		//Casilla 3 - Kendall
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -20.2f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_3.RenderModel();

		//Casilla 4 - Soldado ODST
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -25.15f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_4.RenderModel();

		//Casilla 5 - Conejo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -30.1f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_5.RenderModel();

		//Casilla 6 - Oskar
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -35.05f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_6.RenderModel();

		//Casilla 7 - Soldado Elite
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -40.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_7.RenderModel();

		//Casilla 8 - Buho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -44.95f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_8.RenderModel();

		//Casilla 9 - Escuela
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -49.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_9.RenderModel();

		//Casilla 10 - Spartan-IV
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_10.RenderModel();

		//Casilla 11 - Octorok
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.3f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_11.RenderModel();

		//Casilla 12 - Nuzzlet
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.25f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_12.RenderModel();

		//Casilla 13 - Moa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.2f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_13.RenderModel();

		//Casilla 14 - Cuco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.15f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_14.RenderModel();

		//Casilla 15 - BattleSnax
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.1f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_15.RenderModel();

		//Casilla 16 - Guta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.05f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_16.RenderModel();

		//Casilla 17 - Mutt
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_17.RenderModel();

		//Casilla 18 - Pez Diablo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.95f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_18.RenderModel();

		//Casilla 19 - Rata
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(49.9f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_19.RenderModel();

		//Casilla 20 - Tienda de Herramientas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_20.RenderModel();

		//Casilla 21 - Wei
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -49.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_21.RenderModel();

		//Casilla 22 - Flores Rojas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -44.95f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_22.RenderModel();

		//Casilla 23 - Pina
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -40.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_23.RenderModel();

		//Casilla 24 - Brad
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -35.05f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_24.RenderModel();

		//Casilla 25 - Plantas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -30.1f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_25.RenderModel();
		
		//Casilla 26 - Panal
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -25.15f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_26.RenderModel();

		//Casilla 27 - Gunther
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -20.2f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_27.RenderModel();

		//Casilla 28 - Arboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -15.25f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_28.RenderModel();

		//Casilla 29 - Cofre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -10.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_29.RenderModel();

		//Casilla 30 - Casa de los Buttowski
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_30.RenderModel();

		//Casilla 31 - Dr. Asombroso
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(49.9f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_31.RenderModel();

		//Casilla 32 - Torre Fourunner
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.95f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_32.RenderModel();

		//Casilla 33 - Marin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_33.RenderModel();

		//Casilla 34 - Reinaldo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.05f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_34.RenderModel();

		//Casilla 35 - Torre de Sigilo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.1f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_35.RenderModel();

		//Casilla 36 - Moblin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.15f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_36.RenderModel();

		//Casilla 37 - Jazzy
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.2f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_37.RenderModel();

		//Casilla 38 - Instalacion 04
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.25f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_38.RenderModel();

		//Casilla 39 - Zora
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.3f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casilla_39.RenderModel();
		//=========================================================
		*/

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}