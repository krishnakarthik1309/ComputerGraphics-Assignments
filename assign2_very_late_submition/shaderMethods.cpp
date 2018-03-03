#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

void initializeGlew () {
	glewInit();
	if (glewIsSupported("GL_VERSION_2_0")) {
		printf("Ready for OpenGL 2.0\n");
	}
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}
}

GLuint make_texture(const char *filename)
{
    int width, height;
    void *pixels = read_tga(filename, &width, &height);
    GLuint texture;

    if (!pixels)
        return 0;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_REPEAT);
    glTexImage2D(
        GL_TEXTURE_2D, 0,           /* target, level */
        GL_RGB8,                    /* internal format */
        width, height, 0,           /* width, height, border */
        GL_BGR, GL_UNSIGNED_BYTE,   /* external format, type */
        pixels                      /* pixels */
    );
    free(pixels);
    return texture;
}

void setTextures (GLuint program, char *uniformVarName, int index, const char *textureFile) {
	GLuint texture = make_texture(textureFile);
	if (texture == 0) {
		printf("failed to make texture: %s\n", textureFile);
		return;
	}
	GLuint textureLocation = glGetUniformLocation(program, uniformVarName);

	GLuint textureIndex = GL_TEXTURE0;
	if (index == 0)
		textureIndex = GL_TEXTURE0;
	else if (index == 1)
		textureIndex = GL_TEXTURE1;
	else if (index == 2)
		textureIndex = GL_TEXTURE2;

	glActiveTexture(textureIndex);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureLocation, index);
}

// call initializeGlew once before glutMainLoop()
GLuint setShaders (char *vertShaderFile, char *fragShaderFile) {
	GLuint v, f, p;
	char *vs = NULL,*fs = NULL;
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead(vertShaderFile);
	fs = textFileRead(fragShaderFile);

	const char * vv = vs;
	const char * ff = fs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	printShaderInfoLog(v);
	printShaderInfoLog(f);

	p = glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);

	glBindAttribLocation(p, 0, "position");
	glBindFragDataLocation(p, 0, "outputF");

	glLinkProgram(p);
	printProgramInfoLog(p);

	glUseProgram(p);
	return p;
}
