#version 430 core

in vec4  vertex;
in vec4  color; 

 uniform mat4 u_projMatrix;
 uniform mat4 u_modelViewMatrix;
 uniform vec4 u_modelquaternion;
 vec4 q = vec4(u_modelquaternion);
  
out vec4    vColor; // Outgoing varying data sent to the fragment shader

void main(void) {

	
	vec4 xVertex = u_modelViewMatrix * vertex;
	vec4 Pos = u_projMatrix * xVertex;
	vec3 v = Pos.xyz;
	
	v = (2 * q.x * q.x - 1) * v + 2 * dot(q.yzw,v) * q.yzw + 2 * q.x * cross(q.yzw, v);
	
  	gl_Position = vec4(v.xyz,1.0);
  	
  	vColor = color; 
 
}


