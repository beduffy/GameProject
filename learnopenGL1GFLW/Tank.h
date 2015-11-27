#include "Entity.h"

class Tank : public Entity {
public: // Tank variables
	glm::mat4 model;
public: // Tank functions
	void update(GLfloat dt);
	void draw(Shader shader, glm::mat4 model);
	void processInput(GLfloat dt, GLboolean* keys) {
		// Camera controls
		GLfloat tankSpeed = 0.3f;
		GLfloat angleSpeed = 1.0f;

		//TODO change GLFW_KEY_W TO ENUM FORWARDS LIKE IN CAMERA

		/*if (keys[GLFW_KEY_W]) {
			tank.pos += tank.baseFront * tankSpeed;
		}

		if (keys[GLFW_KEY_S]) {
			tank.pos -= tank.baseFront * tankSpeed;
		}

		if (keys[GLFW_KEY_A]) {
			tank.baseYaw -= angleSpeed;
			//tank.headYaw -= angleSpeed;
		}

		if (keys[GLFW_KEY_D]) {
			tank.baseYaw += angleSpeed;
			//tank.headYaw += angleSpeed;
		}
		if (keys[GLFW_KEY_SPACE]) {
			tank.basePitch += angleSpeed * 0.3f;
		}
		if (keys[GLFW_KEY_LEFT_CONTROL]) {
			tank.basePitch -= angleSpeed * 0.3f;
		}

		if (tank.basePitch > 89.0f) tank.basePitch = 89.0f;
		else if (tank.basePitch < -89.0f) tank.basePitch = -89.0f;*/

		updateBaseVectors();
		updateHeadVectors();
	}

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

private:

};