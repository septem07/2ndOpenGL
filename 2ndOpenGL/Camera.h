#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
class Camera
{
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 worldUp);
	Camera(glm::vec3 cameraPos, float theta_Pitch, float theta_Yaw, glm::vec3 cameraFront, glm::vec3 worldUp);
	~Camera();
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	glm::mat4 GetViewMatirx();
	glm::mat4 GetViewMatirxByEular();
	float Pitch;
	float Yaw;
	float MovementSpeed;
	float MouseSensitivity = 0.005;
	float Zoom;

	glm::vec3 cameraForward;

	void ProcessMouseMovement(float deltaX, float deltaY, GLboolean constrainPitch = true);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseScroll(float yoffset);
private:
	void UpdateCameraVectors();
};

