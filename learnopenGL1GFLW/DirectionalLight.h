#pragma once

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

class DirectionalLight {
public:
	DirectionalLight(glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : 
		direction(dir),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular)
	{}

	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;


private:
};