#version 430 core

layout(location = 0) in vec4  attribute_Position;
layout(location = 1) in vec4  attribute_Color; 

out vec4    varying_Color; // Outgoing varying data sent to the fragment shader

void main(void) {

  gl_Position = attribute_Position;
  varying_Color = attribute_Color; 
 
}
