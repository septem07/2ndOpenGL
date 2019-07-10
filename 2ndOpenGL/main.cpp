#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();  //initialization glfw window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//Hint to glfw: utilize main (3) version of opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//Hint to glfw: utilize branch (.3) version of opengl 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//Using core profile as the profile

	GLFWwindow* window = glfwCreateWindow(1024,768,"The_first_OpenglWindow",NULL,NULL);
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
	glViewport(0, 0, 1024, 768);
	
	void framebuffer_size_callback(GLFWwindow* window, int width, int height); //callback the window size after deformation of window by external 

}