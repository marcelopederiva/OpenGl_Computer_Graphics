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
#define PI 3.14159265
// Constant
// ---------------------------------------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

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
GLuint VAO[5];
GLuint VBO[5];
GLuint colorLoc;
float angle = 0.0f;
float step = -0.05f;
int division_sphere = 20;
int division_toroid = 30;
int division_cone = 25;
int division_cylinder = 30;

float square_v[8][3]={{ 1.0f,0.0f, 1.0f},
                    {-1.0f,0.0f, 1.0f},
                    { 1.0f,1.0f, 1.0f},
                    { -1.0f,1.0f,1.0f},
                    {-1.0f,1.0f,-1.0f},
                    {-1.0f,0.0f,-1.0f},
                    { 1.0f,1.0f,-1.0f},
                    { 1.0f,0.0f,-1.0f}
                    };
float r_int = 0.4f;
float r_ext = 1.0f;
float r_sphere = 1.0f;
float r_cone = 0.5f;
float r_cylinder = 1.0f;
float h_cylinder = 1.0f;
void Calculo_Toroid(float theta, float phi, float point[3]){

        point[0] = (r_ext+r_int*cos(theta))*cos(phi);
        point[1] = (r_ext+r_int*cos(theta))*sin(phi);
        point[2] = r_int*sin(theta);

}   

void Toroid(float vertice_t[division_toroid*division_toroid*6*4]){
    
//    0 2pi

    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_toroid-1);
    float theta2 = div;
    float phi1 = 0.0f;
    float phi2 = div;
    float point[3] = {0.0f,0.0f,0.0f};

    for(int i =0; i< division_toroid*division_toroid*6*4; i+=24){
            
            //Ponto 1
            Calculo_Toroid(theta1,phi1,point);
            vertice_t[i+0] = point[0] ;vertice_t[i+1] = point[1];vertice_t[i+2] = point[2]; vertice_t[i+3] = 1.0f;
            

            //Ponto 2
            Calculo_Toroid(theta2,phi1,point);
            vertice_t[i+4] = point[0] ;vertice_t[i+5] = point[1];vertice_t[i+6] = point[2]; vertice_t[i+7] = 1.0f;

            //Ponto 3
            Calculo_Toroid(theta1,phi2,point);
            vertice_t[i+8] = point[0] ;vertice_t[i+9] = point[1];vertice_t[i+10] = point[2]; vertice_t[i+11] = 1.0f;



            //Ponto 3
            Calculo_Toroid(theta1,phi2,point);
            vertice_t[i+12] = point[0] ;vertice_t[i+13] = point[1];vertice_t[i+14] = point[2]; vertice_t[i+15] = 1.0f;

            //Ponto 4
            Calculo_Toroid(theta2,phi2,point);
            vertice_t[i+16] = point[0] ;vertice_t[i+17] = point[1];vertice_t[i+18] = point[2]; vertice_t[i+19] = 1.0f;

            //Ponto 2
            Calculo_Toroid(theta2,phi1,point);
            vertice_t[i+20] = point[0] ;vertice_t[i+21] = point[1];vertice_t[i+22] = point[2]; vertice_t[i+23] = 1.0f;


            theta1 = theta2;
            theta2+=div;
            if(theta2 > (2.0*PI)){
                phi1 = phi2;
                phi2+=div;
                theta1 = 0.0f;
                theta2 = div; 
            }
            
    }   
    
}

