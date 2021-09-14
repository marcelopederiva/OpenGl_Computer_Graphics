/*
 * animatedClear.c
 *
 *  Created on: 4 de fev de 2021
 *      Author: JMario
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Constant
// ---------------------------------------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Function declaration
// ---------------------------------------
void display(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void init(void);
void processInput(GLFWwindow *window);
GLFWwindow* setupEnvironment(void);

// Variable declaration
// ---------------------------------------


int main(void) {
	fprintf(stdout, "main::start\n");
	fflush(stdout);

	// create window and load OpenGL functions
	// ---------------------------------------
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

	fprintf(stdout, "display::start");
	fflush(stdout);

	float inc = 0.005f;
	float dec = -inc;
	float r = 1.0f;
	float g = 0.0f;
	float b = 1.0f;
	float rupdate = 0.0f;
	float gupdate = inc;
	float bupdate = 0;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {

   // 	fprintf(stdout, "display::render loop\n");
   // 	fflush(stdout);

        // input
        // -----
        processInput(window);

        GLfloat color[] = {r, g, b, 1.0f};
   	    glClearBufferfv(GL_COLOR, 0, color);
    	r += rupdate;
    	g += gupdate;
    	b += bupdate;
    	if( r >= 1.0f && g >= 1.0 && b >= 1) {
    		r = g = b = 1.0;
    	    if(rupdate == 0 && bupdate == 0) {
    	    	rupdate = dec;
    	    	gupdate = 0;
    	    	bupdate = 0;
    	    } else if(gupdate == 0 && bupdate == 0) {
    	    	rupdate = 0;
    	    	gupdate = 0;
    	    	bupdate = dec;
    	    } else {
    	    	rupdate = 0;
    	    	gupdate = dec;
    	    	bupdate = 0;
    	    }
    	} else if (r >= 1.0f && g <= 0.0 && b >= 1) {
    		r = 1.0;
    		g = 0.0;
    		b= 1.0;
    		rupdate = 0;
    		gupdate = inc;
    		bupdate = 0;
    	} else if (r <= 0.0f && g >= 1.0 && b >= 1) {
     		r = 0.0;
        	g = 1.0;
        	b= 1.0;
    		rupdate = inc;
    		gupdate = 0.0;
    		bupdate = 0.0;
    	} else if (r >= 1.0f && g >= 1.0 && b <= 0.0) {
     		r = 1.0;
        	g = 1.0;
        	b= 0.0;
    		rupdate = 0;
    		gupdate = 0;
    		bupdate = inc;
    	}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

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
void init (void) {
	fprintf(stdout, "init::start\n");
	fflush(stdout);

	// Print OpenGL information
	fprintf(stderr, "Renderer %s\n", glGetString(GL_RENDERER));
	fprintf(stderr, "Vendor %s\n", glGetString(GL_VENDOR));
	fprintf(stderr, "Version %s\n", glGetString(GL_VERSION));
	fprintf(stderr, "Shading Language Version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	fflush(stderr);

	fprintf(stdout, "init::end\n");
	fflush(stdout);

	return;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "animatedClear", NULL, NULL);
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

	fprintf(stdout, "prepare::end\n");
	fflush(stdout);

    return window;
}




