/*
Práctica 8: Iluminación 2
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
#include "CommonValues.h"//valores que sirven para indicar cuantas luces puntuales y cuantas spotlight se van a usar (recordatorio de no usar más de 7 porque la octava es la luz direccional) -- commonvalues.h -- //declararlos también en shader_light.frag
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture dadoTexture;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Lampara_M;

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

	unsigned int dado_indices[] = {
		// up
		0, 1, 2,
		// up
		3, 4, 5,
		// up
		6, 7, 8,
		// up
		9, 10, 11,
		// up
		12, 13, 14,
		// down
		15, 16, 17,
		// down
		18, 19, 20,
		// down
		21, 22, 23,
		// down
		24, 25, 26,
		// down
		27, 28, 29,
	};

	GLfloat dado_vertices[] = {
		//Up - Primer número - 10
		//x		y		z		S		T					NX		NY		NZ
		0.0f, 1.0f, 0.0f,	    0.49615f, 0.64996f,			-1.0f,	-1.0f,	1.0f,	//0
		1.0f, 0.0f, 0.0f,		0.27092f, 0.64914f,			-1.0f,	-1.0f,	1.0f,	//1
		0.333f, 0.0f, -1.0f,	0.38279f, 0.49607f,			-1.0f,	-1.0f,	1.0f,	//2

		//Up - Segundo número - 4
		//x		y		z		S		T					NX		NY		NZ
		0.333f, 0.0f, -1.0f, 	0.50463f, 0.33104f,			1.0f,	-1.0f,	1.0f,	//3
		-0.8f, 0.0f, -0.6f,		0.61636f, 0.17754f,			1.0f,	-1.0f,	1.0f,	//4
		0.0f, 1.0f, 0.0f,		0.7294f, 0.33145f,			1.0f,	-1.0f,	1.0f,	//5

		//Up - Tercer número - 6
		//x		y		z		S		T					NX		NY		NZ
		0.0f, 1.0f, 0.0f,   	0.15346f, 0.1767f,			1.0f,	-1.0f,	1.0f,	//6
		-0.8f, 0.0f, -0.6f,		0.37865f, 0.17689f,			1.0f,	-1.0f,	1.0f,	//7
		-0.8f, 0.0f, 0.6f,  	0.26562f, 0.33014f,		    1.0f,	-1.0f,	1.0f,	//8

		//Up - Cuarto número - 2
		//x		y		z		S		T					NX		NY		NZ
		-0.8f, 0.0f, 0.6f, 		0.38757f, 0.48917f,			1.0f,	-1.0f,	-1.0f,	//9
		0.333f, 0.0f, 1.0f,		0.49978f, 0.33825f,			1.0f,	-1.0f,	-1.0f,	//10
		0.0f, 1.0f, 0.0f, 	    0.61267f, 0.49094f,			1.0f,	-1.0f,	-1.0f,	//11

       	//Up - Quinto número - 8
		//x		y		z		S		T					NX		NY		NZ
		0.0f, 1.0f, 0.0f,    	0.26643f, 0.64799f,			-1.0f,	-1.0f,	-1.0f,	//12
		0.333f, 0.0f, 1.0f, 	0.15366f, 0.49524f,			-1.0f,	-1.0f,	-1.0f,	//13
		1.0f, 0.0f,0.0f,  	    0.37862f, 0.49506f,			-1.0f,	-1.0f,	-1.0f,	//14

		//Down - Primer número - 7
		//x		y		z		S		T					NX		NY		NZ
		1.0f,  0.0f, 0.0f,		0.61704f, 0.80788f,			-1.0f,	1.0f,	1.0f,	//15
		0.0f, -1.0f, 0.0f,		0.50517f, 0.65599f,			-1.0f,	1.0f,	1.0f,	//16
		0.333f,  0.0f, -1.0f,	0.72892f, 0.65551f,			-1.0f,	1.0f,	1.0f,	//17

		//Down - Segundo número - 1
		//x		y		z		S		T					NX		NY		NZ
		0.333f, 0.0f, -1.0f, 	0.84489f, 0.80984f,			1.0f,	1.0f,	1.0f,	//18
		0.0f, -1.0f, 0.0f,  	0.62177f, 0.8095f,			1.0f,	1.0f,	1.0f,	//19
		-0.8f, 0.0f, -0.6f,  	0.73383f, 0.65706f,			1.0f,	1.0f,	1.0f,	//20

		//Down - Tercer número - 9
		//x		y		z		S		T					NX		NY		NZ
		-0.8f, 0.0f, -0.6f,  	0.26627f, 0.01738f,			1.0f,	1.0f,	0.0f,	//21
		0.0f, -1.0f, 0.0f,  	0.37848f, 0.17061f,			1.0f,	1.0f,	0.0f,	//22
		-0.8f, 0.0f, 0.6f,		0.155f, 0.17f,				1.0f,	1.0f,	0.0f,	//23

		//Down - Cuarto número - 5
		//x		y		z		S		T					NX		NY		NZ
		-0.8f, 0.0f, 0.6f, 		0.73339f, 0.64795f,			1.0f,	1.0f,	-1.0f,	//24
		0.333f, 0.0f, 1.0f,		0.84456f, 0.49566f,			1.0f,	1.0f,	-1.0f,	//25
		0.0f, -1.0f, 0.0f,	    0.62071f, 0.4954f,			1.0f,	-1.0f,	-1.0f,	//26

		//Down - Quinto número - 3
		//x		y		z		S		T					NX		NY		NZ
		0.0f, -1.0f, 0.0f,     	0.26657f, 0.6579f,			-1.0f,	1.0f,	-1.0f,	//27
		0.333f, 0.0f, 1.0f,		0.15586f, 0.80878f,			-1.0f,	1.0f,	-1.0f,	//28
		1.0f, 0.0f, 0.0f,  	    0.37757f, 0.80906f,			-1.0f,	1.0f,	-1.0f,	//29
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

	Mesh* dado = new Mesh();
	dado->CreateMesh(dado_vertices, dado_indices, 240, 30);//modificado decaedro
	meshList.push_back(dado);

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
	//dadoTexture = Texture("Textures/dado-de-numeros.png");
	dadoTexture = Texture("Textures/diez.tga");
	dadoTexture.LoadTextureA();//siempre verificar la existencia del canal alfa

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();//3 en el índice de Model
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Lampara_M = Model();
	Lampara_M.LoadModel("Models/lampara.obj");



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
		0.3f, 0.3f,//intensidad ambiental - qué tan fuerte va a irradiar la luz el sol // el primero para la intensidad //el segundo para que abarque +/- distancia o rango de iluminación
		0.0f, 0.0f, -1.0f);//si cambiamos este valor, se verá cómo la luz blanca está apuntando a cierta parte del coche, en este caso apunta a -1 en z y por ello se ilumina el lateral izq del coche

	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	/*
	//Declaración de primer luz puntual - roja
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,//luz roja frente al coche
		0.0f, 1.0f,//no ilumina en ambiental y 1 es el número máximo posible -- cambiar el primero para aumentar el alcance/rango de la luz blanca/que tan lejos va a llegar a iluminar
		//si le das 1 al primero y le bajas al segundo el alcance será el mismo pero el color será +/- intenso al centro me parece
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;
	*/

	//=========================================================================

	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f, //color de la luz (blanca)
		0.0f, 15.0f, //intensidad ambiental e intensidad difusa
		5.5f, 2.9f, 4.1f, //posición del haz
		1.0f, 1.0f, 1.0f); //con lin exp
	pointLightCount++;

	//contador de luces spotlight
	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	/*
	//luz helicóptero
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f, //color de la luz (amarilla)
		1.0f, 2.0f, //intensidad ambiental e intensidad difusa
		0.0f, 0.0f, 0.0f, //posición del haz
		0.0f, -1.0f, 0.0f, //dirección del haz (los valores son 0 o 1)
		// -> en este caso es -1 en 'y' para que ilumine en dirección inferior del helicóptero
		1.0f, 0.0f, 0.0f, //con lin exp
		15.0f); //rango panorámico de la luz
	spotLightCount++;
	*/
	//=========================================================================

	/*
	//luz fija -- verde
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,//primero alcance y segundo tonalidad verde -- tal vez, revisar
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	*/

	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
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
		shaderList[0].SetPointLights(pointLights, pointLightCount);/////////////////////////////////////
		//pointLightCount-1 o -2 
		//segunopointlights[0=pointlights[3;
		//segunopointlights[1=pointlights[0;
		//segunopointlights[2=pointlights[1;
		//segunopointlights[3=pointlights[2;
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



		//=========================================================================
		if (mainWindow.getLuzSuiche() == true){
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else{
			shaderList[0].SetPointLights(pointLights, pointLightCount - 1);
		}
		
		//Dado de Opengl
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, 8.5f, -2.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		meshList[4]->RenderMesh();

		/*
		//Helicóptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 5.0f, 6.0));
		/////?posicionhelicoptero = model;
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();
		spotLights[1].SetPos(model[3]);
		*/

		//Lámpara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.0f, 5.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara_M.RenderModel();

		//=========================================================================

		/*
		//Instancia del coche
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 0.5f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//blending: transparencia o traslucidez		//si ponemos este agave después del piso pero antes del coche el plano se mueve de tal manera que en cierto ángulo el carro desaparece// dibuja al final lo translucido o transparente, que sea lo último de las geometrías
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);
		*/

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
//encender luz shader_light.frag comenta la línea 164 y descomenta la 163