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

// #define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


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
GLuint VAO[26];
GLuint VBO[26];
GLuint ObjectColor;
GLuint AmbientColor;
GLuint Ka;


GLuint tex0,tex1,tex2,tex3,tex4,tex5,tex6,tex7,tex8;


float angle = 0.0f;
float step = -0.01f;
const float division_sphere = 30;
const int division_cone = 60;
const int division_cylinder = 20;

int sphere_dim = division_sphere*division_sphere*4;
int cone_dim = division_cone*division_cone*6;
int cylinder_dim = division_cylinder*(division_cylinder)*6;
int disc_dim = (division_cylinder+2);
int disc_c_dim = division_cone+2;


float r_int = 0.4f;
float r_ext = 1.0f;
float r_sphere = 1.0f;
float r_cone = 0.5f;
float h_cone = 1.0f;
float r_cylinder = 1.0f;
float h_cylinder = 1.0f;

GLuint fbo[1];
GLuint rbo[1];
GLuint cubemap[1];
int cube_text_height = 600;
int cube_text_width = 600;



void Calculo_Sphere(float theta, float phi, float point[3],float u[1],float v[1]){

        point[0] = r_sphere*cos(theta)*sin(phi);
        point[1] = r_sphere*sin(theta)*sin(phi);
        point[2] = r_sphere*cos(phi);
        u[0] = theta/(2.0*PI);
        v[0] = phi/(PI);

}  
void Sphere(float vertice_sp[sphere_dim*4],float norm[sphere_dim*4], float sphere_tex[sphere_dim*4]){
//    0 2pi
    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_sphere);
    float theta2 = div;
    float phi1 = 0.0f;
    float div2 = (2.0*PI)/(division_sphere);
    float phi2 = div2;
    float point[3] = {0.0f,0.0f,0.0f};
    float v1[3],v2[3],aux[3],n[3];
    float u[1],v[1];
    for(int i =0; i< sphere_dim*4; i+=24){
            //Ponto 1
            Calculo_Sphere(theta1,phi1,point,u,v);
            vertice_sp[i+0] = point[0] ;vertice_sp[i+1] = point[1];vertice_sp[i+2] = point[2]; vertice_sp[i+3] = 1.0f;
            sphere_tex[i+0] = u[0];        sphere_tex[i+1] = v[0];       sphere_tex[i+2] = 0.0f;     sphere_tex[i+3] = 0.0f;
            
            aux[0] = point[0]; aux[1] = point[1]; aux[2] = point[0];

            //Ponto 2
            Calculo_Sphere(theta2,phi1,point,u,v);
            vertice_sp[i+4] = point[0] ;vertice_sp[i+5] = point[1];vertice_sp[i+6] = point[2]; vertice_sp[i+7] = 1.0f;
            sphere_tex[i+4] = u[0];        sphere_tex[i+5] = v[0];       sphere_tex[i+6] = 0.0f;     sphere_tex[i+7] = 0.0f;
            v1[0] = point[0]; v1[1] = point[1]; v1[2] = point[0];
            


            //Ponto 3
            Calculo_Sphere(theta1,phi2,point,u,v);
            vertice_sp[i+8] = point[0] ;vertice_sp[i+9] = point[1];vertice_sp[i+10] = point[2]; vertice_sp[i+11] = 1.0f;
            sphere_tex[i+8] = u[0];        sphere_tex[i+9] = v[0];       sphere_tex[i+10] = 0.0f;     sphere_tex[i+11] = 0.0f;
            v2[0] = point[0]; v2[1] = point[1]; v2[2] = point[0];

            v1[0] = v1[0] - aux[0];
            v1[1] = v1[1] - aux[1];
            v1[2] = v1[2] - aux[2];

 
            Calculo_Normal((v1),(v2),aux,n);
            norm[i+0] = n[0] ;norm[i+1] = n[1];norm[i+2] = n[2]; norm[i+3] = 1.0f;
            norm[i+4] = n[0] ;norm[i+5] = n[1];norm[i+6] = n[2]; norm[i+7] = 1.0f;
            norm[i+8] = n[0] ;norm[i+9] = n[1];norm[i+10] = n[2]; norm[i+11] = 1.0f;

            // printf("\n %f %f %f ", aux[0],aux[1],aux[2] );
            //Ponto 3
            Calculo_Sphere(theta1,phi2,point,u,v);
            vertice_sp[i+12] = point[0] ;vertice_sp[i+13] = point[1];vertice_sp[i+14] = point[2]; vertice_sp[i+15] = 1.0f;
            sphere_tex[i+12] = u[0];        sphere_tex[i+13] = v[0];       sphere_tex[i+14] = 0.0f;     sphere_tex[i+15] = 0.0f;
            aux[0] = point[0]; aux[1] = point[1]; aux[2] = point[0];

            //Ponto 4
            Calculo_Sphere(theta2,phi2,point,u,v);
            vertice_sp[i+16] = point[0] ;vertice_sp[i+17] = point[1];vertice_sp[i+18] = point[2]; vertice_sp[i+19] = 1.0f;
            sphere_tex[i+16] = u[0];        sphere_tex[i+17] = v[0];       sphere_tex[i+18] = 0.0f;     sphere_tex[i+19] = 0.0f;
            v1[0] = point[0]; v1[1] = point[1]; v1[2] = point[0];

            //Ponto 2
            Calculo_Sphere(theta2,phi1,point,u,v);
            vertice_sp[i+20] = point[0] ;vertice_sp[i+21] = point[1];vertice_sp[i+22] = point[2]; vertice_sp[i+23] = 1.0f;
            sphere_tex[i+20] = u[0];        sphere_tex[i+21] = v[0];       sphere_tex[i+22] = 0.0f;     sphere_tex[i+23] = 0.0f;
            v2[0] = point[0]; v2[1] = point[1]; v2[2] = point[0];


            v1[0] = v1[0] - aux[0];
            v1[1] = v1[1] - aux[1];
            v1[2] = v1[2] - aux[2];

            Calculo_Normal((v1),(v2),aux,n);
            norm[i+12] = n[0] ;norm[i+13] = n[1];norm[i+14] = n[2]; norm[i+15] = 1.0f;
            norm[i+16] = n[0] ;norm[i+17] = n[1];norm[i+18] = n[2]; norm[i+19] = 1.0f;
            norm[i+20] = n[0] ;norm[i+21] = n[1];norm[i+22] = n[2]; norm[i+23] = 1.0f;



            theta1 = theta2;
            theta2+=div;

            if(theta2 >= (2.0*PI)){
                phi1 = phi2;
                phi2+=div2;
                theta1 = 0.0f;
                theta2 = div; 
            }
    }   
    
}