void Calculo_Sphere(float theta, float phi, float point[3]){

        point[0] = r_sphere*sin(phi)*cos(theta);
        point[1] = r_sphere*sin(phi)*sin(theta);
        point[2] = r_sphere*cos(phi);

}  
void Sphere(float vertice_sp[division_sphere*division_sphere*6*4]){
//    0 2pi
    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_sphere-1);
    float theta2 = div;
    float phi1 = 0.0f;
    
    float phi2 = div;
    float point[3] = {0.0f,0.0f,0.0f};

    for(int i =0; i< division_sphere*division_sphere*6*4; i+=24){

            //Ponto 1
            Calculo_Sphere(theta1,phi1,point);
            vertice_sp[i+0] = point[0] ;vertice_sp[i+1] = point[1];vertice_sp[i+2] = point[2]; vertice_sp[i+3] = 1.0f;

            //Ponto 2
            Calculo_Sphere(theta2,phi1,point);
            vertice_sp[i+4] = point[0] ;vertice_sp[i+5] = point[1];vertice_sp[i+6] = point[2]; vertice_sp[i+7] = 1.0f;

            //Ponto 3
            Calculo_Sphere(theta1,phi2,point);
            vertice_sp[i+8] = point[0] ;vertice_sp[i+9] = point[1];vertice_sp[i+10] = point[2]; vertice_sp[i+11] = 1.0f;



            //Ponto 3
            Calculo_Sphere(theta1,phi2,point);
            vertice_sp[i+12] = point[0] ;vertice_sp[i+13] = point[1];vertice_sp[i+14] = point[2]; vertice_sp[i+15] = 1.0f;

            //Ponto 4
            Calculo_Sphere(theta2,phi2,point);
            vertice_sp[i+16] = point[0] ;vertice_sp[i+17] = point[1];vertice_sp[i+18] = point[2]; vertice_sp[i+19] = 1.0f;

            //Ponto 2
            Calculo_Sphere(theta2,phi1,point);
            vertice_sp[i+20] = point[0] ;vertice_sp[i+21] = point[1];vertice_sp[i+22] = point[2]; vertice_sp[i+23] = 1.0f;


            theta1 = theta2;
            theta2+=div;

            if(theta2 >= (2*PI)){
                phi1 = phi2;
                phi2+=div;
                theta1 = 0.0f;
                theta2 = div; 
            }
            
    }   
    
}
void Calculo_Cone(float theta, float r, float point[3]){

        point[0] = r*cos(theta);
        point[1] = r*sin(theta);
        point[2] = r;

}  
void Cone(float vertice_c[division_cone*division_cone*2*6*4]){
//    0 2pi
    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_cone-1);
    float theta2 = div;
    float div2 = r_cone/(division_cone-1);
    float r1 = 0.0f;
    float r2 = div2;
    float point[3] = {0.0f,0.0f,0.0f};

    for(int i =0; i< division_cone*division_cone*6*2*4; i+=24){ 

            //Ponto 1
            Calculo_Cone(theta1,r1,point);
            vertice_c[i+0] = point[0] ;vertice_c[i+1] = point[1];vertice_c[i+2] = point[2]; vertice_c[i+3] = 1.0f;
            //Ponto 2
            Calculo_Cone(theta2,r1,point);
            vertice_c[i+4] = point[0] ;vertice_c[i+5] = point[1];vertice_c[i+6] = point[2]; vertice_c[i+7] = 1.0f;

            //Ponto 3
            Calculo_Cone(theta1,r2,point);
            vertice_c[i+8] = point[0] ;vertice_c[i+9] = point[1];vertice_c[i+10] = point[2]; vertice_c[i+11] = 1.0f;



            //Ponto 3
            Calculo_Cone(theta1,r2,point);
            vertice_c[i+12] = point[0] ;vertice_c[i+13] = point[1];vertice_c[i+14] = point[2]; vertice_c[i+15] = 1.0f;

            //Ponto 4
            Calculo_Cone(theta2,r2,point);
            vertice_c[i+16] = point[0] ;vertice_c[i+17] = point[1];vertice_c[i+18] = point[2]; vertice_c[i+19] = 1.0f;

            //Ponto 2
            Calculo_Cone(theta2,r1,point);
            vertice_c[i+20] = point[0] ;vertice_c[i+21] = point[1];vertice_c[i+22] = point[2]; vertice_c[i+23] = 1.0f;


            theta1 = theta2;
            theta2+=div;

            if(theta1 > (2*PI)){
                r1 = r2;
                r2+=div2;
                theta1 = 0.0f;
                theta2 = div; 
            }
            
    }   
    
}        
void Calculo_Cylinder(float theta, float r, float h, float point[3]){

        point[0] = r*cos(theta);
        point[1] = r*sin(theta);
        point[2] = h;

}  
void Cylinder(float vertice_cy[division_cylinder*division_cylinder*2*6*4]){
//    0 2pi
    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_cylinder-1);
    float theta2 = div;

    float div2 = h_cylinder/(division_cylinder-1);
    float h1 = 0.0f;
    float h2 = div2;

    float point[3] = {0.0f,0.0f,0.0f};
    int j=0;
    for(int i =0; i< division_cylinder*division_cylinder*6*4; i+=24){

            //Ponto 1
            Calculo_Cylinder(theta1,r_cylinder,h1,point);
            vertice_cy[i+0] = point[0] ;vertice_cy[i+1] = point[1];vertice_cy[i+2] = point[2]; vertice_cy[i+3] = 1.0f;
            //Ponto 2
            Calculo_Cylinder(theta2,r_cylinder,h1,point);
            vertice_cy[i+4] = point[0] ;vertice_cy[i+5] = point[1];vertice_cy[i+6] = point[2]; vertice_cy[i+7] = 1.0f;

            //Ponto 3
            Calculo_Cylinder(theta1,r_cylinder,h2,point);
            vertice_cy[i+8] = point[0] ;vertice_cy[i+9] = point[1];vertice_cy[i+10] = point[2]; vertice_cy[i+11] = 1.0f;



            //Ponto 3
            Calculo_Cylinder(theta1,r_cylinder,h2,point);
            vertice_cy[i+12] = point[0] ;vertice_cy[i+13] = point[1];vertice_cy[i+14] = point[2]; vertice_cy[i+15] = 1.0f;

            //Ponto 4
            Calculo_Cylinder(theta2,r_cylinder,h2,point);
            vertice_cy[i+16] = point[0] ;vertice_cy[i+17] = point[1];vertice_cy[i+18] = point[2]; vertice_cy[i+19] = 1.0f;

            //Ponto 2
            Calculo_Cylinder(theta2,r_cylinder,h1,point);
            vertice_cy[i+20] = point[0] ;vertice_cy[i+21] = point[1];vertice_cy[i+22] = point[2]; vertice_cy[i+23] = 1.0f;


            theta1 = theta2;
            theta2+=div;

            if(theta1 > (2*PI)){
                h1 = h2;
                h2+=div2;
                theta1 = 0.0f;
                theta2 = div; 
            }
    
    }
    j+=division_cylinder*division_cylinder*6*4;
    theta1 = 0.0f;
    theta2 = div; 
    h1 = 0.0f;
    h2 = h_cylinder;
    for(int i =0; i< j + division_cylinder*4*4; i+=24){

            //Ponto 1
            Calculo_Cylinder(theta1,r_cylinder,h1,point);
            vertice_cy[j+i+0] = point[0] ;vertice_cy[j+i+1] = point[1];vertice_cy[j+i+2] = point[2]; vertice_cy[j+i+3] = 1.0f;

            //Ponto 2
            Calculo_Cylinder(theta2,r_cylinder,h1,point);
            vertice_cy[j+i+4] = point[0] ;vertice_cy[j+i+5] = point[1];vertice_cy[j+i+6] = point[2]; vertice_cy[j+i+7] = 1.0f;

            //Ponto 3
            Calculo_Cylinder(theta1,0.0f,h1,point);
            vertice_cy[j+i+8] = point[0] ;vertice_cy[j+i+9] = point[1];vertice_cy[j+i+10] = point[2]; vertice_cy[j+i+11] = 1.0f;



            //Ponto 3
            Calculo_Cylinder(theta1,0.0f,h1,point);
            vertice_cy[j+i+12] = point[0] ;vertice_cy[j+i+13] = point[1];vertice_cy[j+i+14] = point[2]; vertice_cy[j+i+15] = 1.0f;

            //Ponto 4
            Calculo_Cylinder(theta2,r_cylinder,h1,point);
            vertice_cy[j+i+16] = point[0] ;vertice_cy[j+i+17] = point[1];vertice_cy[j+i+18] = point[2]; vertice_cy[j+i+19] = 1.0f;

            //Ponto 2
            Calculo_Cylinder(theta2,r_cylinder,h1,point);
            vertice_cy[j+i+20] = point[0] ;vertice_cy[j+i+21] = point[1];vertice_cy[j+i+22] = point[2]; vertice_cy[j+i+23] = 1.0f;


            theta1 = theta2;
            theta2+=div;
            if(theta2 > (2*PI)){
                h1 = h2;
                theta1 = 0.0f;
                theta2 = div; 
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
    ortho(-10.0f, 10.0f, -2.0f, 5.0f, -10.0f, 10.0f, projMatrix);
    int projMatrixLoc = glGetUniformLocation(shaderProgram, "u_projMatrix");
    glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);

    // Set View transformation
    // --------------------------------------
    GLfloat viewMatrix[16];
     lookAt(0.0f, 1.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, viewMatrix);
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
        for(int i=0;i<5;i++){

        glBindVertexArray(VAO[i]);

        GLfloat mRotate[16],mXForm2[16],mXForm3[16],mXForm1[16];

        angle+=step;
        GLfloat Alterations[16];

        if(i==0){//SQUARE

        matrixTranslate4x4(-3.0f, 0.0f, -3.0f, Alterations); 
        matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
        matrixMultiply4x4(mRotate, mXForm, mXForm2);
        matrixMultiply4x4(Alterations, mXForm2, mXForm3);
        matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);

        glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 27);
        }
        else if(i==1){//TOROID

        matrixRotate4x4(90,1.0f,0.0f,0.0f,Alterations);
        matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);

        matrixMultiply4x4(Alterations, mXForm, mXForm2);
        matrixMultiply4x4(mRotate, mXForm2, mXForm3);
        matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);


        glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, division_toroid*division_toroid*6);
        }
        else if(i==2){//SPHERE

        matrixTranslate4x4(-3.0f, 0.0f, 3.0f, Alterations); 
        matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
        matrixMultiply4x4(mRotate, mXForm, mXForm2);
        matrixMultiply4x4(Alterations, mXForm2, mXForm3);
        matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);


        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);


        glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, division_sphere*division_sphere*6*4);
        }

        else if(i==3){//CONE
        GLfloat Alterations2[16];
        matrixTranslate4x4(3.0f, 0.0f, -3.0f, Alterations); 
        matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
        matrixRotate4x4(90,1.0f,0.0f,0.0f,Alterations2);

        matrixMultiply4x4(Alterations2, mXForm, mXForm1);
        matrixMultiply4x4(mRotate, mXForm1, mXForm2);
        matrixMultiply4x4(Alterations, mXForm2, mXForm3);
        matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);


        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);


        glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, division_cone*division_cone*2*6);

        }
        else if(i==4){//CYLINDER
            GLfloat Alterations2[16];
        matrixTranslate4x4(3.0f, 0.0f, 3.0f, Alterations); 
        matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
        matrixRotate4x4(90,1.0f,0.0f,0.0f,Alterations2);

        matrixMultiply4x4(Alterations2, mXForm, mXForm1);
        matrixMultiply4x4(mRotate, mXForm1, mXForm2);
        matrixMultiply4x4(Alterations, mXForm2, mXForm3);

        matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);


        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);


        glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, division_cylinder*division_cylinder*2*6);
        
        }

        matrixIdentity4x4(modelViewMatrix);

        // -------------------------------------------------------------------------------
    }
    glFlush();
    glfwSwapBuffers(window);
    glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(5, VAO);
    glDeleteBuffers(5, VBO);
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

    GLfloat vertices_sq[] = {
        square_v[0][0],square_v[0][1],square_v[0][2],1.0f,
        square_v[1][0],square_v[1][1],square_v[1][2],1.0f,
        square_v[2][0],square_v[2][1],square_v[2][2],1.0f,

        square_v[2][0],square_v[2][1],square_v[2][2],1.0f,
        square_v[3][0],square_v[3][1],square_v[3][2],1.0f,
        square_v[1][0],square_v[1][1],square_v[1][2],1.0f,

        square_v[1][0],square_v[1][1],square_v[1][2],1.0f,
        square_v[3][0],square_v[3][1],square_v[3][2],1.0f,
        square_v[5][0],square_v[5][1],square_v[5][2],1.0f,

        square_v[5][0],square_v[5][1],square_v[5][2],1.0f,
        square_v[3][0],square_v[3][1],square_v[3][2],1.0f,
        square_v[4][0],square_v[4][1],square_v[4][2],1.0f,

        square_v[4][0],square_v[4][1],square_v[4][2],1.0f,
        square_v[5][0],square_v[5][1],square_v[5][2],1.0f,
        square_v[6][0],square_v[6][1],square_v[6][2],1.0f,

        square_v[6][0],square_v[6][1],square_v[6][2],1.0f,
        square_v[5][0],square_v[5][1],square_v[5][2],1.0f,
        square_v[7][0],square_v[7][1],square_v[7][2],1.0f,

        square_v[7][0],square_v[7][1],square_v[7][2],1.0f,
        square_v[2][0],square_v[2][1],square_v[2][2],1.0f,
        square_v[6][0],square_v[6][1],square_v[6][2],1.0f,

        square_v[2][0],square_v[2][1],square_v[2][2],1.0f,
        square_v[6][0],square_v[6][1],square_v[6][2],1.0f,
        square_v[4][0],square_v[4][1],square_v[4][2],1.0f,

        square_v[0][0],square_v[0][1],square_v[0][2],1.0f,
        square_v[1][0],square_v[1][1],square_v[1][2],1.0f,
        square_v[7][0],square_v[7][1],square_v[7][2],1.0f,
    };

    GLfloat vertice_t[division_toroid*division_toroid*6*4];
    Toroid(vertice_t);

    GLfloat vertice_sp[division_sphere*division_sphere*6*4];
    Sphere(vertice_sp);

    GLfloat vertice_c[division_cone*division_cone*2*6*4];
    Cone(vertice_c);

    GLfloat vertice_cy[division_cylinder*division_cylinder*2*6*4];
    Cylinder(vertice_cy);

    //-----------------------------------------------------------------------

    // CRIAR 3 VAOs e 3 VBOS
    glGenVertexArrays(5, VAO);
    glGenBuffers(5, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_sq), vertices_sq, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_t), vertice_t, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_sp), vertice_sp, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_c), vertice_c, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_cy), vertice_cy, GL_STATIC_DRAW);
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


