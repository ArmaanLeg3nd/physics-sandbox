#include "VAO.h"

// VAO stands for Vertex Array Object - used to quickly be able to switch between multiple VBOs

VAO::VAO()
{
    glGenVertexArrays(1, &ID); // **Very Important - Generate VAO before VBOs

}

void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
    VBO.Bind(); // Bind vertex buffer object
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // making sure OpenGL can read the VAO. Parameters - index of the vertex attribute we want to use, no. of values per vertex, what kind of values, this only matters if the values we have are integers - if not then write GL_FALSE, pointer for vertices - amount of data between each vertices. we have 3 floats so just do 3*sizeof(floats), offset - pointer to where vertices are beginning in the array. if the vertices start right in the beginning - write (void*)0
    glEnableVertexAttribArray(layout); // enable vertex attribute array. parameter - position of our vertex attribute
    VBO.Unbind(); // Unbind vertex buffer object
}

void VAO::Bind()
{
    glBindVertexArray(ID); // make VAO as the current object, so any function performed now will be performed on current object.
}

void VAO::Unbind()
{
    glBindVertexArray(0); // unbind by passing 0 as the current vertex array
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID); // delete current element vertex array
}