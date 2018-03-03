// shaders.h: setup vertex and fragment shaders

GLuint setShaders (char *vertShaderFile, char *fragShaderFile);
void initializeGlew ();
void setTextures (GLuint program, char *uniformVarName, int index, const char *textureFile);
