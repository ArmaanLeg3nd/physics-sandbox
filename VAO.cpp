#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID); // **Very Important - Generate VAO before VBOs.

}

void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // making sure OpenGL can read the VAO. Parameters - index of the vertex attribute we want to use, no. of values per vertex, what kind of values, this only matters if the values we have are integers - if not then write GL_FALSE, pointer for vertices - amount of data between each vertices. we have 3 floats so just do 3*sizeof(floats), offset - pointer to where vertices are beginning in the array. if the vertices start right in the beginning - write (void*)0
    glEnableVertexAttribArray(layout); // enable vertex attribute array. parameter - position of our vertex attribute
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}