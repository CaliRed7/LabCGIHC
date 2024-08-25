//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�
static const char* vShaderColorRojo = "shaders/shadercolorrojo.vert";
static const char* fShaderColorRojo = "shaders/shadercolorrojo.frag";
static const char* vShaderColorVerde = "shaders/shadercolorverde.vert";
static const char* fShaderColorVerde = "shaders/shadercolorverde.frag";
static const char* vShaderColorAzul = "shaders/shadercolorazul.vert";
static const char* fShaderColorAzul = "shaders/shadercolorazul.frag";
static const char* vShaderColorCafe = "shaders/shadercolorcafe.vert";
static const char* fShaderColorCafe = "shaders/shadercolorcafe.frag";
static const char* vShaderColorVerdeOscuro = "shaders/shadercolorverdeoscuro.vert";
static const char* fShaderColorVerdeOscuro = "shaders/shadercolorverdeoscuro.frag";

float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//SEGMENTO C�DIGO BASE INICIO
//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}
//SEGMENTO C�DIGO BASE FIN

////LETRAS-INICIO
void CrearLetrasyFiguras()
{
////////////////////////////////////////////////////////////////////
//		//X			Y			Z			R		G		B     //
//		-0.0f,	0.0f,		0.0f,			0.0f,	0.0f,	0.0f, //
//		-0.0f,	0.0f,		0.0f,			0.0f,	0.0f,	0.0f, //
//		-0.0f,	0.0f,		0.0f,			0.0f,	0.0f,	0.0f, //
////////////////////////////////////////////////////////////////////

	//Letra 'C'
	GLfloat vertices_letraC[] = {
		//X			Y			Z			R		G		B
		//Tri�ngulo 1
		-0.15f,	0.84f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.46f,	0.93f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.81f,	0.84f,		0.0f,			0.0f,	255.0f,	255.0f,
		//Tri�ngulo 2
		-0.15f,	0.84f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.3f,	0.79f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.47f,	0.84f,		0.0f,			0.0f,	255.0f,	255.0f,
		//Tri�ngulo 3
		-0.47f,	0.84f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.81f,	0.84f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.81f,	0.745f,		0.0f,			0.0f,	255.0f,	255.0f,
		//Tri�ngulo 4
		-0.47f,	0.56f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.15f,	0.65f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.81f,	0.65f,		0.0f,			0.0f,	255.0f,	255.0f,
		//Tri�ngulo 5
		-0.15f,	0.65f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.3f,	0.7f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.47f,	0.65f,		0.0f,			0.0f,	255.0f,	255.0f,
		//Tri�ngulo 6
		-0.47f,	0.65f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.81f,	0.65f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.81f,	0.745f,		0.0f,			0.0f,	255.0f,	255.0f,
		//Tri�ngulo 7
		-0.66f,	0.785f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.66f,	0.705f,		0.0f,			0.0f,	255.0f,	255.0f,
		-0.81f,	0.745f,		0.0f,			0.0f,	255.0f,	255.0f,
	};
	MeshColor* letraC = new MeshColor();
	letraC->CreateMeshColor(vertices_letraC, 126);
	meshColorList.push_back(letraC);

	//Letra 'L'
	GLfloat vertices_letraL[] = {
		//X			Y			Z			R		G		B
		//Tri�ngulo 1
		-0.81f,	0.515f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.515f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.81f,	0.175f,		0.0f,			1.0f,	0.0f,	0.0f,
		//Tri�ngulo 2
		-0.81f,	0.175f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.175f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.515f,		0.0f,			1.0f,	0.0f,	0.0f,
		//Tri�ngulo 3
		-0.6f,	0.175f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.27f,	0.175f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.255f,		0.0f,			1.0f,	0.0f,	0.0f,
		//Tri�ngulo 4
		-0.27f,	0.175f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.27f,	0.255f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.6f,	0.255f,		0.0f,			1.0f,	0.0f,	0.0f,
	};
	MeshColor* letraL = new MeshColor();
	letraL->CreateMeshColor(vertices_letraL, 72);
	meshColorList.push_back(letraL);

	//Letra 'A'
	GLfloat vertices_letraA[] = {
		//X			Y			Z			R		G		B
		//Tri�ngulo 1
		-0.39f,	0.135f,		0.0f,			46.0f,	139.0f,	0.0f,
		-0.62f,	0.135f,		0.0f,			255.0f,	165.0f,	0.0f,
		-0.88f,	-0.205f,	0.0f,			255.0f,	165.0f,	0.0f,
		//Tri�ngulo 2
		-0.88f,	-0.205f,	0.0f,			255.0f,	165.0f,	0.0f,
		-0.66f,	-0.205f,	0.0f,			255.0f,	165.0f,	0.0f,
		-0.39f,	0.135f,		0.0f,			255.0f,	165.0f,	0.0f,
		//Tri�ngulo 3
		-0.39f,	0.135f,		0.0f,			255.0f,	165.0f,	0.0f,
		-0.36f,	-0.205f,	0.0f,			255.0f,	165.0f,	0.0f,
		-0.13f,	-0.205f,	0.0f,			255.0f,	165.0f,	0.0f,
		//Tri�ngulo 4
		-0.39f,	0.135f,		0.0f,			255.0f,	165.0f,	0.0f,
		-0.51f,	0.05f,		0.0f,			255.0f,	165.0f,	0.0f,
		-0.36f,	-0.205f,	0.0f,			255.0f,	165.0f,	0.0f,
		//Tri�ngulo 5
		-0.59f,	-0.08f,		0.0f,			255.0f,	165.0f,	0.0f,
		-0.63f,	-0.155f,	0.0f,			255.0f,	165.0f,	0.0f,
		-0.43f,	-0.08f,		0.0f,			255.0f,	165.0f,	0.0f,
		//Tri�ngulo 6
		-0.38f,	-0.155f,	0.0f,			255.0f,	165.0f,	0.0f,
		-0.43f,	-0.08f,		0.0f,			255.0f,	165.0f,	0.0f,
		-0.63f,	-0.155f,	0.0f,			255.0f,	165.0f,	0.0f,
	};
	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_letraA, 108);
	meshColorList.push_back(letraA);
}
////LETRAS-FIN

