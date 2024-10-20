#include "Window.h"
float angulo = 0, angulo1 = 0, angulo2 = 0, angulo3 = 0, angulo4 = 0;
int aux = 0, aux1 = 0, aux2 = 0, aux3 = 0, aux4 = 0;

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	muevehelicoptero = 2.0f;
	LuzSuiche = true;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	articulacion7 = 0.0f;
	articulacion8 = 0.0f;
	articulacion9 = 0.0f;
	articulacion10 = 0.0f;
	articulacion11 = 0.0f;
	articulacion12 = 0.0f;
	TURN_ON_OFF = true;
	TURN_ON_OFF2 = true;
	TURN_ON_OFF3 = false;
	TURN_ON_OFF4 = false;
	empezar = false;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica09: Animacion 1", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)//atrás auto
	{
		theWindow-> muevex += 1.0;
	}
	if (key == GLFW_KEY_U)//adelante auto
	{
		theWindow-> muevex -= 1.0;
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
		}
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_E) {
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R) {
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T) {
		theWindow->rotaz += 10.0;
	}
	if (key == GLFW_KEY_F) {
		theWindow->articulacion1 += 10.0;

	}
	if (key == GLFW_KEY_G) {

		if (angulo >= 45) {
			aux = 1;
		}
		if (angulo <= -45) {
			aux = 0;
		}
		if (aux == 0) {
			theWindow->articulacion2 += 10.0;
			angulo = angulo + 10;
		}
		else {
			theWindow->articulacion2 -= 10.0;
			angulo = angulo - 10;
		}
	}
	if (key == GLFW_KEY_H) {
		if (angulo1 >= 45) {
			aux1 = 1;
		}
		if (angulo1 <= -45) {
			aux1 = 0;
		}
		if (aux1 == 0) {
			theWindow->articulacion3 += 10.0;
			angulo1 = angulo1 + 10;
		}
		else {
			theWindow->articulacion3 -= 10.0;
			angulo1 = angulo1 - 10;
		}
	}
	if (key == GLFW_KEY_J){
		if (angulo2 >= 45) {
			aux2 = 1;
		}
		if (angulo2 <= -45) {
			aux2 = 0;
		}
		if (aux2 == 0) {
			theWindow->articulacion4 += 10.0;
			angulo2 = angulo2 + 10;
		}
		else {
			theWindow->articulacion4 -= 10.0;
			angulo2 = angulo2 - 10;
		}
	}
	if (key == GLFW_KEY_K){
		if (angulo3 >= 45) {
			aux3 = 1;
		}
		if (angulo3 <= -45) {
			aux3 = 0;
		}
		if (aux3 == 0) {
			theWindow->articulacion5 += 10.0;
			angulo3 = angulo3 + 10;
		}
		else {
			theWindow->articulacion5 -= 10.0;
			angulo3 = angulo3 - 10;
		}
	}
	if (key == GLFW_KEY_L){
		if (angulo4 >= 0) {
			aux4 = 1;
			theWindow->TURN_ON_OFF2 = false;
			theWindow->TURN_ON_OFF3 = false;
			theWindow->TURN_ON_OFF4 = false;
		}
		if (angulo4 <= -15) {
			aux4 = 0;
			theWindow->TURN_ON_OFF2 = true;
			theWindow->TURN_ON_OFF3 = false;
			theWindow->TURN_ON_OFF4 = false;
		}
		if (aux4 == 0) {
			theWindow->articulacion6 += 10.0;
			angulo4 = angulo4 + 10;
		}
		else {
			theWindow->articulacion6 -= 10.0;
			angulo4 = angulo4 - 10;
		}
	}
	if (key == GLFW_KEY_Z){//tirar dado
		theWindow->TURN_ON_OFF3 = true;
		theWindow->TURN_ON_OFF4 = false;
	}
	if (key == GLFW_KEY_X){//recuperar dado
		theWindow->TURN_ON_OFF3 = false;
		theWindow->TURN_ON_OFF4 = true;
	}
	if (key == GLFW_KEY_C){
		theWindow->articulacion9 += 10.0;
	}
	if (key == GLFW_KEY_V){
		theWindow->articulacion10 -= 10.0;
	}
	if (key == GLFW_KEY_B){
		theWindow->articulacion11 += 10.0;
	}
	if (key == GLFW_KEY_N){
		theWindow->articulacion12 += 10.0;
	}
	if (key == GLFW_KEY_O){
		theWindow->TURN_ON_OFF = true;
	}
	if (key == GLFW_KEY_P){
		theWindow->TURN_ON_OFF = false;
	}
	if (key == GLFW_KEY_M){
		theWindow->empezar = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS){
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
	}
	///////////////////////////////////////////////////////////////////////

	if (key >= 0 && key < 1024){
		if (action == GLFW_PRESS){
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE){
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}