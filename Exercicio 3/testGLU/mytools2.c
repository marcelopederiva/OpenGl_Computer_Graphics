/*
 * mytools.c
 *
 *  Created on: 29 de jan de 2021
 *      Author: JMario
 */
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <math.h>
#define PI 3.14159265
// generateShader: reads shader code from ASCII file and compiles code
// ---------------------------------------------------------------------------------------------

void matrixIdentity4x4(float m[16]){
	m[0]=1.0f;
	m[1]=0.0f;
	m[2]=0.0f;
	m[3]=0.0f;
	m[4]=0.0f;
	m[5]=1.0f;
	m[6]=0.0f;
	m[7]=0.0f;
	m[8]=0.0f;
	m[9]=0.0f;
	m[10]=1.0f;
	m[11]=0.0f;
	m[12]=0.0f;
	m[13]=0.0f;
	m[14]=0.0f;
	m[15]=1.0f;

}

void matrixMultiply4x4(float m2[16], float m1[16], float m[16]){
	// primeira coluna
	m[0]= m2[0]*m1[0] + m2[4]*m1[1] + m2[8]*m1[2]  + m2[12]*m1[3];
	m[1]= m2[1]*m1[0] + m2[5]*m1[1] + m2[9]*m1[2]  + m2[13]*m1[3];
	m[2]= m2[2]*m1[0] + m2[6]*m1[1] + m2[10]*m1[2] + m2[14]*m1[3];
	m[3]= m2[3]*m1[0] + m2[7]*m1[1] + m2[11]*m1[2] + m2[15]*m1[3];
	// segunda coluna
	m[4]= m2[0]*m1[4] + m2[4]*m1[5] + m2[8]*m1[6]   + m2[12]*m1[7];
	m[5]= m2[1]*m1[4] + m2[5]*m1[5] + m2[9]*m1[6]   + m2[13]*m1[7];
	m[6]= m2[2]*m1[4] + m2[6]*m1[5] + m2[10]*m1[6]  + m2[14]*m1[7];
	m[7]= m2[3]*m1[4] + m2[7]*m1[5] + m2[11]*m1[6]  + m2[15]*m1[7];
	// terceira coluna
	m[8]=  m2[0]*m1[8] + m2[4]*m1[9] + m2[8]*m1[10]   + m2[12]*m1[11];
	m[9]=  m2[1]*m1[8] + m2[5]*m1[9] + m2[9]*m1[10]   + m2[13]*m1[11];
	m[10]= m2[2]*m1[8] + m2[6]*m1[9] + m2[10]*m1[10]  + m2[14]*m1[11];
	m[11]= m2[3]*m1[8] + m2[7]*m1[9] + m2[11]*m1[10]  + m2[15]*m1[11];
	// quarta coluna
	m[12]= m2[0]*m1[12] + m2[4]*m1[13] + m2[8]*m1[14]   + m2[12]*m1[15];
	m[13]= m2[1]*m1[12] + m2[5]*m1[13] + m2[9]*m1[14]   + m2[13]*m1[15];
	m[14]= m2[2]*m1[12] + m2[6]*m1[13] + m2[10]*m1[14]  + m2[14]*m1[15];
	m[15]= m2[3]*m1[12] + m2[7]*m1[13] + m2[11]*m1[14]  + m2[15]*m1[15];

}

void matrixTranslate4x4(float x, float y, float z, float m[16]){
	m[0]=1.0f;
	m[1]=0.0f;
	m[2]=0.0f;
	m[3]=0.0f;
	m[4]=0.0f;
	m[5]=1.0f;
	m[6]=0.0f;
	m[7]=0.0f;
	m[8]=0.0f;
	m[9]=0.0f;
	m[10]=1.0f;
	m[11]=0.0f;
	m[12] = x;
	m[13] = y;
	m[14] = z;
	m[15]=1.0f;

}


void matrixRotate4x4(float angle, float x, float y, float z, float m[16]){
	float xn,yn,zn;
	double a;
	a= PI/180;
	xn = x/(sqrt(x*x+y*y+z*z));
	yn = y/(sqrt(x*x+y*y+z*z)); 
	zn = z/(sqrt(x*x+y*y+z*z)); 

	m[0]= xn*xn*(1-cos(a*angle))+cos(a*angle);
	m[1]= xn*yn*(1-cos(a*angle))+zn*sin(a*angle);
	m[2]= xn*zn*(1-cos(a*angle))-yn*sin(a*angle);
	m[3]=0.0f;
	m[4]= xn*yn*(1-cos(a*angle))-zn*sin(a*angle);
	m[5]= yn*yn*(1-cos(a*angle))+cos(a*angle);
	m[6]= yn*zn*(1-cos(a*angle))+xn*sin(a*angle);
	m[7]=0.0f;
	m[8]= xn*zn*(1-cos(a*angle))+yn*sin(a*angle);
	m[9]= yn*zn*(1-cos(a*angle))-xn*sin(a*angle);
	m[10]= zn*zn*(1-cos(a*angle))+cos(a*angle);
	m[11]=0.0f;
	m[12]=0.0f;
	m[13]=0.0f;
	m[14]=0.0f;
	m[15]=1.0f;
}