void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vShaderColorRojo, fShader);
	shaderList.push_back(*shaderRojo);

	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vShaderColorVerde, fShader);
	shaderList.push_back(*shaderVerde);

	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vShaderColorAzul, fShader);
	shaderList.push_back(*shaderAzul);

	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vShaderColorCafe, fShader);
	shaderList.push_back(*shaderCafe);

	Shader* shaderVerdeOscuro = new Shader();
	shaderVerdeOscuro->CreateFromFiles(vShaderColorVerdeOscuro, fShader);
	shaderList.push_back(*shaderVerdeOscuro);

}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //�ndice 0 en MeshList
	CrearCubo();//�ndice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		///INICIALES
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, 0.25f, -5.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.5f, 0.75f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		meshColorList[1]->RenderMeshColor();
		meshColorList[2]->RenderMeshColor();

		//Para el cubo y la pir�mide se usa el primer set de shaders con �ndice 0 en ShaderList
		//Casa Cubo Rojo
		shaderList[2].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.35f, -5.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(1.0f, 1.3f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Techito Pir�mide Azul
		shaderList[4].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -5.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(1.3f, 0.4f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Ventana1 Cubo Verde
		shaderList[3].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, 0.0f, -3.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.25f, -0.25f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Ventana2 Cubo Verde
		shaderList[3].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, 0.0f, -3.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.25f, -0.25f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Puerta Cubo Verde
		shaderList[3].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -3.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.3f, -0.4f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		//Tronco1 Cubo Caf�
		shaderList[5].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.9f, -5.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.15f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Pino1 Pir�mide Verde Oscuro
		shaderList[6].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.6f, -5.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//Tronco2 Cubo Caf�
		shaderList[5].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.9f, -5.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Pino2 Pir�mide Verde Oscuro
		shaderList[6].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//angulo += 0.01; //Cambiar velocidad de rotaci�n
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.6f, -5.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.0f));
		//siempre se recomienda establecer el valor de z en negativo para asegurarnos de que el objeto se dibujar� dentro del monitor
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/