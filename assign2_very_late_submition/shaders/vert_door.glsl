#version 110

// Vertex Shader
varying vec2 texcoord;

void main() {
	gl_Position =
	gl_ModelViewProjectionMatrix * gl_Vertex;
	texcoord = gl_Vertex.yx * vec2(-0.25, 0.25) + vec2(-0.5, 0.5);
}

