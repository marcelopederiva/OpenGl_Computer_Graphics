#version 430 core

in vec4  vertex;
in vec4  color; 

 uniform mat4 u_projMatrix;
 uniform mat4 u_modelViewMatrix;

out vec4    vColor; // Outgoing varying data sent to the fragment shader

void main(void) {

	vec4 xVertex = u_modelViewMatrix * vertex;
  	gl_Position = u_projMatrix * xVertex;
  	vColor = color; 
 
}


