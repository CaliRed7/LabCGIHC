//Esta es la que hay que descomentar para la cámara
#version 330
layout (location =0) in vec3 pos;
out vec4 vColor;
uniform mat4 model;
uniform mat4 projection;
uniform vec3 color;
uniform mat4 view;
void main()
{
	gl_Position=projection*view*model*vec4(pos,1.0f); //alterna comentando entre esta; descomentando esta y comentando la de abajo accedes a la cámara WASD
	//gl_Position=projection*model*vec4(pos,1.0f); //y esta; descomentando esta y comentando la de arriba accedes a la rotación ERT
	vColor=vec4(color,1.0f);

}