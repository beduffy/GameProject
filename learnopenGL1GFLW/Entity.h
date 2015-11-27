#pragma once

#include <glew.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Entity {
public: // Entity Object Variables
	glm::vec3 pos{ 0.0f, 0.0f, 0.0f };
	glm::vec3 vel{ 0.0f, 0.0f, 0.0f };
public:
	Entity() {
		updateBaseVectors();
		updateBaseVectors();
	}
	glm::vec3 worldUp{ 0.0f, 1.0f, 0.0f };
	
	//BASE OF TANK	
	glm::vec3 baseUp{ 0.0f, 1.0f, 0.0f };
	glm::vec3 baseFront;
	glm::vec3 baseRight;
	
	GLfloat baseYaw = 0.0f;
	GLfloat basePitch = 0.0f;

	//TANK TURRET HEAD
	glm::vec3 headFront;
	glm::vec3 headUp{ 0.0f, 1.0f, 0.0f };
	glm::vec3 headRight;
	GLfloat headYaw = 0.0f;
	GLfloat headPitch = 0.0f;

	void updateBaseVectors() {
		//BASE OF TANK vectors
		glm::vec3 baseFront;
		baseFront.x = cos(glm::radians(this->baseYaw)) * cos(glm::radians(this->basePitch));
		baseFront.y = sin(glm::radians(this->basePitch));
		baseFront.z = sin(glm::radians(this->baseYaw)) * cos(glm::radians(this->basePitch));
		this->baseFront = glm::normalize(baseFront);
		// Also re-calculate the Right and Up vector
		this->baseRight = glm::normalize(glm::cross(this->baseFront, this->worldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->baseUp = glm::normalize(glm::cross(this->baseRight, this->baseFront));
	}

	void updateHeadVectors() {
		if (this->headPitch > 89.0f)
			this->headPitch = 89.0f;
		if (this->headPitch < -20.0f)
			this->headPitch = -20.0f;

		//cout << this->headPitch << endl;
		//TANK TURRET HEAD vectors

		//headYaw is relative to baseYaw which is absolute yaw. However the camera doesn't know about relative yaw and treats all yaws like absolute.
		// Therefore find absolute turret yaw by summing both yaws?
		glm::vec3 hFront;
		hFront.x = cos(glm::radians(this->headYaw + this->baseYaw)) * cos(glm::radians(this->headPitch + this->basePitch));
		hFront.y = sin(glm::radians(this->headPitch + this->basePitch));
		hFront.z = sin(glm::radians(this->headYaw + this->baseYaw)) * cos(glm::radians(this->headPitch + this->basePitch));
		this->headFront = glm::normalize(hFront);
		// Also re-calculate the Right and Up vector
		this->headRight = glm::normalize(glm::cross(this->headFront, this->worldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->headUp = glm::normalize(glm::cross(this->headRight, this->headFront));
	}
};