#define GLFW_INCLUDE_NONE
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


GLfloat vertices[] = {
	//               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

GLuint indices[] = {
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
};


int main() {
	//Initialize GLFW
	glfwInit();

	//Tell GLFW what version of OpenGl wer are using
	//Here we are using OpenGl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using CORE profile
	//This means that we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creates the GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(800, 800, "LelleOne", NULL, NULL);
	//Error check
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Intorduce the window to the current context
	glfwMakeContextCurrent(window);

	//Loads glad soit configures OpenGL
	gladLoadGL();

	//Specify the viewpoirt of OpenGL in the window
	//In this case it's 800 * 800 aka from 0, 0 to 800, 800
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Main while loop
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	//Delete window before ending the program
	glfwDestroyWindow(window);
	//Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

//saker för framtida circlar
//void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides) {
//
//	GLint numberOfVertices = numberOfSides + 2;
//
//	GLfloat doublePi = 2.0f * M_PI;
//
//	GLfloat circleVerticesX[numberOfVertices];
//	GLfloat circleVerticesY[numberOfVertices];
//	GLfloat circleVerticesZ[numberOfVertices];
//
//	circleVerticesX[0] = x;
//	circleVerticesY[0] = y;
//	circleVerticesZ[0] = z;
//
//	for (int i = 1; i < numberOfVertices; i++) {
//
//		circleVerticesX = x + (radius * cos(i * doublePi / numberOfSides));
//		circleVerticesY = y + (radius * sin(i * doublePi / numberOfSides));
//		circleVerticesZ = z;
//	}
//
//	GLfloat allCircleVertices[numberOfVertices * 3];
//
//	for (int i = 0; i < numberOfVertices; i++) {
//
//		allCircleVertices[i * 3] = circleVerticesX[i];
//		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
//		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
//	}
//}