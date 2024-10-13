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
Texture sensorTexture;

Model Blackhawk_M;
Model Lampara_M;
Model Auto_M;
Model Auto_Cofre;
Model Llanta_M;
Model Sensor_M;

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

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

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
	sensorTexture = Texture("Textures/sensor.png");
	sensorTexture.LoadTextureA();

	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Lampara_M = Model();
	Lampara_M.LoadModel("Models/lampara.obj");
	Auto_M = Model();
	Auto_M.LoadModel("Models/cochebase.obj");
	Auto_Cofre = Model();
	Auto_Cofre.LoadModel("Models/autocofre.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta.obj");
	Sensor_M = Model();
	Sensor_M.LoadModel("Models/sensor.obj");

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

	//luz lámpara
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f, //color de la luz (blanca)
		0.0f, 15.0f, //intensidad ambiental e intensidad difusa
		//0.0f, 0.0f, 0.0f, //posición del haz
		5.5f, 2.9f, 4.1f, //posición del haz
		1.0f, 1.0f, 1.0f); //con lin exp
	pointLightCount++;
	
	//luz sensor de concha marina
	pointLights[1] = PointLight(1.0f, 0.2f, 0.6f, //color de la luz (rosa mexicano)
		5.0f, 15.0f, //intensidad ambiental e intensidad difusa
		5.0f, 2.0f, -15.05f, //posición del haz
		1.0f, 0.3f, 1.0f); //con lin exp
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
	
	//cofre
	spotLights[1] = SpotLight(
		1.0f, 0.5f, 0.2f,//color de la luz (naranja cálido)
		0.0f, 5.0f, //intensidad ambiental e intensidad difusa
		-3.25f, 0.67f, -0.11f,//posición inicial del cofre (se actualizará cada frame)
		0.0f, 0.0f, -1.0f,//dirección del haz
		1.0f, 0.0f, 0.0f,//con lin exp
		30.0f//rango panorámico de la luz
	);
	spotLightCount++;

	/*
	//faro delantero
	spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f,// Color de la luz (azul)
		5.0f, 5.0f, //intensidad ambiental e intensidad difusa
		0.0f, 0.0f, 0.0f, //posición del haz
		-1.0f, 0.0f, 0.0f, //dirección del haz (los valores son 0 o 1)
		//-> en este caso es -1 en x para que ilumine en dirección frontal del coche como si fuera faro
		0.25f, 0.005f, 0.0025f, //con lin exp
		//1.0f, 0.01f, 0.005f,
		45.0f); //rango panorámico de la luz
	spotLightCount++;
	
	//faro trasero
	spotLights[3] = SpotLight(0.0f, 0.0f, 1.0f,// Color de la luz (azul)
		5.0f, 5.0f, //intensidad ambiental e intensidad difusa
		0.0f, 0.0f, 0.0f, //posición del haz
		1.0f, 0.0f, 0.0f, //dirección del haz (los valores son 0 o 1)
		//-> en este caso es 1 en x para que ilumine en dirección trasera del coche como si fuera faro
		0.25f, 0.005f, 0.0025f, //con lin exp
		//1.0f, 0.01f, 0.005f,
		45.0f); //rango panorámico de la luz
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

		//=========================================================================
		
		//Encendido/apagado
		if (mainWindow.getLuzSuiche() == true) {
			shaderList[0].SetPointLights(pointLights, pointLightCount);
		}
		else {
			shaderList[0].SetPointLights(pointLights, pointLightCount - 2);//2 fuentes de luz
		}

		//Helicóptero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevehelicoptero(), 10.0f, -3.0));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();

		//Lámpara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, -1.0f, 5.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Lampara_M.RenderModel();

		//Sensor de concha marina
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.0f, 1.32f, -15.0f));
		model = glm::scale(model, glm::vec3(2.75f, 2.75f, 2.75f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Sensor_M.RenderModel();

		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 1.4f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_M.RenderModel();
		//spotLights[2].SetPos(model[3]);
		//spotLights[3].SetPos(model[3]);

		// Auto Cofre
		model = glm::mat4(1.0);
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.25f, 0.67f, -0.11f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.4f, 2.4f, 2.4f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(-1.0f, 0.0f, 0.0f)); // Abrir cofre 'F'
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(1.0f, 0.0f, 0.0f));  // Cerrar cofre 'G'
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Auto_Cofre.RenderModel();

		//actualización spotlight del cofre
		{
			//calcular la posición actual del cofre
			glm::vec3 trunkPosition = glm::vec3(model[3]); //extrae la posición de la matriz modelo

			//calcula la dirección del spotlight basado en las rotaciones
			//asumiendo que el cofre rota alrededor del eje X para abrir/cerrar
			float angleX = glm::radians(mainWindow.getarticulacion1() + mainWindow.getarticulacion2());
			glm::vec3 direction = glm::vec3(
				sin(angleX),
				1.0f
				-cos(angleX),
				0.0f //se ajusta según la dirección deseada
			);
			direction = glm::normalize(direction);

			//actualización de la posición y dirección del spotlight del cofre (spotLights[1])
			spotLights[1].SetFlash(
				trunkPosition,//posición del spotlight en el cofre
				direction//dirección del spotlight
			);
		}

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.71f, -1.3f, 2.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(-1.0f, 0.0f, 0.0f));//rotar llantas adelante 'H'
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(1.0f, 0.0f, 0.0f));//rotar llantas atrás  'J'
		//color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		//model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		model = glm::translate(model, glm::vec3(3.91f, -1.3f, 2.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(-1.0f, 0.0f, 0.0f));//rotar llantas adelante 'H'
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(1.0f, 0.0f, 0.0f));//rotar llantas atrás  'J'
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.71f, -1.3f, -2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));//rotar llantas adelante 'H'
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(-1.0f, 0.0f, 0.0f));//rotar llantas atrás  'J'
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();
		
		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(3.91f, -1.3f, -2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));//rotar llantas adelante 'H'
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(-1.0f, 0.0f, 0.0f));//rotar llantas atrás  'J'
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//=========================================================================
	
		/*
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