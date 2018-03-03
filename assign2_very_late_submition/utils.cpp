#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *textFileRead(char *fn) {


	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fp = fopen(fn,"rt");

		if (fp != NULL) {

      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

static short le_short(unsigned char *bytes)
{
    return bytes[0] | ((char)bytes[1] << 8);
}

void *read_tga(const char *filename, int *width, int *height)
{
    struct tga_header {
       char  id_length;
       char  color_map_type;
       char  data_type_code;
       unsigned char  color_map_origin[2];
       unsigned char  color_map_length[2];
       char  color_map_depth;
       unsigned char  x_origin[2];
       unsigned char  y_origin[2];
       unsigned char  width[2];
       unsigned char  height[2];
       char  bits_per_pixel;
       char  image_descriptor;
    } header;
    int i, color_map_size, pixels_size;
    FILE *f;
    size_t read;
    void *pixels;

    f = fopen(filename, "rb");

    if (!f) {
        fprintf(stderr, "Unable to open %s for reading\n", filename);
        return NULL;
    }

    read = fread(&header, 1, sizeof(header), f);

    if (read != sizeof(header)) {
        fprintf(stderr, "%s has incomplete tga header\n", filename);
        fclose(f);
        return NULL;
    }
    if (header.data_type_code != 2) {
        fprintf(stderr, "%s is not an uncompressed RGB tga file\n", filename);
        fclose(f);
        return NULL;
    }
    if (header.bits_per_pixel != 24) {
        fprintf(stderr, "%s is not a 24-bit uncompressed RGB tga file\n", filename);
        fclose(f);
        return NULL;
    }

    for (i = 0; i < header.id_length; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete id string\n", filename);
            fclose(f);
            return NULL;
        }

    color_map_size = le_short(header.color_map_length) * (header.color_map_depth/8);
    for (i = 0; i < color_map_size; ++i)
        if (getc(f) == EOF) {
            fprintf(stderr, "%s has incomplete color map\n", filename);
            fclose(f);
            return NULL;
        }

    *width = le_short(header.width); *height = le_short(header.height);
    pixels_size = *width * *height * (header.bits_per_pixel/8);
    pixels = malloc(pixels_size);

    read = fread(pixels, 1, pixels_size, f);
    fclose(f);

    if (read != pixels_size) {
        fprintf(stderr, "%s has incomplete image\n", filename);
        free(pixels);
        return NULL;
    }

    return pixels;
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}
