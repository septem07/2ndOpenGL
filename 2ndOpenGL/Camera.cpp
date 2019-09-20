#include "Camera.h"


Camera::Camera(glm::vec3 cameraPos, float theta_Pitch, float theta_Yaw, glm::vec3 cameraFront,glm::vec3 worldUp)
{
	Position = cameraPos;
	Pitch = theta_Pitch;
	Yaw = theta_Yaw;
	Front = cameraFront;
	WorldUp = worldUp;
	cameraForward.x = cos(theta_Pitch) * cos(theta_Yaw);
	cameraForward.y = sin(theta_Pitch);
	cameraForward.z = cos(theta_Pitch) * sin(theta_Yaw);
	cameraForward = glm::normalize(cameraForward);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	WorldUp = glm::normalize(glm::cross(Right, Front));
	UpdateCameraVectors();
}

void Camera::ProcessMouseMovement(float offsetX, float offsetY, GLboolean constrainPitch) {

	
	offsetX *= MouseSensitivity;
	offsetY *= MouseSensitivity;
	Yaw += offsetX;
	Pitch += offsetY;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}	
	UpdateCameraVectors();
}
void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}
void Camera::UpdateCameraVectors() {

	cameraForward.x = cos(Pitch) * cos(Yaw);
	cameraForward.y = sin(Pitch);
	cameraForward.z = cos(Pitch) * sin(Yaw);
	Front = glm::normalize(cameraForward);
	Right = glm::normalize(glm::cross(cameraForward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));
}
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	MovementSpeed = 2.5f;
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == UP)
		Position += WorldUp * velocity;
	if (direction == DOWN)
		Position -= WorldUp * velocity;
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
