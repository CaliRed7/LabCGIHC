/*
Animación por keyframes
La textura del skybox fue conseguida desde la página https ://opengameart.org/content/elyvisions-skyboxes?page=1
y edité en Gimp rotando 90 grados en sentido antihorario la imagen  sp2_up.png para poder ver continuidad.
Fuentes :
	https ://www.khronos.org/opengl/wiki/Keyframe_Animation
	http ://what-when-how.com/wp-content/uploads/2012/07/tmpcd0074_thumb.png
	*/
	//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <glew.h>
#include <glfw3.h>
#include <thread>
#include <chrono>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <fstream>
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
float sube;
float subeOffset;
float rotllanta;
float rotllantaOffset;
float rotletrero;
float rotletreroOffset;
bool showCasillas = true;


float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;



bool subir;
bool girar;
bool avanza;
//variables para la animacion del Helicoptero
bool rot1;
bool rot2;
bool rot3;
bool rot4;
int vuelta;
float movH;
float movHZ;
float movHOffset;
float rotHelices;
float rotHelicesOffset;
int rot;
//variables para la animacion del dirigible 
bool rot5;
bool rot6;
bool rot7;
bool rot8;
bool asignacion;
int vuelta2;
float movD;
float movDZ;
float movDOffset;
float rotHelicesD;
float rotHelicesDOffset;
int rotD;
int j;
//========================================================================
//variables para los dados 
int randomNum;
int rotx;
int rotz;
int roty;
int randomNum8;
int rotx8;
int rotz8;
int roty8;
float subeD;
float subeDOffset;
float rotDado;
float rotDadoOffset;
//=========================================================================
float temporizador;
float tiempoespera;
int i;
//=========================================================================
//variables para la animacion de Hipo (recorrido)
bool rotH;
bool rotH2;
bool rotH3;
bool rotH4;
float movHipo;
float movHipoOffset;
float rotHipo;

float rotBrazoD;
float rotBrazoI;
float rotPiernaD;
float rotPiernaI;
float vueltaHipo;
float casillas;
float sumDado;
float restante;
float movx;
float movz;
bool valor;
float posXInicial;
float posZInicial;
float posXFinal;
float posZFinal;
float velocidad;
bool reccorridoZ;
bool reccorridoX;
bool primerT;
float rot1H;
float rot2H;
float rotOffset;
bool cambio;
//=========================================================================
//variables para la animacion de los modelos 
int numcasilla;
int numcasilla2;
float subeModelo;
float subeModeloOffset;
float rotModelo;
float rotModeloOffset;
float subeM1;
float subeM2;
float subeM3;
float subeM4;
float subeM5;
float subeM6;
float subeM7;
float subeM8;
float subeM9;
float subeM10;
float subeM11;
float subeM12;
float subeM13;
float subeM14;
float subeM15;
float subeM16;
float subeM17;
float subeM18;
float subeM19;
float subeM20;
float subeM21;
float subeM22;
float subeM23;
float subeM24;
float subeM25;
float subeM26;
float subeM27;
float subeM28;
float subeM29;
float subeM30;
float subeM31;
float subeM32;
float subeM33;
float subeM34;
float subeM35;
float subeM36;
float subeM37;
float subeM38;
float subeM39;
float subeM40;
bool bajar;
int llamada;
//=========================================================================
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
//Camaras
Camera camera;


Texture FlechaTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture negroTexture;
Texture blancoTexture;
Texture rojoTexture;
Texture helicoptero;
Texture Dirigible;
//=========================================================================
//texturas de Hipo y Link
Texture Hipo;
Texture linkCuerpoTexture;
Texture linkOrejaTexture;
Texture linkOjoTexture;
Texture linkCabelloTexture;
Texture linkBocaTexture;
Texture linkEscudoAdelanteTexture;
Texture linkAtrasTexture;
Texture linkEspejoTexture;
Texture linkEspadaAdelanteTexture;
Texture linkEspadaAtrasTexture;
//=========================================================================
//texturas personajes casillas
Texture tmonitor;
Texture tkirbycuerpo;
Texture tkirbycara;
Texture tkirbytrans;
Texture tflor;
Texture todst;
Texture todstcasco;
Texture tconejocuerpo;
Texture tconejoojo;
Texture tastrid;
Texture telitecuerpo;
Texture telitebrazo;
Texture telitecabeza;
Texture telitepiernas;
Texture tbuho;
Texture tbuhoojo;
Texture tbuhoojito;
Texture testoico;
Texture tcuatro;
Texture tcuatrobump;
Texture tpulpo;
Texture tbocon;
Texture tapeman;
Texture tcuco;
Texture tcucoojo;
Texture tbrutacio;
Texture tflood;
Texture tfloodbrazo;
Texture tmutt;
Texture tmuttojo;
Texture tbrutilda;
Texture trata;
Texture ttienda;
Texture ttiendados;
Texture tpatapez;
Texture tflores;
Texture tpina;
Texture tcasa;
Texture tarbusto;
Texture tpanal;
Texture tchimuelo;
Texture tarbol;
Texture tarboltronco;
Texture tcofre;
Texture trompehuesos;
Texture ttormenta;
Texture tpilaruno;
Texture tpilardos;
Texture tpilartres;
Texture tpilarcuatro;
Texture tpilarcinco;
Texture tpilarseis;
Texture tpilarsiete;
Texture tmarincuerpo;
Texture tmarinojo;
Texture tmarincabeza;
Texture tmarinboca;
Texture thuevo;
Texture thuevonormal;
Texture tsc;
Texture tmoblin;
Texture tmoblinescudo;
Texture tmoblinespada;
Texture tpatan;
Texture thalouno;
Texture thalodos;
Texture thalotres;
Texture thalocuatro;
Texture tzora;
Texture tzoraojo;
//=========================================================================
//textura dado 
Texture dado10Texture;
Texture tableroTexture;
Texture tableronocheTexture;
Texture D8;
Texture D4;
Texture Lampara;

Texture RocketCarTextureUno;
Texture RocketCarTextureDos;

Model Kitt_M;
Model Llanta_M;
Model RocketCar;

Model Letrero;
Model BaseL;
Model cuerpoHelicoptero;
Model HSHelicoptero;
Model HTHelicoptero;
//=========================================================================
//Partes de Hipo
Model BrazoDH;
Model BrazoIH;
Model CuerpoH;
Model PiernaDH;
Model PiernaIH;
Model esferaPI;
Model esferaPD;
Model esferaBI;
Model esferaBD;
//Link
Model Link;
//=========================================================================
//modelos personajes casillas
Model casilla2spark;
Model casilla3kirby;
Model casilla4flor;
Model casilla5odst;
Model casilla6conejo;
Model casilla7astrid;
Model casilla8elite;
Model casilla9buho;
Model casilla10estoico;
Model casilla11cuatro;
Model casilla12pulpo;
Model casilla13bocon;
Model casilla14apeman;
Model casilla15cuco;
Model casilla16brutacio;
Model casilla17flood;
Model casilla18mutt;
Model casilla19brutilda;
Model casilla20rata;
Model casilla21tienda;
Model casilla22patapez;
Model casilla23flores;
Model casilla24pina;
Model casilla25casa;
Model casilla26arbusto;
Model casilla27panal;
Model casilla28chimuelo;
Model casilla29arbol;
Model casilla30cofre;
Model casilla31rompehuesos;
Model casilla32tormenta;
Model casilla33pilar;
Model casilla34marin;
Model casilla35huevo;
Model casilla36sc;
Model casilla37moblin;
Model casilla38patan;
Model casilla39halo;
Model casilla40zora;
//=========================================================================
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
Model Casilla_39;
Model Casilla_40;
//=============================TABLERO NOCHE=========================================
Model CasillaNoche_1;
Model CasillaNoche_2;
Model CasillaNoche_3;
Model CasillaNoche_4;
Model CasillaNoche_5;
Model CasillaNoche_6;
Model CasillaNoche_7;
Model CasillaNoche_8;
Model CasillaNoche_9;
Model CasillaNoche_10;
Model CasillaNoche_11;
Model CasillaNoche_12;
Model CasillaNoche_13;
Model CasillaNoche_14;
Model CasillaNoche_15;
Model CasillaNoche_16;
Model CasillaNoche_17;
Model CasillaNoche_18;
Model CasillaNoche_19;
Model CasillaNoche_20;
Model CasillaNoche_21;
Model CasillaNoche_22;
Model CasillaNoche_23;
Model CasillaNoche_24;
Model CasillaNoche_25;
Model CasillaNoche_26;
Model CasillaNoche_27;
Model CasillaNoche_28;
Model CasillaNoche_29;
Model CasillaNoche_30;
Model CasillaNoche_31;
Model CasillaNoche_32;
Model CasillaNoche_33;
Model CasillaNoche_34;
Model CasillaNoche_35;
Model CasillaNoche_36;
Model CasillaNoche_37;
Model CasillaNoche_38;
Model CasillaNoche_39;
Model CasillaNoche_40;
//=============================CIUDAD=========================================
Model Wraith;

Model Dado8;
Model Dado4;
Model lampara;
Model dirigible;
Model Hdirigible;
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
int random_number(int lower, int upper) {
	return (rand() % (upper - lower + 1)) + lower;
}
void toggleCasillas() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(8));
		showCasillas = !showCasillas;
	}
}

//función para teclado de keyframes 
void inputKeyframes(bool* keys);
void saveCurrentFrame();
void handleKeyframeMovement(bool* keys);
void handleAnimationPlayback();


void changeLight() {
	while (true) {
		// Primera configuración de la luz direccional
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			0.8f, 0.8f,
			0.0f, 0.0f, -1.0f);
		std::this_thread::sleep_for(std::chrono::seconds(10));

		// Segunda configuración de la luz direccional
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			0.3f, 0.3f,
			0.0f, 0.0f, -1.0f);
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}

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

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

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
obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
meshList.push_back(obj7);

calcAverageNormals(indices, 12, vertices, 32, 8, 5);

calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CrearDecaedro() {
	unsigned int decaedro_indices[] = {
		// Caras del decaedro (10 triángulos)
		0, 1, 2,    // Cara 1
		3, 4, 5,    // Cara 2
		6, 7, 8,    // Cara 3
		9, 10, 11,  // Cara 4
		12, 13, 14, // Cara 5
		15, 16, 17, // Cara 6
		18, 19, 20, // Cara 7
		21, 22, 23, // Cara 8
		24, 25, 26, // Cara 9
		27, 28, 29,  // Cara 10
	};

	GLfloat decaedro_vertices[] = {
		//x		y		z		S		T			NX		NY		NZ
		0.0f, 1.0f,  0.0f,	    0.24f,  0.46f,	0.0f,	1.0f,	1.0f,
		1.0f, 0.0f,  0.0f,		0.04,  0.26f,	0.0f,	1.0f,	1.0f,
		0.31f, 0.0f, -0.95f,	0.25f,	 0.06f,	0.0f,	1.0f,	1.0f,

		0.31f, 0.0f, -0.95f, 	0.04f,  0.68f,		01.0f,	0.0f,	01.0f,
		-0.81f, 0.0f, -0.59f,	0.03f,  0.28f,		01.0f,	0.0f,	01.0f,
		 0.0f, 1.0f, 0.0f,      0.24f,  0.48f,		01.0f,	0.0f,	01.0f,

		  0.0f, 1.0f, 0.0f,		 	0.24f,  0.52f,		1.0f,	0.0f,	1.0f,
		  -0.81f, 0.0f, -0.59f,		0.25f,  0.89f,		1.0f,	0.0f,	1.0f,
		  -0.809f, 0.0f, 0.59f,  	0.05f,	0.7f,	    1.0f,	0.0f,	1.0f,

		  -0.809f, 0.0f, 0.59f, 	0.46f,  0.7f,		1.0f,	1.0f,	0.0f,
		  0.309f, 0.0f, 0.95f,		0.27f,	0.89f,		1.0f,	1.0f,	0.0f,
		  0.0f, 1.0f, 0.0f, 	    0.27f,  0.51f,		1.0f,	1.0f,	0.0f,

		  0.0f, 1.0f, 0.0f,    		0.27f,  0.48f,	0.0f,	1.0f,	-1.0f,
		  0.309f, 0.0f, 0.95f,		0.48f,	 0.28f,	0.0f,	1.0f,	-1.0f,
		  1.0f, 0.0f,0.0f,  	    0.48f,  0.68f,	0.0f,	1.0f,	-1.0f,

		   1.0f,  0.0f,   0.0f,		0.5f, 0.28f,		0.0f,	1.0f,	1.0f,
		   0.0f, -1.0f,   0.0f,		0.7f, 0.48f,		0.0f,	1.0f,	1.0f,
		  0.31f,  0.0f, -0.95f,		0.5f, 0.67f,		0.0f,	1.0f,	1.0f,

		  0.31f, 0.0f, -0.95f, 		0.51f,  0.7f,		1.0f,	0.0f,	1.0f,
		  0.0f, -1.0f, 0.0f,  		0.71f,	0.51f,		1.0f,	0.0f,	1.0f,
		  -0.81f, 0.0f, -0.59f,  	0.71f,  0.89f,		1.0f,	0.0f,	1.0f,

		  -0.81f, 0.0f, -0.59f,  	0.74f,  0.89f,		1.0f,	0.0f,	1.0f,
		  0.0f, -1.0f, 0.0f,  		0.73f,	0.5f,		1.0f,	0.0f,	1.0f,
		  -0.809f, 0.0f, 0.59f,		0.93f,  0.7f,		1.0f,	0.0f,	1.0f,

		  -0.809f, 0.0f, 0.59f, 	0.95f,  0.68f,		1.0f,	1.0f,	0.0f,
		  0.309f, 0.0f, 0.95f,		0.94f,	0.28f,		1.0f,	1.0f,	0.0f,
		  0.0f, -1.0f, 0.0f,	    0.74f,  0.48f,		1.0f,	1.0f,	0.0f,

		  0.0f, -1.0f, 0.0f,     	0.73f,  0.46f,		0.0f,	1.0f,	-1.0f,
		  0.309f, 0.0f, 0.95f,		0.93f,	0.26f,		0.0f,	1.0f,	-1.0f,
		  1.0f, 0.0f,0.0f,  	    0.73f,  0.06f,		0.0f,	1.0f,	-1.0f,
	};

	Mesh* dad010c = new Mesh();
	dad010c->CreateMesh(decaedro_vertices, decaedro_indices, 240, 30);
	meshList.push_back(dad010c);
}
//=========================================================================================
//Función para crear el dado de 4 caras
void CrearPiramideTriangular() {
	unsigned int piramide_indices[] = {
		// Cada cara tiene tres índices, sin reutilizar vértices
		0, 1, 2,    // Cara de la base
		3, 4, 5,    // Cara lateral 1
		6, 7, 8,    // Cara lateral 2
		9, 10, 11   // Cara lateral 3
	};

	GLfloat piramide_vertices[] = {
		// Base de la pirámide (cada vértice ajustado)
		-0.5f, -0.25f, -0.333f,   0.7f, 0.5f,   0.0f, -1.0f, 0.0f,  // Vértice 0 - Base
		 0.5f, -0.25f, -0.333f,   0.32f, 0.5f,  0.0f, -1.0f, 0.0f,  // Vértice 1 - Base
		 0.0f, -0.25f,  0.667f,   0.51f, 0.27f, 0.0f, -1.0f, 0.0f,  // Vértice 2 - Base

		 // Cara lateral 1
		 -0.5f, -0.25f, -0.333f,   0.71f, 0.52f, -0.5f, 0.5f, 0.5f,  // Vértice 3
		  0.5f, -0.25f, -0.333f,   0.3f, 0.52f, -0.5f, 0.5f, 0.5f,  // Vértice 4
		  0.0f,  0.75f,  0.167f,   0.51f, 0.76f, -0.5f, 0.5f, 0.5f,  // Vértice 5

		  // Cara lateral 2
		   0.5f, -0.25f, -0.333f,   0.73f, 0.5f,  0.5f, 0.5f, 0.5f,  // Vértice 6
		   0.0f, -0.25f,  0.667f,   0.53f, 0.26f, 0.5f, 0.5f, 0.5f,  // Vértice 7
		   0.0f,  0.75f,  0.167f,   0.92f, 0.26f, 0.5f, 0.5f, 0.5f,  // Vértice 8

		   // Cara lateral 3
			0.0f, -0.25f,  0.667f,   0.3f, 0.5f, -0.5f, 0.5f, -0.5f,  // Vértice 9
		   -0.5f, -0.25f, -0.333f,   0.49f, 0.26f, -0.5f, 0.5f, -0.5f,  // Vértice 10
			0.0f,  0.75f,  0.167f,   0.1f, 0.27f, -0.5f, 0.5f, -0.5f   // Vértice 11
	};


	Mesh* piramideMesh = new Mesh();
	piramideMesh->CreateMesh(piramide_vertices, piramide_indices, 96, 12);
	meshList.push_back(piramideMesh);
}
//=========================================================================================

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}
//=========================================================================================
//Función para visualizar las caras de los dados
struct Giro {
	float x, y, z;
};

// Dado de 4 caras
Giro Vista_Caras_4[4] = {
	{0.0f, 0.0f, 0.0f},  // Cara 1
	{240.0f, 0.0f, 0.0f}, // Cara 2
	{310.0f, 240.0f, 210.0f}, // Cara 3
	{80.0f, 290.0f, 185.0f}   // Cara 4
};

// Dado de 8 caras
Giro Vista_Caras_8[8] = {
	{30.0f, 0.0f, 0.0f},   // Cara 1
	{30.0f, 170.0f, 265.0f}, // Cara 2
	{260.0f, 310.0f, 260.0f}, // Cara 3
	{245.0f, 230.0f, 150.0f}, // Cara 4
	{65.0f, 230.0f, 150.0f},  // Cara 5
	{320.0f, 200.0f, 160.0f}, // Cara 6
	{230.0f, 135.0f, 230.0f}, // Cara 7
	{230.0f, 320.0f, 40.0f}   // Cara 8
};
//=========================================================================================

///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;



//NEW// Keyframes
float posXrocketcar = 2.0, posYrocketcar = 5.0, posZrocketcar = -3.0;//valores iniciales de posición rocket car
float	movrocketcar_x = 0.0f, movrocketcar_z = 0.0f;//se van incrementando y decrementando
float girorocketcar = 0;

#define MAX_FRAMES 800//se van incrementando y decrementando
int i_max_steps = 30;//número de interpolaciones que vamos a calcular
int i_curr_steps = 8;//
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movrocketcar_x;		//Variable para PosicionX - variable auxiliar/complementaria
	float movrocketcar_z;		//Variable para PosicionZ - variable auxiliar/complementaria
	float movrocketcar_xInc;		//Variable para IncrementoX
	float movrocketcar_zInc;		//Variable para IncrementoZ
	float girorocketcar;
	float girorocketcarInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

// Función para guardar fotogramas clave en un archivo
void saveKeyFramesToFile() {
	// Abrir el fichero en modo truncado para sobrescribir el contenido existente
	std::ofstream file("keyframes.txt", std::ios::trunc);

	//	Comprobar si el archivo se ha abierto correctamente
	if (!file.is_open()) {
		std::cerr << "No se pudo abrir el archivo para escribir los keyframes.\n";
		return;
	}

	// Escribe el FrameIndex en el archivo
	file << "FrameIndex = " << FrameIndex << std::endl;

	// Cerrar el archivo después de escribir
	for (int i = 0; i < FrameIndex; ++i) {
		file << "KeyFrame[" << i << "].movrocketcar_x = " << KeyFrame[i].movrocketcar_x << "f;\n";
		file << "KeyFrame[" << i << "].movrocketcar_z = " << KeyFrame[i].movrocketcar_z << "f;\n";
		file << "KeyFrame[" << i << "].girorocketcar = " << KeyFrame[i].girorocketcar << "f;\n\n";
	}

	//	
	file.close();

	//	Notificar que se han guardado los fotogramas clave
	std::cout << "Keyframes guardados en keyframes.txt\n";
}


void saveFrame(void) // tecla TAB //función que guarda en cada keyframe el dato de movrocketcar_x, movrocketcar_z y girorocketcar
{
	printf("frameindex %d\n", FrameIndex);


	if (FrameIndex < MAX_FRAMES) {
		KeyFrame[FrameIndex].movrocketcar_x = movrocketcar_x;
		KeyFrame[FrameIndex].movrocketcar_z = movrocketcar_z;
		KeyFrame[FrameIndex].girorocketcar = girorocketcar;

		FrameIndex++;
	}
	else {
		printf("\nNo se pueden guardar más keyframes, se alcanzó el límite..\n");
	}
}


void resetElements(void) //Tecla 0
{

	movrocketcar_x = KeyFrame[0].movrocketcar_x;
	movrocketcar_z = KeyFrame[0].movrocketcar_z;
	girorocketcar = KeyFrame[0].girorocketcar;
}

void interpolation(void)
{
	KeyFrame[playIndex].movrocketcar_xInc = (KeyFrame[playIndex + 1].movrocketcar_x - KeyFrame[playIndex].movrocketcar_x) / i_max_steps;
	KeyFrame[playIndex].movrocketcar_zInc = (KeyFrame[playIndex + 1].movrocketcar_z - KeyFrame[playIndex].movrocketcar_z) / i_max_steps;
	KeyFrame[playIndex].girorocketcarInc = (KeyFrame[playIndex + 1].girorocketcar - KeyFrame[playIndex].girorocketcar) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animación entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animación con último frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Interpolación del próximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animación
			movrocketcar_x += KeyFrame[playIndex].movrocketcar_xInc;
			movrocketcar_z += KeyFrame[playIndex].movrocketcar_zInc;
			girorocketcar += KeyFrame[playIndex].girorocketcarInc;
			i_curr_steps++;
		}

	}
}

