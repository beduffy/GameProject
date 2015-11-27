#pragma once

#include <glew.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"

class Bullet : public Entity {
public:

	//TODO MAKE SURE TO NORMALISE EVERYTHING. front is normalised already.
	Bullet(glm::vec3 pos, glm::vec3 vel) {
		this->pos = pos;
		this->vel = vel;		
	}

	bool update() {
		pos += vel * 0.2f;

		if (this->pos.length() > 50.0f) return false;
		return true;
	}

	glm::vec3 pos;

	void draw() {
		/*local = glm::mat4();
		local = glm::translate(local, glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(local));
		glDrawArrays(GL_TRIANGLES, 0, 36);*/
	}
private:
	glm::vec3 vel;
	GLfloat speed = 0.1f;
};