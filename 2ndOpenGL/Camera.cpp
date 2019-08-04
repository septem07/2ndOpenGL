#include "Camera.h"

Camera::Camera(glm::vec3 camPos, glm::vec3 camFront, glm::vec3 worldUp)
{
	Position = camPos;
	Front = camFront;
	WorldUp = worldUp;
	Right = glm::normalize(glm::cross(Front, WorldUp));  
	Up = glm::normalize(glm::cross(Right, Front));
}
Camera::Camera(glm::vec3 cameraPos, float theta_Pitch, float theta_Yaw, glm::vec3 worldUp)
{
	Position = cameraPos;
	cameraForward.x = cos(theta_Pitch) * cos(theta_Yaw);
	cameraForward.y = sin(theta_Pitch);
	cameraForward.z = cos(theta_Pitch) * sin(theta_Yaw);
	cameraForward = glm::normalize(cameraForward);
	WorldUp = worldUp;
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatirxByEular() {
	return glm::lookAt(Position, cameraForward, WorldUp);
}

glm::mat4 Camera::GetViewMatirx() {
	return glm::lookAt(Position, Position + Front, WorldUp);
}
