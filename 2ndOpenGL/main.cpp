#define GLEW_STATIC
#include <iostream>
#include <iomanip>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.H"
#include <stdlib.h>
#include <time.h> 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"

//Vertex array
//float vertices[] = {
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,		1.0f, 0.0f,   
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,		0.0f, 0.0f,   
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,		0.0f, 1.0f   
//	/* 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,     1.0f, 1.0f,  
//	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,     1.0f, 0.0f,   
//	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,     0.0f, 0.0f,   
//	 -0.9f,  0.5f, 0.0f, 0.7f, 0.5f, 0.1f	  0.0f, 1.0f */
//};
#pragma region "model paramter"
float vertices[] ={
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
glm::vec3 cubePositions[] = {
  glm::vec3(0.1f,  0.2f,  0.5f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion "model paramter"
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
	2, 3, 0   // second triangle
};
float lastX = 800;
float lastY = 600;
bool firstMouseLocation = true;
float sensitivity = 0.05f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

//create a new camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
float theta_pitch = glm::radians(60.0);
float theta_yaw = glm::radians(0.0);

Camera *secondCamera = new Camera(cameraPos, theta_pitch, theta_yaw, cameraFront, worldUp);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos); 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;


int main() {
	
	glfwInit();  //initialization glfw window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//Hint to glfw: utilize main (3) version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//Hint to glfw: utilize branch (.3) version of opengl 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Using core profile as the profile
	//
	
	
	GLFWwindow* window = glfwCreateWindow(1600,1200,"The_first_OpenglWindow",NULL,NULL);
	if (window == NULL)
	{
		std::cout << "window opening is not success" << std::endl;
		glfwTerminate();
		return -1;

	}
	//setting glfw properties
	glfwMakeContextCurrent(window);	//Context: attribute, lightening, render, etc. information
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//initial glew (gl function in glew)
	glewExperimental = true;
	if (glewInit()	!= GLEW_OK)
	{
		std::cout << "glew ist not success" << std::endl;
	}
	glViewport(200, 0, 1200, 1200);
	//Function, enable opengl to cut off the back(clockwised) vertex or front(anticlockwised) vertex
	/*glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);*/
	//set VAO
	
	Shader *objectShader = new Shader("Object.vert", "Object.frag");
	Shader *lightShader = new Shader("Light.vert", "Light.frag");
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

#pragma region "texture"

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	///*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);*/
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//
	//unsigned int TEXBO_A; //texture buffer object A in context
	//glGenTextures(1, &TEXBO_A);
	//glActiveTexture(GL_TEXTURE0); //active the channel of texture 1, keep texture alive in context
	//glBindTexture(GL_TEXTURE_2D, TEXBO_A);

	//// setting filer for texuture
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	////reverse 180 degree before texture loading. Image's y axis is reverse from opengl
	//stbi_set_flip_vertically_on_load(true);
	//// load texture
	//int width, height, nrChannels;
	//unsigned char *data1 = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	//if (data1)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}

	////second texture buffer object B in context
	//unsigned int TEXBO_B;
	//glGenTextures(1, &TEXBO_B);
	//glActiveTexture(GL_TEXTURE1);  //active the channel of texture 1, keep texture alive in context
	//glBindTexture(GL_TEXTURE_2D, TEXBO_B);
	//// setting filer for texuture
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	////reverse 180 degree before texture loading. Image's y axis is reverse from opengl
	//stbi_set_flip_vertically_on_load(true);
	//// load texture
	//
	//unsigned char *data2 = stbi_load("huajialpha.png", &width, &height, &nrChannels, 0);
	//if (data2)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}


	//stbi_image_free(data1);
	//stbi_image_free(data2);
	//
	////Using shader program	


	////depth buffer enable
	//glEnable(GL_DEPTH_TEST);
	
	//delta time by frame different
#pragma endregion "texture"
	


	void framebuffer_size_callback(GLFWwindow* window, int width, int height);	//callback the window* size after deformation of window by external operation
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window)) //do drawing during window is opening
	{
		//input command from keyboard, if user press corresponding key then the window will be closed
		processInput(window);
		//start to render
			//first to make sure that the screen and buffer have been cleaned 
		glClearColor(0.3f, 0.3f, 1.0f, 1.0f); //clean the screen then fill the window by signed colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clean the buffer
	

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TEXBO_A);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TEXBO_B);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		testShader->use();*/
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glm::mat4 view_Matrix = glm::mat4(1.0f);
		glm::mat4 proj_Matrix = glm::mat4(1.0f);
	
		/*model_Matrix = glm::rotate(model_Matrix, (float)time, glm::vec3(1.0f, 0.5f, 0.3f));
		testShader->setMat4("model", model_Matrix);*/
		/*
		float cameraSpeed = 0.25f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			secondCamera->Position += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			secondCamera->Position -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			secondCamera->Position -= glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			secondCamera->Position += glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;*/
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		objectShader->use();
		objectShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		objectShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		objectShader->setVec3("lightPos", lightPos);

		
		proj_Matrix = glm::perspective(glm::radians(secondCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view_Matrix = secondCamera->GetViewMatirx();
		objectShader->setMat4("projection", proj_Matrix);			
		objectShader->setMat4("view", view_Matrix);
		for (unsigned int i = 0; i < 10; i++)
		{
			std::stringstream ss;
			std::string index;
			ss << i;
			index = ss.str();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			
			if (i % 3 == 0) 
			{				
				float angle = 20.0f * (i + 1);
				model = glm::rotate(model, (float)sin(currentFrame)*(i + 1), glm::vec3(1.0f, 0.5f, 0.3f));
				objectShader->setMat4("model", model);
			}
			else if(i % 3 == 1)
			{							
				float angle = 20.0f * (i + 1);
				model = glm::rotate(model, (float)(currentFrame), glm::vec3(1.0f, 0.5f, 0.3f));
				objectShader->setMat4("model", model);
			}
			else
			{								
				model = glm::rotate(model, (float)cos(currentFrame)*0, glm::vec3(1.0f, 0.5f, 0.3f));
				objectShader->setMat4("model", model);
			}
			//testShader->setVec3(("cPosition[" + index + "]").c_str(), cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		lightShader->use();
		lightShader->setMat4("projection", proj_Matrix);
		lightShader->setMat4("view", view_Matrix);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f)); 
		lightShader->setMat4("model", lightModel);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//glDrawArraysInstanced(GL_TRIANGLES,0,36,10);
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		secondCamera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		secondCamera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		secondCamera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		secondCamera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		secondCamera->ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		secondCamera->ProcessKeyboard(DOWN, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouseLocation == true) {
		lastX = xpos;
		lastY = ypos;
		firstMouseLocation = false;
	}
	float offsetX, offsetY;
	offsetX = xpos - lastX;
	offsetY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	GLboolean constrainPitch = false;
	secondCamera->ProcessMouseMovement(offsetX, offsetY, constrainPitch);
	//std::cout << std::fixed << deltaX << std::endl;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	secondCamera->ProcessMouseScroll(yoffset);
}