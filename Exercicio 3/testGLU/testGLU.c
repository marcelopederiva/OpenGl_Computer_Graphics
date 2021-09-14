/*
 * TestGLU.c
 *
 * Test geometric transformation functions.
 *
 *  Created on: Mach 8 2021
 *      Author: JMario
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
GLuint VAO[1];
GLuint VBO[2];

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
//	ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 3.0f, projMatrix);
	frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 3.0f, projMatrix);
//	frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 5.0f, projMatrix);
	int projMatrixLoc = glGetUniformLocation(shaderProgram, "u_projMatrix");
	glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);

	// Set View transformation
	// --------------------------------------
	GLfloat viewMatrix[16];
	lookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);
//	lookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, viewMatrix);
	int modelViewMatrixLoc = glGetUniformLocation(shaderProgram, "u_modelViewMatrix");

	// Set Model transformation
	// --------------------------------------
	GLfloat mXForm[16];
	matrixIdentity4x4(mXForm);

	// Set ModelView transformation
	// --------------------------------------
	GLfloat modelViewMatrix[16];
	matrixIdentity4x4(modelViewMatrix);





	// Set transformation variables
	// --------------------------------------
	float angle = 0.0f;
	float step = -0.01f;

	float x = cos(angle) * 0.5f;
	float y = sin(angle) * 0.5f;
	float z = cos(angle) - 1.0f;


    // Render loop
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







    	//SEQUENCE
    	GLfloat mXForm1[16];
    	GLfloat mXForm2[16];
    	GLfloat mXForm3[16];
    	GLfloat mTransl[16];
    	GLfloat mRotate[16];
    	GLfloat mScale[16];
    	// Set Translation
    	matrixTranslate4x4(-0.25f,-0.25f,0.0f,mTransl);
    	//Set Rotation
    	matrixRotate4x4(90,0.0f,0.0f,1.0f,mRotate);
    	//Set Scale
    	matrixScale4x4(1.0f,1.0f,2.0f,mScale);


		// Set Model transformation
    	// --------------------------------------
		matrixTranslate4x4(x, y, z, mXForm);



    	//Apply the SEQUENCE
    	matrixMultiply4x4(mTransl, mXForm, mXForm1);
    	matrixMultiply4x4(mRotate, mXForm1, mXForm2);
    	matrixMultiply4x4(mScale, mXForm2, mXForm3);

		// Set ModelView Transformation
		// --------------------------------------
		matrixMultiply4x4(viewMatrix, mXForm3, modelViewMatrix);



		glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);


        // Draw triangles
        // ---------------------------------------
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glFlush();

    	// Update translation parameters
        // --------------------------------------
    	angle += step;
    	if(angle < -360)
    		angle = 0;

    	x = cos(angle) * 0.5f;
    	y = sin(angle) * 0.5f;
    	z = cos(angle) - 1.0f;

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, VAO);
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
	int colorLoc = glGetAttribLocation(shaderProgram, "color");
//	int projMatrixLoc = glGetUniformLocation(shaderProgram, "u_projMatrix");
//	int modelViewMatrixLoc = glGetUniformLocation(shaderProgram, "u_modelViewMatrix");


    // Vertex position data
    // -------------------------------
    GLfloat vertices[] = {
    		0.0f, 0.0f, 0.0f, 1.0f, // Bottom left vertex position
			0.5f, 0.0f, 0.0f, 1.0f,  // Bottom right vertex position
			0.0f, 0.5f, 0.0f, 1.0f,  // Top right vertex position
    };

    // Vertex color Data
    // -------------------------------
    GLfloat colors[] = {
    		1.0f, 0.0f, 0.0f, 1.0f, // Bottom left vertex color (red)
			0.0f, 1.0f, 0.0f, 1.0f, // Bottom right vertex color (green)
			0.0f, 0.0f, 1.0f, 1.0f, // Top right vertex color (blue)
    };

	// Create Vertex Array Object ID
	// ---------------------------------------
    glGenVertexArrays(1, VAO);

    // Create/activate a Vertex Array Object and bind to ID
    // ---------------------------------------
    glBindVertexArray(VAO[0]);

	// Generate Buffer IDs for 2 buffers
    // ---------------------------------------
    glGenBuffers(2, VBO);

    // Create/activate a Buffer and bind to ID VBO[0]
    // ---------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

    // Initialize Buffer with vertex position data
    // ---------------------------------------
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Associate vertex data to vertex shader input
    // ---------------------------------------
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    // Enable vertex data to be transfered to shader
    // ---------------------------------------
    glEnableVertexAttribArray(0);

    // Create/activate a Buffer and bind to ID VBO[1]
    // ---------------------------------------
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

    // Initialize Buffer with color data
    // ---------------------------------------
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // Associate color data to vertex shader input
    // ---------------------------------------
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    // Enable vertex data to be transfered to shader
    // ---------------------------------------
    glEnableVertexAttribArray(1);

//	// Set Projection Matrix
//	GLfloat *projMatrix;
//	projMatrix = matrixIdentity();
//	glUniformMatrix4fv(projMatrixLoc, 1, false, projMatrix);
//
//	// Set view transformation
//	GLfloat *modelViewMatrix;
//	modelViewMatrix = matrixIdentity();
//	glUniformMatrix4fv(modelViewMatrixLoc, 1, false, modelViewMatrix);

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TestGLU", NULL, NULL);
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


