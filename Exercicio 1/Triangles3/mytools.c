/*
 * mytools.c
 *
 *  Created on: 29 de jan de 2021
 *      Author: JMario
 */
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>

// generateShader: reads shader code from ASCII file and compiles code
// ---------------------------------------------------------------------------------------------
unsigned int generateShader(int type, char* filename ) {
	int shader;

	fprintf(stdout, "generateShader::start\n");
	fflush(stdout);

	// input shader file
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "generateShader::fopen::%s\n", filename);
		exit(1);
	}

	// get size
	fseek(file, 0L, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);

	// read file
	char shaderText[fileSize];
	char *shaderSource[] = {(char *) &shaderText};

	if(fread(shaderText, sizeof(char), fileSize, file) != fileSize) {
		fprintf(stderr, "generateShader::fread::%s\n", filename);
		exit(1);
	}

	// close file
	if(fclose(file)) {
		fprintf(stderr, "generateShader::fclose::%s\n", filename);
		exit(1);
	}

	// Create GPU shader handle
	shader = glCreateShader(type);
	glShaderSource(shader, 1, (const char * const*) shaderSource, NULL);

	glCompileShader(shader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		fprintf(stderr, "generateShader::shader compilation failed:: %s\n", infoLog);
		exit(1);
	}

	fprintf(stdout, "generateShader::end\n");
	fflush(stdout);
	return shader;
}




