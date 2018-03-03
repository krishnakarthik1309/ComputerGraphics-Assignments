// glUtils.h: Utility programs like writing logs

char *textFileRead(char *fn);
void *read_tga(const char *filename, int *width, int *height);
int printOglError(char *file, int line);
void printShaderInfoLog(GLuint obj);
void printProgramInfoLog(GLuint obj);
