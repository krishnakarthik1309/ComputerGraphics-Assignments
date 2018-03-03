#version 110

// Vertex Shader
varying vec2 texcoord;

void main() {
	gl_Position =
	gl_ModelViewProjectionMatrix * gl_Vertex;
	texcoord = gl_Vertex.xy * vec2(0.1);
}

