#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.H"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
void processInput(GLFWwindow *window);
//Vertex array
float vertices[] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,		1.0f, 0.0f,   
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,		0.0f, 0.0f,   
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,		0.0f, 1.0f   
	/* 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,     1.0f, 1.0f,  
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,     1.0f, 0.0f,   
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,   
	 -0.9f,  0.5f, 0.0f, 0.7f, 0.5f, 0.1f	  0.0f, 1.0f */
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
	2, 3, 0   // second triangle
};


int main() {

	glfwInit();  //initialization glfw window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//Hint to glfw: utilize main (3) version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//Hint to glfw: utilize branch (.3) version of opengl 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Using core profile as the profile

	GLFWwindow* window = glfwCreateWindow(1600,1200,"The_first_OpenglWindow",NULL,NULL);
	if (window == NULL)
	{
		std::cout << "window opening is not success" << std::endl;
		glfwTerminate();
		return -1;

	}
	glfwMakeContextCurrent(window);	//Context: attribute, lightening, render, etc. information
	//initial glew (gl function in glew)
	glewExperimental = true;
	if (glewInit()	!= GLEW_OK)
	{
		std::cout << "glew ist not success" << std::endl;
	}
	glViewport(0, 0, 1600, 1200);
	//Function, enable opengl to cut off the back(clockwised) vertex or front(anticlockwised) vertex
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/
	//set VAO
	
	Shader *testShader = new Shader("vertexSourceFile.vxs", "fragmentSourceFile.fts");
	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	//5 VAOS creation
	//unsigned int VAO[5];
	//glGenVertexArrays(5, VAO);
	
	//set VBO, connect VBO to an array buffer, send the message(vertice) from cpu to VBO via method glBufferData
	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
	//5 VBOS Creation
	//unsigned int VBO[5];
	//glGenBuffers(VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//interpret the vertex data, vertex attribution (points, color, etc) related VAO;
	//0: location 0 in vertexShaderSource
	//3: number in ShaderSource
	//GL_FLOAT: data type of vertex
	//GL_FLASE: normalize the vertex if it is not in normal space
	//3 * sizeof(float): stride, how much memories will be jump to reach next vertex
	//(void*)0: offset of begin of data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3* sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	unsigned int TEXBO; //texture buffer object in context
	glGenTextures(1, &TEXBO);
	glBindTexture(GL_TEXTURE_2D, TEXBO);
	// setting filer for texuture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//reverse 180 degree before texture loading. Image's y axis is reverse from opengl
	stbi_set_flip_vertically_on_load(true);
	// load texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	//Using shader program	
	
	
	//delete the shader object (because shader source(form) have been pass into program thus the shader object is useless anymore)
	/*glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);*/

	
	
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);	//callback the window* size after deformation of window by external operation
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window)) //do drawing during window is opening
	{
		//input command from keyboard, if user press corresponding key then the window will be closed
		processInput(window);
		//start to render
			//first to make sure that the screen and buffer have been cleaned 
		glClearColor(0.3f, 0.3f, 1.0f, 1.0f); //clean the screen then fill the window by signed colour
		glClear(GL_COLOR_BUFFER_BIT); //clean the buffer
		glBindTexture(GL_TEXTURE_2D, TEXBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/*glUseProgram(shaderProgram);		
		float timeValue = glfwGetTime() * 20;
		float greenValue = (sin(timeValue) / 10.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColour");*/	
		/*glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
		testShader->use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//call the user's event and exchange buffer from front and back
		glfwPollEvents();		
		glfwSwapBuffers(window);
	}


	//release resource after window close
	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}