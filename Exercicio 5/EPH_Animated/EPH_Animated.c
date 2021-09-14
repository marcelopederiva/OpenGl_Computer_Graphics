/*
 * EPH_Animated.c
 *
 * Test geometric transformation functions.
 *
 *  Created on: Mach 8 2021
 *      Author: MPederiva
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mytools2.h"

// Constant
// ---------------------------------------
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

// Function declaration
// ---------------------------------------
void display(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int generateShader(int type, char* filename);
void init(void);
void processInput(GLFWwindow *window);
GLFWwindow* setupEnvironment(void);

// Variable declaration
// ---------------------------------------
GLuint shaderProgram;
GLuint VAO[3];
GLuint VBO[3];
GLuint colorLoc;
float angle = 0.0f;
float step = -0.05f;

// Parabola
const float foco_parab = 0.01f;
const float d_parab = 0.2f;
const int n_parab = 12;
const int n_vertices_p = n_parab +2;


// // Elipse
const float a_elipse = 0.2f;
const float b_elipse = 0.1f;

// const int n_elipse = 10;
const int n_elipse = 24;
// const int n_elipse = 40;
const int n_vertices_e = n_elipse +2;


// // Hiperbole
const float a_hiper = 0.075f;
const float b_hiper = 0.075f;
const float d_hiper = 0.2f;
const int n_hiper = 12;
const int n_vertices_h = n_hiper +2;

// Main: it starts here
// ---------------------------------------
int main(void) {
	fprintf(stdout, "main::start\n");
	fflush(stdout);

    // create window and load OpenGL functions
	 GLFWwindow* window = setupEnvironment();

    // set up data to display
    // ---------------------------------------
    init();

    // render data
    // ----------------------------------------
    display(window);

	fprintf(stdout, "main::end\n");
	fflush(stdout);

    exit(0);
}

// Construct the Parabola

void draw_parabola(float f,float d,int n, float vertices_parabola[n_vertices_p*4]){

    float ymax = sqrt(4*f*d);

    // CENTRO
	vertices_parabola[0]  = d;   vertices_parabola[1]  = 0.0f; 	vertices_parabola[2]  = 0.0f; 	vertices_parabola[3]  = 1.0f;

    // YMAX
	vertices_parabola[4]  = d;	vertices_parabola[5]  = ymax;	vertices_parabola[6]  = 0.0f;	vertices_parabola[7]  = 1.0f;

    float kmin = 2*ymax/n;
    float k;
    k = ymax-kmin;

    for(int i=8 ; i< (n+2)*4 ; i=i+4){
        vertices_parabola[i] = k*k/(4*f);        vertices_parabola[i+1] = k;        vertices_parabola[i+2] = 0.0f;        vertices_parabola[i+3] = 1.0f;
        k = k-kmin;
    }

}

void draw_elipse(float a, float b, int n, float vertices_elipse[n_vertices_e*4]){
    //CENTRO
    vertices_elipse[0]  = 0.0f;   vertices_elipse[1]  = 0.0f;  vertices_elipse[2]  = 0.0f;   vertices_elipse[3]  = 1.0f;
    //XMAX
    vertices_elipse[4]  = 0.0f;  vertices_elipse[5]  = b;   vertices_elipse[6]  = 0.0f;   vertices_elipse[7]  = 1.0f;

    float kmin = 2*b/(n/2);
    float k;
    k = b;

    for(int i=8 ; i<((n/2)+2)*4 ; i=i+4){
        k = k-kmin;
        vertices_elipse[i] = sqrt((b*b-k*k)/(b*b))*a;        vertices_elipse[i+1] = k;        vertices_elipse[i+2] = 0.0f;        vertices_elipse[i+3] = 1.0f;
        
    }
    for(int i=((n/2)+2)*4 ; i<(n+2)*4 ; i=i+4){
        k = k+kmin;
        vertices_elipse[i] = -sqrt((b*b-k*k)/(b*b))*a;        vertices_elipse[i+1] = k;        vertices_elipse[i+2] = 0.0f;        vertices_elipse[i+3] = 1.0f;
        
    }

}
void draw_hiperbole(float a, float b, float d, int n, float vertices_hiperbole[n_vertices_h*4]){
    float ymax = sqrt( (d*d-a*a)/(a*a) )*b;
    //CENTROs
    vertices_hiperbole[0]  = d;   vertices_hiperbole[1]  = 0.0f;  vertices_hiperbole[2]  = 0.0f;   vertices_hiperbole[3]  = 1.0f;
    //yMAX
    vertices_hiperbole[4]  = d;  vertices_hiperbole[5]  = ymax;   vertices_hiperbole[6]  = 0.0f;   vertices_hiperbole[7]  = 1.0f;

    float kmin = 2*ymax/n;
    float k;
    k = ymax-kmin;

    for(int i=8 ; i<(n+2)*4 ; i=i+4){
        vertices_hiperbole[i] = sqrt( (b*b+k*k)/(b*b) )*a;        vertices_hiperbole[i+1] = k;        vertices_hiperbole[i+2] = 0.0f;        vertices_hiperbole[i+3] = 1.0f;
        k = k-kmin;
    }
}


// Render and display data
// ---------------------------------------
void display(GLFWwindow* window) {
	fprintf(stdout, "display::start\n");
	fflush(stdout);

    // Define background color
    // ---------------------------------------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


	// Set Projection Matrix
	// --------------------------------------
	GLfloat projMatrix[16];
	ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 3.0f, projMatrix);
//	 frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 3.0f, projMatrix);
	int projMatrixLoc = glGetUniformLocation(shaderProgram, "u_projMatrix");
	glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);

	// Set View transformation
	// --------------------------------------
	GLfloat viewMatrix[16];
	 lookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);
	// lookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);
	int modelViewMatrixLoc = glGetUniformLocation(shaderProgram, "u_modelViewMatrix");
// 

	// Set Model transformation
	// --------------------------------------
	GLfloat mXForm[16];
	matrixIdentity4x4(mXForm);

	// Set ModelView transformation
	// --------------------------------------
	GLfloat modelViewMatrix[16];
	matrixIdentity4x4(modelViewMatrix);

    // Render loo 
    // ---------------------------------------
    while (!glfwWindowShouldClose(window)) {

   // 	fprintf(stdout, "render loop\n");
   // 	fflush(stdout);

        // Check input
        // ---------------------------------------
        processInput(window);

    	// Clear screen
    	// --------------------------------------
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLfloat mRotate[16],mTransl[16],mXForm2[16],mScale[16],mXForm1[16];

        for(int i=0;i<3;i++){

        glBindVertexArray(VAO[i]);

        angle+=step;
        matrixScale4x4(1.5f, 1.5f, 1.5f, mScale);
        matrixMultiply4x4(mScale, viewMatrix, mXForm1);
        matrixRotate4x4(angle,0.0f,0.0f,1.0f,mRotate);
        matrixMultiply4x4(mRotate, mXForm1, mXForm2);

        //PARABOLA
        if(i==0){
        
        matrixTranslate4x4(+0.4f, 0, 0, mTransl);
        matrixMultiply4x4(mXForm2, mTransl, modelViewMatrix);
        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
        glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLE_FAN, 0, n_vertices_p);
        
        }

        //ELIPSE
        else if(i==1){
        matrixTranslate4x4(0.0f, 0, 0, mTransl);
        matrixMultiply4x4(mXForm2, mTransl, modelViewMatrix);
        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
        glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);

        glDrawArrays(GL_TRIANGLE_FAN, 0, n_vertices_e);
        
        }

        //HIPERBOLE
        else{
        matrixTranslate4x4(-0.6f, 0, 0, mTransl);
        matrixMultiply4x4(mXForm2, mTransl, modelViewMatrix);
        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
        glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);

        glDrawArrays(GL_TRIANGLE_FAN, 0, n_vertices_h);
        
        }

        matrixIdentity4x4(modelViewMatrix);
        }


        glFlush();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

	fprintf(stdout, "display::end\n");
	fflush(stdout);
    return;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	fprintf(stdout, "framebuffer_size_callback::start\n");
	fflush(stdout);

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);

	fprintf(stdout, "framebuffer_size_callback::end\n");
	fflush(stdout);

	return;
}

// Set up OpenGL data
// ---------------------------------------
void init(void) {
	fprintf(stdout, "init::start\n");
	fflush(stdout);

	fprintf(stderr, "Renderer %s\n", glGetString(GL_RENDERER));
	fprintf(stderr, "Vendor %s\n", glGetString(GL_VENDOR));
	fprintf(stderr, "Version %s\n", glGetString(GL_VERSION));
	fprintf(stderr, "Shading Language Version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	fflush(stderr);

    // Create vertex shader
	// ---------------------------------------
	GLuint vertexShader = generateShader(GL_VERTEX_SHADER, "./shader.vert");

    // Create fragment shader
	GLuint fragmentShader = generateShader(GL_FRAGMENT_SHADER, "./shader.frag");

    // Create Program and link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    // ---------------------------------------
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "init::shader program linking failed::%s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use Program
    //-------------------------------
    glUseProgram(shaderProgram);

	// Get position of shader variables
	int vertexLoc = glGetAttribLocation(shaderProgram, "vertex");
	// int colorLoc = glGetAttribLocation(shaderProgram, "color");


	// Create Vertex Array Object ID
	// ---------------------------------------

    //     PARABOLA
    GLfloat vertices_parabola[n_vertices_p*4];
    draw_parabola(foco_parab, d_parab, n_parab, vertices_parabola);

    //     ELIPSE
    // n=10
    // GLfloat vertices_elipse[48];
    // n=20
    GLfloat vertices_elipse[104];
    // n=10
    // GLfloat vertices_elipse[168];
    draw_elipse(a_elipse, b_elipse, n_elipse, vertices_elipse);

    //     HIPERBOLE
    GLfloat vertices_hiperbole[n_vertices_h*4];
    draw_hiperbole(a_hiper, b_hiper, d_hiper, n_hiper, vertices_hiperbole);

    //-----------------------------------------------------------------------

    // CRIAR 3 VAOs e 3 VBOS
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);


    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_parabola), vertices_parabola, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_elipse), vertices_elipse, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_hiperbole), vertices_hiperbole, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

	fprintf(stdout, "init::end\n");
	fflush(stdout);
    return;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
//	fprintf(stdout, "processInput::start\n");
//	fflush(stdout);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

//	fprintf(stdout, "processInput::end\n");
//	fflush(stdout);
}

// Create window and load OpenGL library
// ---------------------------------------
GLFWwindow* setupEnvironment(void) {
	fprintf(stdout, "prepare::start\n");
	fflush(stdout);

    // glfw: initialize and configure
    // ---------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // ---------------------------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "EPH_Animated", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "prepare::failed to create GLFW window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
    	fprintf(stderr, "prepare::failed to initialize GLAD");
        exit(EXIT_FAILURE);
    }

    return window;
}


