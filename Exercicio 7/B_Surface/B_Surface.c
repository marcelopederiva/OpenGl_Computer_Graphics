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
GLuint VAO[2];
GLuint VBO[2];
GLuint colorLoc;
float angle = 0.0f;
float step = -0.05f;
int division = 10;

float M[16] = {-1,3,-3,1,3,-6,3,0,-3,3,0,0,1,0,0,0};
// G = {G11
//      G21
//      G31
//      G41 

//      G12
//      G22
//      G32
//      G42

//      G13
//      G23
//      G33
//      G43

//      G14
//      G24
//      G34
//      G44
//  }
float G[16][3] = {{  1.0f, 0.0f,  1.0f},
                  {  1.0f, 1.0f,  0.5f},
                  {  1.0f, 1.0f, -0.5f},
                  {  1.0f, 0.0f, -1.0f},

                  {  0.5f, 1.0f,  1.0f},
                  {  0.5f, 1.0f,  0.5f},
                  {  0.5f, 1.0f, -0.5f},
                  {  0.5f, 1.0f, -1.0f},

                  { -0.5f, 1.0f,  1.0f},
                  { -0.5f, 1.0f,  0.5f},
                  { -0.5f, 1.0f,  -0.5f},
                  { -0.5f, 1.0f, -1.0f},


                  { -1.0f, 0.0f,  1.0f},
                  { -1.0f, 1.0f,  0.5f},
                  { -1.0f, 1.0f, -0.5f},
                  { -1.0f, 0.0f, -1.0f},
                };
// float G[16][3] = {{  1.0f, 0.0f,  1.0f},
//                   {  1.0f, 1.0f,  0.5f},
//                   {  1.0f, 1.0f, -0.5f},
// // Aumentando o Y do P41
//                   {  1.0f, 1.5f, -1.0f},

//                   {  0.5f, 1.0f,  1.0f},
//                   {  0.5f, 1.0f,  0.5f},
//                   {  0.5f, 1.0f, -0.5f},
//                   {  0.5f, 1.0f, -1.0f},

//                   { -0.5f, 1.0f,  1.0f},
//                   { -0.5f, 1.0f,  0.5f},
//                   { -0.5f, 1.0f,  -0.5f},
//                   { -0.5f, 1.0f, -1.0f},

// // Aumentando o Y do P14
//                   { -1.0f, 1.5f,  1.0f},
//                   { -1.0f, 1.0f,  0.5f},
//                   { -1.0f, 1.0f, -0.5f},
//                   { -1.0f, 0.0f, -1.0f},
//                 };

void calculo_Bezier_S(float s, float t, float ver[3]){
    for(int i=0;i<3;i++){
                //Q = S M G M_T T_T
                float G_c[16] = {G[0][i],G[1][i],G[2][i],G[3][i],  G[4][i],G[5][i],G[6][i],G[7][i],  G[8][i],G[9][i],G[10][i],G[11][i],  G[12][i],G[13][i],G[14][i],G[15][i]};
                
                float Matrix[16], Matrix2[16];

                matrixMultiply4x4(M,G_c,Matrix);
                matrixMultiply4x4(Matrix,M, Matrix2); 

                float S1,S2,S3,S4;

                S1 = (Matrix2[0] *s*s*s)  +  (Matrix2[1] *s*s)  + (Matrix2[2] *s)  + Matrix2[3];
                S2 = (Matrix2[4] *s*s*s)  +  (Matrix2[5] *s*s)  + (Matrix2[6] *s)  + Matrix2[7];
                S3 = (Matrix2[8] *s*s*s)  +  (Matrix2[9] *s*s)  + (Matrix2[10]*s)  + Matrix2[11];
                S4 = (Matrix2[12]*s*s*s) +   (Matrix2[13]*s*s)  + (Matrix2[14]*s)  + Matrix2[15];
                
                // printf("S4: %f\n", S4 );
                ver[i] = (S1*t*t*t) + (S2*t*t) + (S3 *t) + S4;

                        }
}

