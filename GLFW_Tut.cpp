#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
/* IMGUI header files
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
*/


// Custom header files for VAO, VBO, EBO and ShaderClass(also includes vertex shader and fragment shader)
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower Left Corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower Right Corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper Corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner Right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
}; // Vertices for an orange equilateral triangle with another upside down triangle inside with navy blue color

GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
};

int main() 
{
    glfwInit(); // initialize glfw

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // define major opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // define minor opengl version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // define the type of opengl profile being used - core/compatibility (core contains more modern features)
    

    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Tutorial Triangle", NULL, NULL); // create the window. parameters - height, weight, title, fullscreen, ?(not important) 
    if (window == NULL) // handle failing to create the window
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    else
    {
        cout << "GLFW window successfully created" << endl;
    }

    glfwMakeContextCurrent(window); // use window 

    gladLoadGL(); // initialize glad

    glViewport(0, 0, 800, 800); // here the viewport goes from x=0, y=0 to x=800, y=800 - which is our screen size

    Shader shaderProgram("default.vert", "default.frag");

    /*

    GLuint VAO, VBO, EBO; // Array of references, but we only have one object so only one is needed. 

    glGenVertexArrays(1, &VAO); // **Very Important - Generate VAO before VBOs.
    glGenBuffers(1, &VBO); // Only 1 object so 1 in the first parameter, and the second parameter is the reference 
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // make VBO as the current object, so any function performed now will be performed on current object.

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Storing our vertices in VBO. STREAM means vertices will be modified once and used a few times, STATIC means vertices will be modified once, and will be used many times and DYNAMIC means vertices will be modified many times and used many times. Define these properly for Performance. Use DRAW/READ/COPY to draw the vertices and so on... 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // making sure OpenGL can read the VAO. Parameters - index of the vertex attribute we want to use, no. of values per vertex, what kind of values, this only matters if the values we have are integers - if not then write GL_FALSE, pointer for vertices - amount of data between each vertices. we have 3 floats so just do 3*sizeof(floats), offset - pointer to where vertices are beginning in the array. if the vertices start right in the beginning - write (void*)0

    glEnableVertexAttribArray(0); // enable vertex attribute array. parameter - position of our vertex attribute

    glBindBuffer(GL_ARRAY_BUFFER, 0); // optional- to be 100% sure we won't accidentally change VAO or VBO with a function.
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Make sure to unbind it after unbinding VAO since EBO is stored inside VAO. If we do that, we are telling OpenGL that we dont want to use EBO
    
    */

    VAO VAO1; // VAO class object
    VAO1.Bind(); // Call VAO bind function

    VBO VBO1(vertices, sizeof(vertices)); // VBO class object
    EBO EBO1(indices, sizeof(indices)); // EBO class object

    VAO1.LinkVBO(VBO1, 0); // Link VBO function
    VAO1.Unbind(); // Unbind VAO
    VBO1.Unbind(); // Unbind VBO
    EBO1.Unbind(); // Unbind EBO

    while (!glfwWindowShouldClose(window)) // Make the window close only if close button is clicked and not reach the end of the main function immediately 
    {
        glClearColor(0.47f, 0.33f, 0.87f, 1.0f); // prepare to clear the color of the buffer and give it another color
        glClear(GL_COLOR_BUFFER_BIT); // we want to use the above command on color buffer
        /* glUseProgram(shaderProgram); // finally use the shader program */
        shaderProgram.Activate();
        /*glBindVertexArray(VAO); // To tell OpenGL that we want to use this Vertex Array Object. */
        VAO1.Bind();
        /*glDrawArrays(GL_TRIANGLES, 0, 4); // Parameters - Primitive we would like to use, starting index of vertices, no. of vertices we want to draw */
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); // Parameters - Primitive, no. of vertices we want to draw, Data Type of our vertices, starting index of our vertices
        glfwSwapBuffers(window);

        glfwPollEvents(); // Process all the poll events like window resizing etc.
    }

    /*
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram); 
    
    */

    VAO1.Delete(); // Call the Delete function from VAO class 
    VBO1.Delete(); // Call the Delete function from VBO class 
    EBO1.Delete(); // Call the Delete function from EBO class 
    shaderProgram.Delete(); // Delete the shader program
    
    glfwDestroyWindow(window); // Destroy the Window
    glfwTerminate(); // Terminate glfw
    return 0;
}
