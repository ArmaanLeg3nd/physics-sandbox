#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID); // Only 1 object so 1 in the first parameter, and the second parameter is the reference 
	glBindBuffer(GL_ARRAY_BUFFER, ID); // make VBO as the current object, so any function performed now will be performed on current object.
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); // Storing our vertices in VBO. STREAM means vertices will be modified once and used a few times, STATIC means vertices will be modified once, and will be used many times and DYNAMIC means vertices will be modified many times and used many times. Define these properly for Performance. Use DRAW/READ/COPY to draw the vertices and so on... 
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID); // make VBO as the current object, so any function performed now will be performed on current object.
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}