void B_Surface(float M[16],float G[16][3], float vertices_B[division*division*6*4]){

    
    float ver[3];
    float div_t = 1.0/(division-1);
    float t1 = 0.0f;
    float t2 = t1+div_t;
    float div_s = 1.0/(division-1);
    float s1 = 0.0f;
    float s2 = s1+div_s;


    for(int pos = 0; pos < division*division*6*4; pos+=24){

    calculo_Bezier_S(s1, t1, ver);
    vertices_B[pos]  = ver[0] ;   vertices_B[pos+1]  = ver[1];  vertices_B[pos+2]  = ver[2];   vertices_B[pos+3]  = 1.0f;
    
    calculo_Bezier_S(s2, t1, ver);
    vertices_B[pos+4]  = ver[0] ;   vertices_B[pos+5]  = ver[1];  vertices_B[pos+6]  = ver[2];   vertices_B[pos+7]  = 1.0f;

    calculo_Bezier_S(s1, t2, ver);
    vertices_B[pos+8]  = ver[0] ;   vertices_B[pos+9]  = ver[1];  vertices_B[pos+10]  = ver[2];   vertices_B[pos+11]  = 1.0f;


    calculo_Bezier_S(s1, t2, ver);
    vertices_B[pos+12]  = ver[0] ;   vertices_B[pos+13]  = ver[1];  vertices_B[pos+14]  = ver[2];   vertices_B[pos+15]  = 1.0f;

    calculo_Bezier_S(s2, t2, ver);
    vertices_B[pos+16]  = ver[0] ;   vertices_B[pos+17]  = ver[1];  vertices_B[pos+18]  = ver[2];   vertices_B[pos+19]  = 1.0f;

    calculo_Bezier_S(s2, t1, ver);
    vertices_B[pos+20]  = ver[0] ;   vertices_B[pos+21]  = ver[1];  vertices_B[pos+22]  = ver[2];   vertices_B[pos+23]  = 1.0f;


    s1 = s2;
    s2 += div_s;

    

    if (s2>1.0){
        s1 = 0.0f;
        s2 = div_s;
        t1 = t2;
        t2 += div_t;
    }
    if(t2>1.0){
        t1 = 0.0f;
        t2 = t1+div_t;
    }
   

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
    ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.0f, 5.0f, projMatrix);
    int projMatrixLoc = glGetUniformLocation(shaderProgram, "u_projMatrix");
    glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);

    // Set View transformation
    // --------------------------------------
    GLfloat viewMatrix[16];
     lookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);
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
        for(int i=0;i<2;i++){

        glBindVertexArray(VAO[i]);

        GLfloat mRotate[16],mXForm2[16];

        angle+=step;
        matrixRotate4x4(angle,0.0f,1.0f,1.0f,mRotate);
        matrixMultiply4x4(mRotate, mXForm, mXForm2);
        matrixMultiply4x4(viewMatrix, mXForm2, modelViewMatrix);


        if(i==0){
        glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, (division*division*6));
        }
        else if(i==1){
        glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, (16*2+1));
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
    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
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

    GLfloat vertices_B[division*division*6*4];
    B_Surface(M,G,vertices_B);


    GLfloat vertices_c[(16*2+1)*4] = { 
            G[0][0],G[0][1],G[0][2],1.0f,
            G[1][0],G[1][1],G[1][2],1.0f,
            G[2][0],G[2][1],G[2][2],1.0f,
            G[3][0],G[3][1],G[3][2],1.0f,
            
            
            G[7][0],G[7][1],G[7][2],1.0f,
            G[6][0],G[6][1],G[6][2],1.0f,
                G[2][0],G[2][1],G[2][2],1.0f,
                G[6][0],G[6][1],G[6][2],1.0f,
            G[5][0],G[5][1],G[5][2],1.0f,
                G[1][0],G[1][1],G[1][2],1.0f,
                G[5][0],G[5][1],G[5][2],1.0f,
            G[4][0],G[4][1],G[4][2],1.0f,
                G[0][0],G[0][1],G[0][2],1.0f,
                G[4][0],G[4][1],G[4][2],1.0f,

            G[8][0],G[8][1],G[8][2],1.0f,
            G[9][0],G[9][1],G[9][2],1.0f,
                G[5][0],G[5][1],G[5][2],1.0f,
                G[9][0],G[9][1],G[9][2],1.0f,
            G[10][0],G[10][1],G[10][2],1.0f, 
                G[6][0],G[6][1],G[6][2],1.0f,
                G[10][0],G[10][1],G[10][2],1.0f, 
            G[11][0],G[11][1],G[11][2],1.0f,
                G[7][0],G[7][1],G[7][2],1.0f,
                G[11][0],G[11][1],G[11][2],1.0f,

            G[15][0],G[15][1],G[15][2],1.0f,
            G[14][0],G[14][1],G[14][2],1.0f,
                G[10][0],G[10][1],G[10][2],1.0f,
                G[14][0],G[14][1],G[14][2],1.0f,
            G[13][0],G[13][1],G[13][2],1.0f,
                G[9][0],G[9][1],G[9][2],1.0f,
                G[13][0],G[13][1],G[13][2],1.0f,
            G[12][0],G[12][1],G[12][2],1.0f,
                G[8][0],G[8][1],G[8][2],1.0f
            };

    //-----------------------------------------------------------------------

    // CRIAR 3 VAOs e 3 VBOS
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_B), vertices_B, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_c), vertices_c, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    fprintf(stdout, "init::end\n");
    fflush(stdout);
    return;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
//  fprintf(stdout, "processInput::start\n");
//  fflush(stdout);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

//  fprintf(stdout, "processInput::end\n");
//  fflush(stdout);
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


