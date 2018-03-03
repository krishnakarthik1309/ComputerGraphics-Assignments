#version 110

// Vertex Shader
varying vec2 texcoord;

void main() {
	gl_Position =
	gl_ModelViewProjectionMatrix * gl_Vertex;
	texcoord = gl_Vertex.zy * vec2(100.0);
}

