#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>




Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	vertexShaderFile.open(vertexPath);
	fragmentShaderFile.open(fragmentPath);
	vertexShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	try
	{
		if (!vertexShaderFile.is_open() || !fragmentShaderFile.is_open())
		{
			throw std::exception("File open not sucessful");
		}
		vertexSStream << vertexShaderFile.rdbuf();
		fragmentSStream << fragmentShaderFile.rdbuf();
		
		if (!vertexSStream)
		{
			throw std::exception("Empty vertex shader file");
		}
		else if(!fragmentSStream)
		{
			throw std::exception("Empty fragment shader file");
		}
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
		
		std::cout << vertexString.c_str() << std::endl;
		std::cout << fragmentString.c_str()<< std::endl;

		const char* vShaderCode = vertexString.c_str();
		const char * fShaderCode = fragmentString.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}


void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
void Shader::use()
{
	glUseProgram(ID);
}
//~Shader();	

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
//Shader::~Shader()
//{
//}