///////////////* FIN KEYFRAMES*////////////////////////////

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDecaedro();
	//=========================================================================================
	//Se manda a llamar la función para crear el dado de 4 caras
	CrearPiramideTriangular();
	//=========================================================================================
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	std::thread timerThread(toggleCasillas);
	timerThread.detach();  // Permite que el hilo se ejecute independientemente


	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();
	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	blancoTexture = Texture("Textures/blanco-opt.jpg");
	blancoTexture.LoadTextureA();
	negroTexture = Texture("Textures/negro-opt.jpg");
	negroTexture.LoadTextureA();
	rojoTexture = Texture("Textures/rojo-opt.jpg");
	rojoTexture.LoadTextureA();
	helicoptero = Texture("Textures/HH65C.jpg");
	helicoptero.LoadTextureA();
	//=======================================================================
	//Textura de Hipo
	Hipo = Texture("Textures/HiccupTeen.png");
	Hipo.LoadTextureA();
	//Textura de Link
	linkCuerpoTexture = Texture("Textures/mi_body_alb.0.png");
	linkCuerpoTexture.LoadTextureA();
	linkOrejaTexture = Texture("Textures/mi_ear_alb.0.png");
	linkOrejaTexture.LoadTextureA();
	linkOjoTexture = Texture("Textures/mi_eye_alb.0.png");
	linkOjoTexture.LoadTextureA();
	linkCabelloTexture = Texture("Textures/mi_hair_alb.png");
	linkCabelloTexture.LoadTextureA();
	linkBocaTexture = Texture("Textures/mi_mouth_alb.0.png");
	linkBocaTexture.LoadTextureA();
	linkEscudoAdelanteTexture = Texture("Textures/mi_shielda_alb.png");
	linkEscudoAdelanteTexture.LoadTextureA();
	linkAtrasTexture = Texture("Textures/mi_shieldb_alb.png");
	linkAtrasTexture.LoadTextureA();
	linkEspejoTexture = Texture("Textures/mi_shieldbmirror_alb.png");
	linkEspejoTexture.LoadTextureA();
	linkEspadaAdelanteTexture = Texture("Textures/mi_sowrda_alb.png");
	linkEspadaAdelanteTexture.LoadTextureA();
	linkEspadaAtrasTexture = Texture("Textures/mi_sowrdb_alb.png");
	linkEspadaAtrasTexture.LoadTextureA();
	//======================================================================
	//Texturas personajes casillas
	tmonitor = Texture("Textures/monitor_base.png");
	tmonitor.LoadTextureA();
	tkirbycuerpo = Texture("Textures/mi_body1_alb.png");
	tkirbycuerpo.LoadTextureA();
	tkirbycara = Texture("Textures/mi_bodytrans_alb.0.png");
	tkirbycara.LoadTextureA();
	tkirbytrans = Texture("Textures/mi_bodytrans_smt.0.png");
	tkirbytrans.LoadTextureA();
	tflor = Texture("Textures/Image_0.001.jpg");
	tflor.LoadTextureA();
	todst = Texture("Textures/odst_body_diffuse-Alpha.png");
	todst.LoadTextureA();
	todstcasco = Texture("Textures/odst_helmet_diffuse-Alpha.png");
	todstcasco.LoadTextureA();
	tconejocuerpo = Texture("Textures/mi_body_alb.png");
	tconejocuerpo.LoadTextureA();
	tconejoojo = Texture("Textures/mi_eye_alb.02.png");
	tconejoojo.LoadTextureA();
	tastrid = Texture("Textures/Astrid.png");
	tastrid.LoadTextureA();
	telitecuerpo = Texture("Textures/elite_torso.png");
	telitecuerpo.LoadTextureA();
	telitebrazo = Texture("Textures/elite_arms.png");
	telitebrazo.LoadTextureA();
	telitecabeza = Texture("Textures/elite_head.png");
	telitecabeza.LoadTextureA();
	telitepiernas = Texture("Textures/elite_legs.png");
	telitepiernas.LoadTextureA();
	tbuho = Texture("Textures/mi_body_alb.png");
	tbuho.LoadTextureA();
	tbuhoojo = Texture("Textures/mi_eye_alb.png");
	tbuhoojo.LoadTextureA();
	tbuhoojito = Texture("Textures/mi_eyelid0_alb.0.png");
	tbuhoojito.LoadTextureA();
	testoico = Texture("Textures/Stoick1024_Tex.png");
	testoico.LoadTextureA();
	tcuatro = Texture("Textures/masterchief.png");
	tcuatro.LoadTextureA();
	tcuatrobump = Texture("Textures/masterchief_bump.png");
	tcuatrobump.LoadTextureA();
	tpulpo = Texture("Textures/mi_body_albpulpo.png");
	tpulpo.LoadTextureA();
	tbocon = Texture("Textures/GobberTex.png");
	tbocon.LoadTextureA();
	tapeman = Texture("Textures/tree_object_aka_apeman.png");
	tapeman.LoadTextureA();
	tcuco = Texture("Textures/mi_body_albcuco.png");
	tcuco.LoadTextureA();
	tcucoojo = Texture("Textures/mi_eye_alb.0cuco.png");
	tcucoojo.LoadTextureA();
	tbrutacio = Texture("Textures/TuffnutTeen.png");
	tbrutacio.LoadTextureA();
	tflood = Texture("Textures/flood_infection.png");
	tflood.LoadTextureA();
	tfloodbrazo = Texture("Textures/infection_tentacles.png");
	tfloodbrazo.LoadTextureA();
	tmutt = Texture("Textures/mi_body_albmutt.png");
	tmutt.LoadTextureA();
	tmuttojo = Texture("Textures/mi_eye_alb.0mutt.png");
	tmuttojo.LoadTextureA();
	tbrutilda = Texture("Textures/RuffnutTeen.png");
	tbrutilda.LoadTextureA();
	trata = Texture("Textures/rat.png");
	trata.LoadTextureA();
	ttienda = Texture("Textures/MI_BdShop_01_alb.png");
	ttienda.LoadTextureA();
	ttiendados = Texture("Textures/MI_Bdshop_signboard_01_alb.png");
	ttiendados.LoadTextureA();
	tpatapez = Texture("Textures/Fishlegs.png");
	tpatapez.LoadTextureA();
	tflores = Texture("Textures/T_np_flowers_D.png");
	tflores.LoadTextureA();
	tpina = Texture("Textures/MI_pineapple_alb.png");
	tpina.LoadTextureA();
	tcasa = Texture("Textures/default-PBR-BaseColor.png");
	tcasa.LoadTextureA();
	tarbusto = Texture("Textures/texturefile_472.png");
	tarbusto.LoadTextureA();
	tpanal = Texture("Textures/mi_honeycomb_alb.png");
	tpanal.LoadTextureA();
	tchimuelo = Texture("Textures/SoD_PC_DRAGON_Nightfury_Body_D.png");
	tchimuelo.LoadTextureA();
	tarbol = Texture("Textures/firLeaf.png");
	tarbol.LoadTextureA();
	tarboltronco = Texture("Textures/firBark.png");
	tarboltronco.LoadTextureA();
	tcofre = Texture("Textures/mi_dungeontreasurebox_01_alb.png");
	tcofre.LoadTextureA();
	trompehuesos = Texture("Textures/BoneKnapper.png");
	trompehuesos.LoadTextureA();
	ttormenta = Texture("Textures/DeadlyNadder1024Tex.png");
	ttormenta.LoadTextureA();
	tpilaruno = Texture("Textures/pillar_of_autumn_decals.png");
	tpilaruno.LoadTextureA();
	tpilardos = Texture("Textures/pillar_of_autumn_tiler_ao.png");
	tpilardos.LoadTextureA();
	tpilartres = Texture("Textures/pillar_of_autumn1_ao.png");
	tpilartres.LoadTextureA();
	tpilarcuatro = Texture("Textures/pillar_of_autumn1_illum.png");
	tpilarcuatro.LoadTextureA();
	tpilarcinco = Texture("Textures/pillar_of_autumn2_ao.png");
	tpilarcinco.LoadTextureA();
	tpilarseis = Texture("Textures/poa_hull_detail_map.png");
	tpilarseis.LoadTextureA();
	tpilarsiete = Texture("Textures/unsc_poa_details.png");
	tpilarsiete.LoadTextureA();
	tmarincuerpo = Texture("Textures/mi_body_albmarin.png");
	tmarincuerpo.LoadTextureA();
	tmarinojo = Texture("Textures/mi_eye_alb.0marin.png");
	tmarinojo.LoadTextureA();
	tmarincabeza = Texture("Textures/mi_head_albmarin.png");
	tmarincabeza.LoadTextureA();
	tmarinboca = Texture("Textures/mi_mouth_alb.0marin.png");
	tmarinboca.LoadTextureA();
	thuevo = Texture("Textures/EggBuffalord.png");
	thuevo.LoadTextureA();
	thuevonormal = Texture("Textures/EggBuffalord_Normal.png");
	thuevonormal.LoadTextureA();
	tsc = Texture("Textures/supercarrier_diffuse.png");
	tsc.LoadTextureA();
	tmoblin = Texture("Textures/mi_body_albmoblin.png");
	tmoblin.LoadTextureA();
	tmoblinescudo = Texture("Textures/mi_shield_alb.png");
	tmoblinescudo.LoadTextureA();
	tmoblinespada = Texture("Textures/mi_sword_alb.png");
	tmoblinespada.LoadTextureA();
	tpatan = Texture("Textures/SnotloutTeen.png");
	tpatan.LoadTextureA();
	thalouno = Texture("Textures/halo inner ring destroyed.png");
	thalouno.LoadTextureA();
	thalodos = Texture("Textures/halo outer ring.png");
	thalodos.LoadTextureA();
	thalotres = Texture("Textures/halo_inner_ring_destroyed.png");
	thalotres.LoadTextureA();
	thalocuatro = Texture("Textures/halo_outer_ring.png");
	thalocuatro.LoadTextureA();
	tzora = Texture("Textures/mi_body_albzora.png");
	tzora.LoadTextureA();
	tzoraojo = Texture("Textures/mi_eye_alb.0zora.png");
	tzoraojo.LoadTextureA();

	RocketCarTextureUno = Texture("Textures/WindsheildT.bmp.png");
	RocketCarTextureUno.LoadTextureA();
	RocketCarTextureDos = Texture("Textures/rocke_vAll.bmp.png");
	RocketCarTextureDos.LoadTextureA();
	//======================================================================
	//dado 
	tableroTexture = Texture("Textures/dia.png");
	tableroTexture.LoadTextureA();
	tableronocheTexture = Texture("Textures/noche.png");
	tableronocheTexture.LoadTextureA();
	D4 = Texture("Textures/Dado4-opt.tga");
	D4.LoadTextureA();
	D8 = Texture("Textures/Dado8-opt.tga");
	D8.LoadTextureA();
	Lampara = Texture("Textures/LamparaTexture.tga");
	Lampara.LoadTextureA();
	Dirigible = Texture("Textures/DirigibleTextura.tga");
	Dirigible.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	RocketCar = Model();
	RocketCar.LoadModel("Models/rocketcar.obj");

	Letrero = Model();
	Letrero.LoadModel("Models/letrero.obj");
	BaseL = Model();
	BaseL.LoadModel("Models/baseL.obj");
	cuerpoHelicoptero = Model();
	cuerpoHelicoptero.LoadModel("Models/cuerpoHelicoptero.obj");
	HSHelicoptero = Model();
	HSHelicoptero.LoadModel("Models/HSHelicoptero.obj");
	HTHelicoptero = Model();
	HTHelicoptero.LoadModel("Models/HTHelicoptero.obj");

	//==================================================
	/////Personaje/////
	Link = Model();
	Link.LoadModel("Models/link.obj");
	/////////Modelos casillas//////////
	casilla2spark = Model();
	casilla2spark.LoadModel("Models/343halo.obj");
	casilla3kirby = Model();
	casilla3kirby.LoadModel("Models/EnemyKirby.obj");
	casilla4flor = Model();
	casilla4flor.LoadModel("Models/Blue_Blossom_1101181354.obj");
	casilla5odst = Model();
	casilla5odst.LoadModel("Models/odsthalo.obj");
	casilla6conejo = Model();
	casilla6conejo.LoadModel("Models/conejo.obj");
	casilla7astrid = Model();
	casilla7astrid.LoadModel("Models/Astrid.obj");
	casilla8elite = Model();
	casilla8elite.LoadModel("Models/elite.obj");
	casilla9buho = Model();
	casilla9buho.LoadModel("Models/buho.obj");
	casilla10estoico = Model();
	casilla10estoico.LoadModel("Models/Stoick.obj");
	casilla11cuatro = Model();
	casilla11cuatro.LoadModel("Models/masterchetos.obj");
	casilla12pulpo = Model();
	casilla12pulpo.LoadModel("Models/pulpo.obj");
	casilla13bocon = Model();
	casilla13bocon.LoadModel("Models/Gobber.obj");
	casilla14apeman = Model();
	casilla14apeman.LoadModel("Models/apeman.obj");
	casilla15cuco = Model();
	casilla15cuco.LoadModel("Models/cuco.obj");
	casilla16brutacio = Model();
	casilla16brutacio.LoadModel("Models/Tuffnut.obj");
	casilla17flood = Model();
	casilla17flood.LoadModel("Models/flood.obj");
	casilla18mutt = Model();
	casilla18mutt.LoadModel("Models/mutt.obj");
	casilla19brutilda = Model();
	casilla19brutilda.LoadModel("Models/Ruffnut.obj");
	casilla20rata = Model();
	casilla20rata.LoadModel("Models/ratahalo.obj");
	casilla21tienda = Model();
	casilla21tienda.LoadModel("Models/tienda.obj");
	casilla22patapez = Model();
	casilla22patapez.LoadModel("Models/Fishlegs.obj");
	casilla23flores = Model();
	casilla23flores.LoadModel("Models/flores.obj");
	casilla24pina = Model();
	casilla24pina.LoadModel("Models/pina.obj");
	casilla25casa = Model();
	casilla25casa.LoadModel("Models/Casa_Vikingos.obj");
	casilla26arbusto = Model();
	casilla26arbusto.LoadModel("Models/arbusto.obj");
	casilla27panal = Model();
	casilla27panal.LoadModel("Models/panal.obj");
	casilla28chimuelo = Model();
	casilla28chimuelo.LoadModel("Models/chimuelo.obj");
	casilla29arbol = Model();
	casilla29arbol.LoadModel("Models/arbol.obj");
	casilla30cofre = Model();
	casilla30cofre.LoadModel("Models/cofre.obj");
	casilla31rompehuesos = Model();
	casilla31rompehuesos.LoadModel("Models/rompehuesos.obj");
	casilla32tormenta = Model();
	casilla32tormenta.LoadModel("Models/tormenta.obj");
	casilla33pilar = Model();
	casilla33pilar.LoadModel("Models/pahalo.obj");
	casilla34marin = Model();
	casilla34marin.LoadModel("Models/Marin.obj");
	casilla35huevo = Model();
	casilla35huevo.LoadModel("Models/BuffalordEgg.obj");
	casilla36sc = Model();
	casilla36sc.LoadModel("Models/schalo.obj");
	casilla37moblin = Model();
	casilla37moblin.LoadModel("Models/moblin.obj");
	casilla38patan = Model();
	casilla38patan.LoadModel("Models/Snotlout.obj");
	casilla39halo = Model();
	casilla39halo.LoadModel("Models/halo.obj");
	casilla40zora = Model();
	casilla40zora.LoadModel("Models/zora.obj");
	//==================================================

	/////Tablero///////////////
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
	Casilla_39.LoadModel("Models/casilla39.obj");
	Casilla_40 = Model();
	Casilla_40.LoadModel("Models/casilla40.obj");
	/////Tablero Noche///////////////
	CasillaNoche_1 = Model();
	CasillaNoche_1.LoadModel("Models/tableronoche/casilla1.obj");
	CasillaNoche_2 = Model();
	CasillaNoche_2.LoadModel("Models/tableronoche/casilla2.obj");
	CasillaNoche_3 = Model();
	CasillaNoche_3.LoadModel("Models/tableronoche/casilla3.obj");
	CasillaNoche_4 = Model();
	CasillaNoche_4.LoadModel("Models/tableronoche/casilla4.obj");
	CasillaNoche_5 = Model();
	CasillaNoche_5.LoadModel("Models/tableronoche/casilla5.obj");
	CasillaNoche_6 = Model();
	CasillaNoche_6.LoadModel("Models/tableronoche/casilla6.obj");
	CasillaNoche_7 = Model();
	CasillaNoche_7.LoadModel("Models/tableronoche/casilla7.obj");
	CasillaNoche_8 = Model();
	CasillaNoche_8.LoadModel("Models/tableronoche/casilla8.obj");
	CasillaNoche_9 = Model();
	CasillaNoche_9.LoadModel("Models/tableronoche/casilla9.obj");
	CasillaNoche_10 = Model();
	CasillaNoche_10.LoadModel("Models/tableronoche/casilla10.obj");
	CasillaNoche_11 = Model();
	CasillaNoche_11.LoadModel("Models/tableronoche/casilla11.obj");
	CasillaNoche_12 = Model();
	CasillaNoche_12.LoadModel("Models/tableronoche/casilla12.obj");
	CasillaNoche_13 = Model();
	CasillaNoche_13.LoadModel("Models/tableronoche/casilla13.obj");
	CasillaNoche_14 = Model();
	CasillaNoche_14.LoadModel("Models/tableronoche/casilla14.obj");
	CasillaNoche_15 = Model();
	CasillaNoche_15.LoadModel("Models/tableronoche/casilla15.obj");
	CasillaNoche_16 = Model();
	CasillaNoche_16.LoadModel("Models/tableronoche/casilla16.obj");
	CasillaNoche_17 = Model();
	CasillaNoche_17.LoadModel("Models/tableronoche/casilla17.obj");
	CasillaNoche_18 = Model();
	CasillaNoche_18.LoadModel("Models/tableronoche/casilla18.obj");
	CasillaNoche_19 = Model();
	CasillaNoche_19.LoadModel("Models/tableronoche/casilla19.obj");
	CasillaNoche_20 = Model();
	CasillaNoche_20.LoadModel("Models/tableronoche/casilla20.obj");
	CasillaNoche_21 = Model();
	CasillaNoche_21.LoadModel("Models/tableronoche/casilla21.obj");
	CasillaNoche_22 = Model();
	CasillaNoche_22.LoadModel("Models/tableronoche/casilla22.obj");
	CasillaNoche_23 = Model();
	CasillaNoche_23.LoadModel("Models/tableronoche/casilla23.obj");
	CasillaNoche_24 = Model();
	CasillaNoche_24.LoadModel("Models/tableronoche/casilla24.obj");
	CasillaNoche_25 = Model();
	CasillaNoche_25.LoadModel("Models/tableronoche/casilla25.obj");
	CasillaNoche_26 = Model();
	CasillaNoche_26.LoadModel("Models/tableronoche/casilla26.obj");
	CasillaNoche_27 = Model();
	CasillaNoche_27.LoadModel("Models/tableronoche/casilla27.obj");
	CasillaNoche_28 = Model();
	CasillaNoche_28.LoadModel("Models/tableronoche/casilla28.obj");
	CasillaNoche_29 = Model();
	CasillaNoche_29.LoadModel("Models/tableronoche/casilla29.obj");
	CasillaNoche_30 = Model();
	CasillaNoche_30.LoadModel("Models/tableronoche/casilla30.obj");
	CasillaNoche_31 = Model();
	CasillaNoche_31.LoadModel("Models/tableronoche/casilla31.obj");
	CasillaNoche_32 = Model();
	CasillaNoche_32.LoadModel("Models/tableronoche/casilla32.obj");
	CasillaNoche_33 = Model();
	CasillaNoche_33.LoadModel("Models/tableronoche/casilla33.obj");
	CasillaNoche_34 = Model();
	CasillaNoche_34.LoadModel("Models/tableronoche/casilla34.obj");
	CasillaNoche_35 = Model();
	CasillaNoche_35.LoadModel("Models/tableronoche/casilla35.obj");
	CasillaNoche_36 = Model();
	CasillaNoche_36.LoadModel("Models/tableronoche/casilla36.obj");
	CasillaNoche_37 = Model();
	CasillaNoche_37.LoadModel("Models/tableronoche/casilla37.obj");
	CasillaNoche_38 = Model();
	CasillaNoche_38.LoadModel("Models/tableronoche/casilla38.obj");
	CasillaNoche_39 = Model();
	CasillaNoche_39.LoadModel("Models/tableronoche/casilla39.obj");
	CasillaNoche_40 = Model();
	CasillaNoche_40.LoadModel("Models/tableronoche/casilla40.obj");
	/////////////////////////////////////////////
	//=========================CIUDAD=========================
	Wraith = Model();
	Wraith.LoadModel("Models/Wraith.obj");
	/////////////////////////////////////////////
	//////////////PErsonaje/////////////////
	// Model BrazoDH;
	BrazoIH = Model();
	BrazoIH.LoadModel("Models/BrazoI.obj");
	BrazoDH = Model();
	BrazoDH.LoadModel("Models/BrazoD.obj");
	CuerpoH = Model();
	CuerpoH.LoadModel("Models/CuerpoH.obj");
	PiernaDH = Model();
	PiernaDH.LoadModel("Models/PiernaD.obj");
	PiernaIH = Model();
	PiernaIH.LoadModel("Models/PiernaI.obj");
	esferaPI = Model();
	esferaPI.LoadModel("Models/EsferaPI.obj");
	esferaPD = Model();
	esferaPD.LoadModel("Models/EsferaPD.obj");
	esferaBI = Model();
	esferaBI.LoadModel("Models/EsferaI.obj");
	esferaBD = Model();
	esferaBD.LoadModel("Models/EsferaD.obj");
	////////////////////////////////////////////

   //////////////Dados//////////////////////////
	Dado8 = Model();
	Dado8.LoadModel("Models/D8.obj");
	Dado4 = Model();
	Dado4.LoadModel("Models/D4.obj");
	///////////////////////////////////////////


	lampara = Model();
	lampara.LoadModel("Models/lampara.obj");
	dirigible = Model();
	dirigible.LoadModel("Models/dirigible.obj");
	Hdirigible = Model();
	Hdirigible.LoadModel("Models/heliceDirigible.obj");
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/sp2_rt.jpg");
	skyboxFaces.push_back("Textures/Skybox/sp2_lf.jpg");
	skyboxFaces.push_back("Textures/Skybox/sp2_dn.jpg");
	skyboxFaces.push_back("Textures/Skybox/sp2_up.jpg");
	skyboxFaces.push_back("Textures/Skybox/sp2_bk.jpg");
	skyboxFaces.push_back("Textures/Skybox/sp2_ft.jpg");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	std::thread lightThread(changeLight);
	lightThread.detach();



	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	////Declaración de primer luz puntual
	//pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f,
	//	-6.0f, 1.5f, 1.5f,
	//	0.3f, 0.2f, 0.1f);
	//pointLightCount++;

	unsigned int spotLightCount = 0;
	////linterna
	//spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
	//	0.0f, 2.0f,
	//	0.0f, 0.0f, 0.0f,
	//	0.0f, -1.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	5.0f);
	//spotLightCount++;

	////luz fija
	//spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
	//	1.0f, 2.0f,
	//	5.0f, 10.0f, 0.0f,
	//	0.0f, -5.0f, 0.0f,
	//	1.0f, 0.0f, 0.0f,
	//	15.0f);
	//spotLightCount++;

	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	//inicializando las variables del helicoptero


	movCoche = 0.0f;
	movOffset = 0.01f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;
	glm::vec3 posrocketcar = glm::vec3(2.0f, 0.0f, 0.0f);

	movH = -20.0f;
	movHZ = 25;
	movHOffset = .3f;
	rotHelices = 0.0f;
	rotHelicesOffset = 25.0f;
	i = 0;
	rot1 = true;
	rot2 = false;
	rot3 = false;
	rot4 = false;
	vuelta = 0;
	rot = 0;
	//=====================================================================
	//inicializando las variables de de los dados
	rotx = 0;
	rotz = 0;
	roty = 0;
	rotx8 = 0;
	rotz8 = 0;
	roty8 = 0;
	subeD = 20.0f;
	subeDOffset = .5f;
	rotDado = 0.0f;
	rotDadoOffset = 7.0f;
	//=====================================================================
	//inicializando las variables del dirigible
	movD = 75.0f;
	movDZ = 25.0f;
	movDOffset = .3f;
	rotHelicesD = 0.0f;
	rotHelicesDOffset = 25.0f;
	j = 0;
	rot5 = true;
	rot6 = false;
	rot7 = false;
	rot8 = false;
	vuelta2 = 0;
	rotD = 0;
	asignacion = false;
	//=====================================================================
	//inicializando las variables de la animacion de Hipo
	movHipo = 0.0f;
	sumDado = 0.0f;
	casillas = 0;
	posXInicial = 3.75f;
	posXFinal = 3.75f;
	posZInicial = -3.75f;
	posZFinal = -3.75f;
	movz = posZInicial;
	movx = posXInicial;
	restante = 0;
	rotH = true;
	rotH2 = false;
	rotH3 = false;
	rotH4 = false;
	valor = false;
	velocidad = 0.5;
	reccorridoX = false;
	reccorridoZ = false;
	rot1H = 0.0f;
	rot2H = 0.0f;
	rotOffset = 5.0f;
	bool xCompleto = false; // Indica si se completó el recorrido en el eje X
	bool zCompleto = false; // Indica si se completó el recorrido en el eje Z
	primerT = true;
	cambio = true;
	//=====================================================================
	//inicializando las variables de la animacion de los modelos 
	numcasilla = 0;
	numcasilla2 = 0;
	temporizador = 0;
	subeModelo = 0.0;
	subeModeloOffset = 0.1f;
	rotModelo = 0.0f;
	rotModeloOffset = 5.0;
	subeM1 = -12.0f;
	subeM2 = -12.0f;
	subeM3 = -12.0f;
	subeM4 = -12.0f;
	subeM5 = -12.0f;
	subeM6 = -12.0f;
	subeM7 = -12.0f;
	subeM8 = -12.0f;
	subeM9 = -12.0f;
	subeM10 = -12.0f;
	subeM11 = -12.0f;
	subeM12 = -12.0f;
	subeM13 = -12.0f;
	subeM14 = -12.0f;
	subeM15 = -12.0f;
	subeM16 = -12.0f;
	subeM17 = -12.0f;
	subeM18 = -12.0f;
	subeM19 = -12.0f;
	subeM20 = -12.0f;
	subeM21 = -12.0f;
	subeM22 = -12.0f;
	subeM23 = -12.0f;
	subeM24 = -12.0f;
	subeM25 = -12.0f;
	subeM26 = -12.0f;
	subeM27 = -12.0f;
	subeM28 = -12.0f;
	subeM29 = -12.0f;
	subeM30 = -12.0f;
	subeM31 = -12.0f;
	subeM32 = -12.0f;
	subeM33 = -12.0f;
	subeM34 = -12.0f;
	subeM35 = -12.0f;
	subeM36 = -12.0f;
	subeM37 = -12.0f;
	subeM38 = -12.0f;
	subeM39 = -12.0f;
	subeM40 = -12.0f;
	llamada = 0;
	bajar = false;
	float inicioTemporizador = -1.0f;
	float tiempoTranscurrido;
	/*arrancar = glfwGetTime();
	arrancar = glfwSetTime(0);*/
	////Loop mientras no se cierra la ventana
	double tiempoActual = glfwGetTime();

	//---------PARA TENER KEYFRAMES GUARDADOS NO VOLATILES QUE SIEMPRE SE UTILIZARAN SE DECLARAN AQUÍ
		//Se agregan nuevos frames 

	printf("\nTeclas para uso de Keyframes:\n1.-Presionar barra espaciadora para reproducir animacion.\n2.-Presionar 0 para volver a habilitar reproduccion de la animacion\n");
	printf("3.-Presiona TAB para guardar frame\n4.-Presiona SHIFT para habilitar guardar nuevo frame\n5.-Presiona 1 para mover en -X\n6.-Presiona 2 para habilitar mover en -X\n");
	printf("7.-Presiona 3 para mover en +X\n8.-Presiona 4 para habilitar mover en +X\n");
	printf("9.-Presiona 5 para mover en -z\n10.-Presiona 6 para habilitar mover en -z\n");
	printf("11.-Presiona 7 para mover en +z\n12.-Presiona 8 para habilitar mover en +z\n");
	printf("13.-Presiona 9 para rotar 45 grados \n14.-Presiona R para habilitar rotar en 45 grados \n");



	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		angulovaria += 0.5f * deltaTime;



		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//-------Para Keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

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
		glm::mat4 modelaux2(1.0);
		glm::mat4 modelaux3(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();



		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movCoche - 50.0f, 0.5f, -2.0f));
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


		model = glm::mat4(1.0);
		posrocketcar = glm::vec3(posXrocketcar + movrocketcar_x, posYrocketcar, posZrocketcar + movrocketcar_z);
		model = glm::translate(model, posrocketcar);
		model = glm::translate(model, glm::vec3(-10.0f, -5.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, girorocketcar * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//color = glm::vec3(0.0f, 1.0f, 0.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RocketCar.RenderModel();






		//Helicoptero
		if (rot1) {
			if (movH < 75) {
				if (vuelta == 0) {
					rot = -90;
					vuelta++;
				}

				movH += movHOffset * deltaTime;
				rotHelices -= rotHelicesOffset * deltaTime;
			}
			else {
				rot2 = true;
				rot1 = false;
				rot += 90;
			}
		}
		else if (rot2) {
			if (movHZ > -75) {

				movHZ -= movHOffset * deltaTime;
				rotHelices -= rotHelicesOffset * deltaTime;
			}
			else {
				rot3 = true;
				rot2 = false;
				rot += 90;
			}
		}
		else if (rot3) {
			if (movH > -20) {

				movH -= movHOffset * deltaTime;
				rotHelices -= rotHelicesOffset * deltaTime;
			}
			else {
				rot4 = true;
				rot3 = false;
				rot += 90;
			}
		}
		else if (rot4) {
			if (movHZ < 25) {

				movHZ += movHOffset * deltaTime;
				rotHelices -= rotHelicesOffset * deltaTime;
			}
			else {
				rot1 = true;
				rot4 = false;
				rot += 90;
			}
		}
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movH, 20.0f, movHZ));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, rot * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoHelicoptero.RenderModel();
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 4.5f, -6.5f));
		model = glm::rotate(model, rotHelices * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));*/
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HSHelicoptero.RenderModel();
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.750f, -0.4f, 25.95f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));*/
		model = glm::rotate(model, rotHelices * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HTHelicoptero.RenderModel();


		//=========================PERSONAJES=========================


		//=========================MODELOS CASILLAS==================
		if (mainWindow.getTURN_ON_OFF()) {
			if (subeM2 < -0.39) {
				subeM2 += subeModeloOffset * deltaTime;
				subeM3 += subeModeloOffset * deltaTime;
				subeM5 += subeModeloOffset * deltaTime;
				subeM6 += subeModeloOffset * deltaTime;
				subeM7 += subeModeloOffset * deltaTime;
				subeM8 += subeModeloOffset * deltaTime;
				subeM9 += subeModeloOffset * deltaTime;
				subeM10 += subeModeloOffset * deltaTime;
				subeM11 += subeModeloOffset * deltaTime;
				subeM12 += subeModeloOffset * deltaTime;
				subeM13 += subeModeloOffset * deltaTime;
				subeM14 += subeModeloOffset * deltaTime;
				subeM15 += subeModeloOffset * deltaTime;
				subeM16 += subeModeloOffset * deltaTime;
				subeM17 += subeModeloOffset * deltaTime;
				subeM18 += subeModeloOffset * deltaTime;
				subeM19 += subeModeloOffset * deltaTime;
				subeM20 += subeModeloOffset * deltaTime;
				subeM21 += subeModeloOffset * deltaTime;
				subeM22 += subeModeloOffset * deltaTime;
				subeM23 += subeModeloOffset * deltaTime;
				subeM25 += subeModeloOffset * deltaTime;
				subeM26 += subeModeloOffset * deltaTime;
				subeM28 += subeModeloOffset * deltaTime;
				subeM29 += subeModeloOffset * deltaTime;
				subeM30 += subeModeloOffset * deltaTime;
				subeM34 += subeModeloOffset * deltaTime;
				subeM35 += subeModeloOffset * deltaTime;
				subeM36 += subeModeloOffset * deltaTime;
				subeM37 += subeModeloOffset * deltaTime;
				subeM38 += subeModeloOffset * deltaTime;
				subeM40 += subeModeloOffset * deltaTime;
			}
			if (subeM1 < 0.225) {
				subeM1 += subeModeloOffset * deltaTime;
			}
			if (subeM4 < 1.39) {
				subeM4 += subeModeloOffset * deltaTime;
				subeM24 += subeModeloOffset * deltaTime;

			}
			if (subeM27 < 1.0) {
				subeM27 += subeModeloOffset * deltaTime;
				subeM31 += subeModeloOffset * deltaTime;
				subeM32 += subeModeloOffset * deltaTime;

			}
			if (subeM33 < 0.39) {
				subeM33 += subeModeloOffset * deltaTime;
			}
			if (subeM39 < 6.39) {
				subeM39 += subeModeloOffset * deltaTime;
			}
			numcasilla = 0;
		}
		else {
			if (!mainWindow.getTURN_ON_OFF() && numcasilla == 0) {
				if (subeM2 > -12.0) {
					subeM2 -= subeModeloOffset * deltaTime;
					subeM3 -= subeModeloOffset * deltaTime;
					subeM5 -= subeModeloOffset * deltaTime;
					subeM6 -= subeModeloOffset * deltaTime;
					subeM7 -= subeModeloOffset * deltaTime;
					subeM8 -= subeModeloOffset * deltaTime;
					subeM9 -= subeModeloOffset * deltaTime;
					subeM10 -= subeModeloOffset * deltaTime;
					subeM11 -= subeModeloOffset * deltaTime;
					subeM12 -= subeModeloOffset * deltaTime;
					subeM13 -= subeModeloOffset * deltaTime;
					subeM14 -= subeModeloOffset * deltaTime;
					subeM15 -= subeModeloOffset * deltaTime;
					subeM16 -= subeModeloOffset * deltaTime;
					subeM17 -= subeModeloOffset * deltaTime;
					subeM18 -= subeModeloOffset * deltaTime;
					subeM19 -= subeModeloOffset * deltaTime;
					subeM20 -= subeModeloOffset * deltaTime;
					subeM21 -= subeModeloOffset * deltaTime;
					subeM22 -= subeModeloOffset * deltaTime;
					subeM23 -= subeModeloOffset * deltaTime;
					subeM25 -= subeModeloOffset * deltaTime;
					subeM26 -= subeModeloOffset * deltaTime;
					subeM28 -= subeModeloOffset * deltaTime;
					subeM29 -= subeModeloOffset * deltaTime;
					subeM30 -= subeModeloOffset * deltaTime;
					subeM34 -= subeModeloOffset * deltaTime;
					subeM35 -= subeModeloOffset * deltaTime;
					subeM36 -= subeModeloOffset * deltaTime;
					subeM37 -= subeModeloOffset * deltaTime;
					subeM38 -= subeModeloOffset * deltaTime;
					subeM40 -= subeModeloOffset * deltaTime;
				}
				if (subeM1 > -12.0) {
					subeM1 -= subeModeloOffset * deltaTime;
				}
				if (subeM4 > -12.0) {
					subeM4 -= subeModeloOffset * deltaTime;
					subeM24 -= subeModeloOffset * deltaTime;
				}
				if (subeM27 > -12.0) {
					subeM27 -= subeModeloOffset * deltaTime;
					subeM31 -= subeModeloOffset * deltaTime;
					subeM32 -= subeModeloOffset * deltaTime;
				}
				if (subeM33 > -12.0) {
					subeM33 -= subeModeloOffset * deltaTime;
				}
				if (subeM39 > -12.0) {
					subeM39 -= subeModeloOffset * deltaTime;
				}
			}
		}
		//===========================================================
		//Elevacion de los modelos en el tablero
		if (numcasilla == 1) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM1 < 0.225 && bajar == false) {
				subeM1 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM1 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM1 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 2) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;

			if (subeM2 < -0.39 && bajar == false) {
				subeM2 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM2 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM2 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 3) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM3 < -0.39 && bajar == false) {
				subeM3 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM3 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM3 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 4) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM4 < 1.39 && bajar == false) {
				subeM4 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM4 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM4 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 5) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM5 < -0.39 && bajar == false) {
				subeM5 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM5 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM5 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 6) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM6 < -0.39 && bajar == false) {
				subeM6 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM6 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM6 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 7) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM7 < -0.39 && bajar == false) {
				subeM7 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM7 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM7 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 8) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM8 < -0.39 && bajar == false) {
				subeM8 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM8 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM8 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 9) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM9 < -0.39 && bajar == false) {
				subeM9 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM9 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM9 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 10) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM10 < -0.39 && bajar == false) {
				subeM10 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM10 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM10 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 11) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM11 < -0.39 && bajar == false) {
				subeM11 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM11 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM11 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 12) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM12 < -0.39 && bajar == false) {
				subeM12 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM12 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM12 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 13) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM13 < -0.39 && bajar == false) {
				subeM13 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM13 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM13 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 14) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM14 < -0.39 && bajar == false) {
				subeM14 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM14 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM14 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 15) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM15 < -0.39 && bajar == false) {
				subeM15 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM15 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM15 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 16) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM16 < -0.39 && bajar == false) {
				subeM16 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM16 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM16 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 17) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM17 < -0.39 && bajar == false) {
				subeM17 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM17 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM17 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 18) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM18 < -0.39 && bajar == false) {
				subeM18 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM18 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM18 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 19) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM19 < -0.39 && bajar == false) {
				subeM19 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM19 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM19 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}

		if (numcasilla == 20) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM20 < -0.39 && bajar == false) {
				subeM20 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM20 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM20 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 21) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM21 < -0.39 && bajar == false) {
				subeM21 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM21 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM21 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 22) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM22 < -0.39 && bajar == false) {
				subeM22 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM22 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM22 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 23) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM23 < -0.39 && bajar == false) {
				subeM23 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM23 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM23 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 24) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM24 < 1.39 && bajar == false) {
				subeM24 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM24 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM24 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 25) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM25 < -0.39 && bajar == false) {
				subeM25 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM25 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM25 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 26) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM26 < -0.39 && bajar == false) {
				subeM26 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM26 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM26 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 27) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM27 < 1.0 && bajar == false) {
				subeM27 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM27 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM27 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 28) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM28 < -0.39 && bajar == false) {
				subeM28 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM28 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM28 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 29) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM29 < -0.39 && bajar == false) {
				subeM29 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM29 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM29 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 30) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM30 < -0.39 && bajar == false) {
				subeM30 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM30 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM30 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 31) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM31 < 1.0 && bajar == false) {
				subeM31 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM31 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM31 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 32) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM32 < 1.0 && bajar == false) {
				subeM32 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM32 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM32 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 33) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM33 < 0.39 && bajar == false) {
				subeM33 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM33 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM33 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 34) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM34 < -0.39 && bajar == false) {
				subeM34 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM34 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM34 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 35) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM35 < -0.39 && bajar == false) {
				subeM35 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM35 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM35 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 36) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM36 < -0.39 && bajar == false) {
				subeM36 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM36 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM36 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 37) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM37 < -0.39 && bajar == false) {
				subeM37 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM37 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM37 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 38) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM38 < -0.39 && bajar == false) {
				subeM38 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM38 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM38 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 39) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM39 < 6.39 && bajar == false) {
				subeM39 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM39 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM39 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}
		if (numcasilla == 40) {
			if (inicioTemporizador < 0) {
				inicioTemporizador = glfwGetTime();
			}
			tiempoTranscurrido = glfwGetTime() - inicioTemporizador;
			if (subeM40 < -0.39 && bajar == false) {
				subeM40 += subeModeloOffset * deltaTime;
				rotModelo += rotModeloOffset * deltaTime;
			}
			else if (tiempoTranscurrido < 4.0) {
				bajar = true;
			}
			else if (subeM40 > -12 && bajar == true && tiempoTranscurrido > 4) {
				subeM40 -= subeModeloOffset * deltaTime;
				rotModelo -= rotModeloOffset * deltaTime;
			}
			else {
				numcasilla = 0;
				inicioTemporizador = -1.0f;
				bajar = false;
			}
		}


		//Personaje - Link
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9, subeM1, -3.9));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Link.RenderModel();

		//Casilla 2 - 343 Guilty Spark
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM2, -10.3f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla2spark.RenderModel();


		//Casilla 3 - Anti-Kirby
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM3, -15.25f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla3kirby.RenderModel();

		//Casilla 4 - Flor del dragón
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM4, -20.2f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla4flor.RenderModel();

		//Casilla 5 - Soldado ODST
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM5, -25.15f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla5odst.RenderModel();


		//Casilla 6 - Conejo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM6, -30.1f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla6conejo.RenderModel();


		//Casilla 7 - Astrid
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM7, -35.05f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla7astrid.RenderModel();

		//Casilla 8 - Soldado Elite
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM8, -40.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla8elite.RenderModel();


		//Casilla 9 - Búho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM9, -44.95f));
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla9buho.RenderModel();


		//Casilla 10 - Estoico
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM10, -49.9f));
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla10estoico.RenderModel();


		//Casilla 11 - Spartan-IV - Esquina 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.9f, subeM11, -56.3f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla11cuatro.RenderModel();


		//Casilla 12 - Octorok
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.3f, subeM12, -64.3f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla12pulpo.RenderModel();


		//Casilla 13 - Bocón
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.25f, subeM13, -64.3f));
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla13bocon.RenderModel();


		//Casilla 14 - Caveman
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.2f, subeM14, -64.3f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla14apeman.RenderModel();


		//Casilla 15 - Cuco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.15f, subeM15, -64.3f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla15cuco.RenderModel();


		//Casilla 16 - Brutacio
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.1f, subeM16, -64.3f));
		model = glm::scale(model, glm::vec3(4.5, 4.5f, 4.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla16brutacio.RenderModel();


		//Casilla 17 - Espora Flood
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.05f, subeM17, -64.3f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla17flood.RenderModel();

		//Casilla 18 - Mutt
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, subeM18, -64.3f));
		model = glm::scale(model, glm::vec3(5.5f, 5.5f, 5.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla18mutt.RenderModel();

		//Casilla 19 - Brutilda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.95f, subeM19, -64.3f));
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla19brutilda.RenderModel();

		//Casilla 20 - Rata
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(49.9f, subeM20, -64.3f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla20rata.RenderModel();

		//Casilla 21 - Tienda de Herramientas - Esquina 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM21, -56.3f));
		model = glm::scale(model, glm::vec3(3.75f, 3.75f, 3.75f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla21tienda.RenderModel();

		//Casilla 22 - Patapez
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM22, -49.9f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla22patapez.RenderModel();

		//Casilla 23 - Flores Rojas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM23, -44.95f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla23flores.RenderModel();

		//Casilla 24 - Piña
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM24, -40.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla24pina.RenderModel();

		//Casilla 25 - Casa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM25, -35.05f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla25casa.RenderModel();

		//Casilla 26 - Arbustos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM26, -30.1f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla26arbusto.RenderModel();

		//Casilla 27 - Panal
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM27, -25.15f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla27panal.RenderModel();

		//Casilla 28 - Chimuelo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM28, -20.2f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla28chimuelo.RenderModel();

		//Casilla 29 - Árbol
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM29, -15.25f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla29arbol.RenderModel();

		//Casilla 30 - Cofre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM30, -10.3f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla30cofre.RenderModel();

		//Casilla 31 - Rompe Huesos - Esquina 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(64.3f, subeM31, -3.9f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla31rompehuesos.RenderModel();

		//Casilla 32 - Tormenta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(49.9f, subeM32, 5.9f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla32tormenta.RenderModel();

		//Casilla 33 - Pillar de Autumn
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.95f, subeM33, 5.9f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla33pilar.RenderModel();

		//Casilla 34 - Marin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, subeM34, 5.9f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.5f, 4.5f, 4.5f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla34marin.RenderModel();

		//Casilla 35 - Nido huevo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.05f, subeM35, 5.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla35huevo.RenderModel();

		//Casilla 36 - Supercarguero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.1f, subeM36, 5.9f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla36sc.RenderModel();

		//Casilla 37 - Moblin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.15f, subeM37, 5.9f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla37moblin.RenderModel();

		//Casilla 38 - Patán
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.2f, subeM38, 5.9f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla38patan.RenderModel();

		//Casilla 39 - Instalación 04
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.25f, subeM39, 5.9f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla39halo.RenderModel();

		//Casilla 40 - Zora
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.3f, subeM40, 5.9f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::rotate(model, rotModelo * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casilla40zora.RenderModel();

		if (showCasillas) {
			//=========================TABLERO=========================
	//Casilla 1 - Salida - Esquina 1
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_1.RenderModel();

			//Casilla 2 - 343 Guilty Spark
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -10.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_2.RenderModel();

			//Casilla 3 - Anti-Kirby
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -15.25f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_3.RenderModel();

			//Casilla 4 - Flor del dragón
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -20.2f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_4.RenderModel();

			//Casilla 5 - Soldado ODST
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -25.15f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_5.RenderModel();

			//Casilla 6 - Conejo
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -30.1f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_6.RenderModel();

			//Casilla 7 - Astrid
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -35.05f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_7.RenderModel();

			//Casilla 8 - Soldado Elite
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -40.0f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_8.RenderModel();

			//Casilla 9 - Búho
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -44.95f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_9.RenderModel();

			//Casilla 10 - Estoico
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -49.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_10.RenderModel();

			//Casilla 11 - Spartan-IV - Esquina 2
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(3.9f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_11.RenderModel();

			//Casilla 12 - Octorok
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(10.3f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_12.RenderModel();

			//Casilla 13 - Bocón
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(15.25f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_13.RenderModel();

			//Casilla 14 - Caveman
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(20.2f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_14.RenderModel();

			//Casilla 15 - Cuco
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(25.15f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_15.RenderModel();

			//Casilla 16 - Brutacio
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(30.1f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_16.RenderModel();

			//Casilla 17 - Espora Flood
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(35.05f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_17.RenderModel();

			//Casilla 18 - Mutt
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(40.0f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_18.RenderModel();

			//Casilla 19 - Brutilda
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(44.95f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_19.RenderModel();

			//Casilla 20 - Rata
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(49.9f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_20.RenderModel();

			//Casilla 20 - Tienda de Herramientas - Esquina 3
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -56.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_21.RenderModel();

			//Casilla 22 - Patapez
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -49.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_22.RenderModel();

			//Casilla 23 - Flores Rojas
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -44.95f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_23.RenderModel();

			//Casilla 24 - Piña
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -40.0f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_24.RenderModel();

			//Casilla 25 - Casa
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -35.05f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_25.RenderModel();

			//Casilla 26 - Árboles
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -30.1f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_26.RenderModel();

			//Casilla 27 - Panal
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -25.15f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_27.RenderModel();

			//Casilla 28 - Chimuelo
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -20.2f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_28.RenderModel();

			//Casilla 29 - Árboles
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -15.25f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_29.RenderModel();

			//Casilla 30 - Cofre
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -10.3f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_30.RenderModel();

			//Casilla 31 - Rompe Huesos - Esquina 4
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(56.3f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_31.RenderModel();

			//Casilla 32 - Tormenta
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(49.9f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_32.RenderModel();

			//Casilla 33 - Pillar de Autumn
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(44.95f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_33.RenderModel();

			//Casilla 34 - Marin
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(40.0f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_34.RenderModel();

			//Casilla 35 - Nido huevo
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(35.05f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_35.RenderModel();

			//Casilla 36 - Supercarguero
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(30.1f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_36.RenderModel();

			//Casilla 37 - Moblin
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(25.15f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_37.RenderModel();

			//Casilla 38 - Patán
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(20.2f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_38.RenderModel();

			//Casilla 39 - Instalación 04
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(15.25f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_39.RenderModel();

			//Casilla 40 - Zora
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(10.3f, -0.39f, -3.9f));
			model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Casilla_40.RenderModel();
		}
		//=========================CIUDAD=========================
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.3f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Wraith.RenderModel();

		//=========================TABLERO NOCHE=========================
		//CasillaNoche 1 - Salida - Esquina 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_1.RenderModel();

		//CasillaNoche 2 - 343 Guilty Spark
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -10.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_2.RenderModel();

		//CasillaNoche 3 - Anti-Kirby
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -15.25f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_3.RenderModel();

		//CasillaNoche 4 - Flor del dragón
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -20.2f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_4.RenderModel();

		//CasillaNoche 5 - Soldado ODST
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -25.15f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_5.RenderModel();

		//CasillaNoche 6 - Conejo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -30.1f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_6.RenderModel();

		//CasillaNoche 7 - Astrid
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -35.05f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_7.RenderModel();

		//CasillaNoche 8 - Soldado Elite
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -40.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_8.RenderModel();

		//CasillaNoche 9 - Búho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -44.95f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_9.RenderModel();

		//CasillaNoche 10 - Estoico
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -49.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_10.RenderModel();

		//CasillaNoche 11 - Spartan-IV - Esquina 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.9f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_11.RenderModel();

		//CasillaNoche 12 - Octorok
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.3f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_12.RenderModel();

		//CasillaNoche 13 - Bocón
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.25f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_13.RenderModel();

		//CasillaNoche 14 - Caveman
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.2f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_14.RenderModel();

		//CasillaNoche 15 - Cuco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.15f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_15.RenderModel();

		//CasillaNoche 16 - Brutacio
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.1f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_16.RenderModel();

		//CasillaNoche 17 - Espora Flood
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.05f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_17.RenderModel();

		//CasillaNoche 18 - Mutt
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_18.RenderModel();

		//CasillaNoche 19 - Brutilda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.95f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_19.RenderModel();

		//CasillaNoche 20 - Rata
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(49.9f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_20.RenderModel();

		//CasillaNoche 20 - Tienda de Herramientas - Esquina 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -56.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_21.RenderModel();

		//CasillaNoche 22 - Patapez
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -49.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_22.RenderModel();

		//CasillaNoche 23 - Flores Rojas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -44.95f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_23.RenderModel();

		//CasillaNoche 24 - Piña
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -40.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_24.RenderModel();

		//CasillaNoche 25 - Casa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -35.05f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_25.RenderModel();

		//CasillaNoche 26 - Árboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -30.1f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_26.RenderModel();

		//CasillaNoche 27 - Panal
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -25.15f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_27.RenderModel();

		//CasillaNoche 28 - Chimuelo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -20.2f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_28.RenderModel();

		//CasillaNoche 29 - Árboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -15.25f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_29.RenderModel();

		//CasillaNoche 30 - Cofre
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -10.3f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_30.RenderModel();

		//CasillaNoche 31 - Rompe Huesos - Esquina 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(56.3f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_31.RenderModel();

		//CasillaNoche 32 - Tormenta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(49.9f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_32.RenderModel();

		//CasillaNoche 33 - Pillar de Autumn
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(44.95f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_33.RenderModel();

		//CasillaNoche 34 - Marin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_34.RenderModel();

		//CasillaNoche 35 - Nido huevo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(35.05f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_35.RenderModel();

		//CasillaNoche 36 - Supercarguero
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.1f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_36.RenderModel();

		//CasillaNoche 37 - Moblin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.15f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_37.RenderModel();

		//CasillaNoche 38 - Patán
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.2f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_38.RenderModel();

		//CasillaNoche 39 - Instalación 04
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.25f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_39.RenderModel();

		//CasillaNoche 40 - Zora
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.3f, -0.39f, -3.9f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CasillaNoche_40.RenderModel();

		/////////////////////////Dados///////////////////////////////////////////
		//bloque de codigo para que lso dados muestren sus caras de forma aleatori
		if (mainWindow.getTURN_ON_OFF3() == true) {
			if (subeD > 1) {
				subeD -= subeDOffset * deltaTime;
				rotDado -= rotDadoOffset * deltaTime;
				rotx = rotDado;
				rotz = rotDado;
				rotx8 = rotDado;
				rotz8 = rotDado;
				asignacion = false;
			}
			else if (subeD < 1 && !asignacion) {
				randomNum = random_number(1, 4);
				rotx = 0;
				rotz = 0;
				roty = 0;
				rotx8 = 0;
				rotz8 = 0;
				roty8 = 0;
				randomNum8 = random_number(1, 8);

				Giro rotSelect = Vista_Caras_4[randomNum - 1];
				Giro rotSelect2 = Vista_Caras_8[randomNum8 - 1];
				sumDado = randomNum + randomNum8;
				numcasilla2 += sumDado;
				if (numcasilla2 > 40) {
					numcasilla2 -= 40;
				}
				numcasilla = numcasilla2;
				if (primerT) {
					sumDado = (sumDado * 5) - 5;
					primerT = false;
				}
				else {
					sumDado = (sumDado * 5);
				}

				rotx = rotSelect.x;
				rotz = rotSelect.z;
				roty = rotSelect.y;
				rotx8 = rotSelect2.x;
				rotz8 = rotSelect2.z;
				roty8 = rotSelect2.y;
				asignacion = true;
				valor = true;
			}


		}
		else if (mainWindow.getTURN_ON_OFF4() == true) {
			if (subeD < 20) {
				subeD += subeDOffset * deltaTime;
				rotx = 0;
				rotz = 0;
				roty = 0;
				rotx8 = 0;
				rotz8 = 0;
				roty8 = 0;
			}
		}



		//dado 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, subeD, -015.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, rotx * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, roty * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotz * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		D4.UseTexture();
		meshList[5]->RenderMesh();



		//////dado 8
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, subeD, -015.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, rotx8 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, roty8 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotz8 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado8.RenderModel();
		//=======================================================
		////////////////////ILUMINACION/////////////////////////////////////////
		//lampara 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.6, 0.1f, -0.75));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();
		//lampara 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(59.4f, 0.1f, -0.75));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();
		//lampara 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.6, 0.1f, -59.4f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();
		//lampara 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(59.4f, 0.1f, -59.4f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();
		//////////////////////////////////////////////////////////////////////////////////
		// 
		// 
		// //animacion dirigible//
		if (rot5) {
			if (movDZ > -75) {
				if (vuelta2 == 0) {
					rotD = 180;
					vuelta2++;
				}

				movDZ -= movDOffset * deltaTime;
				rotHelicesD -= rotHelicesDOffset * deltaTime;
			}
			else {
				rot6 = true;
				rot5 = false;
				rotD += 90;
			}
		}
		else if (rot6) {
			if (movD > -20) {

				movD -= movDOffset * deltaTime;
				rotHelicesD -= rotHelicesDOffset * deltaTime;
			}
			else {
				rot7 = true;
				rot6 = false;
				rotD += 90;
			}
		}
		else if (rot7) {
			if (movDZ < 25) {

				movDZ += movDOffset * deltaTime;
				rotHelicesD -= rotHelicesDOffset * deltaTime;
			}
			else {
				rot8 = true;
				rot7 = false;
				rotD += 90;
			}
		}
		else if (rot8) {
			if (movD < 75) {

				movD += movDOffset * deltaTime;
				rotHelicesD -= rotHelicesDOffset * deltaTime;
			}
			else {
				rot5 = true;
				rot8 = false;
				rotD += 90;
			}
		}
		// //Dirigible referencia inicial 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movD, 18.0f, movDZ));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::rotate(model, rotD * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirigible.RenderModel();

		//Hélice Dirigible 1
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.57f, 3.1f, 0.85f));
		model = glm::rotate(model, rotHelicesD * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hdirigible.RenderModel();

		//Hélice Dirigible 2
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.9f, -0.54f, 0.85f));
		model = glm::rotate(model, rotHelicesD * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hdirigible.RenderModel();

		//Hélice Dirigible 3
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.1f, -0.46f, 0.85f));
		model = glm::rotate(model, rotHelicesD * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hdirigible.RenderModel();
		//=======================================================
		//Recorrido en el tablero , falta ajustar la rotacion 
		//ajustar rotacions de brazos, piernas
		//que se asemeje el movimiento de caminata y no de teletransportacion
		if (valor) {
			// Movimiento en el eje -Z
			if (rotH) {
				posZFinal = posZInicial - sumDado;
				if (posZFinal < -53.75f) { // Si excede el límite inferior en Z
					restante = -53.75f - posZFinal; // Exceso en Z
					posZFinal = -53.75f;
					rotH = false; rotH2 = true;
					rotHipo -= 90;

					if (posZFinal == -53.75f) {

						posXFinal = posXInicial + restante; // Pasa el resto al eje +X

					}
				}

			}
			// Movimiento en el eje +X
			else if (rotH2) {
				posXFinal = posXInicial + sumDado;
				if (posXFinal > 53.75f) { // Si excede el límite superior en X
					restante = posXFinal - 53.75f; // Exceso en X
					posXFinal = 53.75f;
					rotH2 = false; rotH3 = true;
					rotHipo -= 90;

					if (posXFinal == 53.75f) {
						posZFinal = posZInicial + restante; // Pasa el resto al eje +Z

					}
				}
			}
			// Movimiento en el eje +Z
			else if (rotH3) {
				posZFinal = posZInicial + sumDado;
				if (posZFinal > -3.75f) { // Si excede el límite superior en Z
					restante = posZFinal - -3.75f; // Exceso en Z
					posZFinal = -3.75f;
					rotH3 = false; rotH4 = true;
					rotHipo -= 90;

					if (posZFinal == -3.75f) {
						posXFinal = posXInicial - restante; // Pasa el resto al eje -X

					}
				}
			}
			// Movimiento en el eje -X
			else if (rotH4) {
				posXFinal = posXInicial - sumDado;
				if (posXFinal < 3.75f) { // Si excede el límite inferior en X
					restante = 3.75f - posXFinal; // Exceso en X
					posXFinal = 3.75f;
					rotH4 = false; rotH = true;
					rotHipo -= 90;

					if (posXFinal == 3.75f) {
						posZFinal = posZInicial - restante; // Pasa el resto al eje -Z

					}
				}
			}

			valor = false;

		}

		// Movimiento gradual hacia la posición final en el eje actual
		if (movx != posXFinal) {
			movx += (posXFinal > movx) ? velocidad : -velocidad;
			if (std::abs(movx - posXFinal) < velocidad) {
				movx = posXFinal; // Asegura precisión en el punto final
				posXInicial = movx; // Actualiza la posición inicial para el siguiente movimiento
			}
			if (cambio) {
				rot1H += rotOffset * deltaTime;
				rot2H -= rotOffset * deltaTime;
				if (rot1H > 45) {
					cambio = false;
				}
			}
			else {
				rot1H -= rotOffset * deltaTime;
				rot2H += rotOffset * deltaTime;
				if (rot1H < -45) {
					cambio = true;
				}
			}
		}
		if (movz != posZFinal) {
			movz += (posZFinal > movz) ? velocidad : -velocidad;
			if (std::abs(movz - posZFinal) < velocidad) {
				movz = posZFinal; // Asegura precisión en el punto final
				posZInicial = movz; // Actualiza la posición inicial para el siguiente movimiento
			}
			if (cambio) {
				rot1H += rotOffset * deltaTime;
				rot2H -= rotOffset * deltaTime;
				if (rot1H > 45) {
					cambio = false;
				}
			}
			else {
				rot1H -= rotOffset * deltaTime;
				rot2H += rotOffset * deltaTime;
				if (rot1H < -45) {
					cambio = true;
				}
			}
		}


		//////////////////////////////////////////////////////////////////////////////////////////
		// Configuración de modelo en la posición calculada
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(movx, 3.1f, movz));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotHipo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoH.RenderModel();
		//////esferaBD
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.175f, 0.425f, 0.0f));
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esferaBD.RenderModel();
		//////BrazoD
		model = modelaux2;
		model = glm::translate(model, glm::vec3(-0.35f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::rotate(model, glm::radians(rot1H), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoDH.RenderModel();

		//////esferaBI
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.15f, 0.425f, 0.0f));
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esferaBI.RenderModel();

		//////BrazoI
		model = modelaux2;
		model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
		modelaux2 = model;
		model = glm::rotate(model, glm::radians(rot2H), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoIH.RenderModel();

		//////esferaPD
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.085f, -0.065f, 0.0f));
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esferaBD.RenderModel();
		////////PiernaD
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.085f, -0.1f, 0.05f));
		modelaux2 = model;
		model = glm::rotate(model, glm::radians(rot2H), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaDH.RenderModel();


		//////esferaPI

		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.065f, -0.065f, 0.0f));
		modelaux2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esferaBI.RenderModel();
		/////PiernaI
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.105f, -0.1f, 0.0f));
		modelaux2 = model;
		model = glm::rotate(model, glm::radians(rot1H), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PiernaIH.RenderModel();
		////=========================================================


		glDisable(GL_BLEND);
		tiempoActual = glfwGetTime();
		srand(time(0));



		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

void inputKeyframes(bool* keys) {
	if (keys[GLFW_KEY_SPACE] && reproduciranimacion < 1) {
		handleAnimationPlayback();
	}

	if (keys[GLFW_KEY_0] && habilitaranimacion < 1 && reproduciranimacion > 0) {
		std::cout << "Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora\n";
		reproduciranimacion = 0;
		habilitaranimacion++;
	}

	if (keys[GLFW_KEY_TAB] && guardoFrame < 1) {
		saveCurrentFrame();
	}

	if (keys[GLFW_KEY_LEFT_SHIFT] && reinicioFrame < 1) {
		guardoFrame = 0;
		reinicioFrame++;
		std::cout << "Ya puedes guardar otro frame presionando la tecla TAB\n";
	}

	handleKeyframeMovement(keys);
}

void handleAnimationPlayback() {
	if (!play && FrameIndex > 1) {
		resetElements();
		interpolation();
		play = true;
		playIndex = 0;
		i_curr_steps = 0;
		reproduciranimacion++;
		std::cout << "Presiona 0 para habilitar reproducir de nuevo la animación\n";
		habilitaranimacion = 0;
	}
	else {
		play = false;
	}
}

void saveCurrentFrame() {
	saveFrame();
	saveKeyFramesToFile();
	std::cout << "movrocketcar_x: " << movrocketcar_x << "\n"
		<< "movrocketcar_z: " << movrocketcar_z << "\n"
		<< "girorocketcar: " << girorocketcar << "\n"
		<< "Presiona SHIFT para habilitar guardar otro frame\n";
	guardoFrame++;
	reinicioFrame = 0;
}

void handleKeyframeMovement(bool* keys) {
	static int movementState = 0;

	if (keys[GLFW_KEY_1] && movementState == 0) {
		movrocketcar_x -= 1.0f;
		std::cout << "morocketcar_x: " << movrocketcar_x << "\n";
		movementState = 1;
		std::cout << "Presiona la tecla 2 para habilitar la variable\n";
	}
	else if (keys[GLFW_KEY_2] && movementState == 1) {
		movementState = 0;
		std::cout << "Ya puedes modificar movrocketcar_x presionando la tecla 1\n";
	}
	else if (keys[GLFW_KEY_3] && movementState == 0) {
		movrocketcar_x += 1.0f;
		std::cout << "movrocketcar_x: " << movrocketcar_x << "\n";
		movementState = 3;
		std::cout << "Presiona la tecla 4 para habilitar la variable\n";
	}
	else if (keys[GLFW_KEY_4] && movementState == 3) {
		movementState = 0;
		std::cout << "Ya puedes modificar movrocketcar_x presionando la tecla 3\n";
	}
	else if (keys[GLFW_KEY_5] && movementState == 0) {
		movrocketcar_z -= 1.0f;
		std::cout << "movrocketcar_z: " << movrocketcar_z << "\n";
		movementState = 5;
		std::cout << "Presiona la tecla 6 para habilitar la variable\n";
	}
	else if (keys[GLFW_KEY_6] && movementState == 5) {
		movementState = 0;
		std::cout << "Ya puedes modificar movrocketcar_z presionando la tecla 5\n";
	}
	else if (keys[GLFW_KEY_7] && movementState == 0) {
		movrocketcar_z += 1.0f;
		std::cout << "movrocketcar_z: " << movrocketcar_z << "\n";
		movementState = 7;
		std::cout << "Presiona la tecla 8 para habilitar la variable\n";
	}
	else if (keys[GLFW_KEY_8] && movementState == 7) {
		movementState = 0;
		std::cout << "Ya puedes modificar movrocketcar_z presionando la tecla 7\n";
	}
	else if (keys[GLFW_KEY_9] && movementState == 0) {
		girorocketcar -= 45.0f;
		std::cout << "girorocketcar: " << girorocketcar << "\n";
		movementState = 9;
		std::cout << "Presiona la tecla R para habilitar la variable girorocketcar\n";
	}
	else if (keys[GLFW_KEY_R] && movementState == 9) {
		movementState = 0;
		std::cout << "Ya puedes modificar girorocketcar presionando la tecla 9\n";
	}
}