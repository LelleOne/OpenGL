#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::VBO::Bind() {

	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::VBO::Unbind() {

	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::VBO::Delete() {

	glDeleteBuffers(1, &ID);
}