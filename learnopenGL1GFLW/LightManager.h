#pragma once

#include <vector>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shader.h"

#include "SpotLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class LightManager {
public:
	std::vector<SpotLight> spotLights;
	std::vector<DirectionalLight> directionalLights;
	std::vector<PointLight> pointLights;
	// other functions? add pointLight, spotLight? etc?
public:
	LightManager() {}
	void draw() {}
	void update() {}
	void sendAllLightsToShader(Shader shader) {
		//Send all directional lighta
		for (int i = 0; i < directionalLights.size(); i++) {
			std::string baseString = "directionalLights[" + std::to_string(i) + "].";
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "direction").c_str()), directionalLights[i].direction.x, directionalLights[i].direction.y, directionalLights[i].direction.z);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "ambient").c_str()), directionalLights[i].ambient.r, directionalLights[i].ambient.g, directionalLights[i].ambient.b);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "diffuse").c_str()), directionalLights[i].diffuse.r, directionalLights[i].diffuse.g, directionalLights[i].diffuse.b);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "specular").c_str()), directionalLights[i].specular.r, directionalLights[i].specular.g, directionalLights[i].specular.b);
		}

		//Send all point lights
		for (int i = 0; i < pointLights.size(); i++) {
			std::string baseString = "pointLights[" + std::to_string(i) + "].";
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "position").c_str()), pointLights[i].position.x, pointLights[i].position.y, pointLights[i].position.z);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "ambient").c_str()), pointLights[i].ambient.r, pointLights[i].ambient.g, pointLights[i].ambient.b);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "diffuse").c_str()), pointLights[i].diffuse.r, pointLights[i].diffuse.g, pointLights[i].diffuse.b);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "specular").c_str()), pointLights[i].specular.r, pointLights[i].specular.g, pointLights[i].specular.b);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "constant").c_str()), pointLights[i].constant);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "linear").c_str()), pointLights[i].linear);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "quadratic").c_str()), pointLights[i].quadratic);
		}

		//Send all spotlights
		for (int i = 0; i < spotLights.size(); i++) {
			std::string baseString = "spotLights[" + std::to_string(i) + "].";
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "position").c_str()), spotLights[i].position.x, spotLights[i].position.y, spotLights[i].position.z);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "direction").c_str()), spotLights[i].direction.x, spotLights[i].direction.y, spotLights[i].direction.z);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "ambient").c_str()), spotLights[i].ambient.r, spotLights[i].ambient.g, spotLights[i].ambient.b);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "diffuse").c_str()), spotLights[i].diffuse.r, spotLights[i].diffuse.g, spotLights[i].diffuse.b);
			glUniform3f(glGetUniformLocation(shader.ID, (baseString + "specular").c_str()), spotLights[i].specular.r, spotLights[i].specular.g, spotLights[i].specular.b);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "constant").c_str()), spotLights[i].constant);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "linear").c_str()), spotLights[i].linear);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "quadratic").c_str()), spotLights[i].quadratic);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "cutOff").c_str()), spotLights[i].cutOff);
			glUniform1f(glGetUniformLocation(shader.ID, (baseString + "outerCutOff").c_str()), spotLights[i].outerCutOff);
		}
	}
	void addDirectionalLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) {
		directionalLights.push_back(DirectionalLight(dir, amb, diff, spec));  //4 parameters
	}
	void addPointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, GLfloat linear, GLfloat quadratic) {
		pointLights.push_back(PointLight(pos, amb, diff, spec, linear, quadratic)); //6 parameters
	}
	void addSpotLight(glm::vec3 dir, glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		GLfloat linear, GLfloat quadratic, GLfloat cutOff, GLfloat outerCutOff) { //9 parameters
		spotLights.push_back(SpotLight(dir, pos, ambient, diffuse, specular, linear, quadratic, cutOff, outerCutOff));
	}
private:

};