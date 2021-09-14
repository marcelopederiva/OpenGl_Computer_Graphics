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
float d = -0.2f;
int subdivitions = 25;
int resolution = 50;




// Pontos de controle até 12


// UNIFORME 
const int k = 5;
const int p_control = 5;
float B[5][2] ={{0.0f,0.0f},
                {0.2f,1.0f},
                {0.4f,0.0f},
                {0.6f,1.0f},
                {0.8f,0.0f}
                };
int sizex = 9;
float x[9] = {1,2,3,4,5,6,7,8,9};

// NÃO UNIFORME SLIDE 48
// const int k = 4;
// const int p_control = 7;
// float B[7][2] ={{0.0f,0.1f},
//                 {0.16f,0.3f},
//                 {0.33f,0.1f},
//                 {0.5f,0.55f},
//                 {0.66f,0.16f},
//                 {0.83f,0.3f},
//                 {1.0f,0.1f}
//                 };
// int sizex = 9;
// float x[9] = {0,0,0,0,0.4,1.5,2.6,3,3};

float N_ik(int i, int k, float t){
    float N=0.0f;
    if(k==1){
        if ((x[i]<=t) && (x[i+1]>t)){
            N = 1.0f;
        }
    }
    else{

        if ( ( (x[i+k-1]-x[i]) == 0) && ( (x[i+k]-x[i+1])==0 ) ) {

                N = 0.0f;
            }

        else{

            if((x[i+k-1]-x[i]) == 0){
                N = ( (x[i+k]-t)/(x[i+k]-x[i+1]) * N_ik(i+1,k-1,t) );

            }
            else if ((x[i+k]-x[i+1])==0){
                N = ( (t-x[i])/(x[i+k-1]-x[i]) * N_ik(i,k-1,t) );

            }
            else{
                N = ( ((t-x[i])/(x[i+k-1]-x[i])) * N_ik(i,k-1,t) ) + ( ((x[i+k]-t)/(x[i+k]-x[i+1])) * N_ik(i+1,k-1,t) );
            }
        }
        
    }
    return N;
}
void BSpline_d(float d, float vertices_B[resolution*4],float vertices_B_d[resolution*4]){
    for(int i=0;i<resolution*4;i+=4){
            vertices_B_d[i] = vertices_B[i];
            vertices_B_d[i+1] = vertices_B[i+1];
            vertices_B_d[i+2] = d;
            vertices_B_d[i+3] = vertices_B[i+3];
        }
        
    }
void BSpline(int k ,int p_control, float B[p_control][2], float x[sizex] ,float vertices_B[resolution*4]){
    // Definir a Equação

   
    float ver_x_total = 0.0f;
    float ver_y_total = 0.0f;

    float div = (x[sizex-1]-x[0])/(resolution-1);
    float div_i=x[0];

    for(int t=0;t<resolution*4;t+=4){
        
        for(int i=0;i<p_control;i++){
            
            float ver_x = B[i][0]*N_ik((i),k,div_i);
            float ver_y = B[i][1]*N_ik((i),k,div_i);
            
            ver_x_total += ver_x;
            ver_y_total += ver_y;

        }
        
        vertices_B[t]  = ver_x_total ;   vertices_B[t+1]  = ver_y_total;  vertices_B[t+2]  = 0.0f;   vertices_B[t+3]  = 1.0f;

        ver_x_total = 0.0f;
        ver_y_total = 0.0f;

        div_i+=div;
        
    } 
     
}
void Wireframe(float d, int k ,int p_control, float B[p_control][2], float x[sizex] ,float vertices_w[((subdivitions*2)-2)*4]){

    float ver_x_total = 0.0f;
    float ver_y_total = 0.0f;

    float div = (x[sizex-1]-x[0])/(subdivitions );
    float div_i=x[0];

    for(int t=0;t<((subdivitions*2)-2)*4;t+=8){
        
        for(int i=0;i<p_control;i++){
            
            float ver_x = B[i][0]*N_ik((i),k,div_i);
            float ver_y = B[i][1]*N_ik((i),k,div_i);
            
            ver_x_total += ver_x;
            ver_y_total += ver_y;
        }
        
        vertices_w[t]  = ver_x_total ;   vertices_w[t+1]  = ver_y_total;  vertices_w[t+2]  = 0.0f;   vertices_w[t+3]  = 1.0f;
        vertices_w[t+4]  = ver_x_total ;   vertices_w[t+5]  = ver_y_total;  vertices_w[t+6]  = d;   vertices_w[t+7]  = 1.0f;

        
        ver_x_total = 0.0f;
        ver_y_total = 0.0f;

        div_i+=div;
    } 
     
}

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
	ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 5.0f, projMatrix);
	int projMatrixLoc = glGetUniformLocation(shaderProgram, "u_projMatrix");
	glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);

	// Set View transformation
	// --------------------------------------
	GLfloat viewMatrix[16];
	 lookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);
	int modelViewMatrixLoc = glGetUniformLocation(shaderProgram, "u_modelViewMatrix");

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

        // Check input
        // ---------------------------------------
        processInput(window);

    	// Clear screen
    	// --------------------------------------
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        for(int i=0;i<3;i++){

        glBindVertexArray(VAO[i]);

        GLfloat mTransl[16],mRotate[16],mXForm1[16],mXForm2[16];

        angle+=step;
        matrixRotate4x4(angle,1.0f,0.0f,1.0f,mRotate);
        matrixTranslate4x4(-0.5f, -0.5f, 0, mTransl); 



        matrixMultiply4x4(mTransl, mXForm, mXForm1);
        matrixMultiply4x4(mRotate, mXForm1, mXForm2);
        matrixMultiply4x4(viewMatrix, mXForm2, modelViewMatrix);


        if(i==0){
        glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, (resolution-4) );
        }
        else if(i==1){
        glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, (resolution-4));
        }

        else{
        glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, ((subdivitions*2)-2));
        }

        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
        
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
    GLfloat vertices_B[resolution*4];
    BSpline(k ,p_control, B, x, vertices_B);

    GLfloat vertices_B_d[resolution*4];
    BSpline_d(d, vertices_B,vertices_B_d);

    GLfloat vertices_w[((subdivitions*2)-2)*4];
    Wireframe(d,  k , p_control,  B,  x , vertices_w);

    //-----------------------------------------------------------------------

    // CRIAR 3 VAOs e 3 VBOS
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_B), vertices_B, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_B_d), vertices_B_d, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_w), vertices_w, GL_STATIC_DRAW);
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Bezier_Animated", NULL, NULL);
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


