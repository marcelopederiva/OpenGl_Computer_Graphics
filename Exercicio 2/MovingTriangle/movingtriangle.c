
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "mytools.h"
#include <math.h>
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
GLuint VBO[1], VAO[1];
GLuint gl_VertexID;
// Main: it starts here
// ---------------------------------------
int main(void) {
	fprintf(stdout, "main\n");
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

void display(GLFWwindow* window) {
	fprintf(stdout, "display::start\n");
	fflush(stdout);

	GLfloat step = 0.0;
	GLint offsetLoc = glGetAttribLocation(shaderProgram, "offset");
	GLint colorLoc = glGetAttribLocation(shaderProgram, "color");

    // render loop
    // ---------------------------------------
    while (!glfwWindowShouldClose(window)) {

   // 	fprintf(stdout, "render loop\n");
   // 	fflush(stdout);

        // Check input
        // ---------------------------------------
        processInput(window);

        // Set background color
        // ---------------------------------------
		GLfloat bg[] = {0.0, 0.0, 1.0, 1.0};
		glClearBufferfv(GL_COLOR, 0, bg);

		// Set offset (static vertex attribute)
		// ---------------------------------------
		GLfloat offset[] = {(GLfloat) sin(step) * 0.5, (GLfloat) cos(step) * 0.6, 0.0, 0.0f};
		glVertexAttrib4fv(offsetLoc, offset);

		// Set color (static vertex attribute)
		// ---------------------------------------
		GLfloat color[] = {1.0, (GLfloat)(sin(step) + 1) * 0.5, (GLfloat)(cos(step) + 1) * 0.5, 1.0};
		glVertexAttrib4fv(colorLoc, color);

		// Draw triangle
		//---------------------------------------
		glDrawArrays(GL_TRIANGLES, 0, 3);

		step += 0.01;

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, VAO);
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

	// Print OpenGL information
	fprintf(stderr, "Renderer %s\n", glGetString(GL_RENDERER));
	fprintf(stderr, "Vendor %s\n", glGetString(GL_VENDOR));
	fprintf(stderr, "Version %s\n", glGetString(GL_VERSION));
	fprintf(stderr, "Shading Language Version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	fflush(stderr);

    // Create vertex shader
	// ---------------------------------------
	GLuint vertexShader = generateShader(GL_VERTEX_SHADER, "./movingtriangle.vert");

    // Create fragment shader
	// ---------------------------------------
	GLuint fragmentShader = generateShader(GL_FRAGMENT_SHADER, "./movingtriangle.frag");

    // Create Program and link shaders
	// ---------------------------------------
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


	// Create Vertex Array Object ID
	// ---------------------------------------
    glGenVertexArrays(1, VAO);

    // Create/activate a Vertex Array Object and bind to ID
    // ---------------------------------------
    glBindVertexArray(VAO[0]);

	// Create Buffer ID
    // ---------------------------------------
//    glGenBuffers(1, &gl_VertexID);

    // Create/activate Buffer nd bind to ID
    // ---------------------------------------
//    glBindBuffer(GL_ARRAY_BUFFER, gl_VertexID);
//
    // Initialize  Buffer  with vertex position data
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Associate vertex position data to vertex shader input
    // ---------------------------------------
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) NULL);

    // Enable vertex data to be transfered to shader
    // ---------------------------------------
//    glEnableVertexAttribArray(0);

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

    // glfw: window creation
    // ---------------------------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangles1", NULL, NULL);
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

