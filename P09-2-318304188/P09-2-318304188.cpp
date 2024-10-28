/*
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada
Sesión 2
Compleja: Por medio de funciones y algoritmos.
Textura Animada
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
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;

//Variables para la animación de Cabeza_1 y Cabeza_5
const float a = 0.2f; //ajustar para la lemniscata
const float scaleFactor = 10.0f; //factor de escala para reducir la velocidad de la animación

//Definir la variable de rotación para la Cabeza_2
float rotationAngleCabeza2 = 0.0f;
const float rotationSpeedCabeza2 = 10.0f; //velocidad de rotación en grados por segundo
//Función para actualizar la rotación de la Cabeza_2
float calculateRotationAngle(float initialAngle, float deltaTime, float rotationSpeed) {
	float newAngle = initialAngle + rotationSpeed * deltaTime;
	return fmod(newAngle, 360.0f); //Mantener el ángulo en el rango de 0 a 360 grados
}
//De lado a lado Cabeza_2
float calculateAlternatingRotation(float time, float speed) {
	return 75.0f * sin(speed * time); //Rotación de -75° a 75°
}


// Constantes para el movimiento sinusoidal de la Cabeza_3
const float head3Amplitude = 0.25f; //Amplitud del movimiento sinusoidal
const float head3Frequency = 1.0f; //Frecuencia del movimiento sinusoidal

//Variables para la animación de Cabeza_4
glm::vec3 calculateRosePath(float t, float scale) {
	float k = 3.0f; //Número de pétalos
	float r = scale * cos(k * t); //Ecuación de la rosa
	float x = r * cos(t);
	float y = r * sin(t);
	float z = 0.0f;
	return glm::vec3(x, y, z);
}

//Variables para la animación de Cabeza_5
glm::vec3 calculateHeartPath(float t, float scale) {
	float h = scale * 16 * pow(sin(t), 3);
	float j = scale * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
	float k = 0.0f; //Mantener k constante o ajustar según sea necesario
	return glm::vec3(h, j, k);
}
//Define la variable de velocidad del tiempo
const float timeSpeedHeart = 0.5f; //Velocidad

//Texturas elementos escupidos cabezas
float flamesTimer = 0.0f;
float raysTimer = 0.0f;
float gasTimer = 0.0f;
float iceTimer = 0.0f;
float sandTimer = 0.0f;
const float effectDuration = 50.0f; // Duración texturas

bool emitFlames = false;
bool emitRays = false;
bool emitGas = false;
bool emitIce = false;
bool emitSand = false;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture FlechaTexture;
Texture NumerosTexture;
Texture LetreroLetrasTexture;
Texture Numero1Texture;
Texture Numero2Texture;
Texture CabezasTexture;
Texture arcoTexture;
Texture letreroTexture;
Texture flamesTexture;
Texture raysTexture;
Texture gasTexture;
Texture iceTexture;
Texture sandTexture;

Model Kitt_M;
Model Llanta_M;
Model Dragon_M;
Model Tiamat_M;
Model Dragon_Cuerpo;
Model Ala_Derecha;
Model Ala_Izquierda;
Model Cabeza_1;
Model Cabeza_2;
Model Cabeza_3;
Model Cabeza_4;
Model Cabeza_5;
Model Letrero;
Model Arco;

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



//cálculo del promedio de las normales para sombreado de Phong
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

/*
//RECORRIDO
glm::vec3 calculateBackAndForthPath(float t, float length, float speed, float& angle) {
	float position = length * sin(speed * t); // Movimiento sinusoidal entre -length y length
	if (sin(speed * t) >= 0) {
		angle = 0.0f; // Dirección hacia adelante
	}
	else {
		angle = 180.0f; // Dirección hacia atrás
	}
	return glm::vec3(position, 0.0f, 0.0f); // Movimiento solo en el eje x
}
*/


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


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int letreroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat letreroVertices[] = {
		-3.5f, 0.0f, 0.5f,		0.0f, 0.85f,		0.0f, -1.0f, 0.0f,
		3.5f, 0.0f, 0.5f,		0.382f, 0.85f,		0.0f, -1.0f, 0.0f,
		3.5f, 0.0f, -0.5f,		0.382f, 0.95f,		0.0f, -1.0f, 0.0f,
		-3.5f, 0.0f, -0.5f,		0.0f, 0.95f,		0.0f, -1.0f, 0.0f,

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

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(letreroVertices, letreroIndices, 32, 6);
	meshList.push_back(obj7);

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

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

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
	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	LetreroLetrasTexture = Texture("Textures/letrerobase.tga");
	LetreroLetrasTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();
	CabezasTexture = Texture("Textures/colores.tga");
	CabezasTexture.LoadTextureA();
	arcoTexture = Texture("Textures/mggate_alb.png");
	arcoTexture.LoadTextureA();
	letreroTexture = Texture("Textures/mggateopa_alb.png");
	letreroTexture.LoadTextureA();
	flamesTexture = Texture("Textures/fuego.png");
	flamesTexture.LoadTextureA();
	raysTexture = Texture("Textures/rayos.png");
	raysTexture.LoadTextureA();
	gasTexture = Texture("Textures/gas.png");
	gasTexture.LoadTextureA();
	iceTexture = Texture("Textures/hielo.png");
	iceTexture.LoadTextureA();
	sandTexture = Texture("Textures/arena.png");
	sandTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Dragon_M = Model();
	Dragon_M.LoadModel("Models/17174_Tiamat_new.obj");
	Dragon_Cuerpo = Model();
	Dragon_Cuerpo.LoadModel("Models/Dragon_Cuerpo.obj");
	Ala_Derecha = Model();
	Ala_Derecha.LoadModel("Models/Ala_Derecha.obj");
	Ala_Izquierda = Model();
	Ala_Izquierda.LoadModel("Models/Ala_Izquierda.obj");
	Cabeza_1 = Model();
	Cabeza_1.LoadModel("Models/Cabeza_1.obj");
	Cabeza_2 = Model();
	Cabeza_2.LoadModel("Models/Cabeza_2.obj");
	Cabeza_3 = Model();
	Cabeza_3.LoadModel("Models/Cabeza_3.obj");
	Cabeza_4 = Model();
	Cabeza_4.LoadModel("Models/Cabeza_4.obj");
	Cabeza_5 = Model();
	Cabeza_5.LoadModel("Models/Cabeza_5.obj");
	Letrero = Model();
	Letrero.LoadModel("Models/letrero.obj");
	Arco = Model();
	Arco.LoadModel("Models/arco.obj");

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
		0.0f, 2.5f, 1.5f,
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
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;



	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movCoche = 0.0f;
	movOffset = 0.01f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		angulovaria += 1.5f * deltaTime;
		//angulovaria += 5.0f * deltaTime;//arreglo de velocidad dragón

		if (movCoche < 30.0f)
		{
			movCoche -= movOffset * deltaTime;
			//printf("avanza%f \n ",movCoche);
			rotllanta += rotllantaOffset * deltaTime;
		}

		// Actualizar la rotación de la Cabeza_2
		rotationAngleCabeza2 = calculateRotationAngle(rotationAngleCabeza2, deltaTime, rotationSpeedCabeza2);

		// Actualizar los temporizadores y desactivar los efectos si el tiempo ha pasado
		if (emitFlames) flamesTimer += deltaTime;
		if (emitRays) raysTimer += deltaTime;
		if (emitGas) gasTimer += deltaTime;
		if (emitIce) iceTimer += deltaTime;
		if (emitSand) sandTimer += deltaTime;

		if (flamesTimer >= effectDuration) { emitFlames = false; flamesTimer = 0.0f; }
		if (raysTimer >= effectDuration) { emitRays = false; raysTimer = 0.0f; }
		if (gasTimer >= effectDuration) { emitGas = false; gasTimer = 0.0f; }
		if (iceTimer >= effectDuration) { emitIce = false; iceTimer = 0.0f; }
		if (sandTimer >= effectDuration) { emitSand = false; sandTimer = 0.0f; }

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Manejar entrada del teclado para activar/desactivar efectos
		if (mainWindow.getsKeys()[GLFW_KEY_F] && !emitFlames) { emitFlames = true; flamesTimer = 0.0f; }
		if (mainWindow.getsKeys()[GLFW_KEY_R] && !emitRays) { emitRays = true; raysTimer = 0.0f; }
		if (mainWindow.getsKeys()[GLFW_KEY_G] && !emitGas) { emitGas = true; gasTimer = 0.0f; }
		if (mainWindow.getsKeys()[GLFW_KEY_H] && !emitIce) { emitIce = true; iceTimer = 0.0f; }
		if (mainWindow.getsKeys()[GLFW_KEY_N] && !emitSand) { emitSand = true; sandTimer = 0.0f; }

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
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
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
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//=========================================================================
		//RECORRIDO float g = angulovaria / scaleFactor;

		// Variables para la posición y el ángulo
		//RECORRIDO float rotationAngleDragon = 0.0f;
		//RECORRIDO glm::vec3 backAndForthPath = calculateBackAndForthPath(g, 10.0f, 0.09f, rotationAngleDragon);//cambio longitud y velocidads

		// Cuerpo del dragón con movimiento de ida y vuelta en el eje x y giro de 180°
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f - angulovaria / 100, 5.0f + (4 * sin(glm::radians(angulovaria))), 6.0));//ideal -> arreglar velocidad "arreglo de velocidad dragón"
		//RECORRIDO model = glm::translate(model, backAndForthPath); // Añadir movimiento de ida y vuelta en el eje x
		//RECORRIDO model = glm::rotate(model, glm::radians(rotationAngleDragon), glm::vec3(0.0f, 1.0f, 0.0f)); // Añadir giro de 180°
		modelaux = model;
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dragon_Cuerpo.RenderModel();

		//Ala derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.44f, 0.95f, -1.1f));
		model = glm::rotate(model, glm::radians(20.0f * sin(glm::radians(angulovaria * 10.0f))), glm::vec3(1.0f, 0.0f, 0.0f));//aleteo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ala_Derecha.RenderModel();

		//Ala izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.15f, 0.96f, 0.25f));
		model = glm::rotate(model, glm::radians(-20.0f * sin(glm::radians(angulovaria * 10.0f))), glm::vec3(1.0f, 0.0f, 0.0f));//aleteo
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ala_Izquierda.RenderModel();

		//Cálculo posición de la Cabeza_1 en la trayectoria de lemniscata
		float t = angulovaria / scaleFactor; //toma el ángulo como parámetro de tiempo y lo escala
		float lemniscataX = a * cos(t) / (1 + sin(t) * sin(t));
		float lemniscataY = a * sin(t) * cos(t) / (1 + sin(t) * sin(t));
		// Cabeza 1 - Superior derecha, con trayectoria en lemniscata
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.85f, 2.1f, -1.42f)); // Posición base de la cabeza
		model = glm::translate(model, glm::vec3(lemniscataX, lemniscataY, 0.0f)); // Añadir movimiento de lemniscata
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_1.RenderModel();

		// Textura Cabeza_1 -> Fuego
		if (emitFlames)
		{
			// Habilitar la mezcla alfa
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glm::mat4 flamesModel = modelaux;
			flamesModel = glm::translate(flamesModel, glm::vec3(-2.85f, 2.1f, -1.42f)); // Posición base de la Cabeza_1
			flamesModel = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
			flamesModel = glm::translate(flamesModel, glm::vec3(lemniscataX, lemniscataY, 0.0f)); // Añadir movimiento de lemniscata
			flamesModel = glm::translate(flamesModel, glm::vec3(0.2f, -0.5f, -2.5f)); // Mover las llamas hacia adelante de la cabeza
			flamesModel = glm::scale(flamesModel, glm::vec3(2.5f, 2.5f, 2.5f)); // Escalar las llamas
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(flamesModel));
			flamesTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[4]->RenderMesh();

			// Deshabilitar la mezcla alfa
			glDisable(GL_BLEND);
		}

		// Actualizar la rotación de la Cabeza_2
		float rotationAngleCabeza2 = calculateAlternatingRotation(angulovaria, 0.025f); //velocidad volteo de lado a lado
		// Cabeza 2 - Superior izquierda, con trayectoria de volteo de derecha a izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.67f, 2.19f, 0.55f)); // Posición base de la cabeza
		model = glm::rotate(model, glm::radians(rotationAngleCabeza2), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación sobre su eje Y
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_2.RenderModel();

		// Textura Cabeza_2 -> Rayos
		if (emitRays)
		{
			// Habilitar la mezcla alfa
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glm::mat4 raysModel = modelaux;
			raysModel = glm::translate(raysModel, glm::vec3(-2.67f, 2.19f, 0.55f)); // Posición base de la Cabeza_2
			//raysModel = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
			raysModel = glm::rotate(raysModel, glm::radians(rotationAngleCabeza2), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación sobre su eje Y
			raysModel = glm::translate(raysModel, glm::vec3(-1.0f, 0.0f, 3.0f)); // Mover los rayos hacia adelante de la cabeza
			raysModel = glm::scale(raysModel, glm::vec3(2.5f, 2.5f, 2.5f)); // Escalar los rayos
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(raysModel));
			raysTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[4]->RenderMesh();

			// Deshabilitar la mezcla alfa
			glDisable(GL_BLEND);
		}

		//Cálculo posición de la Cabeza_3 en una trayectoria sinusoidal en el eje y
		float sinY = head3Amplitude * sin(head3Frequency * t); // Movimiento sinusoidal en y
		// Cabeza 3 - Inferior derecha, con trayectoria sinusoidal en y sincronizada con el cuerpo
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.5f, 0.55f + sinY, -1.55f)); // Posición base de la cabeza + movimiento sinusoidal en y
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_3.RenderModel();

		// Textura Cabeza_3 -> Gas venenoso
		if (emitGas)
		{
			// Habilitar la mezcla alfa
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glm::mat4 gasModel = modelaux;
			gasModel = glm::translate(gasModel, glm::vec3(-2.67f, 2.19f, 0.55f)); // Posición base de la Cabeza_3
			gasModel = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
			gasModel = glm::translate(gasModel, glm::vec3(-1.5f, 0.0f, -3.0f)); // Mover el gas hacia adelante de la cabeza
			gasModel = glm::scale(gasModel, glm::vec3(2.5f, 2.5f, 2.5f)); // Escalar el gas
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(gasModel));
			gasTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();

			// Deshabilitar la mezcla alfa
			glDisable(GL_BLEND);
		}

		//Cálculo posición de la Cabeza_4 en una trayectoria de rosa de tres pétalos
		glm::vec3 rosePath = calculateRosePath(t, 0.075f); //velocidad trayectoria de rosas
		// Cabeza 4 - Inferior central, con trayectoria de rosa de tres pétalos
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.62f, 1.46f, -0.2f)); // Posición base de la cabeza
		model = glm::translate(model, rosePath); // Añadir movimiento de rosa
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_4.RenderModel();;

		// Textura Cabeza_4 -> Hielos
		if (emitIce)
		{
			// Habilitar la mezcla alfa
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glm::mat4 iceModel = modelaux;
			iceModel = glm::translate(iceModel, glm::vec3(-2.67f, 2.19f, 0.55f)); // Posición base de la Cabeza_4
			iceModel = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
			iceModel = glm::translate(iceModel, glm::vec3(-1.0f, 0.0f, -3.5f)); // Mover el hielo hacia adelante de la cabeza
			iceModel = glm::scale(iceModel, glm::vec3(2.5f, 2.5f, 2.5f)); // Escalar el hielo
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(iceModel));
			iceTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();

			// Deshabilitar la mezcla alfa
			glDisable(GL_BLEND);
		}

		float tHeart = angulovaria / scaleFactor * timeSpeedHeart; //uso de timeSpeedHeart para controlar la velocidad del tiempo
		//Cálculo posición de la Cabeza_5 en una trayectoria de corazón
		glm::vec3 heartPath = calculateHeartPath(tHeart, 0.01f); // Ajusta el factor de escala para la longitud de la trayectoria
		// Cabeza 5 - Inferior izquierda, con trayectoria en forma de corazón
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.55f, 0.242f, 1.2f)); // Posición base de la cabeza
		model = glm::translate(model, heartPath); // Añadir movimiento de corazón
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_5.RenderModel();

		// Textura Cabeza_5 -> Arena
		if (emitSand)
		{
			// Habilitar la mezcla alfa
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glm::mat4 sandModel = modelaux;
			sandModel = glm::translate(sandModel, glm::vec3(-2.67f, 2.19f, 0.55f)); // Posición base de la Cabeza_5
			sandModel = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
			sandModel = glm::translate(sandModel, glm::vec3(0.0f, 0.0f, -2.5f)); // Mover la arena hacia adelante de la cabeza
			sandModel = glm::scale(sandModel, glm::vec3(2.5f, 2.5f, 2.5f)); // Escalar la arena
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(sandModel));
			sandTexture.UseTexture();
			Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[5]->RenderMesh();

			// Deshabilitar la mezcla alfa
			glDisable(GL_BLEND);
		}

		//Letrero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 15.7f, -25.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letrero.RenderModel();

		//Arco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.25f, -25.0));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arco.RenderModel();
		//=========================================================================


		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Agave ¿qué sucede si lo renderizan antes del coche y de la pista?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		//textura con movimiento
		//Importantes porque la variable uniform no podemos modificarla directamente
		toffsetflechau += 0.001;
		toffsetflechav = 0.000;
		//para que no se desborde la variable
		if (toffsetflechau > 1.0)
			toffsetflechau = 0.0;
		//if (toffsetv > 1.0)
		//	toffsetv = 0;
		//printf("\ntfosset %f \n", toffsetu);
		//pasar a la variable uniform el valor actualizado
		toffset = glm::vec2(toffsetflechau, toffsetflechav);

		/*
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		FlechaTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();


		//plano con todos los números
		toffsetnumerou = 0.0;
		toffsetnumerov = 0.0;
		toffset = glm::vec2(toffsetnumerou, toffsetnumerov);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, 2.0f, -6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//número 1
		//toffsetnumerou = 0.0;
		//toffsetnumerov = 0.0;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 2.0f, -6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		NumerosTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();


		for (int i = 1; i < 4; i++)
		{
			//números 2-4
			toffsetnumerou += 0.25;
			toffsetnumerov = 0.0;
			toffset = glm::vec2(toffsetnumerou, toffsetnumerov);
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-10.0f - (i * 3.0), 2.0f, -6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			NumerosTexture.UseTexture();
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[6]->RenderMesh();

		}


		for (int j = 1; j < 5; j++)
		{
			//números 5-8
			toffsetnumerou += 0.25;
			toffsetnumerov = -0.33;
			toffset = glm::vec2(toffsetnumerou, toffsetnumerov);
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-7.0f - (j * 3.0), 5.0f, -6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			color = glm::vec3(1.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			NumerosTexture.UseTexture();
			Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
			meshList[6]->RenderMesh();
		}
		*/

		//letrero "PROYECTO CGEIHC MONOPOLY"
		toffsetnumerocambiau += 0.0025;//velocidad desplazamiento
		if (toffsetnumerocambiau > 1.0)
			toffsetnumerocambiau = 0.0;
		toffsetnumerov = 0.0;
		toffset = glm::vec2(toffsetnumerocambiau, toffsetnumerov);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.15f, 15.5f, -24.75f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.5f, 3.0f, 3.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LetreroLetrasTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		/*
		//cambiar automáticamente entre textura número 1 y número 2
		toffsetnumerou = 0.0;
		toffsetnumerov = 0.0;
		toffset = glm::vec2(toffsetnumerou, toffsetnumerov);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, 10.0f, -6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Numero1Texture.UseTexture();
		//if
		//Numero1Texture.UseTexture();
		//Numero2Texture.UseTexture();

		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();
		*/

		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