void matrixScale4x4(float x, float y, float z, float m[16]){
	m[0]  =  x;
	m[1]=0.0f;
	m[2]=0.0f;
	m[3]=0.0f;
	m[4]=0.0f;
	m[5]  =  y;
	m[6]=0.0f;
	m[7]=0.0f;
	m[8]=0.0f;
	m[9]=0.0f;
	m[10] = z;
	m[11] =0.0f;
	m[12]=0.0f;
	m[13]=0.0f;
	m[14]=0.0f;
	m[15]=1.0f;
	
	
	
 
}


void lookAt(float ex, float ey, float ez, float cx, float cy, float cz, float ux , float uy, float uz, float m[16]){
	float lx,ly,lz,dx,dy,dz,ox,oy,oz;

	dx = (cx - ex)/sqrt( ((cx-ex)*(cx-ex)) + ((cy-ey)*(cy-ey)) + ((cz-ez)*(cz-ez)) );
	dy = (cy - ey)/sqrt( ((cx-ex)*(cx-ex)) + ((cy-ey)*(cy-ey)) + ((cz-ez)*(cz-ez)) );
	dz = (cz - ez)/sqrt( ((cx-ex)*(cx-ex)) + ((cy-ey)*(cy-ey)) + ((cz-ez)*(cz-ez)) );

	lx = (dy*uz - dz*uy)/sqrt( ((dy*uz-dz*uy)*(dy*uz-dz*uy)) + ((dz*ux-dx*uz)*(dz*ux-dx*uz)) + ((dx*uy-dy*ux)*(dx*uy-dy*ux)) );
	ly = (dz*ux - dx*uz)/sqrt( ((dy*uz-dz*uy)*(dy*uz-dz*uy)) + ((dz*ux-dx*uz)*(dz*ux-dx*uz)) + ((dx*uy-dy*ux)*(dx*uy-dy*ux)) );
	lz = (dx*uy - dy*ux)/sqrt( ((dy*uz-dz*uy)*(dy*uz-dz*uy)) + ((dz*ux-dx*uz)*(dz*ux-dx*uz)) + ((dx*uy-dy*ux)*(dx*uy-dy*ux)) );

	ox = ly*dz - lz*dy;
	oy = lz*dx - lx*dz;
	oz = lx*dy - ly*dx;

	float m1[16] = {lx,ox,-dx,0.0f,ly,oy,-dy,0.0f,lz,oz,-dz,0.0f,0.0f,0.0f,0.0f,1.0f};

	float m2[16] = {1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,-ex,ey,-ez,1.0f};

	matrixMultiply4x4(m1,m2,m);
}

void ortho(float l, float r, float b, float t, float n, float f, float m[16]){

	m[0] = 2/(r-l);
	m[1]=0.0f;
	m[2]=0.0f;
	m[3]=0.0f;
	m[4]=0.0f;
	m[5] = 2/(t-b);
	m[6]=0.0f;
	m[7]=0.0f;
	m[8]=0.0f;
	m[9]=0.0f;
	m[10] = -2/(f-n);
	m[11]=0.0f;
	m[12] = -(r+l)/(r-l);
	m[13] = -(t+b)/(t-b);
	m[14] = -(f+n)/(f-n);
	m[15]=1.0f;

}

void frustum(float l, float r, float b, float t, float n, float f, float m[16]){
	m[0] = 2*n/(r-l);
	m[1]=0.0f;
	m[2]=0.0f;
	m[3]=0.0f;
	m[4]=0.0f;
	m[5] = 2*n/(t-b);
	m[6]=0.0f;
	m[7]=0.0f;
	m[8] = (r+l)/(r-l);
	m[9] = (t+b)/(t-b);
	m[10] = -(f+n)/(f-n);
	m[11]=-1.0f;
	m[12]=0.0f;
	m[13]=0.0f;
	m[14] = -(2*f*n)/(f-n);
	m[15]=0.0f;

}


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