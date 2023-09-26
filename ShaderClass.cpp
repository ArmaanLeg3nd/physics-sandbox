#include "ShaderClass.h"

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a new vertex shader
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // Use the source code for vertex shader
	glCompileShader(vertexShader); // Compile the shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create a new fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Use the source code for fragment shader
	glCompileShader(fragmentShader); // Compile the shader

	ID = glCreateProgram(); // To actually use these shaders, we have to wrap it up in a shader program

	glAttachShader(ID, vertexShader); // Attach the vertex shader to the shader program
	glAttachShader(ID, fragmentShader); // Attach the fragment shader to the shader program

	glLinkProgram(ID); // Wrap off the shader program

	glDeleteShader(vertexShader); // Tidying up. Shader already in the program, no need to keep the original shader anymore
	glDeleteShader(fragmentShader); // Tidying up. Shader already in the program, no need to keep the original shader anymore
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}