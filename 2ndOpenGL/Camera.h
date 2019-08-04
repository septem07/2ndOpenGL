#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
class Camera
{
public:
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 worldUp);
	Camera(glm::vec3 cameraPos, float theta_Pitch, float theta_Yaw, glm::vec3 worldUp);
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
	glm::vec3 cameraForward;
private:
	void calculateEular();
};