void Calculo_Cone(float theta, float h, float point[3],float u[1], float v[1]){

        point[0] = ((h_cone-h)/(h_cone))*r_cone*cos(theta);
        point[1] = ((h_cone-h)/(h_cone))*r_cone*sin(theta);
        point[2] = h;
        u[0] = theta/(2.0*PI);
        v[0] = h/(h_cone);
}  
void Cone(float vertice_c[cone_dim*4], float norm[cone_dim*4], float cone_tex[cone_dim*4]){
//    0 2pi
    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_cone);
    float theta2 = div;
    float div2 = h_cone/(division_cone);
    float h1 = h_cone;
    float h2 = h_cone- div2;
    float point[3] = {0.0f,0.0f,0.0f};
    float v1[3],v2[3],aux[3],n[3];
    float u[1],v[1];
    for(int i =0; i< cone_dim*4; i+=24){ 

            //Ponto 1
            Calculo_Cone(theta1,h1,point,u,v);
            vertice_c[i+0] = point[0] ;vertice_c[i+1] = point[1];vertice_c[i+2] = point[2]; vertice_c[i+3] = 1.0f;
            cone_tex[i+0]  = u[0];        cone_tex[i+1]  = v[0];       cone_tex[i+2]  = 0.0f;     cone_tex[i+3]  = 0.0f;
            aux[0] = point[0]; aux[1] = point[1]; aux[2] = point[2];
            //Ponto 2
            Calculo_Cone(theta2,h1,point,u,v);
            vertice_c[i+4] = point[0] ;vertice_c[i+5] = point[1];vertice_c[i+6] = point[2]; vertice_c[i+7] = 1.0f;
            cone_tex[i+4]  = u[0];        cone_tex[i+5]  = v[0];       cone_tex[i+6]  = 0.0f;     cone_tex[i+7]  = 0.0f;
            v1[0] = point[0]; v1[1] = point[1]; v1[2] = point[2];

            //Ponto 3
            Calculo_Cone(theta1,h2,point,u,v);
            vertice_c[i+8] = point[0] ;vertice_c[i+9] = point[1];vertice_c[i+10] = point[2]; vertice_c[i+11] = 1.0f;
            cone_tex[i+8]  = u[0];        cone_tex[i+9]  = v[0];       cone_tex[i+10]  = 0.0f;     cone_tex[i+11]  = 0.0f;
            v2[0] = point[0]; v2[1] = point[1]; v2[2] = point[2];


            Calculo_Normal(v1,v2,aux,n);
            norm[i+0] = n[0] ;norm[i+1] = n[1];norm[i+2] = n[2]; norm[i+3] = 1.0f;
            norm[i+4] = n[0] ;norm[i+5] = n[1];norm[i+6] = n[2]; norm[i+7] = 1.0f;
            norm[i+8] = n[0] ;norm[i+9] = n[1];norm[i+10] = n[2]; norm[i+11] = 1.0f;


            //Ponto 3
            Calculo_Cone(theta1,h2,point,u,v);
            vertice_c[i+12] = point[0] ;vertice_c[i+13] = point[1];vertice_c[i+14] = point[2]; vertice_c[i+15] = 1.0f;
            cone_tex[i+12]  = u[0];        cone_tex[i+13]  = v[0];       cone_tex[i+14]  = 0.0f;     cone_tex[i+15]  = 0.0f;
            aux[0] = point[0]; aux[1] = point[1]; aux[2] = point[2];

            //Ponto 4
            Calculo_Cone(theta2,h2,point,u,v);
            vertice_c[i+16] = point[0] ;vertice_c[i+17] = point[1];vertice_c[i+18] = point[2]; vertice_c[i+19] = 1.0f;
            cone_tex[i+16]  = u[0];        cone_tex[i+17]  = v[0];       cone_tex[i+18]  = 0.0f;     cone_tex[i+19]  = 0.0f;
            v1[0] = point[0]; v1[1] = point[1]; v1[2] = point[2];

            //Ponto 2
            Calculo_Cone(theta2,h1,point,u,v);
            vertice_c[i+20] = point[0] ;vertice_c[i+21] = point[1];vertice_c[i+22] = point[2]; vertice_c[i+23] = 1.0f;
            cone_tex[i+20]  = u[0];        cone_tex[i+21]  = v[0];       cone_tex[i+22]  = 0.0f;     cone_tex[i+23]  = 0.0f;
            v2[0] = point[0]; v2[1] = point[1]; v2[2] = point[2];


            Calculo_Normal(v1,v2,aux,n);
            norm[i+12] = n[0] ;norm[i+13] = n[1];norm[i+14] = n[2]; norm[i+15] = 1.0f;
            norm[i+16] = n[0] ;norm[i+17] = n[1];norm[i+18] = n[2]; norm[i+19] = 1.0f;
            norm[i+20] = n[0] ;norm[i+21] = n[1];norm[i+22] = n[2]; norm[i+23] = 1.0f;


            theta1 = theta2;
            theta2+=div;

            if(theta2 > (2*PI)){
                if(h2<0.0f){
                    h1 = h_cone;
                    h2=h_cone- div2;
                }
                else{
                    h1 = h2;
                    h2-=div2;
                }
                
                theta1 = 0.0f;
                theta2 = div; 
            }
            
    }   
    
}        
void Calculo_Cylinder(float theta, float r, float h, float point[3], float u[1], float v[1]){

        point[0] = r*cos(theta);
        point[1] = r*sin(theta);
        point[2] = h;
        u[0] = h/(h_cylinder)*cos(theta);
        v[0] = h/(h_cylinder)*sin(theta);

}  
void Cylinder(float vertice_cy[cylinder_dim*4],float norm[cylinder_dim*4],float cy_tex[cylinder_dim*4]){
//    0 2pi
    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_cylinder);
    float theta2 = div;

    float div2 = h_cylinder/(division_cylinder);
    float h1 = 0.0f;
    float h2 = div2;

    float point[3] = {0.0f,0.0f,0.0f};
    float v1[3],v2[3],aux[3];
    float u[1],v[1];
    for(int i =0; i< cylinder_dim*4; i+=24){

            //Ponto 1
            Calculo_Cylinder(theta1,r_cylinder,h1,point,u,v);
            vertice_cy[i+0] = point[0] ;vertice_cy[i+1] = point[1];vertice_cy[i+2] = point[2]; vertice_cy[i+3] = 1.0f;
                cy_tex[i+0] = u[0];            cy_tex[i+1] = v[0];           cy_tex[i+2] = 0.0f;         cy_tex[i+3]  = 0.0f;
            aux[0] = point[0]; aux[1] = point[1]; aux[2] = point[0];
            //Ponto 2
            Calculo_Cylinder(theta2,r_cylinder,h1,point,u,v);
            vertice_cy[i+4] = point[0] ;vertice_cy[i+5] = point[1];vertice_cy[i+6] = point[2]; vertice_cy[i+7] = 1.0f;
                cy_tex[i+4] = u[0];            cy_tex[i+5] = v[0];           cy_tex[i+6] = 0.0f;         cy_tex[i+7]  = 0.0f;
            v1[0] = point[0]; v1[1] = point[1]; v1[2] = point[0];

            //Ponto 3
            Calculo_Cylinder(theta1,r_cylinder,h2,point,u,v);
            vertice_cy[i+8] = point[0] ;vertice_cy[i+9] = point[1];vertice_cy[i+10] = point[2]; vertice_cy[i+11] = 1.0f;
                cy_tex[i+8] = u[0];            cy_tex[i+9] = v[0];           cy_tex[i+10] = 0.0f;         cy_tex[i+11]  = 0.0f;
            v2[0] = point[0]; v2[1] = point[1]; v2[2] = point[0];

            norm[i+0] = aux[0] ;norm[i+1] = aux[1];norm[i+2] = 0.0f; norm[i+3] = 1.0f;
            norm[i+4] = v1[0] ;norm[i+5] = v1[1];norm[i+6] = 0.0f; norm[i+7] = 1.0f;
            norm[i+8] = v2[0] ;norm[i+9] = v2[1];norm[i+10] = 0.0f; norm[i+11] = 1.0f;

            //Ponto 3
            Calculo_Cylinder(theta1,r_cylinder,h2,point,u,v);
            vertice_cy[i+12] = point[0] ;vertice_cy[i+13] = point[1];vertice_cy[i+14] = point[2]; vertice_cy[i+15] = 1.0f;
                cy_tex[i+12] = u[0];            cy_tex[i+13] = v[0];           cy_tex[i+14] = 0.0f;         cy_tex[i+15]  = 0.0f;
            aux[0] = point[0]; aux[1] = point[1]; aux[2] = point[0];

            //Ponto 4
            Calculo_Cylinder(theta2,r_cylinder,h2,point,u,v);
            vertice_cy[i+16] = point[0] ;vertice_cy[i+17] = point[1];vertice_cy[i+18] = point[2]; vertice_cy[i+19] = 1.0f;
                cy_tex[i+16] = u[0];            cy_tex[i+17] = v[0];           cy_tex[i+18] = 0.0f;         cy_tex[i+19]  = 0.0f;
            v1[0] = point[0]; v1[1] = point[1]; v1[2] = point[0];

            //Ponto 2
            Calculo_Cylinder(theta2,r_cylinder,h1,point,u,v);
            vertice_cy[i+20] = point[0] ;vertice_cy[i+21] = point[1];vertice_cy[i+22] = point[2]; vertice_cy[i+23] = 1.0f;
                cy_tex[i+20] = u[0];            cy_tex[i+21] = v[0];           cy_tex[i+22] = 0.0f;         cy_tex[i+23]  = 0.0f;
            v2[0] = point[0]; v2[1] = point[1]; v2[2] = point[0];


            norm[i+12] = aux[0] ;norm[i+13] = aux[1];norm[i+14] = 0.0f; norm[i+15] = 1.0f;
            norm[i+16] = v1[0] ;norm[i+17] = v1[1];norm[i+18] = 0.0f; norm[i+19] = 1.0f;
            norm[i+20] = v2[0] ;norm[i+21] = v2[1];norm[i+22] = 0.0f; norm[i+23] = 1.0f;


            theta1 = theta2;
            theta2+=div;

            if(theta1 > (2*PI)){
                h1 = h2;
                h2+=div2;
                theta1 = 0.0f;
                theta2 = div; 
            }
    }

}  
void Calculo_Disc(float theta, float r, float h, float point[3], float u[1], float v[1]){

        point[0] = r*cos(theta);
        point[1] = r*sin(theta);
        point[2] = h;
        u[0] = r*cos(theta);
        v[0] = r*sin(theta);

} 
void Disc(float h , float vertice_disc[(disc_dim+2)*7],float disc_tex[(disc_dim+2)*7]){
    float theta1 = 0.0f;
    float div = (2.0*PI)/(division_cylinder);

    float point[3] = {0.0f,0.0f,0.0f};
    float factor = 1.0f;
    float u[1],v[1];
    if(h == 0.0f){
            factor = -1.0f;
        }

    vertice_disc[0] = 0.0f ;vertice_disc[1] = 0.0f ;vertice_disc[2] = h; vertice_disc[3] = 1.0f;
    disc_tex    [0] = 0.5f;     disc_tex[1] = 0.5f;     disc_tex[2] = 0.0f;  disc_tex[3]  = 0.0f;
    vertice_disc[4] = 0.0f ;vertice_disc[5] = 0.0f ;vertice_disc[6] = 1.0*factor;
    disc_tex    [4] = 0.0f;     disc_tex[5] = 0.0f;     disc_tex[6] = 0.0f; 
    

    for(int i = 7; i< (disc_dim+2)*7; i+=7){
            
            Calculo_Disc(theta1,r_cylinder,h,point,u,v);
            
            vertice_disc[i+0] = point[0] ;vertice_disc[i+1] = point[1];vertice_disc[ i+2] = point[2]; vertice_disc[ i+3] = 1.0f;
            disc_tex    [i+0] = u[0];     disc_tex[i+1] = v[0];     disc_tex[i+2] = 0.0f;  disc_tex[i+3]  = 0.0f;
            vertice_disc[i+4] = 0.0f ;vertice_disc[i+5] = 0.0f;vertice_disc[ i+6] = 1.0*factor; 
            disc_tex    [i+4] = 0.0f;     disc_tex[i+5] = 0.0f;     disc_tex[i+6] = 0.0f;
            theta1 += div;

            if(theta1 > (2.0*PI)){
                theta1 = 0.0f;
            }
            
    }
}

