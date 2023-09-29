#include "EBO.h"

// EBO is Element Array Buffer

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID); // Only 1 object so 1 in the first parameter, and the second parameter is the reference 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // make VBO as the current object, so any function performed now will be performed on current object.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); // Storing our vertices in VBO. STREAM means vertices will be modified once and used a few times, STATIC means vertices will be modified once, and will be used many times and DYNAMIC means vertices will be modified many times and used many times. Define these properly for Performance. Use DRAW/READ/COPY to draw the vertices and so on... 
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // make EBO as the current object, so any function performed now will be performed on current object.
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind by passing 0 as the current element buffer
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID); // delete current element array buffer object
}