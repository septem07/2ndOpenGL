
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


#pragma region "model paramter"
float vertices[] ={
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
unsigned int loadTexture(char const* path);
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;


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
	glViewport(200, 0, 1600, 1200);

	
	Shader *objectShader = new Shader("Object.vert", "Object.frag");
	Shader *lightShader = new Shader("Light.vert", "Light.frag");
	unsigned int VBO, objectVAO,TEXBO_A,TEXBO_B;
	glGenVertexArrays(1, &objectVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(objectVAO);
	//glVertexAttribPointer(int layout number, int length of this attribute, GL_FLOAT, GL_FALSE, total number of an attribute node * sizeof(float), distance between same attribute (first position))(void*)0);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture attibute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	
	
	
	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	//reverse
	stbi_set_flip_vertically_on_load(true);
	//load texture
	unsigned int diffuseMap = loadTexture("container2.png");
	unsigned int specularMap = loadTexture("container2_specular.png");

	glEnable(GL_DEPTH_TEST);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		//callback the window* size after deformation of window by external operation
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	while (!glfwWindowShouldClose(window)) //do drawing during window is opening
	{
		//input command from keyboard, if user press corresponding key then the window will be closed
		processInput(window);
		//start to render
			//first to make sure that the screen and buffer have been cleaned 
		glClearColor(0.3f, 0.3f, 1.0f, 1.0f); //clean the screen then fill the window by signed colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clean the buffer
	

		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
	
	

		glm::vec3 lightPos =glm::vec3(0.0f,0.0f,-1.5f);
		lightPos.x = sin(glfwGetTime())*2.0f;
		lightPos.y = 0.0f;
		lightPos.z = cos(glfwGetTime())*2.0f -1.5f;

		objectShader->use();
		objectShader->setVec3("newLight.position", lightPos);

		objectShader->setVec3("cameraPos", secondCamera->Position);

		glm::vec3 lightColor = glm::vec3(1.0f,1.0f,1.0f);
	/*	lightColor.x = abs(sin(glfwGetTime() * 2.0f));
		lightColor.y = abs(sin(glfwGetTime() * 0.7f));
		lightColor.z = abs(sin(glfwGetTime() * 1.3f));		*/
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		
		objectShader->setVec3("newLight.ambient", ambientColor);
		objectShader->setVec3("newLight.diffuse", diffuseColor);
		objectShader->setVec3("newLight.specular", 1.0f, 1.0f, 1.0f);
	
		
		//objectShader->setVec3("newMaterial.ambient", 1.0f, 0.5f, 0.31f);
		//objectShader->setVec3("newMaterial.diffuse", 1.0f, 0.5f, 0.31f);
		objectShader->setInt("newMaterial.diffuse", 0);
		objectShader->setInt("newMaterial.specular", 1);
		/*objectShader->setVec3("newMaterial.specular", 0.5f, 0.5f, 0.5f);*/
		objectShader->setFloat("newMaterial.shiness", 32.0f);
		
		//Texture
		glActiveTexture(GL_TEXTURE0); //active the channel of texture 1, keep texture alive in context
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1); //active the channel of texture 2, keep texture alive in context
		glBindTexture(GL_TEXTURE_2D, specularMap);
		
		glm::mat4 proj_Matrix = glm::perspective(glm::radians(secondCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view_Matrix= secondCamera->GetViewMatirx();
		objectShader->setMat4("projection", proj_Matrix);			
		objectShader->setMat4("view", view_Matrix);
		float transAlpha = currentFrame;
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
					
				model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.5f, 0.3f));
				objectShader->setMat4("model", model);
			}
			else if(i % 3 == 1)
			{							
			
				model = glm::rotate(model, 20.0f, glm::vec3(1.0f, 0.5f, 0.3f));
				objectShader->setMat4("model", model);
			}
			else
			{								
				model = glm::rotate(model, -45.0f, glm::vec3(1.0f, 0.5f, 0.3f));
				objectShader->setMat4("model", model);
			}
			glBindVertexArray(objectVAO);
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

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}