void Disc_Cone(float h , float vertice_c_disc[(disc_c_dim+2)*8]){
    float theta1 = 0.0f;
    float div = (2.0*PI)/(cone_dim-1);

    float point[3] = {0.0f,0.0f,0.0f};
    float factor = 1.0f;
    float u[1],v[1];
    if(h == 0.0f){
            factor = -1.0f;
        }

    vertice_c_disc[0] = 0.0f ;vertice_c_disc[1] = 0.0f ;vertice_c_disc[2] = h; vertice_c_disc[3] = 1.0f;
    vertice_c_disc[4] = 0.0f ;vertice_c_disc[5] = 0.0f ;vertice_c_disc[6] = 1.0*factor;
    

    for(int i = 7; i< (cone_dim+2)*8; i+=7){
            
            Calculo_Cylinder(theta1,r_cone,h,point,u,v);

            vertice_c_disc[i+0] = point[0] ;vertice_c_disc[i+1] = point[1];vertice_c_disc[ i+2] = point[2]; vertice_c_disc[ i+3] = 1.0f;
            vertice_c_disc[i+4] = 0.0f ;vertice_c_disc[i+5] = 0.0f;vertice_c_disc[ i+6] = 1.0*factor; 

            theta1 += div;

            if(theta1 > (2.0*PI)){
                theta1 = 0.0f;
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set Projection Matrix
    // --------------------------------------
    GLfloat projMatrix[16];
    // ortho(-10.0f, 10.0f, -5.0f, 5.0f, -10.0f, 10.0f, projMatrix);
    frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f, projMatrix);
    int projMatrixLoc = glGetUniformLocation(shaderProgram, "u_projMatrix");
    glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);

    // Set View transformation
    // --------------------------------------
    float viewer_p[] = {0.0f,3.0f,8.0f};
    GLfloat viewMatrix[16];
    lookAt(viewer_p[0], viewer_p[1], viewer_p[2], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);
    int viewerMatrixloc = glGetUniformLocation(shaderProgram, "viewerMatrix");
    glUniformMatrix4fv(viewerMatrixloc, 1, false, viewMatrix);
    int modelViewMatrixLoc = glGetUniformLocation(shaderProgram, "u_modelViewMatrix");

    int LightPos = glGetUniformLocation(shaderProgram,"light.lightPos");
    int AmbientColor = glGetUniformLocation(shaderProgram,"light.AmbientColor");
    int DiffColor = glGetUniformLocation(shaderProgram,"light.DiffColor");
    int SpecColor = glGetUniformLocation(shaderProgram,"light.SpecColor");
    int SpotDirection = glGetUniformLocation(shaderProgram,"light.Spot_Direction");
    int SpotCutOff = glGetUniformLocation(shaderProgram,"light.spot_cutoff");
    int spot_exp = glGetUniformLocation(shaderProgram,"light.spot_exp");
    int model = glGetUniformLocation(shaderProgram,"model");
    int viewer_pos = glGetUniformLocation(shaderProgram,"viewPos");
    int tonalizationType = glGetUniformLocation(shaderProgram,"ton");
    int LType = glGetUniformLocation(shaderProgram,"light_type");
    int material_diff = glGetUniformLocation(shaderProgram,"material.diffuse");
    int material_spec = glGetUniformLocation(shaderProgram,"material.specular");
    int shineness = glGetUniformLocation(shaderProgram,"material.shineness");
    int Ka = glGetUniformLocation(shaderProgram,"material.Ka");
    int Kd = glGetUniformLocation(shaderProgram,"material.Kd");
    int Ks = glGetUniformLocation(shaderProgram,"material.Ks");

    glUniform1i(material_diff, 0);
    glUniform1i(material_spec, 1);


    // TONALIZATION TYPE
    // 0: POINT LIGHT 
    // 1: DIRETIONAL LIGHT 
    // 2: SPOT LIGHT

    glUniform1i(tonalizationType, 0);

    // L TYPE
    // 0: PHONG 
    // 1: GOURAUD 
    // 2: FLAT 

    glUniform1i(LType, 0);

    
    glUniform4f(LightPos,0.0f, 3.0f, 8.0f,1.0f);
    // glUniform4f(LightPos,0.0f, 3.0f, -8.0f,1.0f);
    // glUniform4f(LightPos,8.0f, 0.0f, 0.0f,1.0f);
    // glUniform4f(LightPos,0.0f, 0.0f, 0.0f,1.0f);

    glUniform4f(AmbientColor, 0.8f, 0.8f, 0.8f, 1.0f);
    glUniform4f(DiffColor, 0.4f, 0.4f, 0.4f, 1.0f);
    glUniform4f(SpecColor, 1.0f, 1.0f, 1.0f, 1.0f);

    glUniform4f(SpotDirection, 0.0f,0.0f,0.0f,1.0f);
    glUniform1f(SpotCutOff, 30); // Em Graus
    glUniform1f(spot_exp, 1); // Em Graus

    // Set Model transformation
    // --------------------------------------
    GLfloat mXForm[16];
    matrixIdentity4x4(mXForm);
    // Set ModelView transformation
    // --------------------------------------
    GLfloat modelViewMatrix[16];
    matrixIdentity4x4(modelViewMatrix);
    float time=0;



    // Render loo 
    // ---------------------------------------
    while (!glfwWindowShouldClose(window)) {
        // Check input
        // ---------------------------------------
        processInput(window);

        // Clear screen
        // --------------------------------------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        time+= 0.005f;

        // glUniform4f(LightPos, 5+ cos(time) * 10.0f,5.0f, 5+  sin(time) * 10.0f,1.0f);
        
        glUniform4f(viewer_pos, viewer_p[0], viewer_p[1], viewer_p[2],1.0f);

        // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glEnable(GL_DEPTH_TEST);
        for(int i=0;i<11;i++){

            glBindVertexArray(VAO[i]);

            GLfloat mRotate[16],mXForm2[16],mXForm3[16],mXForm1[16],mXForm4[16];

            angle+=step;
            GLfloat Alterations[16];
            GLfloat Alterations2[16];
            matrixIdentity4x4(Alterations2);

            matrixIdentity4x4(modelViewMatrix);
            matrixIdentity4x4(Alterations);

            if(i==0){


            glBindTexture(GL_TEXTURE_2D, tex0);

            //SQUARES 1
            matrixTranslate4x4(0.0f, 0.0f, -5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixMultiply4x4(mRotate, mXForm, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            
            glUniform1i(shineness, 1);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,0.1f,0.1f,0.1f);


            glDrawArrays(GL_TRIANGLES, 0, 36);
             
            }
            else if(i==1){
            //SQUARES 2

            glBindTexture(GL_TEXTURE_2D, tex1);
            matrixTranslate4x4(0.0f, 0.0f, 5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixMultiply4x4(mRotate, mXForm, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 1);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,0.0f,0.0f,0.0f);

            glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            else if(i==2){
            //SPHERE 1 
            // glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, tex8);
            matrixTranslate4x4(0.0f, 0.0f, 0.0f, Alterations); 
            matrixRotate4x4(0,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(Alterations, mXForm1, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 64);
            glUniform3f(Ka,0.5f,0.5f,0.5f);
            glUniform3f(Kd,0.4f,0.4f,0.4f);
            glUniform3f(Ks,1.0f,1.0f,1.0f);

            glDrawArrays(GL_TRIANGLES, 0, sphere_dim);
            }

            else if(i==3){
            //SPHERE 2
            glBindTexture(GL_TEXTURE_2D, tex2);
            matrixTranslate4x4(-5.0f, 0.0f, 5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 1);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,0.0f,0.0f,0.0f);

            glDrawArrays(GL_TRIANGLES, 0, sphere_dim);        
            }
            else if(i==4){
            //SPHERE 3
            glBindTexture(GL_TEXTURE_2D, tex3);
            matrixTranslate4x4(5.0f, 0.0f, -5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 64);
            glUniform3f(Ka,0.3f,0.3f,0.3f);
            glUniform3f(Kd,0.7f,0.7f,0.7f);
            glUniform3f(Ks,1.0f,1.0f,1.0f);

            glDrawArrays(GL_TRIANGLES, 0, sphere_dim);    
            }
            
            else if(i==5){
            //CONE 1
            glBindTexture(GL_TEXTURE_2D, tex4);
            matrixTranslate4x4(5.0f, 0.0f, 0.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 128);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,1.0f,1.0f,1.0f);

            glDrawArrays(GL_TRIANGLES, 0, cone_dim);    
            }

            else if(i==6){
            //CONE 2
            glBindTexture(GL_TEXTURE_2D, tex5);
            matrixTranslate4x4(-5.0f, 0.0f, 0.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 2);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,0.5f,0.5f,0.5f);

            glDrawArrays(GL_TRIANGLES, 0, cone_dim);    
            }
            
            else if(i==7){
            // CYLINDER 1
            glBindTexture(GL_TEXTURE_2D, tex6);
            matrixTranslate4x4(-5.0f, 0.0f, -5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 1);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,0.5f,0.5f,0.5f);

            glDrawArrays(GL_TRIANGLES, 0, cylinder_dim);    
            }
            else if(i==8){
            // DISC CYLINDER 1 
            glBindTexture(GL_TEXTURE_2D, tex6);    
            matrixTranslate4x4(-5.0f, 0.0f, -5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);

            glUniform1i(shineness, 1);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,0.5f,0.5f,0.5f);

            glDrawArrays(GL_TRIANGLE_FAN, 0, (disc_dim+2));   
            }

            
            else if(i==9){
            // CYLINDER 2
            glBindTexture(GL_TEXTURE_2D, tex7); 
            matrixTranslate4x4(5.0f, 0.0f, 5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);
            
            glUniform1i(shineness, 128);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,1.0f,1.0f,1.0f);

            glDrawArrays(GL_TRIANGLES, 0, cylinder_dim);    
            }

            else if(i==10){
            // DISC CYLINDER 2
            glBindTexture(GL_TEXTURE_2D, tex7); 
            matrixTranslate4x4(5.0f, 0.0f, 5.0f, Alterations); 
            matrixRotate4x4(angle,0.0f,1.0f,0.0f,mRotate);
            matrixRotate4x4(-90,1.0f,0.0f,0.0f,Alterations2);
            matrixMultiply4x4(Alterations2, mXForm, mXForm1);
            matrixMultiply4x4(mRotate, mXForm1, mXForm4);
            matrixMultiply4x4(Alterations, mXForm4, mXForm2);
            matrixMultiply4x4(mRotate, mXForm2, mXForm3);    
            glUniformMatrix4fv(model, 1, false, mXForm3);
            matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);
            glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);

            glUniform1i(shineness, 128);
            glUniform3f(Ka,0.4f,0.4f,0.4f);
            glUniform3f(Kd,0.8f,0.8f,0.8f);
            glUniform3f(Ks,1.0f,1.0f,1.0f);

            glDrawArrays(GL_TRIANGLE_FAN, 0, (disc_dim+2));    
            }
        
        }
        // -------------------------------------------------------------------------------
    
    glFlush();
    glfwSwapBuffers(window);
    glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(26, VAO);
    glDeleteBuffers(26, VBO);
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


        // --------------------------TEXTURES---------------------------
    
    

    glGenTextures(1, &tex0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    // Load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *image = stbi_load("./texture/container.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    glGenTextures(1, &tex1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/fabric.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);
 
    glGenTextures(1, &tex2);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/grass.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    glGenTextures(1, &tex3);
    glBindTexture(GL_TEXTURE_2D, tex3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/wall.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    glGenTextures(1, &tex4);
    glBindTexture(GL_TEXTURE_2D, tex4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/floor.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    glGenTextures(1, &tex5);
    glBindTexture(GL_TEXTURE_2D, tex5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/water.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    glGenTextures(1, &tex6);
    glBindTexture(GL_TEXTURE_2D, tex6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/plastic.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);


    glGenTextures(1, &tex7);
    glBindTexture(GL_TEXTURE_2D, tex7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/padrao.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

    glGenTextures(1, &tex8);
    glBindTexture(GL_TEXTURE_2D, tex8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    image = stbi_load("./texture/inox.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

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
    int normalLoc = glGetAttribLocation(shaderProgram, "aNormal");
    int texLoc = glGetAttribLocation(shaderProgram, "atexCoords");


    // Create Vertex Array Object ID
    // ---------------------------------------

    GLfloat vertices_sq[] = {
        -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, -1.0f,0.0f,0.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, -1.0f,1.0f,0.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, -1.0f,1.0f,1.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, -1.0f,1.0f,1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, -1.0f,0.0f,1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, -1.0f,0.0f,0.0f,


        -0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,0.0f,0.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,1.0f,0.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,1.0f,1.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,1.0f,1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,0.0f,1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f,0.0f,0.0f,


        -0.5f,  0.5f,  0.5f, 1.0f, -1.0f,  0.0f,  0.0f,1.0f,0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, -1.0f,  0.0f,  0.0f,1.0f,1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, -1.0f,  0.0f,  0.0f,0.0f,1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, -1.0f,  0.0f,  0.0f,0.0f,1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, -1.0f,  0.0f,  0.0f,0.0f,0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, -1.0f,  0.0f,  0.0f,1.0f,0.0f,


         0.5f,  0.5f,  0.5f, 1.0f,  1.0f,  0.0f,  0.0f,1.0f,0.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  0.0f,1.0f,1.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  0.0f,0.0f,1.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  0.0f,0.0f,1.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  1.0f,  0.0f,  0.0f,0.0f,0.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  1.0f,  0.0f,  0.0f,1.0f,0.0f,


        -0.5f, -0.5f, -0.5f, 1.0f,  0.0f, -1.0f,  0.0f,0.0f,1.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f, -1.0f,  0.0f,1.0f,1.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f,1.0f,0.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f,1.0f,0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f,  0.0f, -1.0f,  0.0f,0.0f,1.0f,


        -0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  1.0f,  0.0f,0.0f,1.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  1.0f,  0.0f,1.0f,1.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  1.0f,  0.0f,1.0f,0.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  1.0f,  0.0f,1.0f,0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  1.0f,  0.0f,0.0f,0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  1.0f,  0.0f,0.0f,1.0f

    };
    // -------------------------SPHERE------------------------------------
    GLfloat vertice_sp[sphere_dim*4];
    GLfloat norm_np[sphere_dim*4];
    GLfloat sphere_tex[sphere_dim*4];
    Sphere(vertice_sp, norm_np,sphere_tex);


    GLfloat vertice_c[cone_dim*4];
    GLfloat norm_c[cone_dim*4];
    GLfloat cone_tex[cone_dim*4];
    Cone(vertice_c,norm_c,cone_tex);


    GLfloat vertice_cy[cylinder_dim*2*4];
    GLfloat norm_cy[cylinder_dim*2*4];
    GLfloat cy_tex[cylinder_dim*4];
    Cylinder(vertice_cy,norm_cy,cy_tex);

    // GLfloat norm_disc_cy[(disc_dim+2)*4];
    GLfloat vertice_disc[(disc_dim+2)*7];
    GLfloat disc_tex[(disc_dim+2)*7];
    Disc(h_cylinder, vertice_disc,disc_tex);

    //-----------------------------------------------------------------------

    // CRIAR 3 VAOs e 3 VBOS
    glGenVertexArrays(26, VAO);
    glGenBuffers(26, VBO);
    //---------------------------SQUARE------------------------------------
    //SQUARE 1
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_sq), vertices_sq, GL_STATIC_DRAW);
    glBindVertexArray(VAO[0]);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(4*sizeof(float)));
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(7*sizeof(float)));
    glEnableVertexAttribArray(2); 

    //SQUARE 2
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_sq), vertices_sq, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(4*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid*)(7*sizeof(float)));
    glEnableVertexAttribArray(2); 

    // //---------------------------SPHERE------------------------------------
    // //SHPERE 1
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_sp), vertice_sp, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(1); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_tex), sphere_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);
    //SPHERE 2
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_sp), vertice_sp, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(1); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_tex), sphere_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);
    //SPHERE 3
    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_sp), vertice_sp, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_tex), sphere_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    // //---------------------------CONE------------------------------------

    //CONE 1
    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_c), vertice_c, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[24]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(norm_c), norm_c, GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cone_tex), cone_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    // //CONE 2
    glBindVertexArray(VAO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_c), vertice_c, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[25]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(norm_c), norm_c, GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[11]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cone_tex), cone_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);


    // //---------------------------CYLINDER------------------------------------

    // //CYLINDER 1
    glBindVertexArray(VAO[7]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[12]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_cy), vertice_cy, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[13]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(norm_cy), norm_cy, GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[14]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cy_tex), cy_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[8]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[15]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_disc), vertice_disc, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE,  7 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[16]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_disc), vertice_disc, GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)(4*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[17]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(disc_tex), disc_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  7 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    // //CYLINDER 2
    glBindVertexArray(VAO[9]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[18]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_cy), vertice_cy, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[19]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(norm_cy), norm_cy, GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[20]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cy_tex), cy_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  4 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[10]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[21]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_disc), vertice_disc, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE,  7 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[22]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_disc), vertice_disc, GL_STATIC_DRAW);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)(4*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[23]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(disc_tex), disc_tex, GL_STATIC_DRAW);
    glVertexAttribPointer(texLoc,2, GL_FLOAT, GL_FALSE,  7 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(2);






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


